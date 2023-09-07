#!/usr/bin/python

# ===================== begin_copyright_notice ============================
#
# Copyright (C) 2023 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
# ===================== end_copyright_notice ==============================

from generator_vulkan import *
import operator
import re

import sys
import os
import shutil

vulkan_flags = [
  'VkFlags',
  'VkInstanceCreateFlags',
  'VkFormatFeatureFlags',
  'VkImageUsageFlags',
  'VkImageCreateFlags',
  'VkSampleCountFlags',
  'VkQueueFlags',
  'VkMemoryPropertyFlags',
  'VkMemoryHeapFlags',
  'VkDeviceCreateFlags',
  'VkDeviceQueueCreateFlags',
  'VkPipelineStageFlags',
  'VkMemoryMapFlags',
  'VkImageAspectFlags',
  'VkSparseImageFormatFlags',
  'VkSparseMemoryBindFlags',
  'VkFenceCreateFlags',
  'VkSemaphoreCreateFlags',
  'VkEventCreateFlags',
  'VkQueryPoolCreateFlags',
  'VkQueryPipelineStatisticFlags',
  'VkQueryResultFlags',
  'VkBufferCreateFlags',
  'VkBufferUsageFlags',
  'VkBufferViewCreateFlags',
  'VkImageViewCreateFlags',
  'VkShaderModuleCreateFlags',
  'VkPipelineCacheCreateFlags',
  'VkPipelineCreateFlags',
  'VkPipelineShaderStageCreateFlags',
  'VkPipelineVertexInputStateCreateFlags',
  'VkPipelineInputAssemblyStateCreateFlags',
  'VkPipelineTessellationStateCreateFlags',
  'VkPipelineViewportStateCreateFlags',
  'VkPipelineRasterizationStateCreateFlags',
  'VkPipelineRasterizationStateStreamCreateFlagsEXT',
  'VkCullModeFlags',
  'VkPipelineMultisampleStateCreateFlags',
  'VkPipelineDepthStencilStateCreateFlags',
  'VkPipelineColorBlendStateCreateFlags',
  'VkColorComponentFlags',
  'VkPipelineDynamicStateCreateFlags',
  'VkPipelineLayoutCreateFlags',
  'VkShaderStageFlags',
  'VkSamplerCreateFlags',
  'VkDescriptorSetLayoutCreateFlags',
  'VkDescriptorPoolCreateFlags',
  'VkDescriptorPoolResetFlags',
  'VkFramebufferCreateFlags',
  'VkRenderPassCreateFlags',
  'VkAttachmentDescriptionFlags',
  'VkSubpassDescriptionFlags',
  'VkAccessFlags',
  'VkDependencyFlags',
  'VkCommandPoolCreateFlags',
  'VkCommandPoolResetFlags',
  'VkCommandBufferUsageFlags',
  'VkQueryControlFlags',
  'VkCommandBufferResetFlags',
  'VkStencilFaceFlags',
  'VkSurfaceTransformFlagsKHR',
  'VkCompositeAlphaFlagsKHR',
  'VkSwapchainCreateFlagsKHR',
  'VkDisplayModeCreateFlagsKHR',
  'VkDisplayPlaneAlphaFlagsKHR',
  'VkDisplaySurfaceCreateFlagsKHR',
  'VkXlibSurfaceCreateFlagsKHR',
  'VkXcbSurfaceCreateFlagsKHR',
  'VkWaylandSurfaceCreateFlagsKHR',
  'VkMirSurfaceCreateFlagsKHR',
  'VkAndroidSurfaceCreateFlagsKHR',
  'VkWin32SurfaceCreateFlagsKHR',
  'VkCommandPoolTrimFlagsKHR',
  'VkDebugReportFlagsEXT',
  'VkExternalMemoryHandleTypeFlagsNV',
  'VkExternalMemoryFeatureFlagsNV',
  'VkPeerMemoryFeatureFlagsKHX',
  'VkMemoryAllocateFlagsKHX',
  'VkDeviceGroupPresentModeFlagsKHX',
  'VkViSurfaceCreateFlagsNN',
  'VkExternalMemoryHandleTypeFlagsKHX',
  'VkExternalMemoryFeatureFlagsKHX',
  'VkExternalSemaphoreHandleTypeFlagsKHX',
  'VkExternalSemaphoreFeatureFlagsKHX',
  'VkIndirectCommandsLayoutUsageFlagsNVX',
  'VkObjectEntryUsageFlagsNVX',
  'VkSurfaceCounterFlagsEXT',
  'VkDescriptorUpdateTemplateCreateFlags',
  'VkDeviceGroupPresentModeFlagsKHR',
  'VkMemoryAllocateFlags',
  'VkPipelineRasterizationDepthClipStateCreateFlagsEXT',
  'VkSemaphoreWaitFlags',
  'VkConditionalRenderingFlagsEXT',
  'VkPipelineCreationFeedbackFlags',
  'VkPipelineCreationFeedbackFlagsEXT',
  'VkDescriptorBindingFlags',
  'VkDeviceMemoryReportFlagsEXT',
  'VkSubmitFlagsKHR',
  'VkVideoSessionCreateFlagsKHR',
  'VkVideoBeginCodingFlagsKHR',
  'VkVideoEndCodingFlagsKHR',
  'VkVideoCodingQualityPresetFlagsKHR',
  'VkVideoCapabilitiesFlagsKHR',
  'VkVideoCodingControlFlagsKHR',
  'VkVideoDecodeH264CreateFlagsEXT',
  'VkVideoDecodeH265CreateFlagsEXT',
  'VkVideoEncodeH264CapabilitiesFlagsEXT',
  'VkVideoEncodeH264InputModeFlagsEXT',
  'VkVideoEncodeH264OutputModeFlagsEXT',
  'VkVideoEncodeH264CreateFlagsEXT',
  'VkVideoEncodeRateControlFlagsKHR',
  'VkVideoChromaSubsamplingFlagsKHR',
  'VkVideoCodecOperationFlagsKHR',
  'VkVideoDecodeFlagsKHR',
  'VkVideoEncodeFlagsKHR',
  'VkSubmitFlags',
  'VkRenderingFlags',
  'VkGraphicsPipelineLibraryFlagsEXT',
]

vulkan_uint32 = vulkan_flags + [
  'uint32_t',
  'bool32_t',
  'VkBool32',
]
vulkan_uint64 = [
  'VkDeviceSize',
  'VkDeviceAddress',
  'VkAccessFlags2',
  'VkAccessFlags2KHR',
  'VkPipelineStageFlags2',
  'VkPipelineStageFlags2KHR',
]

vulkan_union = [
  "VkClearColorValue",
  "VkClearValue"
]

vulkan_other_primitives = [
  "bool",
  "int32_t",
  "int64_t",
  "uint8_t",
  "uint16_t",
  "uint32_t",
  "uint64_t",
  "size_t",
  "float",
  "double",
  "void*",
  "void**",
  "nullptr"
]

vulkan_enums = []
for enum in enums_table:
  vulkan_enums.append(enum['name'])

vulkan_structs = []
for enum in structs_table:
  vulkan_structs.append(enum['name'].rstrip('_'))

primitive_types = vulkan_enums + vulkan_uint32 + vulkan_uint64 + vulkan_union + vulkan_other_primitives

opaque_dispatchable_handles = [
  "VkInstance",
  "VkPhysicalDevice",
  "VkDevice",
  "VkQueue",
  "VkCommandBuffer",
]

opaque_nondispatchable_handles = [
  'VkSemaphore',
  'VkFence',
  'VkDeviceMemory',
  'VkBuffer',
  'VkImage',
  'VkEvent',
  'VkQueryPool',
  'VkBufferView',
  'VkImageView',
  'VkShaderModule',
  'VkPipelineCache',
  'VkPipelineLayout',
  'VkRenderPass',
  'VkPipeline',
  'VkDescriptorSetLayout',
  'VkSampler',
  'VkDescriptorPool',
  'VkDescriptorSet',
  'VkFramebuffer',
  'VkCommandPool',
  'VkSamplerYcbcrConversion',
  'VkDescriptorUpdateTemplate',
  'VkSurfaceKHR',
  'VkSwapchainKHR',
  'VkDisplayKHR',
  'VkDisplayModeKHR',
  'VkDebugReportCallbackEXT',
  'VkObjectTableNVX',
  'VkIndirectCommandsLayoutNVX',
  'VkDebugUtilsMessengerEXT',
  'VkValidationCacheEXT',
  'VkPerformanceConfigurationINTEL',
  'VkVideoSessionKHR',
  'VkVideoSessionParametersKHR',
]

other_opaque_handles = [
  "HWND",
  "HINSTANCE",
]

opaque_handles = opaque_dispatchable_handles + opaque_nondispatchable_handles + other_opaque_handles

# Data for CCode
types_needing_name_registration = [
  "StringArray",
  "ByteStringArray",
]

types_not_needing_declaration = vulkan_enums + vulkan_uint32 + vulkan_uint64 + vulkan_other_primitives + opaque_handles + [
  "NullWrapper",
  "VoidPtr",
]

vulkan_mapped_types = opaque_dispatchable_handles
vulkan_mapped_types_nondisp = opaque_nondispatchable_handles

copyright_header = """//====================== begin_copyright_notice ============================
//
// Copyright (C) 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
//====================== end_copyright_notice ==============================

"""

structs_names = []


def arg_decl(fdata, prototypes=False, vkDrivers=False):
  content = ''
  if (fdata['type'] != 'void') and (vkDrivers is False):
    content += fdata['type'] + ' return_value, '
  for arg in fdata['args']:
    arg_type = arg['type']
    arg_array = ''
    re_array = re.search(r'\[([0-9_]+)\]', arg_type)
    if re_array:
      arg_type = arg_type.replace(re_array.group(0), '')
      arg_array = re_array.group(0)
    content += arg_type + ' ' + arg['name'] + arg_array + ','
    if prototypes is True:
      content += '\n'
    else:
      content += ' '
  content = content.rstrip(', \n')
  return content


def add_version(name, version):
  name = name.strip('_')
  if (version is not None and version > 0):
    return name + '_V' + str(version)
  else:
    return name


def make_id(name, version):
  id_ = re.sub('([a-z])([A-Z])', r'\g<1>_\g<2>', name)
  id_ = re.sub('([0-9])D', r'_\g<1>D_', id_)

  id_final = 'ID_' + id_.upper().strip('_')
  id_final = add_version(id_final, version)
  return id_final

def make_type(fdata):
  type = ""
  if fdata['functionType']&Param:
    type += "GITS_VULKAN_PARAM_APITYPE | "
  if fdata['functionType']&QueueSubmit:
    type += "GITS_VULKAN_QUEUE_SUBMIT_APITYPE | "
  if fdata['functionType']&CreateImage:
    type += "GITS_VULKAN_CREATE_IMAGE_APITYPE | "
  if fdata['functionType']&CreateBuffer:
    type += "GITS_VULKAN_CREATE_BUFFER_APITYPE | "
  if fdata['functionType']&CmdBufferSet:
    type += "GITS_VULKAN_CMDBUFFER_SET_APITYPE | "
  if fdata['functionType']&CmdBufferBind:
    type += "GITS_VULKAN_CMDBUFFER_BIND_APITYPE | "
  if fdata['functionType']&CmdBufferPush:
    type += "GITS_VULKAN_CMDBUFFER_PUSH_APITYPE | "
  if fdata['functionType']&BeginRenderPass:
    type += "GITS_VULKAN_BEGIN_RENDERPASS_APITYPE | "
  if fdata['functionType']&EndRenderPass:
    type += "GITS_VULKAN_END_RENDERPASS_APITYPE | "
  type = type.strip(" | ")
  return type

def arg_call(fdata, prePostExec=False, vkDrivers=False):
  content = ""
  if (fdata['type'] != 'void') and (vkDrivers is False):
    content += 'return_value, '
  if prePostExec is True:
    content += "drvVk, "
  for arg in fdata['args']:
    content += arg['name'] + ", "
  content = content.rstrip(", ")
  return content


def generate_vulkan_drivers(functions):
  vk_drivers = open('vulkanDriversAuto.inl', 'w')
  vk_drivers.write(copyright_header)
  global_level_functions = ""
  instance_level_functions = ""
  device_level_functions = ""
  prototype_level_functions = ""

  for name in sorted(functions.keys()):
    function = functions[name][0]  # 0 because we only want the base version.
    type = function['type']
    if type == 'void':
      type = 'void_t'
    args_decl = arg_decl(function, False, True)
    args_call = arg_call(function, False, True)

    content = "_LEVEL_FUNCTION(%(type)s, %(name)s, (%(args_decl)s), (%(args_call)s)" % locals()
    definition = "VK_"

    if function['customDriver'] is True:
      definition += "CUSTOM_"

    if function['level'] == GlobalLevel:
      global_level_functions += definition + "GLOBAL" + content + ")\n"
    elif function['level'] == InstanceLevel:
      instance_level_functions += definition + "INSTANCE" + content + ", " + function['args'][0]['name'] + ")\n"
    elif function['level'] == PrototypeLevel:
      prototype_level_functions += definition + "PROTOTYPE" + content + ")\n"
    else:
      device_level_functions += definition + "DEVICE" + content + ", " + function['args'][0]['name'] + ")\n"

  content = """
#ifndef VK_GLOBAL_LEVEL_FUNCTION
#define VK_GLOBAL_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call)
#endif

#ifndef VK_CUSTOM_GLOBAL_LEVEL_FUNCTION
#define VK_CUSTOM_GLOBAL_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call) VK_GLOBAL_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call)
#endif

%(global_level_functions)s
#undef VK_GLOBAL_LEVEL_FUNCTION
#undef VK_CUSTOM_GLOBAL_LEVEL_FUNCTION


#ifndef VK_INSTANCE_LEVEL_FUNCTION
#define VK_INSTANCE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name)
#endif

#ifndef VK_CUSTOM_INSTANCE_LEVEL_FUNCTION
#define VK_CUSTOM_INSTANCE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name) VK_INSTANCE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name)
#endif

%(instance_level_functions)s
#undef VK_INSTANCE_LEVEL_FUNCTION
#undef VK_CUSTOM_INSTANCE_LEVEL_FUNCTION


#ifndef VK_DEVICE_LEVEL_FUNCTION
#define VK_DEVICE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name)
#endif

#ifndef VK_CUSTOM_DEVICE_LEVEL_FUNCTION
#define VK_CUSTOM_DEVICE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name) VK_DEVICE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call, first_argument_name)
#endif

%(device_level_functions)s
#undef VK_DEVICE_LEVEL_FUNCTION
#undef VK_CUSTOM_DEVICE_LEVEL_FUNCTION


#ifndef VK_PROTOTYPE_LEVEL_FUNCTION
#define VK_PROTOTYPE_LEVEL_FUNCTION(return_type, function_name, function_arguments, arguments_call)
#endif

%(prototype_level_functions)s
#undef VK_PROTOTYPE_LEVEL_FUNCTION
""" % {'global_level_functions': global_level_functions, 'instance_level_functions': instance_level_functions, 'device_level_functions': device_level_functions, 'prototype_level_functions': prototype_level_functions}

  vk_drivers.write(content)


def generate_vulkan_log(structs, enums):
  vk_log_auto_cpp = open('vulkanLogAuto.cpp', 'w')
  vk_log_auto_inl = open('vulkanLogAuto.inl', 'w')

  vk_log_auto_cpp.write(copyright_header)
  vk_log_auto_inl.write(copyright_header)

  vk_log_auto_cpp.write("""
#include "vulkanLog.h"

namespace gits {
namespace Vulkan {

""")

  content = ""
  content_inl = ""
  declared_structs = []
  while len(declared_structs) < len(structs):
    for key in sorted(structs.keys()):
      if key not in declared_structs:
        to_declare = []
        struct = structs[key][0]  # 0 because we only need the base version.
        for var in struct['vars']:
          elem_type = var['type'] + '_'
          if (elem_type not in declared_structs) and (elem_type in structs.keys()):
            to_declare.append(elem_type)
        if len(to_declare) == 0:
          versioned_name = add_version(key, struct.get('version'))
          content_inl += "CVkLog & operator<<(const " + versioned_name + "& c);\n"
          content += "CVkLog & CVkLog::operator<<(const " + versioned_name + "& c) {\n"
          content += "  *this << \"{\" << "

          for var in struct['vars']:
            content += "\" " + var['name'] + ": \""

            type_cast = var['type'].replace("Flags", "FlagBits")
            if (var['type'].find("Flags") != -1) and (type_cast in enums):
              type_cast = "(" + type_cast + ")"
            else:
              type_cast = ""

            if (var['name'] == "pNext"):
              content += " << (PNextPointerTypeTag)c.pNext << \", \" << "
            elif ('count' in var):
              content += ";\n"

              content += "  if ((isTraceDataOptPresent(TraceData::VK_STRUCTS))"
              # Avoid nullptr checks for arrays on the stack.
              if '[' not in var['type']:
                content+= " && (c." + var['name'] + " != nullptr)"
              if ('logCondition' in var):
                content += " && (" + var['logCondition'] + ")"
              content += ") {\n"

              content += "    *this << \"{\";\n"
              content += "    for (uint32_t i = 0; i < (uint32_t)c." + var['count'] + "; ++i) {\n"
              content += "      *this << \" [\" << i << \"]:\" << " + type_cast + "c." + var['name'] + "[i];\n"
              content += "    }\n"
              content += "    *this << \" }\";\n"
              content += "  } else {\n"
              content += "    *this << (void*)c." + var['name'] + ";\n"
              content += "  }\n"
              content += "  *this << \", \" << "
            else:
              content += " << " + type_cast + "c." + var['name'] + " << \", \" << "

          content = content.rstrip("<< \", \" << ")
          content += " << \" }\";\n"
          content += "  return *this;\n"
          content += "}\n\n"

          content_inl += "CVkLog & operator<<(const " + versioned_name + "* c);\n"
          content += "CVkLog & CVkLog::operator<<(const " + versioned_name + "* c) {\n"
          content += "  if (c != nullptr) {\n"
          content += "    if (isTraceDataOptPresent(TraceData::VK_STRUCTS))\n"
          content += "      *this << *c;\n"
          content += "    else\n"
          content += "      _buffer << \"{ \" << (void*)c << \" }\";\n"
          content += "  } else {\n"
          content += "    _buffer << \"{ 0 }\";\n"
          content += "  }\n"
          content += "  return *this;\n"
          content += "}\n\n"

          declared_structs.append(key)
  content = content.replace("\", \" << \" ", "\", ")
  content = content.replace("\"{\" << \" ", "\"{ ")
  content = content.replace("c.8", "8")
  content = content.replace("c.6", "6")
  content = content.replace("c.4", "4")
  content = content.replace("c.3", "3")
  content = content.replace("c.2", "2")
  content = content.replace("c.1", "1")
  vk_log_auto_cpp.write(content)
  vk_log_auto_inl.write(content_inl)

  content_enums = ""
  content_enums_inl = ""
  for key in sorted(enums.keys()):
    for enum in enums[key]:
      content_enums_inl += "CVkLog & operator<<(const " + key + "& c);\n"
      content_enums += "CVkLog & CVkLog::operator<<(const " + key + "& c) {\n"

      if key.find("Bits") != -1:
        content_enums += "  std::underlying_type_t<" + key + "> e = c;\n"
        content_enums += "  std::ostringstream os;\n"

        enum['vars'].sort(key=lambda x: int(x['value']), reverse=True)
        if enum['vars'][-1]['value'] == '0':
          content_enums += "  if (e == 0) {\n"
          content_enums += "    os << \"" + enum['vars'][-1]['name'] + " | \";\n"
          content_enums += "  }\n"
        for var in enum['vars']:
          if var['value'] != '0':
            content_enums += "  if (isBitSet(e, " + var['name'] + ")) {\n"
            content_enums += "    os << \"" + var['name'] + " | \";\n"
            content_enums += "    e &= ~" + var['name'] + ";\n"
            content_enums += "  }\n"

        content_enums += "  for (decltype(e) i = 1; i <= e; i <<= 1) {\n"
        content_enums += "    if (i & e) {\n"

        content_enums += "      os << i << \" | \";\n"
        content_enums += "      Log(WARN) << \"Unknown enum number: \" << i << \" for " + key + "\";\n"
        content_enums += "      break;\n"
        content_enums += "    }\n"
        content_enums += "  }\n"
        content_enums += "  std::string str = os.str();\n"
        content_enums += "  if (str.size() > 3) {\n"
        content_enums += "    str = str.substr(0, str.size() - 3);\n"
        content_enums += "  } else {\n"
        content_enums += "    str = \"0\";\n"
        content_enums += "  }\n"
        content_enums += "  _buffer << \"{ \" << str << \" }\";\n"

      else:
        content_enums += "  switch (c) {\n"
        for var in enum['vars']:
          content_enums += "    case " + var['value'] + ":\n"
          content_enums += "      _buffer << \"" + var['name'] + "\";\n"
          content_enums += "      break;\n"

        content_enums += "    default:\n"
        content_enums += "      _buffer << c;\n"
        content_enums += "      Log(WARN) << \"Unknown enum number: \" << c << \" for " + key + "\";\n"
        content_enums += "      break;\n"
        content_enums += "  }\n"

      content_enums += "  return *this;\n"
      content_enums += "}\n\n"
  vk_log_auto_cpp.write(content_enums)
  vk_log_auto_inl.write(content_enums_inl)

  content_nondisp = "#if defined(__LP64__) || defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)\n"
  content_nondisp_inl = content_nondisp
  for key in vulkan_mapped_types_nondisp:
    content_nondisp_inl += "CVkLog & operator<<(const " + key + "& c);\n"
    content_nondisp += "CVkLog & CVkLog::operator<<(const " + key + "& c) {\n"
    content_nondisp += "  *this << \"{ \" << (void*)c << \" }\";\n"
    content_nondisp += "  return *this;\n"
    content_nondisp += "}\n\n"

    content_nondisp_inl += "CVkLog & operator<<(const " + key + "* c);\n"
    content_nondisp += "CVkLog & CVkLog::operator<<(const " + key + "* c) {\n"
    content_nondisp += "  if (c != nullptr) {\n"
    content_nondisp += "    if (isTraceDataOptPresent(TraceData::VK_STRUCTS))\n"
    content_nondisp += "      *this << *c;\n"
    content_nondisp += "    else\n"
    content_nondisp += "      _buffer << \"{ \" << (void*)c << \" }\";\n"
    content_nondisp += "  } else {\n"
    content_nondisp += "    _buffer << \"{ 0 }\";\n"
    content_nondisp += "  }\n"
    content_nondisp += "  return *this;\n"
    content_nondisp += "}\n\n"

  content_nondisp += "#endif\n"
  content_nondisp_inl += "#endif\n"
  vk_log_auto_cpp.write(content_nondisp)
  vk_log_auto_inl.write(content_nondisp_inl)

  content_disp = ""
  content_disp_inl = ""
  for key in vulkan_mapped_types:
    content_disp_inl += "CVkLog & operator<<(const " + key + "& c);\n"
    content_disp += "CVkLog & CVkLog::operator<<(const " + key + "& c) {\n"
    content_disp += "  *this << \"{ \" << (void *)c << \" }\";\n"
    content_disp += "  return *this;\n"
    content_disp += "}\n\n"

    content_disp_inl += "CVkLog & operator<<(const " + key + "* c);\n"
    content_disp += "CVkLog & CVkLog::operator<<(const " + key + "* c) {\n"
    content_disp += "  if (c != nullptr) {\n"
    content_disp += "    if (isTraceDataOptPresent(TraceData::VK_STRUCTS))\n"
    content_disp += "      *this << *c;\n"
    content_disp += "    else\n"
    content_disp += "      _buffer << \"{ \" << (void*)c << \" }\";\n"
    content_disp += "  } else {\n"
    content_disp += "    _buffer << \"{ 0 }\";\n"
    content_disp += "  }\n"
    content_disp += "  return *this;\n"
    content_disp += "}\n\n"
  vk_log_auto_cpp.write(content_disp)
  vk_log_auto_inl.write(content_disp_inl)

  vk_log_auto_cpp.write("""
} // namespace Vulkan
} // namespace gits
""")

  return content


def generate_vulkan_tracer(functions, enums):
  vk_tracer = open('vulkanTracer.h', 'w')
  vk_tracer.write(copyright_header)

  content = """\
#pragma once

#include "vulkanLog.h"

namespace gits {

  template<class T>
  void trace_return_value(T r) {
    VkLog(TRACE, NO_PREFIX) << " = " << r;
  }

  template<>
  void trace_return_value<void_t>(void_t) {
    VkLog(TRACE, NO_PREFIX) << "";
  }

"""

  for name in sorted(functions.keys()):
    function = functions[name][0]  # 0 because we only need the base version.
    content += "  void " + name + "_trace("

    content += arg_decl(function, False, True)

    content += ") {\n"
    content += "    VkLog(TRACE, RAW) << \"(\""

    for arg in function['args']:
      if (arg['type'] != 'void'):
        content += " << \" " + arg['type'] + " " + arg['name'] + "=\""

        type_cast = arg['type'].replace("Flags", "FlagBits")
        if (arg['type'].find("Flags") != -1) and (type_cast in enums):
          type_cast = "(" + type_cast + ")"
        else:
          type_cast = ""

        if ('count' in arg):
          content += ";\n"
          is_pointer = False
          dereference_pointer = ""

          for argument in function['args']:
            if (argument['name'].find(arg['count']) != -1):
              if (argument['type'].find("*") != -1):
                is_pointer = True
                dereference_pointer = "*"

          content += "    if ((isTraceDataOptPresent(TraceData::VK_STRUCTS)) && (" + arg['name'] + " != nullptr)"
          if is_pointer:
            content += " && (" + arg['count'] + " != nullptr)"
          content += ") {\n"

          content += "      VkLog(TRACE, RAW) << \"{\";\n"
          content += "      for (uint32_t i = 0; i < (uint32_t)" + dereference_pointer + arg['count'] + "; ++i) {\n"
          content += "        VkLog(TRACE, RAW) << \" [\" << i << \"]:\" << " + type_cast + arg['name'] + "[i];\n"
          content += "      }\n"
          content += "      VkLog(TRACE, RAW) << \" }\";\n"
          content += "    } else {\n"
          content += "      VkLog(TRACE, RAW) << " + arg['name'] + ";\n"
          content += "    }\n"
          content += "    VkLog(TRACE, RAW) << \",\""
        else:
          content += " << " + type_cast + arg['name'] + " << \",\""

    if content.rfind("<< \",\"", len(content)-7) > 0:
      content = content[:-7]

    content += " << \" )\";\n"
    content += "  };\n"
    content += "\n"

  content += "} // namespace gits\n"

  content = content.replace("\",\" << \" ", "\", ")
  content = content.replace("\"(\" << \" ", "\"( ")

  vk_tracer.write(content)


def generate_vulkan_struct_storage(structs, enums):
  content = ""
  content_cpp = ""
  declared_structs = []
  vk_struct_storage_h = open('vulkanStructStorageAuto.h', 'w')
  vk_struct_storage_h.write(copyright_header)
  vk_struct_storage_cpp = open('vulkanStructStorageAuto.cpp', 'w')
  vk_struct_storage_cpp.write(copyright_header)

  begin_cpp = """#include "vulkanStructStorageAuto.h"
#include "vulkanTools_lite.h"

"""
  begin_h = """#pragma once

#include <vector>
#include <memory>
#include "vulkanStructStorageBasic.h"

namespace gits{
namespace Vulkan {
"""

  vk_struct_storage_h.write(begin_h)
  vk_struct_storage_cpp.write(begin_cpp)

  content_nondisp = ""
  for key in vulkan_mapped_types_nondisp:
    content_nondisp += f"    typedef CSimpleMappedData<{key}> C{key}Data;\n"
    content_nondisp += f"    typedef CDataArray<{key}, C{key}Data> C{key}DataArray;\n"
  vk_struct_storage_h.write(content_nondisp)
  content_disp = ""
  for key in vulkan_mapped_types:
    content_disp += f"    typedef CSimpleMappedData<{key}> C{key}Data;\n"
    content_disp += f"    typedef CDataArray<{key}, C{key}Data> C{key}DataArray;\n"
  vk_struct_storage_h.write(content_disp)

  content_enums = ""
  for key in sorted(enums.keys()):
    for elem in enums[key]:
      content_enums += f"    typedef CSimpleData<{key}> C{key}Data;\n"
      content_enums += f"    typedef CDataArray<{key}, C{key}Data> C{key}DataArray;\n"

  vk_struct_storage_h.write(content_enums)
  while len(declared_structs) < len(structs):

    for key in sorted(structs.keys()):
      if key not in declared_structs:
        to_declare = []
        for elem in structs[key]:
          for var in elem['vars']:
            elem_type = var['type'].rstrip('**').rstrip('*').replace('const ', '') + '_'
            if (elem_type not in declared_structs) and (elem_type in structs.keys()):
              to_declare.append(elem_type)
          if len(to_declare) == 0:
            if elem.get('custom') is not True:
              Ctypes = []
              Cnames = []
              Cwraps = []
              Csize = []
              types = []
              key_name = key.strip('_')
              versioned_name = add_version(key, elem.get('version'))
             # content += "inline void copyVkStruct(" + key.rstrip('_') + "& dst, const " + key.rstrip('_') + " & src)\n{\n"

              for var in elem['vars']:
                Cnames.append('_' + var['name'])
                typename = var['type']
                if var.get('wrapType'):
                  wrapType = ""
                  if '::CSArray' in var['wrapType'] or '::CSMapArray' in var['wrapType']:
                    wrapType = var['wrapType'].replace('::CSArray', 'DataArray').replace('::CSMapArray', 'DataArray')
                  elif 'Array' in var['wrapType']:
                    wrapType = var['wrapType'].replace('Array', 'DataArray')
                  else:
                    wrapType = var['wrapType'] + 'Data'
                  Ctypes.append(wrapType)
                elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types_nondisp and '*' in typename and 'const' not in typename:
                  typename_mod = typename.replace('const ', '').replace('*', '').replace(' ', '')
                  Ctypes.append('C' + typename_mod + 'DataArray')
                elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types and '*' in typename and 'const' not in typename:
                  typename_mod = typename.replace('const ', '').replace('*', '').replace(' ', '')
                  Ctypes.append('C' + typename_mod + 'DataArray')
                elif typename.replace('const ', '').strip(' *') in vulkan_uint32:
                  Ctypes.append('Cuint32_tData')
                elif typename.replace('const ', '').strip(' *') in vulkan_uint64:
                  Ctypes.append('Cuint64_tData')
                elif '*' in typename and typename.replace('const ', '').strip(' *') == 'void' and var['name'] == 'pNext':
                  Ctypes.append('CpNextWrapperData')
                elif '*' in typename and typename.replace('const ', '').strip(' *') == 'void':
                  Ctypes.append('CvoidPtrData')
                elif re.search(r'\[([0-9]+)\]', typename.replace('const ', '')):
                  Ctypes.append('C' + re.sub(r'\[([0-9_]+)\]', '', typename.replace('const ', '')) + 'DataArray')
                else:
                  typename_mod = typename.replace('const ', '').replace(' *', '').replace(' ', '')
                  Ctypes.append('C' + typename_mod + 'Data')
                types.append(typename.replace('const ', '').replace(' *', '').replace(' ', ''))

                if var.get('wrapParams'):
                  Cwraps.append(var['wrapParams'])
                else:
                  Cwraps.append('')
                if re.search(r'\[([0-9]+)\]', typename.replace('const ', '')):
                  size = re.findall(r'\[([0-9_]+)\]', typename)
                  Csize.append(size[0])
                else:
                  Csize.append('1')
              key_variable = key_name.replace('Vk', '').lower()
              key_decl = '_' + key_name.replace('Vk', '')
              argd = 'const ' + key_name + '* ' + key_variable
              argd_decl = key_name + '* ' + key_decl

              argsDecl = ""
              for n, t in zip(Cnames, Ctypes):
                argsDecl += '      ' + t + '* ' + n + ';\n'

              counter = 0

              function_delete = ''
              function_operator = ''
              init = ''
              mapped_pointers = '\n  std::set<uint64_t> returnMap;\n  '
              if len(elem['vars']) > 0:
                init = '  if (!*_isNullPtr)  {\n'
                init_to_nullptr = '  } else {\n'
                init_default = ''
                function_operator = 'if (' + key_decl + ' == nullptr)  {\n'
              function_operator += '    ' + key_decl + ' = new ' + key_name + ';\n'
              for n, w, t, s, ot in zip(Cnames, Cwraps, Ctypes, Csize, types):
                if t != 'COutArgument':
                  counter += 1

                  if (ot not in primitive_types):
                    mapped_pointers += 'for (auto obj : ' + n + '->GetMappedPointers())\n    returnMap.insert((uint64_t)obj);\n  '

                  if w == '':
                    struct_type = t[1:].replace("Data", "") + '_'
                    if (struct_type) in structs.keys():
                      init += '    ' + n + ' = new ' + t + '(&' + key_variable + '->' + n.strip('_') + ');\n'
                    elif t[1:].strip(' *') in vulkan_mapped_types_nondisp:
                      init += '    ' + n + ' = new ' + t + '(' + key_variable + '->' + n.strip('_') + ');\n'
                    elif t[1:].strip(' *') in vulkan_mapped_types:
                      init += '    ' + n + ' = new ' + t + '(' + key_variable + '->' + n.strip('_') + ');\n'  # uint64_t cast
                    elif s != '1':
                      init += '    ' + n + ' = new ' + t + '(' + s + ', ' + key_variable + '->' + n.strip('_') + ');\n'
                    else:
                      init += '    ' + n + ' = new ' + t + '(' + key_variable + '->' + n.strip('_') + ');\n'
                  else:
                    init += '    ' + n + ' = new ' + t + '(' + w + ');\n'

                  init_to_nullptr += '    ' + n + ' = nullptr;\n'
                  init_default += n + '(new ' + t + '()), '
                  if s != '1':
                    function_operator += '    auto ' + n.strip('_') + 'Values = **' + n + ';\n'
                    function_operator += '    if (' + n.strip('_') + 'Values != nullptr) {\n'
                    function_operator += '      for (int i = 0; i < ' + s + '; i++)\n'
                    function_operator += '        ' + key_decl + '->' + n.strip('_') + '[i] = ' + n.strip('_') + 'Values[i];\n'
                    function_operator += '    } else {\n'
                    function_operator += '      throw std::runtime_error(EXCEPTION_MESSAGE);\n'
                    function_operator += '    }\n'
                  else:
                    function_operator += '    ' + key_decl + '->' + n.strip('_') + ' = **' + n + ';\n'

                  function_delete += '  delete ' + n + ';\n'

              function_delete += '  delete ' + key_decl + ';\n'
              mapped_pointers += 'return returnMap;'
              if len(elem['vars']) > 0:
                init += init_to_nullptr
                init += '  }'
                function_operator += '  }'
              if counter > 0:
                function_delete = function_delete.strip('\n')
                init_default = init_default.strip(', ')
              else:
                init = ''
              function_operator += '\n  return ' + key_decl + ';'
              key_name_data = versioned_name + "Data"
              if len(elem['vars']) > 0:
                content += """    class C%(name_data)s : public CBaseDataStruct, gits::noncopyable {
%(argsDecl)s
      %(argd_decl)s;
      CboolData _isNullPtr;

    public:
      C%(name_data)s(%(argd)s);
      ~C%(name_data)s();
      %(unversioned_name)s* Value();

      PtrConverter<%(unversioned_name)s> operator*() {
        return PtrConverter<%(unversioned_name)s>(Value());
      }
      void * GetPtrType() override { return (void *)Value(); }
      std::set<uint64_t> GetMappedPointers();
    };
""" % {'unversioned_name': key_name, 'name_data': key_name_data, 'argd': argd, 'argsDecl': argsDecl, 'argd_decl': argd_decl}
                content += "    typedef CDataArray<" + key_name + ", C" + key_name_data + "> C" + key_name_data + "Array;\n\n\n"
                content_cpp += """gits::Vulkan::C%(name_data)s::C%(name_data)s(%(argd)s) : %(key_decl)s(nullptr), _isNullPtr(%(key_variable)s == nullptr) {
%(init)s
}

gits::Vulkan::C%(name_data)s::~C%(name_data)s() {
%(function_delete)s
}

%(unversioned_name)s* gits::Vulkan::C%(name_data)s::Value() {
  if (*_isNullPtr)
    return nullptr;
  %(function_operator)s
}

std::set<uint64_t> gits::Vulkan::C%(name_data)s::GetMappedPointers() {
%(mapped_pointers)s
}

""" % {'unversioned_name': key_name, 'name_data': key_name_data, 'argd': argd, 'init': init, 'function_operator': function_operator, 'function_delete': function_delete, 'key_variable': key_variable, 'key_decl': key_decl, 'mapped_pointers': mapped_pointers}

            declared_structs.append(key)
  vk_struct_storage_cpp.write(content_cpp)
  end_h = """
  } // namespace Vulkan
} // namespace gits
"""
  vk_struct_storage_h.write(content)
  vk_struct_storage_h.write(end_h)


def generate_vulkan_header(enums, structs, functions):
  vk_header = open('vulkanHeader.h', 'w')
  vk_header.write(copyright_header)
  output = ""

  vk_header_include = """#pragma once

#include "vulkan_basic.h"
#ifdef GITS_PLATFORM_WINDOWS
#ifdef BUILD_FOR_CCODE
// If we include windows.h, it includes further headers. One of them defines
// WGL functions which we have already defined ourselves. This breaks OGL and
// OCL CCode. So instead of including windows.h, we just declare the types we
// need from it.
struct _SECURITY_ATTRIBUTES;
typedef _SECURITY_ATTRIBUTES SECURITY_ATTRIBUTES;
#else
#include <windows.h>
#endif  // BUILD_FOR_CCODE
#endif  // GITS_PLATFORM_WINDOWS
"""
  vk_header.write(vk_header_include)
  for key in sorted(enums.keys()):
    for enum in enums[key]:

      if enum['size'] == 64:
        output += "typedef enum " + key + "_ : VkFlags64 {\n"
      else:
        output += "typedef enum " + key + "_ {\n"

      for var in enum['vars']:
        output += "  " + var['name']
        ending = ",\n"

        if int(var['value']) >= 0:
          output += " = " + hex(int(var['value'])).rstrip('L') + ending
        else:
          output += " = -(" + hex(abs(int(var['value']))).rstrip('L') + ")" + ending

      output += "} " + key + ";\n\n"

  for key in sorted(structs.keys()):
    struct = structs[key][0]  # 0 because we only need the base version.
    decl_name = "struct"
    if struct.get('type'):
      decl_name = struct.get('type')
    output += decl_name + " " + key + ";\n"
    output += "typedef " + key + " " + key.rstrip('_') + ";\n\n"
  for key in sorted(functions.keys()):
    function = functions[key][0]  # 0 because we only need the base version.
    output += "typedef " + function['type'] + " (VKAPI_PTR *PFN_" + key + ") ("
    output += arg_decl(function, False, True)
    output += ");\n"
  output += "\n#ifdef VK_PROTOTYPES\n"
  for key in sorted(functions.keys()):
    function = functions[key][0]  # 0 because we only need the base version.
    output += "VKAPI_ATTR " + function['type'] + " VKAPI_CALL " + key + "(\n"
    output += arg_decl(function, True, True)
    output += ");\n\n"
  output += "#endif\n"
  declared_structs = []
  while len(declared_structs) < len(structs):
    for key in sorted(structs.keys()):
      if key not in declared_structs:
        to_declare = []
        struct = structs[key][0]  # 0 because we only need the base version.
        for var in struct['vars']:
          elem_type = var['type'] + '_'
          if (elem_type not in declared_structs) and (elem_type in structs.keys()):
            to_declare.append(elem_type)
        if len(to_declare) == 0:
          if struct.get('type'):
            output += struct.get('type') + " " + key + " {\n"
          else:
            output += "struct " + key + " {\n"
          import re

          for var in struct['vars']:
            var_type = var['type']
            var_name = var['name']
            if re.search(r':([A-Za-z0-9_]+)', var_type):
              bit_field_found = re.search(r':([A-Za-z0-9_]+)', var_type)
              var_type = re.sub(r':([A-Za-z0-9_]+)', '', var_type)
              var_name += bit_field_found.group(0)
            if re.search(r'\[([A-Za-z0-9_]+)\]', var_type):
              tmp = re.search(r'\[([A-Za-z0-9_]+)\]', var_type)
              output += "  " + re.sub(r'\[([A-Za-z0-9_]+)\]', '', var_type) + " " + var_name + "[" + tmp.group(1) + "];\n"
            else:
              output += "  " + var_type + " " + var_name + ";\n"
          output += "}" + ";\n\n"
          declared_structs.append(key)

  vk_header.write(output)
  vk_header.close()


def generate_vulkan_def(functions, def_filename, library_name):
  plugin_def = open(def_filename, 'w')
  header_def = """;====================== begin_copyright_notice ============================
;
; Copyright (C) 2023 Intel Corporation
;
; SPDX-License-Identifier: MIT
;
;====================== end_copyright_notice ==============================

  LIBRARY %(library_name)s
  EXPORTS
""" % {'library_name': library_name}
  plugin_def.write(header_def)
  for key in sorted(functions.keys()):
    if functions[key][0]['level'] == PrototypeLevel:
      continue
    plugin_def.write("    " + key + "\n")

  plugin_def.close()


def generate_layer_json():
  layer_json = open('VkLayer_vulkan_GITS_recorder.json', 'w')

  vulkan_layer_bin = ".\\\\VkLayer_vulkan_GITS_recorder.dll" #Windows
  if sys.platform.lower().startswith('linux'):
    vulkan_layer_bin = "./libVkLayer_vulkan_GITS_recorder.so" #Linux
  contents = """{
    "file_format_version" : "1.1.0",
    "layer" : {
        "name": "VK_LAYER_INTEL_vulkan_GITS_recorder",
        "type": "GLOBAL",
        "library_path": "%(vulkan_layer_bin)s",
        "api_version": "1.3.248",
        "implementation_version": "1",
        "description": "Vulkan layer used to record GITS Vulkan streams"
    }
}
""" % {'vulkan_layer_bin': vulkan_layer_bin}

  layer_json.write(contents)
  layer_json.close()


def generate_prepost(functions):
  prepost_c = open('vulkanPrePostAuto.cpp', 'w')
  prepost_c.write(copyright_header)
  prepost_c_include = """
#include "vulkanRecorderWrapper.h"
#include "gitsPluginVulkan.h"
#include "log.h"
#include "exception.h"
#include "vulkanExecWrap.h"
"""
  prepost_c.write(prepost_c_include)
  prepost_c_static = """
namespace {
  boost::recursive_mutex globalMutex;
} // namespace

using namespace gits::Vulkan;

void thread_tracker() {
  static std::map<boost::thread::id, int> threadIdMap;
  static int currentThreadId = 0;
  static int generatedThreadId = 0;

  //Add thread to map if not mapped
  if (threadIdMap.find(boost::this_thread::get_id()) == threadIdMap.end()) {
    threadIdMap[boost::this_thread::get_id()] = generatedThreadId;
    generatedThreadId++;
  }

  //If thread changed schedule thread change
  if (currentThreadId != threadIdMap[boost::this_thread::get_id()]) {
    currentThreadId = threadIdMap[boost::this_thread::get_id()];
    Log(TRACE) << "ThreadID: " << currentThreadId;
  }
}

namespace {
  // Avoid recording API - recursive functions.
  uint32_t recursionDepth = 0;
  const uint32_t disableDepth = 1000;
} // namespace

void PrePostDisableVulkan() {
  recursionDepth = disableDepth;
  CGitsPluginVulkan::_recorderFinished = true;
}

void EndFramePost() {
  CGitsPluginVulkan::RecorderWrapper().EndFramePost();
}

void CloseRecorderIfRequired() {
  CGitsPluginVulkan::RecorderWrapper().CloseRecorderIfRequired();
}

#define VKATTRIB

#define GITS_WRAPPER_PRE                                            \\
  --recursionDepth;                                                 \\
  if (CGitsPluginVulkan::Configuration().recorder.basic.enabled) {  \\
    if (recursionDepth == 0) {                                      \\
      try {

#define GITS_WRAPPER_POST                                           \\
        CloseRecorderIfRequired();                                  \\
      }                                                             \\
      catch (...) {                                                 \\
        topmost_exception_handler(__FUNCTION__);                    \\
      }                                                             \\
    }                                                               \\
  }

#define GITS_ENTRY                                                  \\
  ++recursionDepth;                                                 \\
  thread_tracker();                                                 \\
  IRecorderWrapper& wrapper = CGitsPluginVulkan::RecorderWrapper();

#define GITS_MUTEX boost::unique_lock<boost::recursive_mutex> lock(globalMutex);
#define GITS_ENTRY_VK GITS_MUTEX GITS_ENTRY
"""
  extern_str = "\nextern \"C\" {\n"
  prepost_c_static += extern_str
  prepost_c.write(prepost_c_static)

  interceptorExportedFunctions = ""

  for function_name in sorted(functions.keys()):
    function = functions[function_name][0]  # 0 because we only need the base version.
    if function['level'] == PrototypeLevel:
      continue

    interceptorExportedFunctions += "  {\"" + function_name + "\", (PFN_vkVoidFunction)" + function_name + "},\n"

    return_type = function['type']
    function_arguments = arg_decl(function, False, True)
    stored_value = "auto return_value = "
    success_value = "return_value, "
    function_call = "wrapper.Drivers()."
    function_arguments_call = arg_call(function, False, True)
    returned_value = "return return_value;"

    if (function.get('recExecWrap') is True):
      function_call = "recExecWrap_"
    if (return_type == "void"):
      stored_value = ""
      success_value = ""
      returned_value = ""

    function_pre_call = "\n  " + stored_value + function_call + function_name + "(" + function_arguments_call + ");"
    function_post_call = ""

    if (function.get('execPostRecWrap') is True):
      function_post_call = function_pre_call
      function_pre_call = ""
      if (return_type != "void"):
        success_value = "VK_SUCCESS, "
    if (function.get('endFrameTag') is True):
      function_post_call += "\n  EndFramePost();"

    gits_plugin_initialization = ""
    if function['level'] == GlobalLevel:
      gits_plugin_initialization = "CGitsPluginVulkan::Initialize();"
    func_def = f"\nVKATTRIB VISIBLE {return_type} VKAPI_CALL {function_name}({function_arguments}) {{\n"
    func_body = (
      f"  GITS_ENTRY_VK{function_pre_call}\n"
      f"  GITS_WRAPPER_PRE\n"
      f"  wrapper.{function_name}({success_value}{function_arguments_call});\n"
      f"  GITS_WRAPPER_POST{function_post_call}"
      )
    if gits_plugin_initialization:
      func_body = f"  {gits_plugin_initialization}\n{func_body}"
    if returned_value:
      func_body = f"{func_body}\n  {returned_value}"
    content = f"{func_def}{func_body}\n}}\n"
    prepost_c.write(content)

  content = """}

const std::unordered_map<std::string, PFN_vkVoidFunction> interceptorExportedFunctions = {
%(interceptorExportedFunctions)s};
""" % {'interceptorExportedFunctions': interceptorExportedFunctions}
  prepost_c.write(content)

  prepost_c.close()


def generate_vulkan_tokens(functions):
  tokens_h = open('vulkanFunctions.h', 'w')
  tokens_c = open('vulkanFunctions.cpp', 'w')
  tokens_h.write(copyright_header)
  tokens_c.write(copyright_header)

  tokens_c_include = """#include "vulkanFunctions.h"
#include "vulkanPlayerRunWrap.h"
#include "vulkanStateTracking.h"
"""
  tokens_h_include = """#pragma once

#include <array>

#include "vkFunction.h"
#include "vulkanArgumentsAuto.h"

namespace gits {
  namespace Vulkan{
    using std::uint64_t;
"""
  tokens_c.write(tokens_c_include)
  tokens_h.write(tokens_h_include)
  for key in sorted(functions.keys()):
    for elem in functions[key]:
      Ctypes = []
      Cnames = []
      Cwraps = []
      types = []
      counter = 0
      versioned_name = add_version(key, elem.get('version'))
      if elem['custom'] is not True:
        if (elem['type'] != 'void'):
          Cnames.append('_return_value')
          typename = elem['type']
          if elem.get('retVwrapType'):
            Ctypes.append(elem.get('retVwrapType'))
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types_nondisp and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('*', '').replace('const ', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('*', '').replace('const ', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '') in vulkan_uint32:
            Ctypes.append('Cuint32_t')
          elif typename.replace('const ', '') in vulkan_uint64:
            Ctypes.append('Cuint64_t')
          elif '*' in typename and typename.replace('const ', '').strip(' *') == 'void' and arg['name'] == 'pNext':
            Ctypes.append('CpNextWrapper')
          else:
            Ctypes.append('C' + typename.replace('const ', ''))
          types.append(typename.replace('*', '').replace('const ', '').replace(' ', ''))
          if (elem.get('retVwrapParams')):
            Cwraps.append(elem.get('retVwrapParams'))
          else:
            Cwraps.append('')

        remove_mapping = ""
        for arg in elem['args']:
          Cnames.append('_' + arg['name'])
          typename = arg['type']#.strip(' *')
          if arg.get('removeMapping') is True:
            remove_mapping += "\n  %(name)s.RemoveMapping();" % {'name': '_' + arg['name']}
          if arg.get('wrapType'):
            Ctypes.append(arg['wrapType'])
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types_nondisp and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('*', '').replace('const ', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('*', '').replace('const ', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '') in vulkan_uint32:
            Ctypes.append('Cuint32_t')
          elif typename.replace('const ', '') in vulkan_uint64:
            Ctypes.append('Cuint64_t')
          elif '*' in typename and typename.replace('const ', '').strip(' *') == 'void' and arg['name'] == 'pNext':
            Ctypes.append('CpNextWrapper')
          elif '*' in typename and typename.replace('const ', '').strip(' *') not in structs_names:
            typename_mod = typename.replace('const ', '').strip(' *')
            Ctypes.append('C' + typename_mod + '::CSArray')
          else:
            typename_mod = typename.replace('const ', '').strip(' *')
            Ctypes.append('C' + typename_mod)
          types.append(typename.replace('*', '').replace('const ', '').replace(' ', ''))
          if arg.get('wrapParams'):
            Cwraps.append(arg['wrapParams'])
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types_nondisp and '*' in typename and 'const' not in typename:
            Cwraps.append('1, ' + arg['name'])
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types and '*' in typename and 'const' not in typename:
            Cwraps.append('1, ' + arg['name'])  # uint64_t cast
          elif typename.replace('const ', '').strip(' ') in vulkan_mapped_types_nondisp and '*' not in typename:
            Cwraps.append(arg['name'])
          elif typename.replace('const ', '').strip(' ') in vulkan_mapped_types and '*' not in typename:
            Cwraps.append(arg['name'])  # uint64_t cast
          else:
            Cwraps.append('')
          counter += 1
        func = elem
        argd = arg_decl(elem)

        argsDecl = ""
        for n, t in zip(Cnames, Ctypes):
          argsDecl += '      ' + t + ' ' + n + ';\n'

        def undecorate(type):
          # type: (str) -> str
          """Strip the type to its core, e.g. const float* to just float."""
          return type.replace('const ', '', 1).strip('* ')

        argInfos = ""
        wrapTypes = list(Ctypes)
        # Remove retval if present so the arguments match their wraps.
        try:
          wrapTypes.remove('CVkResult')
        except ValueError:
          pass
        for arg, wraptype in zip(elem['args'], wrapTypes):
          typename = arg['type']
          numPtr = typename.count('*')
          needs_ampersand = 'false'

          argInfos += '{ gits::Vulkan::ArgType::'
          if undecorate(typename) in opaque_handles:
            argInfos += 'OPAQUE_HANDLE'
          elif undecorate(typename) in enums_table:
            argInfos += 'ENUM'
          elif undecorate(typename) in primitive_types:
            argInfos += 'PRIMITIVE_TYPE'
            if (undecorate(typename) in vulkan_union) and (numPtr == 1):
              needs_ampersand = 'true'
          elif undecorate(typename) in vulkan_structs:
            argInfos += 'STRUCT'
            if not wraptype.endswith('Array'):
              needs_ampersand = 'true'
          elif 'void*' in typename:
            argInfos += 'OTHER'  # void* or void**
          else:
            argInfos += 'OTHER'
            print("Warning: type \"" + typename + "\" is of unknown category.")

          argInfos += ', ' + str(numPtr) + ', ' + needs_ampersand + ' }, // ' + typename + ' (' + wraptype + ')\n  '
        argInfos = argInfos.strip('\n ')

        argsCall = ""
        argsCallOrig = ""
        wrapCall = ""
        stateTrackCall = ""
        for n in Cnames:
          if n != '_return_value':
            argsCall += '*' + n + ', '
            argsCallOrig += n + '.Original(), '
          wrapCall += n + ', '
          stateTrackCall += '*' + n + ', '
        argsCall = argsCall.strip(', ')
        argsCallOrig = argsCallOrig.strip(', ')
        wrapCall = wrapCall.strip(', ')
        stateTrackCall = stateTrackCall.strip(', ')

        c = ""
        inherit_type = 'CFunction'
        run_name = 'Run'
        if func.get('functionType') & QueueSubmit:
          inherit_type = 'CQueueSubmitFunction'
          run_name = 'RunImpl'
        elif func.get('functionType') & CreateImage:
          inherit_type = 'CImageFunction'
          run_name = 'RunImpl'
        if func.get('functionType') & CreateBuffer:
          inherit_type = 'CBufferFunction'
          run_name = 'RunImpl'
        return_override = ""
        if func['type'] != 'void':
          return_override = "\n      virtual MaybeConstCArgRef Return() const { return (stream_older_than(GITS_VULKAN_RETURN_VALUE_FIX) && Config::IsPlayer()) ? CFunction::Return() : _return_value; }"

        ccodePostActionNeeded = ""
        if func.get('ccodePostActionNeeded') is False:
          ccodePostActionNeeded = "\n      virtual bool CCodePostActionNeeded() const override { return false; }"

        suffix = ""
        if func.get('ccodeWrap') is True:
          suffix = "\n      virtual const char* Suffix() const { return \"_CCODEWRAP\"; }"

        write_wrap_decl = ""
        write_wrap_def = ""
        if func.get('ccodeWriteWrap') is True:
          write_wrap_decl += '\n      virtual void Write(CCodeOStream& stream) const override;'
          write_wrap_decl += '\n      friend void C' + versioned_name + '_CCODEWRITEWRAP(CCodeOStream& stream, const C' + versioned_name + '& function);'
          write_wrap_def += '\n\nvoid gits::Vulkan::C' + versioned_name + '::Write(CCodeOStream& stream) const {'
          write_wrap_def += '\n  stream.select(stream.selectCCodeFile());'
          write_wrap_def += '\n  C' + versioned_name + '_CCODEWRITEWRAP(stream, *this);'
          write_wrap_def += '\n}'
          if func.get('ccodeWrap') is True:
            raise RuntimeError("If ccodeWriteWrap is enabled, ccodeWrap does "
                               "not do anything. Having both enabled "
                               "indicates a logic error.")

        if len(func['args']) > 0 or func['type'] != 'void':
          c = """
    class C%(versioned_name)s : public %(inherit_type)s, gits::noncopyable {
%(argsDecl)s
      virtual CArgument &Argument(unsigned idx) override;
      static const std::array<ArgInfo, %(argc)s> argumentInfos_;
      virtual ArgInfo ArgumentInfo(unsigned idx) const override;
      virtual unsigned ArgumentCount() const override { return %(argc)s; }%(return_override)s

    public:
      C%(versioned_name)s();
      C%(versioned_name)s(%(argd)s);
      virtual unsigned Id() const override { return %(id)s; }
      virtual unsigned Type() const { return %(type)s;}
      virtual const char *Name() const override { return "%(unversioned_name)s"; }%(suffix)s%(ccodePostActionNeeded)s
      virtual void %(run_name)s() override;%(write_wrap_decl)s
      virtual void Exec();
      virtual void StateTrack();
      virtual void RemoveMapping();
      virtual std::set<uint64_t> GetMappedPointers();
      virtual void TokenBuffersUpdate();
    };""" % {'unversioned_name': key, 'versioned_name': versioned_name, 'return_override': return_override, 'id': make_id(key, func['version']), 'argc': len(func['args']), 'argd': argd, 'argsDecl': argsDecl, 'inherit_type': inherit_type, 'run_name': run_name, 'write_wrap_decl': write_wrap_decl, 'suffix': suffix, 'ccodePostActionNeeded': ccodePostActionNeeded, 'type': make_type(func)}
        else:
          c = """
    class C%(versioned_name)s : public %(inherit_type)s, gits::noncopyable {
%(argsDecl)s
      virtual CArgument &Argument(unsigned idx) override;
      static const std::array<ArgInfo, %(argc)s> argumentInfos_;
      virtual ArgInfo ArgumentInfo(unsigned idx) const override;
      virtual unsigned ArgumentCount() const override { return %(argc)s; }

    public:
      C%(versioned_name)s();
      virtual unsigned Id() const override { return %(id)s; }
      virtual unsigned Type() const { return %(type)s;}
      virtual const char *Name() const override { return "%(unversioned_name)s"; }%(suffix)s
      virtual void %(run_name)s() override;%(write_wrap_decl)s
      virtual void Exec();
      virtual void StateTrack();
      virtual void RemoveMapping();
      virtual std::set<uint64_t> GetMappedPointers();
      virtual void TokenBuffersUpdate();
    };""" % {'unversioned_name': key, 'versioned_name': versioned_name, 'id': make_id(key, func['version']), 'argc': len(func['args']), 'argsDecl': argsDecl, 'inherit_type': inherit_type, 'run_name': run_name, 'write_wrap_decl': write_wrap_decl, 'suffix': suffix, 'type': make_type(func)}
        tokens_h.write(c + '\n')

        cargument = 'return get_cargument(__FUNCTION__, idx, '
        count = 0
        for arg in Cnames:
          if (arg != '_return_value'):
            cargument += arg + ', '
            count = count + 1
        cargument = cargument.strip(', ')
        cargument += ');'
        if (count == 0):
          cargument = 'report_cargument_error(__FUNCTION__, idx);'
        init = ''
        if len(func['args']) > 0 or func['type'] != 'void':
          init = ':\n  '
        mapped_pointers = '\n  std::set<uint64_t> returnMap;\n  '
        counter = 0
        for n, w, t, o in zip(Cnames, Cwraps, Ctypes, types):
          if t != 'COutArgument':
            counter += 1
            if (o not in primitive_types):
              mapped_pointers += 'for (auto obj : ' + n + '.GetMappedPointers())\n    returnMap.insert((uint64_t)obj);\n  '
            if w == '':
              init += n + '(' + n.strip('_') + '), '
            else:
              init += n + '(' + w + '), '
        if counter > 0:
          init = init.strip(', ')
        else:
          init = ''
        mapped_pointers += 'return returnMap;'

        run_cmd = """Exec();
  StateTrack();
  RemoveMapping();"""
        if func.get('runWrap') is True:
          run_cmd = "%(name)s_WRAPRUN(%(wrapCall)s);" % {'name': func.get('runWrapName'), 'wrapCall': wrapCall}
        exec_cmd = "drvVk.%(name)s(%(argsCall)s)" % {'name': key, 'argsCall': argsCall}
        state_track = ""
        if func.get('stateTrack') is True:
          state_track = "\n  %(name)s_SD(%(argsCall)s);" % {'name': func.get('stateTrackName'), 'argsCall': stateTrackCall}
        return_value = ""
        return_value_end = ";"
        if func.get('type') not in ('void', 'VkDeviceAddress'):
          return_value = "_return_value.Assign("
          return_value_end = ");"
        token_buff_update = ""
        if func.get('tokenCache') is not None:
          token_buff_update = "\n  SD()._commandbufferstates[*_commandBuffer]->tokensBuffer.Add(new C%(name)s(%(argsCallOrig)s));" % {'name': versioned_name, 'argsCallOrig': argsCallOrig}
          if func.get('runWrap') is not True:
            run_cmd = """if (Config::Get().player.execCmdBuffsBeforeQueueSubmit) {
    TokenBuffersUpdate();
  } else {
    Exec();
    StateTrack();
    RemoveMapping();
  }"""
        c = ""
        if len(func['args']) > 0 or func['type'] != 'void':
          c = """
/* ***************************** %(id)s *************************** */

const std::array<gits::Vulkan::ArgInfo, %(argc)s> gits::Vulkan::C%(versioned_name)s::argumentInfos_ = {{
  %(argInfos)s
}};

gits::Vulkan::C%(versioned_name)s::C%(versioned_name)s()
{
}


gits::Vulkan::C%(versioned_name)s::C%(versioned_name)s(%(argd)s)%(init)s
{
}

gits::CArgument &gits::Vulkan::C%(versioned_name)s::Argument(unsigned idx)
{
  %(cargument)s
}

gits::Vulkan::ArgInfo gits::Vulkan::C%(versioned_name)s::ArgumentInfo(unsigned idx) const
{
  return argumentInfos_[idx];
}

std::set<uint64_t> gits::Vulkan::C%(versioned_name)s::GetMappedPointers()
{%(mapped_pointers)s
}

void gits::Vulkan::C%(versioned_name)s::%(run_name)s()
{
  %(run_cmd)s
}

void gits::Vulkan::C%(versioned_name)s::Exec()
{
  %(return_value)s%(exec_cmd)s%(return_value_end)s
}

void gits::Vulkan::C%(versioned_name)s::StateTrack()
{%(state_track)s
}

void gits::Vulkan::C%(versioned_name)s::TokenBuffersUpdate()
{%(token_buff_update)s
}

void gits::Vulkan::C%(versioned_name)s::RemoveMapping()
{%(remove_mapping)s
}%(write_wrap_def)s""" % {'id': make_id(key, func['version']), 'versioned_name': versioned_name, 'cargument': cargument, 'argc': len(func['args']), 'argd': argd, 'argInfos': argInfos, 'init': init, 'run_name': run_name, 'write_wrap_def': write_wrap_def, 'mapped_pointers': mapped_pointers, 'exec_cmd': exec_cmd, 'state_track': state_track, 'return_value': return_value, 'return_value_end': return_value_end, 'remove_mapping': remove_mapping, 'run_cmd': run_cmd, 'token_buff_update': token_buff_update}
        else:
          c = """
/* ***************************** %(id)s *************************** */

const std::array<gits::Vulkan::ArgInfo, %(argc)s> gits::Vulkan::%(versioned_name)s::argumentInfos_ = {{
  %(argInfos)s
}};

gits::Vulkan::C%(versioned_name)s::C%(versioned_name)s()
{
}

gits::CArgument &gits::Vulkan::C%(versioned_name)s::Argument(unsigned idx)
{
  %(cargument)s
}

gits::Vulkan::ArgInfo gits::Vulkan::C%(versioned_name)s::ArgumentInfo(unsigned idx) const
{
  return argumentInfos_[idx];
}

std::set<uint64_t> gits::Vulkan::C%(versioned_name)s::GetMappedPointers()
{%(mapped_pointers)s
}

void gits::Vulkan::C%(versioned_name)s::%(run_name)s()
{
  %(run)s
}%(write_wrap_def)s""" % {'id': make_id(key, func['version']), 'versioned_name': versioned_name, 'cargument': cargument, 'argc': len(func['args']), 'argInfos': argInfos, 'run': run, 'run_name': run_name, 'write_wrap_def': write_wrap_def, 'mapped_pointers': mapped_pointers}
        tokens_c.write(c + '\n')
  tokens_h_end = """  } // namespace Vulkan
} // namespace gits
"""
  tokens_h.write(tokens_h_end)
  tokens_h.close()
  tokens_c.close()


def generate_vulkan_recorder_wrapper(functions):
  wrap_h = open('vulkanRecorderWrapperAuto.h', 'w')
  wrap_c = open('vulkanRecorderWrapperAuto.cpp', 'w')
  wrap_i = open('vulkanRecorderWrapperIfaceAuto.h', 'w')
  wrap_h.write(copyright_header)
  wrap_c.write(copyright_header)
  wrap_i.write(copyright_header)

  wrap_c_include = """#include "vulkanRecorderWrapper.h"
#include "vulkanRecorderSubwrappers.h"

namespace gits {
namespace Vulkan {
"""
  wrap_c.write(wrap_c_include)
  for key in sorted(functions.keys()):
    value = functions[key][-1]
    if value.get('custom') is not True:
      if (value.get('enabled') is True) or (value.get('recWrap') is True):
        wrapper_pre_post = ""
        if value.get('functionType') & QueueSubmit:
          wrapper_pre_post = "QUEUE_SUBMIT_WRAPPER_PRE_POST\n  "
        elif value.get('functionType') & CreateImage:
          wrapper_pre_post = "CREATE_IMAGE_WRAPPER_PRE_POST\n  "
        elif value.get('functionType') & CreateBuffer:
          wrapper_pre_post = "CREATE_BUFFER_WRAPPER_PRE_POST\n  "
        pre_token = ""
        if value.get('preToken') is not None and (value.get('recWrap') is not True) and value.get('preToken') is not False:
          pre_token = "_recorder.Schedule(new %(name)s);\n    " % {'name': value.get('preToken')}
        pre_schedule = ""
        if value.get('preSchedule') is not None and (value.get('recWrap') is not True) and value.get('preSchedule') is not False:
          pre_schedule = "%(name)s;\n    " % {'name': value.get('preSchedule')}
        post_token = ""
        if value.get('postToken') is not None and (value.get('recWrap') is not True):
          post_token = "\n    _recorder.Schedule(new %(name)s);\n" % {'name': value.get('postToken')}
        rec_cond = ""
        if value.get('recCond') and (value.get('recWrap') is not True):
          rec_cond = "if (%(recCond)s) {" % {'recCond': value.get('recCond')}
        elif (value.get('recCond') is not True) and (value.get('tokenCache') is not None) and (value.get('recWrap') is not True):
          rec_cond = "if (_recorder.Running() && !Config::Get().recorder.vulkan.utilities.scheduleCommandBuffersBeforeQueueSubmit) {"
        elif (value.get('recCond') is not True) and (value.get('recWrap') is not True):
          rec_cond = "if (_recorder.Running()) {"
        state_track = ""
        rec_cond_end = ""
        new_line = ""
        if value.get('stateTrack') is True and (value.get('recWrap') is not True):
          state_track = "\n  %(name)s_SD(%(argsCall)s);" % {'name': value.get('stateTrackName'), 'argsCall': arg_call(value)}
        rec_wrap = ""
        if (value.get('recWrap') is True):
          rec_wrap = "%(name)s_RECWRAP(%(argsCall)s, _recorder);" % {'name': value.get('recWrapName'), 'argsCall': arg_call(value)}
        else:
          rec_cond_end = "\n  }"
          new_line = "\n    "
        schedule = ""
        versioned_name = add_version(key, value.get('version'))

        if (value.get('recWrap') is not True):
          schedule = "_recorder.Schedule(new C%(name)s(%(arg_call)s));" % {'name': versioned_name, 'arg_call': arg_call(value)}
        tokenCache = ""
        if (value.get('tokenCache') is not None) and (value.get('recWrap') is not True):
          tokenCache = " else {\n    " + value.get('tokenCache')
          tokenCache += ".Add(new C%(name)s(%(arg_call)s));" % {'name': versioned_name, 'arg_call': arg_call(value)}
          tokenCache += "\n  }"
        wc = """
void CRecorderWrapper::%(name)s(%(arg_decl)s) const
{
  %(wrapper_pre_post)s%(rec_cond)s%(rec_wrap)s%(new_line)s%(pre_schedule)s%(pre_token)s%(schedule)s%(post_token)s%(rec_cond_end)s%(tokenCache)s%(state_track)s
}""" % {'name': key, 'arg_decl': arg_decl(value), 'pre_schedule': pre_schedule, 'pre_token': pre_token, 'post_token': post_token, 'rec_cond': rec_cond, 'state_track': state_track, 'rec_wrap': rec_wrap, 'schedule': schedule, 'tokenCache': tokenCache, 'rec_cond_end': rec_cond_end, 'wrapper_pre_post': wrapper_pre_post, 'new_line': new_line}
        wrap_c.write(wc + '\n')
        wrap_h.write('void ' + key + '(' + arg_decl(value) + ') const override;\n')
        wrap_i.write('virtual void ' + key + '(' + arg_decl(value) + ') const = 0;\n')
      else:
        wc = """
void CRecorderWrapper::%(name)s(%(arg_decl)s) const
{
  CALL_ONCE [] { Log(ERR) << "function %(name)s not implemented"; };
}""" % {'name': key, 'arg_decl': arg_decl(value)}
        wrap_c.write(wc + '\n')
        wrap_h.write('void ' + key + '(' + arg_decl(value) + ') const override;\n')
        wrap_i.write('virtual void ' + key + '(' + arg_decl(value) + ') const = 0;\n')
  wrap_c.write('} // namespace Vulkan\n} // namespace gits\n')


def generate_vulkan_arguments(structs, enums_dict):
  arguments_h = open('vulkanArgumentsAuto.h', 'w')
  arguments_cpp = open('vulkanArgumentsAuto.cpp', 'w')
  arguments_h.write(copyright_header)
  arguments_cpp.write(copyright_header)
  arguments_h_include = """#pragma once

#include "vulkanArgumentsBasic.h"

namespace gits {
namespace Vulkan {
"""
  arguments_h_end = """
} // namespace Vulkan
} // namespace gits
"""
  arguments_cpp_include = """
#include "vulkanArgumentsAuto.h"
"""
  arguments_cpp.write(arguments_cpp_include)
  arguments_h.write(arguments_h_include)

  enums_decls = ''
  enums_defs = ''
  for name, enums in sorted(enums_dict.items()):
    for enum in enums:
      enums_decls += '    typedef CVulkanEnum<' + name + '> C' + name + ';\n'
      enums_decls += '    template<>\n'
      enums_decls += '    class CVulkanEnumTypeTraits<' + name + '> {\n'
      enums_decls += '    public:\n'
      enums_decls += '      static const char* Name();\n'
      enums_decls += '      static std::string GetVariantName(' + name + ' variant);\n'
      enums_decls += '    };\n\n'

      enums_defs += 'const char* gits::Vulkan::CVulkanEnumTypeTraits<' + name + '>::Name() {\n'
      enums_defs += '  return "' + name + '";\n'
      enums_defs += '}\n'
      enums_defs += 'std::string gits::Vulkan::CVulkanEnumTypeTraits<' + name + '>::GetVariantName(' + name + ' variant) {\n'
      enums_defs += '  switch (variant) {\n'

      for variant in enum['vars']:
        if enum['size'] == 64:
          enums_defs += '  case ' + name + "::" + variant['name'] + ':\n'
        else:
          enums_defs += '  case ' + variant['name'] + ':\n'
        enums_defs += '    return "' + variant['name'] + '";\n'

      enums_defs += '  default:\n'
      enums_defs += '    Log(WARN) << "Unknown enum variant: " << variant << " of ' + name + '";\n'
      enums_defs += '    return "(' + name + ')" + std::to_string((int)variant);\n'
      enums_defs += '  }\n'
      enums_defs += '}\n\n'

  arguments_h.write(enums_decls)
  arguments_cpp.write(enums_defs)

  mapped_decls = '''
    // On 32-bit, all nondispatchable handle types are typedef'd to uint64_t.
    // This means compiler sees e.g. CVulkanObj<VkBuffer> as identical to
    // CVulkanObj<VkEvent>. On the other hand type tags below are seen by the
    // compiler as distinct types. We use them to instantiate the template for
    // each handle type.\n'''
  mapped_defs = ''
  for name in sorted(vulkan_mapped_types) + sorted(vulkan_mapped_types_nondisp):
    mapped_decls += '    typedef struct ' + name + '_T* ' + name + 'TypeTag;\n'
    mapped_decls += '    typedef CVulkanObj<' + name + ', ' + name + 'TypeTag> C' + name + ';\n\n'

    mapped_defs += 'template<>\n'
    mapped_defs += 'const char* gits::Vulkan::CVulkanObj<' + name + ', gits::Vulkan::' + name + 'TypeTag>::NAME = "' + name + '";\n\n'
  arguments_h.write(mapped_decls)
  arguments_cpp.write(mapped_defs)

  for key in sorted(structs.keys()):
    for elem in structs[key]:
      key_name = key.strip('_')
      versioned_name = add_version(key, elem.get('version'))
      if elem.get('custom') is not True:
        class_def = "    class C" + versioned_name + ';\n'
        arguments_h.write(class_def)
      if elem.get('declareArray'):
        arguments_h.write('    typedef CStructArray<' + key_name + ', C' + versioned_name + '> C' + versioned_name + 'Array;\n')

  for key in sorted(structs.keys()):
    for elem in structs[key]:
      Ctypes = []
      Cnames = []
      Cwraps = []
      Csize = []
      types = []
      counter = 0
      key_name = key.strip('_')
      versioned_name = add_version(key, elem.get('version'))

      if elem.get('custom') is not True:
        for arg in elem['vars']:
          Cnames.append('_' + arg['name'])
          typename = arg['type']#.strip(' *')
          #typename = typename.replace('const ', '')
          if arg.get('wrapType'):
            Ctypes.append(arg['wrapType'])
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types_nondisp and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('const ', '').replace('*', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '').strip(' *') in vulkan_mapped_types and '*' in typename and 'const' not in typename:
            typename_mod = typename.replace('const ', '').replace('*', '').replace(' ', '')
            Ctypes.append('C'+typename_mod+'::CSArray')
          elif typename.replace('const ', '').strip(' *') in vulkan_uint32:
            Ctypes.append('Cuint32_t')
          elif typename.replace('const ', '').strip(' *') in vulkan_uint64:
            Ctypes.append('Cuint64_t')
          elif '*' in typename and typename.replace('const ', '').strip(' *') == 'void' and arg['name'] == 'pNext':
            Ctypes.append('CpNextWrapper')
          elif re.search(r'\[([0-9]+)\]', typename.replace('const ', '')):
            Ctypes.append('C' + re.sub(r'\[([0-9_]+)\]', '', typename.replace('const ', '')) + '::CSArray')
          else:
            typename_mod = typename.replace('const ', '').replace(' *', '').replace(' ', '')
            Ctypes.append('C' + typename_mod)
          types.append(typename.replace('const ', '').replace(' *', '').replace(' ', ''))
          if arg.get('wrapParams'):
            Cwraps.append(arg['wrapParams'])
          else:
            Cwraps.append('')
          if re.search(r'\[([0-9]+)\]', typename.replace('const ', '')):
            size = re.findall(r'\[([0-9_]+)\]', typename)
            Csize.append(size[0])
          else:
            Csize.append('1')
          counter += 1
        func = elem
        key_variable = key_name.replace('Vk', '').lower()
        key_decl = '_' + key_name.replace('Vk', '')
        key_decl_original = key_decl + 'Original'
        argd = 'const ' + key_name + '* ' + key_variable
        argd_decl = key_name + '* ' + key_decl
        argd_decl_original = key_name + '* ' + key_decl_original

        argsDecl = ""
        for n, t in zip(Cnames, Ctypes):
          argsDecl += '      ' + t + '* ' + n + ';\n'

        argsCall = ""
        counter = 0

        function_read = ''
        function_write = ''
        function_delete = ''
        function_operator = ''
        function_original = ''
        init = ''
        mapped_pointers = '\n  std::set<uint64_t> returnMap;\n  '
        if len(func['vars']) > 0:
          init = '  if (!*_isNullPtr) {\n'
          init_to_nullptr = '  } else {\n'
          init_default = ''
          function_read = '  if (!*_isNullPtr) {\n'
          function_write = '  if (!*_isNullPtr) {\n'
          function_operator = '  if (' + key_decl + ' == nullptr) {\n'
          function_original = '  if (' + key_decl_original + ' == nullptr) {\n'
        function_operator += '    ' + key_decl + ' = new ' + key_name + ';\n'
        function_original += '    ' + key_decl_original + ' = new ' + key_name + ';\n'
        for n, w, t, s, ot in zip(Cnames, Cwraps, Ctypes, Csize, types):
          if t != 'COutArgument':
            counter += 1

            if (ot not in primitive_types):
              mapped_pointers += 'for (auto obj : ' + n + '->GetMappedPointers())\n    returnMap.insert((uint64_t)obj);\n  '

            if w == '':
              struct_type = t[1:] + '_'
              if (struct_type) in structs.keys():
                init += '    ' + n + ' = new ' + t + '(&' + key_variable + '->' + n.strip('_') + ');\n'
              elif s != '1':
                init += '    ' + n + ' = new ' + t + '(' + s + ', ' + key_variable + '->' + n.strip('_') + ');\n'
              else:
                init += '    ' + n + ' = new ' + t + '(' + key_variable + '->' + n.strip('_') + ');\n'
            else:
              init += '    ' + n + ' = new ' + t + '(' + w + ');\n'

            init_to_nullptr += '    ' + n + ' = nullptr;\n'
            init_default += n + '(new ' + t + '()), '
            if s != '1':
              decayed_type = re.sub(r'\[([0-9_]+)\]', '*', ot) # Turn arrays to pointers.
              function_operator += '    ' + decayed_type + ' ' + n.strip('_') + 'Values = **' + n + ';\n'
              function_operator += '    if (' + n.strip('_') + 'Values != nullptr) {\n'
              function_operator += '      for (int i = 0; i < ' + s + '; i++)\n'
              function_operator += '        ' + key_decl + '->' + n.strip('_') + '[i] = ' + n.strip('_') + 'Values[i];\n'
              function_operator += '    } else {\n'
              function_operator += '      throw std::runtime_error(EXCEPTION_MESSAGE);\n'
              function_operator += '    }\n'
              function_original += '    ' + decayed_type + ' ' + n.strip('_') + 'ValuesOriginal = ' + n + '->Original();\n'
              function_original += '    if (' + n.strip('_') + 'ValuesOriginal != nullptr) {\n'
              function_original += '      for (int i = 0; i < ' + s + '; i++)\n'
              function_original += '        ' + key_decl_original + '->' + n.strip('_') + '[i] = ' + n.strip('_') + 'ValuesOriginal[i];\n'
              function_original += '    } else {\n'
              function_original += '      throw std::runtime_error(EXCEPTION_MESSAGE);\n'
              function_original += '    }\n'
            else:
              function_operator += '    ' + key_decl + '->' + n.strip('_') + ' = **' + n + ';\n'
              function_original += '    ' + key_decl_original + '->' + n.strip('_') + ' = ' + n + '->Original();\n'

            function_delete += '  delete ' + n + ';\n'
            function_read += '    ' + n + '->Read(stream);\n'
            function_write += '    ' + n + '->Write(stream);\n'

        function_delete += '  delete ' + key_decl + ';\n'
        function_delete += '  delete ' + key_decl_original + ';\n'
        if len(func['vars']) > 0:
          init += init_to_nullptr
          init += '  }'
          function_read += '  }'
          function_write += '  }'
          function_operator += '  }'
          function_original += '  }'
        if counter > 0:
          function_read = function_read.strip('\n')
          function_write = function_write.strip('\n')
          function_delete = function_delete.strip('\n')
          init_default = init_default.strip(', ')
        else:
          init = ''
        function_operator += '\n  return ' + key_decl + ';'
        function_original += '\n  return PtrConverter<' + key_name + '>(' + key_decl_original + ');'
        mapped_pointers += 'return returnMap;'
        for n in Cnames:
          if n not in ('_return_value', '_self'):
            argsCall += re.sub('[_]', '', n) + ': *' + n + ' '
        argsCall = argsCall.strip(' ')

        # CCode - Write, Declare and DeclarationNeeded methods
        type_name = add_version(key_name, elem.get('version'))
        camel_case_type_name = key_name[0].lower() + key_name[1:]
        # Temporary defines:
        if type_name not in types_not_needing_declaration:
          ampersand_declare = '\n      virtual bool AmpersandNeeded() const override;'
          ampersand_define = 'bool gits::Vulkan::C' + type_name + '::AmpersandNeeded() const {\n'
          ampersand_define += '  return !*_isNullPtr;\n'
          ampersand_define += '}\n'

          decl_declare = '\n      virtual bool DeclarationNeeded() const override { return true; }'
          decl_declare += '\n      virtual void Declare(CCodeOStream &stream) const override;'

          decl_define = 'void gits::Vulkan::C' + type_name + '::Declare(CCodeOStream &stream) const {\n'
          decl_define += '  if (!*_isNullPtr) {\n'

          pre_declarations = ''
          declarations = '\n    stream.Register(ScopeKey(), "' + camel_case_type_name + '", true);\n'
          declarations += '    stream.Indent() << Name() << " " << stream.VariableName(ScopeKey()) << " = {\\n";\n'
          declarations += '    stream.ScopeBegin();\n'
          post_declarations = '\n'
          for cname, ctype, csize in zip(Cnames, Ctypes, Csize):
            if ctype[0] == 'C':
              t = ctype[1:]
            else:
              t = ctype
            # Remove argument version suffix. #TODO: is it needed in Vk?
            t = re.sub(r'_V\d+$', '', t)

            if cname[0] == '_':
              n = cname[1:]
            else:
              n = cname

            if t in types_not_needing_declaration:
              declarations += '    stream.Indent() << *(this->' + cname + ') << ", // ' + n + '\\n";\n'
            else:
              if t in types_needing_name_registration or True:  # TODO: finetune it.
                pre_declarations += '    ' + cname + '->VariableNameRegister(stream, false);\n'

              pre_declarations += '    ' + cname + '->Declare(stream);\n'

              if csize != '1':
                count = ""
                for var in elem['vars']:
                  if ('_' + var['name']) == cname:
                    if 'count' in var.keys():
                      if csize != var['count']:
                        count = " && i < \" << stream.VariableName(ScopeKey()) << \"." + var['count']

                post_declarations += '    stream.Indent() << "for (int i = 0; i < ' + csize + count + '; ++i)\\n";\n'
                post_declarations += '    stream.ScopeBegin(); // For indentation.\n'
                post_declarations += '    stream.Indent() << stream.VariableName(ScopeKey()) << ".' + n + '[i] = " << *' + cname + ' << "[i];\\n";\n'
                post_declarations += '    stream.ScopeEnd();\n'
                declarations += '    stream.Indent() << "{}, // ' + n + '\\n";\n'
              else:
                declarations += '    stream.Indent() << *' + cname + ' << ", // ' + n + '\\n";\n'

          declarations += '    stream.ScopeEnd();\n'
          declarations += '    stream.Indent() << "};\\n";\n'

          decl_define += pre_declarations
          decl_define += declarations
          decl_define += post_declarations
          decl_define += '  }\n'
          decl_define += '}\n'

          function_ccode_write = '  if (*_isNullPtr) {\n'
          function_ccode_write += '    stream << "nullptr";\n'
          function_ccode_write += '  } else {\n'
          function_ccode_write += '    stream << stream.VariableName(ScopeKey());\n'
          #function_ccode_write += '    intptr_t varNameKey = reinterpret_cast<intptr_t>(this);\n'
          #function_ccode_write += '    std::string varName = stream.VariableName(varNameKey);\n'
          #function_ccode_write += '    stream << varName;\n'
          function_ccode_write += '  }'
        else:
          ampersand_declare = ''
          ampersand_define = ''
          decl_declare = ''
          decl_define = ''
          function_ccode_write = '  throw ENotImplemented(EXCEPTION_MESSAGE);'

        c = ""
        inherit_type = 'CArgument'
        if len(func['vars']) > 0:
          c = """
    class C%(versioned_name)s : public %(inherit_type)s, gits::noncopyable {
%(argsDecl)s
      %(argd_decl)s;
      %(argd_decl_original)s;
      Cbool _isNullPtr;

    public:
      C%(versioned_name)s();
      ~C%(versioned_name)s();
      C%(versioned_name)s(%(argd)s);
      static const char* NAME;
      virtual const char* Name() const override { return NAME; }
      %(unversioned_name)s* Value();

      PtrConverter<%(unversioned_name)s> operator*() {
        return PtrConverter<%(unversioned_name)s>(Value());
      }
      PtrConverter<%(unversioned_name)s> Original();
      void * GetPtrType() override { return (void *)Value(); }
      virtual std::set<uint64_t> GetMappedPointers();
      virtual void Write(CBinOStream& stream) const override;
      virtual void Read(CBinIStream& stream) override;
      virtual void Write(CCodeOStream& stream) const override;%(ampersand_declare)s%(decl_declare)s
    };""" % {'versioned_name': versioned_name, 'unversioned_name': key_name, 'argd': argd, 'argsDecl': argsDecl, 'inherit_type': inherit_type, 'argd_decl': argd_decl, 'argd_decl_original': argd_decl_original, 'ampersand_declare': ampersand_declare, 'decl_declare': decl_declare, }
          d = """
gits::Vulkan::C%(versioned_name)s::C%(versioned_name)s(): %(init_default)s, %(key_decl)s(nullptr), %(key_decl_original)s(nullptr), _isNullPtr(false) {
}

gits::Vulkan::C%(versioned_name)s::~C%(versioned_name)s() {
%(function_delete)s
}

gits::Vulkan::C%(versioned_name)s::C%(versioned_name)s(%(argd)s): %(key_decl)s(nullptr), %(key_decl_original)s(nullptr), _isNullPtr(%(key_variable)s == nullptr) {
%(init)s
}

const char* gits::Vulkan::C%(versioned_name)s::NAME = "%(unversioned_name)s";

%(unversioned_name)s* gits::Vulkan::C%(versioned_name)s::Value() {
  if (*_isNullPtr)
    return nullptr;
%(function_operator)s
}

gits::PtrConverter<%(unversioned_name)s> gits::Vulkan::C%(versioned_name)s::Original() {
  if (*_isNullPtr)
    return PtrConverter<%(unversioned_name)s>(nullptr);
%(function_original)s
}

std::set<uint64_t> gits::Vulkan::C%(versioned_name)s::GetMappedPointers() {
%(mapped_pointers)s
}

void gits::Vulkan::C%(versioned_name)s::Write(CBinOStream& stream) const {
  _isNullPtr.Write(stream);
%(function_write)s
}

void gits::Vulkan::C%(versioned_name)s::Read(CBinIStream& stream) {
  _isNullPtr.Read(stream);
%(function_read)s
}

void gits::Vulkan::C%(versioned_name)s::Write(CCodeOStream& stream) const {
%(function_ccode_write)s
}

%(ampersand_define)s
%(decl_define)s
""" % {'versioned_name': versioned_name, 'unversioned_name': key_name, 'argd': argd, 'init': init, 'function_operator': function_operator, 'function_read': function_read, 'function_write': function_write, 'function_ccode_write': function_ccode_write, 'ampersand_define': ampersand_define, 'decl_define': decl_define, 'function_delete': function_delete, 'key_variable': key_variable, 'key_decl': key_decl, 'init_default': init_default, 'function_original': function_original, 'key_decl_original': key_decl_original, 'mapped_pointers': mapped_pointers}

        arguments_h.write(c + '\n')
        arguments_cpp.write(d+'\n')

  arguments_h.write(arguments_h_end)

  arguments_h.close()
  arguments_cpp.close()


def generate_vulkan_create_switch(functions):
  vulkan_function_cpp = open('vulkanIDswitch.h', 'w')
  vulkan_function_cpp.write(copyright_header)
  output = ""
  for key in sorted(functions.keys()):
    for elem in functions[key]:
      output += 'case ' + make_id(key, elem['version']) + ':\n'
      versioned_name = add_version(key, elem['version'])
      output += '  return new C' + versioned_name + ';\n'
  vulkan_function_cpp.write(output)
  vulkan_function_cpp.close()


def generate_vulkan_function_ids_header(functions):
  vulkan_functions_generated = open('vulkanIDs.h', 'r')
  functions_ids = []
  try:
    for line in vulkan_functions_generated:
      elem = line.strip(",\n")
      if 'ID' in elem:
        functions_ids.append(elem)
  finally:
    vulkan_functions_generated.close()

  vulkanfunction_h = open('vulkanIDs.h', 'a')
  generated_id = ""
  for key in sorted(functions.keys()):
    for func in functions[key]:
      if make_id(key, func['version']) not in functions_ids:
        generated_id += make_id(key, func['version']) + ',\n'

  vulkanfunction_h.write(generated_id)
  vulkanfunction_h.close()


def generate_vulkan_lua_enums(enums):
  vulkan_enums_lua_generated = open('vulkanLuaEnums.h', 'w')
  vulkan_enums_lua_generated.write(copyright_header)
  output = ""
  for key in sorted(enums.keys()):
    for elem in enums[key]:
      output += "template<> inline " + key + " lua_to(lua_State* L, int pos) { return static_cast<" + key + ">(lua_tointeger(L, pos)); }\n"
  vulkan_enums_lua_generated.write(output)
  vulkan_enums_lua_generated.close()


def generate_vulkan_ccode_arguments():
  arguments_h = open('vulkanCCodeArgumentsAuto.h', 'w')
  arguments_h.write(copyright_header)
  arguments_h_include = """#pragma once

namespace gits {
namespace Vulkan {
"""
  arguments_h_end = """
} // namespace Vulkan
} // namespace gits
"""
  arguments_h.write(arguments_h_include)

  mapped_decls = ''
  for name in sorted(vulkan_mapped_types) + sorted(vulkan_mapped_types_nondisp):
    mapped_decls += '    typedef CVulkanObj<' + name + '> C' + name + ';\n'
  arguments_h.write(mapped_decls)
  arguments_h.write(arguments_h_end)


enums = GetEnums()
functions = GetFunctions()
structs = GetStructs()

enums_table = {}
structs_table = {}
structs_enabled_table = {}
functions_all_table = {}
functions_enabled_table = {}

for e in enums:
  enum = {}
  enum['vars'] = []
  enum['size'] = 32
  if e.get('size') is not None:
    enum['size'] = int(e.get('size'))
  i = 1

  for enumerator in e.get('enumerators'):
    var = {}
    var['name'] = enumerator.get('name')
    var['value'] = enumerator.get('value')
    enum['vars'].append(var)
    i += 1
  if enums_table.get(e.get('name')) is None:
    enums_table[e.get('name')] = []
  enums_table[e.get('name')].append(enum)

for s in structs:
  struct = {}
  struct['enabled'] = s.get('enabled')
  if s.get('name').strip('_') not in structs_names:
    structs_names.append(s.get('name').strip('_'))
  if (s.get('type')):
    struct['type'] = s.get('type')
  if (s.get('custom')):
    struct['custom'] = s.get('custom')
  if (s.get('declareArray')):
    struct['declareArray'] = s.get('declareArray')
  if (s.get('version')):
    struct['version'] = s.get('version')
  else:
    struct['version'] = 0
  struct['vars'] = []
  i = 1
  while s.get('var'+str(i)):
    var = {}
    var['name'] = s.get('var'+str(i)).get('name')
    var['type'] = s.get('var'+str(i)).get('type')
    if(s.get('var'+str(i)).get('wrapType')):
      var['wrapType'] = s.get('var'+str(i)).get('wrapType')
    if(s.get('var'+str(i)).get('wrapParams')):
      var['wrapParams'] = s.get('var'+str(i)).get('wrapParams')
    if(s.get('var'+str(i)).get('count')):
      var['count'] = s.get('var'+str(i)).get('count')
    if(s.get('var'+str(i)).get('logCondition')):
      var['logCondition'] = s.get('var'+str(i)).get('logCondition')
    struct['vars'].append(var)
    i += 1
  if structs_table.get(s.get('name')) is None:
    structs_table[s.get('name')] = []
  structs_table[s.get('name')].append(struct)
  if (structs_enabled_table.get(s.get('name')) is None) and (struct['enabled'] is True):
    structs_enabled_table[s.get('name')] = []
  if struct['enabled'] is True:
    structs_enabled_table[s.get('name')].append(struct)

for f in functions:
  function = {}
  function['args'] = []
  function['type'] = ''
  function['level'] = 'DeviceLevel'
  function['customDriver'] = False
  function['functionType'] = None
  function['enabled'] = f.get('enabled')
  function['custom'] = False
  function['version'] = 0
  if f.get('inheritFrom'):
    inherit_name = f.get('inheritFrom')
    function['inheritName'] = inherit_name
    for g in functions:
      if g.get('name') == inherit_name:
        if g.get('retV'):
          function['type'] = g.get('retV').get('type')
          if g.get('retV').get('wrapType'):
            function['retVwrapType'] = g.get('retV').get('wrapType')
          if g.get('retV').get('wrapParams'):
            function['retVwrapParams'] = g.get('retV').get('wrapParams')
        if g.get('type'):
          function['functionType'] = g.get('type')
        if g.get('custom'):
          function['custom'] = g.get('custom')
        if g.get('version'):
          function['version'] = g.get('version')
        if g.get('tokenCache'):
          function['tokenCache'] = g.get('tokenCache')
        i = 1
        while g.get('arg'+str(i)):
          arg = {}
          arg['type'] = g.get('arg'+str(i)).get('type')
          arg['name'] = g.get('arg'+str(i)).get('name')
          if g.get('arg'+str(i)).get('wrapType'):
            arg['wrapType'] = g.get('arg'+str(i)).get('wrapType')
          if g.get('arg'+str(i)).get('wrapParams'):
            arg['wrapParams'] = g.get('arg'+str(i)).get('wrapParams')
          if g.get('arg'+str(i)).get('logCondition'):
            arg['logCondition'] = g.get('arg'+str(i)).get('logCondition')
          if g.get('arg'+str(i)).get('count'):
            arg['count'] = g.get('arg'+str(i)).get('count')
          if g.get('arg'+str(i)).get('removeMapping'):
            arg['removeMapping'] = g.get('arg'+str(i)).get('removeMapping')
          function['args'].append(arg)
          i += 1
        if g.get('preToken') is not None:
          function['preToken'] = g.get('preToken')
          function['preTokenName'] = inherit_name
        if g.get('postToken') is not None:
          function['postToken'] = g.get('postToken')
          function['postTokenName'] = inherit_name
        if g.get('stateTrack') is not None:
          function['stateTrack'] = g.get('stateTrack')
          function['stateTrackName'] = inherit_name
        if g.get('recCond') is not None:
          function['recCond'] = g.get('recCond')
        if g.get('preSchedule') is not None:
          function['preSchedule'] = g.get('preSchedule')
        if g.get('recWrap') is not None:
          function['recWrap'] = g.get('recWrap')
          function['recWrapName'] = inherit_name
        if g.get('runWrap') is not None:
          function['runWrap'] = g.get('runWrap')
          function['runWrapName'] = inherit_name
        if g.get('ccodeWrap') is not None:
          function['ccodeWrap'] = g.get('ccodeWrap')
          function['ccodeWrapName'] = inherit_name
        if g.get('ccodeWriteWrap') is not None:
          function['ccodeWriteWrap'] = g.get('ccodeWriteWrap')
          function['ccodeWriteWrapName'] = inherit_name
        if g.get('ccodePostActionNeeded') is not None:
          function['ccodePostActionNeeded'] = g.get('ccodePostActionNeeded')
        if g.get('recExecWrap') is not None:
          function['recExecWrap'] = g.get('recExecWrap')
          function['recExecWrapName'] = inherit_name
        if g.get('pluginWrap') is not None:
          function['pluginWrap'] = g.get('pluginWrap')
          function['pluginWrapName'] = inherit_name
        if g.get('execPostRecWrap') is not None:
          function['execPostRecWrap'] = g.get('execPostRecWrap')
        if g.get('endFrameTag') is not None:
          function['endFrameTag'] = g.get('endFrameTag')
        if g.get('level') is not None:
          function['level'] = g.get('level')
        if g.get('customDriver') is not None:
          function['customDriver'] = True
  if f.get('retV'):
    function['type'] = f.get('retV').get('type')
    if f.get('retV').get('wrapType'):
      function['retVwrapType'] = f.get('retV').get('wrapType')
    if f.get('retV').get('wrapParams'):
      function['retVwrapParams'] = f.get('retV').get('wrapParams')
  if f.get('type'):
    function['functionType'] = f.get('type')
  if f.get('custom'):
    function['custom'] = f.get('custom')
  if f.get('version'):
    function['version'] = f.get('version')
  if f.get('tokenCache'):
    function['tokenCache'] = f.get('tokenCache')
  i = 1

  while f.get('arg'+str(i)) or (i <= len(function['args'])):
    if f.get('arg'+str(i)):
      arg = {}
      arg['type'] = f.get('arg'+str(i)).get('type')
      arg['name'] = f.get('arg'+str(i)).get('name')
      if f.get('arg'+str(i)).get('wrapType'):
        arg['wrapType'] = f.get('arg'+str(i)).get('wrapType')
      if f.get('arg'+str(i)).get('wrapParams'):
        arg['wrapParams'] = f.get('arg'+str(i)).get('wrapParams')
      if f.get('arg'+str(i)).get('count'):
        arg['count'] = f.get('arg'+str(i)).get('count')
      if f.get('arg'+str(i)).get('logCondition'):
        arg['logCondition'] = f.get('arg'+str(i)).get('logCondition')
      if f.get('arg'+str(i)).get('removeMapping'):
        arg['removeMapping'] = f.get('arg'+str(i)).get('removeMapping')
      if i <= len(function['args']):
        function['args'][i-1] = arg
      else:
        function['args'].append(arg)
    i += 1
  if f.get('preToken') is not None:
    function['preToken'] = f.get('preToken')
    function['preTokenName'] = f.get('name')
  if f.get('postToken') is not None:
    function['postToken'] = f.get('postToken')
    function['postTokenName'] = f.get('name')
  if f.get('stateTrack') is not None:
    function['stateTrack'] = f.get('stateTrack')
    function['stateTrackName'] = f.get('name')
  if f.get('recCond') is not None:
    function['recCond'] = f.get('recCond')
  if f.get('preSchedule') is not None:
    function['preSchedule'] = f.get('preSchedule')
  if f.get('recWrap') is not None:
    function['recWrap'] = f.get('recWrap')
    function['recWrapName'] = f.get('name')
  if f.get('runWrap') is not None:
    function['runWrap'] = f.get('runWrap')
    function['runWrapName'] = f.get('name')
  if f.get('ccodeWrap') is not None:
    function['ccodeWrap'] = f.get('ccodeWrap')
    function['ccodeWrapName'] = f.get('name')
  if f.get('ccodeWriteWrap') is not None:
    function['ccodeWriteWrap'] = f.get('ccodeWriteWrap')
    function['ccodeWriteWrapName'] = f.get('name')
  if f.get('ccodePostActionNeeded') is not None:
    function['ccodePostActionNeeded'] = f.get('ccodePostActionNeeded')
  if f.get('recExecWrap') is not None:
    function['recExecWrap'] = f.get('recExecWrap')
    function['recExecWrapName'] = f.get('name')
  if f.get('pluginWrap') is not None:
    function['pluginWrap'] = f.get('pluginWrap')
    function['pluginWrapName'] = f.get('name')
  if f.get('execPostRecWrap') is not None:
    function['execPostRecWrap'] = f.get('execPostRecWrap')
  if f.get('endFrameTag') is not None:
    function['endFrameTag'] = f.get('endFrameTag')
  if f.get('level') is not None:
    function['level'] = f.get('level')
  if f.get('customDriver') is not None:
    function['customDriver'] = True
  if functions_all_table.get(f.get('name')) is None:
    functions_all_table[f.get('name')] = []
  if (functions_enabled_table.get(f.get('name')) is None) and (function['enabled'] is True):
    functions_enabled_table[f.get('name')] = []
  functions_all_table[f.get('name')].append(function)
  functions_all_table[f.get('name')].sort(key=operator.itemgetter('version'))
  if function['enabled'] is True:
    functions_enabled_table[f.get('name')].append(function)
    functions_enabled_table[f.get('name')].sort(key=operator.itemgetter('version'))

generate_vulkan_header(enums_table, structs_table, functions_all_table)
generate_prepost(functions_all_table)
generate_vulkan_def(functions_all_table, 'vkPlugin.def', 'vulkan-1.dll')
generate_vulkan_def(functions_all_table, 'vkLayer.def', 'VkLayer_vulkan_GITS_recorder.dll')
generate_layer_json()
generate_vulkan_drivers(functions_all_table)
generate_vulkan_log(structs_table, enums_table)
generate_vulkan_tracer(functions_all_table, enums_table)
generate_vulkan_tokens(functions_enabled_table)
generate_vulkan_recorder_wrapper(functions_all_table)
generate_vulkan_arguments(structs_enabled_table, enums_table)
generate_vulkan_function_ids_header(functions_enabled_table)
generate_vulkan_create_switch(functions_enabled_table)
generate_vulkan_struct_storage(structs_enabled_table, enums_table)
generate_vulkan_lua_enums(enums_table)
generate_vulkan_ccode_arguments()


def move_file(filename, subdir):
  path = os.path.join('../' + subdir, filename)
  print('Moving {} to {}...'.format(filename, path))
  shutil.move(filename, path)


def copy_file(filename, subdir):
  path = os.path.join('../' + subdir, filename)
  print('Copying {} to {}...'.format(filename, path))
  shutil.copy2(filename, path)


copy_file('vulkanIDs.h', 'common/include')
move_file('vulkanPrePostAuto.cpp', 'interceptor')
move_file('vulkanLogAuto.cpp', 'common')
move_file('vulkanLogAuto.inl', 'common/include')
move_file('vulkanTracer.h', 'common/include')
move_file('vulkanHeader.h', 'common/include')
move_file('vulkanDriversAuto.inl', 'common/include')
move_file('vkPlugin.def', 'interceptor')
move_file('vkLayer.def', 'layer')
move_file('VkLayer_vulkan_GITS_recorder.json', 'layer')
move_file('vulkanArgumentsAuto.cpp', 'common')
move_file('vulkanArgumentsAuto.h', 'common/include')
move_file('vulkanStructStorageAuto.h', 'common/include')
move_file('vulkanStructStorageAuto.cpp', 'common')
move_file('vulkanFunctions.cpp', 'common')
move_file('vulkanFunctions.h', 'common/include')
move_file('vulkanIDswitch.h', 'common/include')
move_file('vulkanRecorderWrapperAuto.cpp', 'recorder')
move_file('vulkanRecorderWrapperAuto.h', 'recorder/include')
move_file('vulkanRecorderWrapperIfaceAuto.h', 'recorder/include')
move_file('vulkanLuaEnums.h', 'common/include')
move_file('vulkanCCodeArgumentsAuto.h', '../CCodeFiles/src/include')
