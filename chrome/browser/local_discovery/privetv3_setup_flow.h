// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SETUP_FLOW_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SETUP_FLOW_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/local_discovery/gcd_api_flow.h"
#include "chrome/browser/local_discovery/privet_http.h"

namespace local_discovery {

// Provides complete flow for Privet v3 device setup.
class PrivetV3SetupFlow {
 public:
  // Delegate to be implemented by client code.
  class Delegate {
   public:
    typedef base::Callback<void(bool success)> ResultCallback;
    // If |ssid| is empty, call failed to get credentials.
    // If |key| is empty, network is open.
    typedef base::Callback<void(const std::string& ssid,
                                const std::string& key)> CredentialsCallback;

    typedef base::Callback<void(scoped_ptr<PrivetV3HTTPClient>)>
        PrivetClientCallback;

    virtual ~Delegate();

    // Creates |GCDApiFlowImpl| for making requests to GCD server.
    virtual scoped_ptr<GCDApiFlow> CreateApiFlow() = 0;

    // Requests WiFi credentials.
    virtual void GetWiFiCredentials(const CredentialsCallback& callback) = 0;

    // Switches to setup WiFi network.
    // If switch was successfully |RestoreWifi| should be called later.
    virtual void SwitchToSetupWiFi(const ResultCallback& callback) = 0;

    // Starts device resolution that should callback with ready
    // |PrivetV3HTTPClient|.
    virtual void CreatePrivetV3Client(const std::string& service_name,
                                      const PrivetClientCallback& callback) = 0;

    // Requests client to prompt user to check |confirmation_code|.
    virtual void ConfirmSecurityCode(const std::string& confirmation_code,
                                     const ResultCallback& callback) = 0;

    // Restores WiFi network.
    virtual void RestoreWifi(const ResultCallback& callback) = 0;

    // Notifies client that device is set up.
    virtual void OnSetupDone() = 0;

    // Notifies client setup failed.
    virtual void OnSetupError() = 0;
  };

  explicit PrivetV3SetupFlow(Delegate* delegate);
  ~PrivetV3SetupFlow();

  // Starts registration.
  void Register(const std::string& service_name);

#if defined(ENABLE_WIFI_BOOTSTRAPPING)
  void SetupWifiAndRegister(const std::string& device_ssid);
#endif  // ENABLE_WIFI_BOOTSTRAPPING

 private:
  Delegate* delegate_;
  std::string service_name_;
  base::WeakPtrFactory<PrivetV3SetupFlow> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrivetV3SetupFlow);
};

}  // namespace local_discovery

#endif  // CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SETUP_FLOW_H_
