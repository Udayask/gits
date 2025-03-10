# ===================== begin_copyright_notice ============================
#
# Copyright (C) 2023-2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
# ===================== end_copyright_notice ==============================

add_library(DirectX_utils STATIC)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(UTILS_FILES
  ${SRC_DIR}/pluginService.h
  ${SRC_DIR}/pluginService.cpp
  ${SRC_DIR}/resourceDump.h
  ${SRC_DIR}/resourceDump.cpp
  ${SRC_DIR}/gpuExecutionTracker.h
  ${SRC_DIR}/gpuExecutionTracker.cpp
)
source_group("" FILES ${UTILS_FILES})

target_sources(DirectX_utils PRIVATE
  ${UTILS_FILES}
)

target_include_directories(DirectX_utils PRIVATE
  ${D3D12_HEADERS_DIR}
  ${DML_HEADERS_DIR}
  ${DSTORAGE_HEADERS_DIR}
  ${PLUGINS_DIR}
  ${CMAKE_SOURCE_DIR}/third_party/DirectXTex/DirectXTex
)

set_target_properties(DirectX_utils PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(DirectX_utils PROPERTIES FOLDER DirectX/DirectX_common)
