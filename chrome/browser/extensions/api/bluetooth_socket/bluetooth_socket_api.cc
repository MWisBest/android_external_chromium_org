// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/extensions/api/bluetooth_socket/bluetooth_socket_api.h"

#include "chrome/browser/extensions/api/bluetooth_socket/bluetooth_api_socket.h"
#include "chrome/browser/extensions/api/bluetooth_socket/bluetooth_socket_event_dispatcher.h"
#include "chrome/common/extensions/api/bluetooth/bluetooth_manifest_data.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_thread.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_adapter_factory.h"
#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_socket.h"
#include "extensions/common/permissions/permissions_data.h"
#include "net/base/io_buffer.h"

using content::BrowserThread;
using extensions::BluetoothApiSocket;
using extensions::api::bluetooth_socket::ListenOptions;
using extensions::api::bluetooth_socket::SocketInfo;
using extensions::api::bluetooth_socket::SocketProperties;

namespace {

const char kDeviceNotFoundError[] = "Device not found";
const char kInvalidUuidError[] = "Invalid UUID";
const char kPermissionDeniedError[] = "Permission denied";
const char kSocketNotFoundError[] = "Socket not found";

linked_ptr<SocketInfo> CreateSocketInfo(int socket_id,
                                        BluetoothApiSocket* socket) {
  DCHECK(BrowserThread::CurrentlyOn(BluetoothApiSocket::kThreadId));
  linked_ptr<SocketInfo> socket_info(new SocketInfo());
  // This represents what we know about the socket, and does not call through
  // to the system.
  socket_info->socket_id = socket_id;
  if (!socket->name().empty()) {
    socket_info->name.reset(new std::string(socket->name()));
  }
  socket_info->persistent = socket->persistent();
  if (socket->buffer_size() > 0) {
    socket_info->buffer_size.reset(new int(socket->buffer_size()));
  }
  socket_info->paused = socket->paused();
  socket_info->connected = socket->IsConnected();

  if (socket->IsConnected())
    socket_info->address.reset(new std::string(socket->device_address()));
  socket_info->uuid.reset(new std::string(socket->uuid().canonical_value()));

  return socket_info;
}

void SetSocketProperties(BluetoothApiSocket* socket,
                         SocketProperties* properties) {
  if (properties->name.get()) {
    socket->set_name(*properties->name.get());
  }
  if (properties->persistent.get()) {
    socket->set_persistent(*properties->persistent.get());
  }
  if (properties->buffer_size.get()) {
    // buffer size is validated when issuing the actual Recv operation
    // on the socket.
    socket->set_buffer_size(*properties->buffer_size.get());
  }
}

extensions::api::BluetoothSocketEventDispatcher* GetSocketEventDispatcher(
    content::BrowserContext* browser_context) {
  extensions::api::BluetoothSocketEventDispatcher* socket_event_dispatcher =
      extensions::api::BluetoothSocketEventDispatcher::Get(browser_context);
  DCHECK(socket_event_dispatcher)
      << "There is no socket event dispatcher. "
         "If this assertion is failing during a test, then it is likely that "
         "TestExtensionSystem is failing to provide an instance of "
         "BluetoothSocketEventDispatcher.";
  return socket_event_dispatcher;
}

}  // namespace

namespace extensions {
namespace api {

BluetoothSocketAsyncApiFunction::BluetoothSocketAsyncApiFunction() {}

BluetoothSocketAsyncApiFunction::~BluetoothSocketAsyncApiFunction() {}

bool BluetoothSocketAsyncApiFunction::RunAsync() {
  if (!PrePrepare() || !Prepare()) {
    return false;
  }
  AsyncWorkStart();
  return true;
}

bool BluetoothSocketAsyncApiFunction::PrePrepare() {
  if (!BluetoothManifestData::CheckSocketPermitted(GetExtension())) {
    error_ = kPermissionDeniedError;
    return false;
  }

  manager_ = ApiResourceManager<BluetoothApiSocket>::Get(browser_context());
  DCHECK(manager_)
      << "There is no socket manager. "
         "If this assertion is failing during a test, then it is likely that "
         "TestExtensionSystem is failing to provide an instance of "
         "ApiResourceManager<BluetoothApiSocket>.";
  return manager_ != NULL;
}

bool BluetoothSocketAsyncApiFunction::Respond() { return error_.empty(); }

void BluetoothSocketAsyncApiFunction::AsyncWorkCompleted() {
  SendResponse(Respond());
}

void BluetoothSocketAsyncApiFunction::Work() {}

void BluetoothSocketAsyncApiFunction::AsyncWorkStart() {
  Work();
  AsyncWorkCompleted();
}

int BluetoothSocketAsyncApiFunction::AddSocket(BluetoothApiSocket* socket) {
  return manager_->Add(socket);
}

content::BrowserThread::ID
BluetoothSocketAsyncApiFunction::work_thread_id() const {
  return BluetoothApiSocket::kThreadId;
}

BluetoothApiSocket* BluetoothSocketAsyncApiFunction::GetSocket(
    int api_resource_id) {
  return manager_->Get(extension_id(), api_resource_id);
}

void BluetoothSocketAsyncApiFunction::RemoveSocket(int api_resource_id) {
  manager_->Remove(extension_id(), api_resource_id);
}

base::hash_set<int>* BluetoothSocketAsyncApiFunction::GetSocketIds() {
  return manager_->GetResourceIds(extension_id());
}

BluetoothSocketCreateFunction::BluetoothSocketCreateFunction() {}

BluetoothSocketCreateFunction::~BluetoothSocketCreateFunction() {}

bool BluetoothSocketCreateFunction::Prepare() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  params_ = bluetooth_socket::Create::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketCreateFunction::Work() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));

  BluetoothApiSocket* socket = new BluetoothApiSocket(extension_id());

  bluetooth_socket::SocketProperties* properties =
      params_.get()->properties.get();
  if (properties) {
    SetSocketProperties(socket, properties);
  }

  bluetooth_socket::CreateInfo create_info;
  create_info.socket_id = AddSocket(socket);
  results_ = bluetooth_socket::Create::Results::Create(create_info);
  AsyncWorkCompleted();
}

BluetoothSocketUpdateFunction::BluetoothSocketUpdateFunction() {}

BluetoothSocketUpdateFunction::~BluetoothSocketUpdateFunction() {}

bool BluetoothSocketUpdateFunction::Prepare() {
  params_ = bluetooth_socket::Update::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketUpdateFunction::Work() {
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    return;
  }

  SetSocketProperties(socket, &params_.get()->properties);
  results_ = bluetooth_socket::Update::Results::Create();
}

BluetoothSocketSetPausedFunction::BluetoothSocketSetPausedFunction()
    : socket_event_dispatcher_(NULL) {}

BluetoothSocketSetPausedFunction::~BluetoothSocketSetPausedFunction() {}

bool BluetoothSocketSetPausedFunction::Prepare() {
  params_ = bluetooth_socket::SetPaused::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());

  socket_event_dispatcher_ = GetSocketEventDispatcher(browser_context());
  return socket_event_dispatcher_ != NULL;
}

void BluetoothSocketSetPausedFunction::Work() {
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    return;
  }

  if (socket->paused() != params_->paused) {
    socket->set_paused(params_->paused);
    if (!params_->paused) {
      socket_event_dispatcher_->OnSocketResume(extension_id(),
                                               params_->socket_id);
    }
  }

  results_ = bluetooth_socket::SetPaused::Results::Create();
}

BluetoothSocketListenFunction::BluetoothSocketListenFunction() {}

BluetoothSocketListenFunction::~BluetoothSocketListenFunction() {}

bool BluetoothSocketListenFunction::Prepare() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  if (!CreateParams())
    return false;
  socket_event_dispatcher_ = GetSocketEventDispatcher(browser_context());
  return socket_event_dispatcher_ != NULL;
}

void BluetoothSocketListenFunction::AsyncWorkStart() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  device::BluetoothAdapterFactory::GetAdapter(
      base::Bind(&BluetoothSocketListenFunction::OnGetAdapter, this));
}

void BluetoothSocketListenFunction::OnGetAdapter(
    scoped_refptr<device::BluetoothAdapter> adapter) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  BluetoothApiSocket* socket = GetSocket(socket_id());
  if (!socket) {
    error_ = kSocketNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  device::BluetoothUUID bluetooth_uuid(uuid());
  if (!bluetooth_uuid.IsValid()) {
    error_ = kInvalidUuidError;
    AsyncWorkCompleted();
    return;
  }

  BluetoothPermissionRequest param(uuid());
  if (!BluetoothManifestData::CheckRequest(GetExtension(), param)) {
    error_ = kPermissionDeniedError;
    AsyncWorkCompleted();
    return;
  }

  CreateService(
      adapter,
      bluetooth_uuid,
      base::Bind(&BluetoothSocketListenFunction::OnCreateService, this),
      base::Bind(&BluetoothSocketListenFunction::OnCreateServiceError, this));
}


void BluetoothSocketListenFunction::OnCreateService(
    scoped_refptr<device::BluetoothSocket> socket) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));

  // Fetch the socket again since this is not a reference-counted object, and
  // it may have gone away in the meantime (we check earlier to avoid making
  // a connection in the case of an obvious programming error).
  BluetoothApiSocket* api_socket = GetSocket(socket_id());
  if (!api_socket) {
    error_ = kSocketNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  api_socket->AdoptListeningSocket(socket,
                                   device::BluetoothUUID(uuid()));
  socket_event_dispatcher_->OnSocketListen(extension_id(), socket_id());

  CreateResults();
  AsyncWorkCompleted();
}

void BluetoothSocketListenFunction::OnCreateServiceError(
    const std::string& message) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  error_ = message;
  AsyncWorkCompleted();
}

BluetoothSocketListenUsingRfcommFunction::
    BluetoothSocketListenUsingRfcommFunction() {}

BluetoothSocketListenUsingRfcommFunction::
    ~BluetoothSocketListenUsingRfcommFunction() {}

int BluetoothSocketListenUsingRfcommFunction::socket_id() const {
  return params_->socket_id;
}

const std::string& BluetoothSocketListenUsingRfcommFunction::uuid() const {
  return params_->uuid;
}

bool BluetoothSocketListenUsingRfcommFunction::CreateParams() {
  params_ = bluetooth_socket::ListenUsingRfcomm::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketListenUsingRfcommFunction::CreateService(
    scoped_refptr<device::BluetoothAdapter> adapter,
    const device::BluetoothUUID& uuid,
    const device::BluetoothAdapter::CreateServiceCallback& callback,
    const device::BluetoothAdapter::CreateServiceErrorCallback&
        error_callback) {
  int channel = device::BluetoothAdapter::kChannelAuto;

  ListenOptions* options = params_->options.get();
  if (options) {
    if (options->channel.get())
      channel = *(options->channel);
  }

  adapter->CreateRfcommService(uuid, channel, callback, error_callback);
}

void BluetoothSocketListenUsingRfcommFunction::CreateResults() {
  results_ = bluetooth_socket::ListenUsingRfcomm::Results::Create();
}

BluetoothSocketListenUsingL2capFunction::
    BluetoothSocketListenUsingL2capFunction() {}

BluetoothSocketListenUsingL2capFunction::
    ~BluetoothSocketListenUsingL2capFunction() {}

int BluetoothSocketListenUsingL2capFunction::socket_id() const {
  return params_->socket_id;
}

const std::string& BluetoothSocketListenUsingL2capFunction::uuid() const {
  return params_->uuid;
}

bool BluetoothSocketListenUsingL2capFunction::CreateParams() {
  params_ = bluetooth_socket::ListenUsingL2cap::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketListenUsingL2capFunction::CreateService(
    scoped_refptr<device::BluetoothAdapter> adapter,
    const device::BluetoothUUID& uuid,
    const device::BluetoothAdapter::CreateServiceCallback& callback,
    const device::BluetoothAdapter::CreateServiceErrorCallback&
        error_callback) {
  int psm = device::BluetoothAdapter::kPsmAuto;

  ListenOptions* options = params_->options.get();
  if (options) {
    if (options->psm.get())
      psm = *(options->psm);
  }

  adapter->CreateL2capService(uuid, psm, callback, error_callback);
}

void BluetoothSocketListenUsingL2capFunction::CreateResults() {
  results_ = bluetooth_socket::ListenUsingL2cap::Results::Create();
}

BluetoothSocketConnectFunction::BluetoothSocketConnectFunction() {}

BluetoothSocketConnectFunction::~BluetoothSocketConnectFunction() {}

bool BluetoothSocketConnectFunction::Prepare() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  params_ = bluetooth_socket::Connect::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());

  socket_event_dispatcher_ = GetSocketEventDispatcher(browser_context());
  return socket_event_dispatcher_ != NULL;
}

void BluetoothSocketConnectFunction::AsyncWorkStart() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  device::BluetoothAdapterFactory::GetAdapter(
      base::Bind(&BluetoothSocketConnectFunction::OnGetAdapter, this));
}

void BluetoothSocketConnectFunction::OnGetAdapter(
    scoped_refptr<device::BluetoothAdapter> adapter) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  device::BluetoothDevice* device = adapter->GetDevice(params_->address);
  if (!device) {
    error_ = kDeviceNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  device::BluetoothUUID uuid(params_->uuid);
  if (!uuid.IsValid()) {
    error_ = kInvalidUuidError;
    AsyncWorkCompleted();
    return;
  }

  BluetoothPermissionRequest param(params_->uuid);
  if (!BluetoothManifestData::CheckRequest(GetExtension(), param)) {
    error_ = kPermissionDeniedError;
    AsyncWorkCompleted();
    return;
  }

  device->ConnectToService(
      uuid,
      base::Bind(&BluetoothSocketConnectFunction::OnConnect, this),
      base::Bind(&BluetoothSocketConnectFunction::OnConnectError, this));
}

void BluetoothSocketConnectFunction::OnConnect(
    scoped_refptr<device::BluetoothSocket> socket) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));

  // Fetch the socket again since this is not a reference-counted object, and
  // it may have gone away in the meantime (we check earlier to avoid making
  // a connection in the case of an obvious programming error).
  BluetoothApiSocket* api_socket = GetSocket(params_->socket_id);
  if (!api_socket) {
    error_ = kSocketNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  api_socket->AdoptConnectedSocket(socket,
                                   params_->address,
                                   device::BluetoothUUID(params_->uuid));
  socket_event_dispatcher_->OnSocketConnect(extension_id(),
                                            params_->socket_id);

  results_ = bluetooth_socket::Connect::Results::Create();
  AsyncWorkCompleted();
}

void BluetoothSocketConnectFunction::OnConnectError(
    const std::string& message) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  error_ = message;
  AsyncWorkCompleted();
}

BluetoothSocketDisconnectFunction::BluetoothSocketDisconnectFunction() {}

BluetoothSocketDisconnectFunction::~BluetoothSocketDisconnectFunction() {}

bool BluetoothSocketDisconnectFunction::Prepare() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  params_ = bluetooth_socket::Disconnect::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketDisconnectFunction::AsyncWorkStart() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    AsyncWorkCompleted();
    return;
  }

  socket->Disconnect(base::Bind(&BluetoothSocketDisconnectFunction::OnSuccess,
                                this));
}

void BluetoothSocketDisconnectFunction::OnSuccess() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  results_ = bluetooth_socket::Disconnect::Results::Create();
  AsyncWorkCompleted();
}

BluetoothSocketCloseFunction::BluetoothSocketCloseFunction() {}

BluetoothSocketCloseFunction::~BluetoothSocketCloseFunction() {}

bool BluetoothSocketCloseFunction::Prepare() {
  params_ = bluetooth_socket::Close::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketCloseFunction::Work() {
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    return;
  }

  RemoveSocket(params_->socket_id);
  results_ = bluetooth_socket::Close::Results::Create();
}

BluetoothSocketSendFunction::BluetoothSocketSendFunction()
    : io_buffer_size_(0) {}

BluetoothSocketSendFunction::~BluetoothSocketSendFunction() {}

bool BluetoothSocketSendFunction::Prepare() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));
  params_ = bluetooth_socket::Send::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());

  io_buffer_size_ = params_->data.size();
  io_buffer_ = new net::WrappedIOBuffer(params_->data.data());
  return true;
}

void BluetoothSocketSendFunction::AsyncWorkStart() {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    return;
  }

  socket->Send(io_buffer_,
               io_buffer_size_,
               base::Bind(&BluetoothSocketSendFunction::OnSuccess, this),
               base::Bind(&BluetoothSocketSendFunction::OnError, this));
}

void BluetoothSocketSendFunction::OnSuccess(int bytes_sent) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  results_ = bluetooth_socket::Send::Results::Create(bytes_sent);
  AsyncWorkCompleted();
}

void BluetoothSocketSendFunction::OnError(
    BluetoothApiSocket::ErrorReason reason,
    const std::string& message) {
  DCHECK(BrowserThread::CurrentlyOn(work_thread_id()));
  error_ = message;
  AsyncWorkCompleted();
}

BluetoothSocketGetInfoFunction::BluetoothSocketGetInfoFunction() {}

BluetoothSocketGetInfoFunction::~BluetoothSocketGetInfoFunction() {}

bool BluetoothSocketGetInfoFunction::Prepare() {
  params_ = bluetooth_socket::GetInfo::Params::Create(*args_);
  EXTENSION_FUNCTION_VALIDATE(params_.get());
  return true;
}

void BluetoothSocketGetInfoFunction::Work() {
  BluetoothApiSocket* socket = GetSocket(params_->socket_id);
  if (!socket) {
    error_ = kSocketNotFoundError;
    return;
  }

  linked_ptr<bluetooth_socket::SocketInfo> socket_info =
      CreateSocketInfo(params_->socket_id, socket);
  results_ = bluetooth_socket::GetInfo::Results::Create(*socket_info);
}

BluetoothSocketGetSocketsFunction::BluetoothSocketGetSocketsFunction() {}

BluetoothSocketGetSocketsFunction::~BluetoothSocketGetSocketsFunction() {}

bool BluetoothSocketGetSocketsFunction::Prepare() { return true; }

void BluetoothSocketGetSocketsFunction::Work() {
  std::vector<linked_ptr<bluetooth_socket::SocketInfo> > socket_infos;
  base::hash_set<int>* resource_ids = GetSocketIds();
  if (resource_ids != NULL) {
    for (base::hash_set<int>::iterator it = resource_ids->begin();
         it != resource_ids->end();
         ++it) {
      int socket_id = *it;
      BluetoothApiSocket* socket = GetSocket(socket_id);
      if (socket) {
        socket_infos.push_back(CreateSocketInfo(socket_id, socket));
      }
    }
  }
  results_ = bluetooth_socket::GetSockets::Results::Create(socket_infos);
}

}  // namespace api
}  // namespace extensions
