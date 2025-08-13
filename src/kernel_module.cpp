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

#include <ditto/kernel_module.h>

#include <ditto/shared_variables.h>
#include <ditto/utils.h>

namespace dittosuite {

KernelModuleInterface::KernelModuleInterface(const std::string& name, const Params& params)
    : Instruction(name, params) {}

KernelLoadModule::KernelLoadModule(const Params& params, int input_fd_key)
    : KernelModuleInterface(kName, params), kModuleFdKey(input_fd_key) {}

void KernelLoadModule::SetUpSingle() {
  Instruction::SetUpSingle();
}

void KernelLoadModule::RunSingle() {
  int fd = std::get<int>(SharedVariables::Get(kModuleFdKey));
  if (syscall_.FinitModule(fd, dittosuite::EMPTY_STRING.c_str(), 0) != 0) {
    PLOGF("Failed loading kernel module");
  }
}

KernelUnloadModule::KernelUnloadModule(const Params& params, const std::string& module_name)
    : KernelModuleInterface(kName, params), kModuleName(module_name) {}

void KernelUnloadModule::SetUpSingle() {
  Instruction::SetUpSingle();
}

void KernelUnloadModule::RunSingle() {
  if (syscall_.DeleteModule(kModuleName.c_str(), O_NONBLOCK) != 0) {
    PLOGF("Failed unloading kernel module: " + kModuleName);
  }
}

}  // namespace dittosuite
