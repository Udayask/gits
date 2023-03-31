// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#pragma once

#include <functional>

#include "platform.h"

#include "l0Header.h"

namespace gits {
namespace l0 {
class CDriver;

class IRecorderWrapper {
public:
  virtual void StreamFinishedEvent(std::function<void()> e) = 0;
  virtual void CloseRecorderIfRequired() = 0;
  virtual CDriver& Drivers() const = 0;
  virtual void InitializeDriver() const = 0;

#include "l0WrapperFunctionsIface.h"
  virtual void zeCommandQueueExecuteCommandLists_pre(ze_result_t return_value,
                                                     ze_command_queue_handle_t hCommandQueue,
                                                     uint32_t numCommandLists,
                                                     ze_command_list_handle_t* phCommandLists,
                                                     ze_fence_handle_t hFence) const = 0;
  virtual void zeCommandListAppendLaunchKernel_pre(ze_result_t return_value,
                                                   ze_command_list_handle_t hCommandList,
                                                   ze_kernel_handle_t hKernel,
                                                   const ze_group_count_t* pLaunchFuncArgs,
                                                   ze_event_handle_t hSignalEvent,
                                                   uint32_t numWaitEvents,
                                                   ze_event_handle_t* phWaitEvents) const = 0;
  virtual void UnProtectMemoryPointers(
      const ze_command_list_handle_t& hCommandList = nullptr) const = 0;
  virtual void ProtectMemoryPointers(
      const ze_command_list_handle_t& hCommandList = nullptr) const = 0;
  virtual void MarkRecorderForDeletion() = 0;
  virtual void DestroySniffedRegion(void* ptr) const = 0;
  virtual void UnProtectMemoryRegion(void* ptr) const = 0;
  virtual void ProtectMemoryRegion(void* ptr) const = 0;
  virtual bool IsMemorySnifferInstalled() const = 0;
  virtual void TrackThread() const = 0;
};
} // namespace l0
} // namespace gits

typedef gits::l0::IRecorderWrapper*(STDCALL* FGITSRecoderL0)();

extern "C" {
gits::l0::IRecorderWrapper* STDCALL GITSRecorderL0() VISIBLE;
}
