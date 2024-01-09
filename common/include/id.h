// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2024 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

/**
 * @file   id.h
 *
 * @brief Declaration of a class that handles entity identifiers.
 *
 */

#pragma once

#include <cstdint>

namespace gits {
class CBinOStream;
class CBinIStream;

/**
   * @brief Class that handles GITS project entities identifiers.
   *
   * gits::CId class is responsible for handling GITS project entities
   * identifiers.
   */
class CId {
  uint32_t _id;

public:
  CId();
  explicit CId(uint32_t id);

  uint32_t operator*() const {
    return _id;
  }

  void Write(CBinOStream& stream) const;
  void Read(CBinIStream& stream);
};
} // namespace gits
