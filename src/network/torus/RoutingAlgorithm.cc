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
#include "network/torus/RoutingAlgorithm.h"

#include <factory/Factory.h>

#include "network/torus/util.h"

namespace Torus {

RoutingAlgorithm::RoutingAlgorithm(
    const std::string& _name, const Component* _parent, Router* _router,
    u32 _baseVc, u32 _numVcs, const std::vector<u32>& _dimensionWidths,
    u32 _concentration, u32 _inputPort, Json::Value _settings)
    : ::RoutingAlgorithm(_name, _parent, _router, _baseVc, _numVcs, _settings),
      dimensionWidths_(_dimensionWidths), concentration_(_concentration),
      inputPort_(_inputPort),
      inputPortDim_(computeInputPortDim(dimensionWidths_, concentration_,
                                        inputPort_)) {}

RoutingAlgorithm::~RoutingAlgorithm() {}

RoutingAlgorithm* RoutingAlgorithm::create(
    const std::string& _name, const Component* _parent, Router* _router,
    u32 _baseVc, u32 _numVcs, const std::vector<u32>& _dimensionWidths,
    u32 _concentration, u32 _inputPort, Json::Value _settings) {
  // retrieve the algorithm
  const std::string& algorithm = _settings["algorithm"].asString();

  // attempt to create the routing algorithm
  RoutingAlgorithm* ra = factory::Factory<
    RoutingAlgorithm, TORUS_ROUTINGALGORITHM_ARGS>::create(
        algorithm, _name, _parent, _router, _baseVc, _numVcs, _dimensionWidths,
        _concentration, _inputPort, _settings);

  // check that the factory had this type
  if (ra == nullptr) {
    fprintf(stderr, "invalid Torus routing algorithm: %s\n", algorithm.c_str());
    assert(false);
  }
  return ra;
}

}  // namespace Torus
