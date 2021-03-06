/*
 * Copyright 2016 Hewlett Packard Enterprise Development LP
 *
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef NETWORK_BUTTERFLY_NETWORK_H_
#define NETWORK_BUTTERFLY_NETWORK_H_

#include <json/json.h>
#include <prim/prim.h>

#include <string>
#include <vector>

#include "event/Component.h"
#include "interface/Interface.h"
#include "network/Channel.h"
#include "network/Network.h"
#include "network/butterfly/RoutingAlgorithm.h"
#include "router/Router.h"

namespace Butterfly {

class Network : public ::Network {
 public:
  Network(const std::string& _name, const Component* _parent,
          MetadataHandler* _metadataHandler, Json::Value _settings);
  ~Network();

  // this is the routing algorithm factory for this network
  ::RoutingAlgorithm* createRoutingAlgorithm(
       u32 _vc, u32 _port, const std::string& _name, const Component* _parent,
       Router* _router) override;

  // Network
  u32 numRouters() const override;
  u32 numInterfaces() const override;
  Router* getRouter(u32 _id) const override;
  Interface* getInterface(u32 _id) const override;
  void translateInterfaceIdToAddress(
      u32 _id, std::vector<u32>* _address) const override;
  u32 translateInterfaceAddressToId(
      const std::vector<u32>* _address) const override;
  void translateRouterIdToAddress(
      u32 _id, std::vector<u32>* _address) const override;
  u32 translateRouterAddressToId(
      const std::vector<u32>* _address) const override;

 protected:
  void collectChannels(std::vector<Channel*>* _channels) override;

 private:
  u32 routerRadix_;
  u32 numStages_;
  u32 stageWidth_;
  u32 tmpStage_;

  std::vector<Router*> routers_;

  std::vector<Channel*> externalChannels_;
  std::vector<Channel*> internalChannels_;
  std::vector<Interface*> interfaces_;
};

}  // namespace Butterfly

#endif  // NETWORK_BUTTERFLY_NETWORK_H_
