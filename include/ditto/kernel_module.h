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

#pragma once

#include <ditto/instruction.h>

namespace dittosuite {

class KernelModuleInterface : public Instruction {
 protected:
  KernelModuleInterface(const KernelModuleInterface&) = delete;
  KernelModuleInterface& operator=(const KernelModuleInterface&) = delete;

  KernelModuleInterface(const std::string& name, const Params& params);
  virtual ~KernelModuleInterface() = default;
};

class KernelLoadModule : public KernelModuleInterface {
 public:
  inline static const std::string kName = "module_load";

  KernelLoadModule(const KernelLoadModule&) = delete;
  KernelLoadModule& operator=(const KernelLoadModule&) = delete;

  explicit KernelLoadModule(const Params& params, int input_fd_key);
  ~KernelLoadModule() = default;

 private:
  void SetUpSingle() override;
  void RunSingle() override;

  int kModuleFdKey;
};

class KernelUnloadModule : public KernelModuleInterface {
 public:
  inline static const std::string kName = "module_unload";

  KernelUnloadModule(const KernelUnloadModule&) = delete;
  KernelUnloadModule& operator=(const KernelUnloadModule&) = delete;

  explicit KernelUnloadModule(const Params& params, const std::string& module_name);
  ~KernelUnloadModule() = default;

 private:
  void SetUpSingle() override;
  void RunSingle() override;

  const std::string kModuleName;
};

}  // namespace dittosuite
