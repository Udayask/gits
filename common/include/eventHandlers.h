// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2024 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#pragma once

#include <Windows.h>
#include <thread>
#include <atomic>

namespace gits {

class ExitEventHandler {
public:
  ExitEventHandler();
  ~ExitEventHandler();

  void Start();
  void Stop();

private:
  void WaitForExitEvent();

  HANDLE _hEventExit;
  std::thread _eventThread;
  std::atomic<bool> _stopWaiting;
};

} // namespace gits