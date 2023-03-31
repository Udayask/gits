// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#pragma once

#include "platform.h"
#include "pragmas.h"

DISABLE_WARNINGS
#include <boost/optional.hpp>
ENABLE_WARNINGS
#include <functional>
#include <map>
#include <vector>

typedef unsigned int uint;

namespace InputListener {

class CInputListener {
public:
  class HotKeyHolder {
  public:
    typedef std::function<void()> HotKeyEvent;
    HotKeyHolder(std::vector<uint> keys, uint maxId) : _id(maxId), _keys(keys) {}
    uint Id() const {
      return _id;
    }

    void CallClickedEvents() {
      for (auto clickedEvent : _clickedEvents) {
        clickedEvent();
      }
    }
    void AddClickedEvent(HotKeyEvent clickedEvent) {
      _clickedEvents.push_back(clickedEvent);
    }
    void RegisterKey();
    void UnregisterKey();
    std::vector<uint> Keys() {
      return _keys;
    }

  private:
    uint _id;
    std::vector<HotKeyEvent> _clickedEvents;
    std::vector<uint> _keys;
  };

public:
  typedef boost::optional<HotKeyHolder&> HotKeyOptional;
  CInputListener() : _threadHandle(), _maxRegisteredHotKeyID(0) {}
  ~CInputListener(void);
  int AddHotKey(const std::vector<uint>& keys);
  void AddHotKeyEvent(uint hotKeyId, HotKeyHolder::HotKeyEvent clickEvent);
  HotKeyOptional GetHotKey(const uint hotKeyId);
  void SetAsPressed(uint hotKeyId);
  bool WasPressed(uint hotKeyId);
  void StartHotKeyListener(bool useMessageLoop = true);
  void RegisterHotKeys() {
    for (auto hotKey : _hotKeys) {
      hotKey.RegisterKey();
    }
  }
  void UnregisterHotKeys() {
    for (auto hotKey : _hotKeys) {
      hotKey.UnregisterKey();
    }
  }

private:
  void* _threadHandle;
  uint _maxRegisteredHotKeyID;
  std::map<uint, bool> _pressedHistory;
  std::vector<HotKeyHolder> _hotKeys;
  bool _useMessageLoop;
};
} // namespace InputListener
