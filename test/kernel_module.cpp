// Copyright (C) 2025 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "include/instruction_test.h"

#include <ditto/kernel_module.h>
#include <ditto/shared_variables.h>
#include <ditto/syscall.h>
#include <ditto/utils.h>

using dittosuite::Instruction;
using dittosuite::SharedVariables;
using testing::_;

class KernelModuleTest : public InstructionTest {
 protected:
  int fd_ = MockSyscall::kDefaultFileDescriptor;
  int input_key_;

  // Set input fd
  void SetUp() override {
    InstructionTest::SetUp();
    input_key_ = SharedVariables::GetKey(thread_ids, "test_input");
    SharedVariables::Set(input_key_, fd_);
  }
};

TEST_F(KernelModuleTest, KernelLoadModule) {
  EXPECT_CALL(syscall_, FinitModule(fd_, dittosuite::EMPTY_STRING.c_str(), 0));

  dittosuite::KernelLoadModule instruction((Instruction::Params){syscall_, 1}, input_key_);
  instruction.Run();
}
