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
#ifndef TRAFFIC_SIZE_RANDOMMSD_H_
#define TRAFFIC_SIZE_RANDOMMSD_H_

#include <json/json.h>
#include <prim/prim.h>

#include <string>

#include "traffic/size/MessageSizeDistribution.h"
#include "types/Message.h"

class RandomMSD : public MessageSizeDistribution {
 public:
  RandomMSD(
      const std::string& _name, const Component* _parent,
      Json::Value _settings);
  virtual ~RandomMSD();

  // size bounds
  u32 minMessageSize() const override;
  u32 maxMessageSize() const override;

  // generates a new message size from scratch
  u32 nextMessageSize() override;

  // this calls the above function!
  u32 nextMessageSize(const Message* _msg) override;

 private:
  const u32 minMessageSize_;
  const u32 maxMessageSize_;
  const bool doDependent_;
  const u32 depMinMessageSize_;
  const u32 depMaxMessageSize_;
};

#endif  // TRAFFIC_SIZE_RANDOMMSD_H_
