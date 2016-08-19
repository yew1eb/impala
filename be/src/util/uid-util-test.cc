// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gtest/gtest.h>

#include "util/uid-util.h"

namespace impala {

TEST(UidUtil, FragmentInstanceId) {
  boost::uuids::random_generator uuid_generator;
  boost::uuids::uuid query_uuid = uuid_generator();
  TUniqueId query_id = UuidToQueryId(query_uuid);

  for (int i = 0; i < 100; ++i) {
    TUniqueId instance_id = CreateInstanceId(query_id, i);
    EXPECT_EQ(instance_id.hi, query_id.hi);

    TUniqueId qid = GetQueryId(instance_id);
    EXPECT_EQ(qid.hi, query_id.hi);
    EXPECT_EQ(qid.lo, query_id.lo);

    EXPECT_EQ(GetInstanceIdx(instance_id), i);
  }
}

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
