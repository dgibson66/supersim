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
#ifndef NETWORK_TORUS_ROUTINGALGORITHM_H_
#define NETWORK_TORUS_ROUTINGALGORITHM_H_

#include <json/json.h>
#include <prim/prim.h>

#include <string>
#include <vector>

#include "event/Component.h"
#include "network/RoutingAlgorithm.h"
#include "router/Router.h"

#define TORUS_ROUTINGALGORITHM_ARGS const std::string&, const Component*, \
    Router*, u32, u32, const std::vector<u32>&, u32, u32, Json::Value

namespace Torus {

class RoutingAlgorithm : public ::RoutingAlgorithm {
 public:
  RoutingAlgorithm(
      const std::string& _name, const Component* _parent,
      Router* _router, u32 _baseVc, u32 _numVcs,
      const std::vector<u32>& _dimensionWidths, u32 _concentration,
      u32 _inputPort, Json::Value _settings);
  virtual ~RoutingAlgorithm();

  // this is a routing algorithm factory for the torus topology
  static RoutingAlgorithm* create(TORUS_ROUTINGALGORITHM_ARGS);

 protected:
  const std::vector<u32> dimensionWidths_;
  const u32 concentration_;
  const u32 inputPort_;
  const u32 inputPortDim_;
};

}  // namespace Torus

#endif  // NETWORK_TORUS_ROUTINGALGORITHM_H_
