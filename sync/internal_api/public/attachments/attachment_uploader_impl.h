// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_UPLOADER_IMPL_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_UPLOADER_IMPL_H_

#include "base/containers/scoped_ptr_hash_map.h"
#include "base/threading/non_thread_safe.h"
#include "google_apis/gaia/oauth2_token_service_request.h"
#include "net/url_request/url_request_context_getter.h"
#include "sync/api/attachments/attachment_uploader.h"

class GURL;

namespace net {
class URLRequestContextGetter;
}  // namespace net

namespace syncer {

// An implementation of AttachmentUploader.
class SYNC_EXPORT AttachmentUploaderImpl : public AttachmentUploader,
                                           public base::NonThreadSafe {
 public:
  // |url_prefix| is the URL prefix (including trailing slash) to be used when
  // uploading attachments.
  //
  // |url_request_context_getter| provides a URLRequestContext.
  //
  // |account_id| is the account id to use for uploads.
  //
  // |scopes| is the set of scopes to use for uploads.
  //
  // |token_service_provider| provides an OAuth2 token service.
  AttachmentUploaderImpl(
      const std::string& url_prefix,
      const scoped_refptr<net::URLRequestContextGetter>&
          url_request_context_getter,
      const std::string& account_id,
      const OAuth2TokenService::ScopeSet& scopes,
      scoped_ptr<OAuth2TokenServiceRequest::TokenServiceProvider>
          token_service_provider);
  virtual ~AttachmentUploaderImpl();

  // AttachmentUploader implementation.
  virtual void UploadAttachment(const Attachment& attachment,
                                const UploadCallback& callback) OVERRIDE;

 private:
  class UploadState;
  typedef std::string UniqueId;
  typedef base::ScopedPtrHashMap<UniqueId, UploadState> StateMap;

  GURL GetUploadURLForAttachmentId(const AttachmentId& attachment_id) const;
  void DeleteUploadStateFor(const UniqueId& unique_id);

  std::string url_prefix_;
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;
  std::string account_id_;
  OAuth2TokenService::ScopeSet scopes_;
  scoped_ptr<OAuth2TokenServiceRequest::TokenServiceProvider>
      token_service_provider_;
  StateMap state_map_;
  DISALLOW_COPY_AND_ASSIGN(AttachmentUploaderImpl);
};

}  // namespace syncer

#endif  // SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_UPLOADER_IMPL_H_
