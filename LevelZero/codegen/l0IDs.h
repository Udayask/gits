// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2025 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

// clang-format off
ID_L0_COMMAND_LIST_APPEND_BARRIER,
ID_L0_COMMAND_LIST_APPEND_EVENT_RESET,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY_FROM_MEMORY,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY_REGION,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY_TO_MEMORY,
ID_L0_COMMAND_LIST_APPEND_LAUNCH_COOPERATIVE_KERNEL,
ID_L0_COMMAND_LIST_APPEND_LAUNCH_KERNEL,
ID_L0_COMMAND_LIST_APPEND_LAUNCH_KERNEL_INDIRECT,
ID_L0_COMMAND_LIST_APPEND_LAUNCH_MULTIPLE_KERNELS_INDIRECT,
ID_L0_COMMAND_LIST_APPEND_MEM_ADVISE,
ID_L0_COMMAND_LIST_APPEND_MEMORY_COPY,
ID_L0_COMMAND_LIST_APPEND_MEMORY_COPY_FROM_CONTEXT,
ID_L0_COMMAND_LIST_APPEND_MEMORY_COPY_REGION,
ID_L0_COMMAND_LIST_APPEND_MEMORY_FILL,
ID_L0_COMMAND_LIST_APPEND_MEMORY_PREFETCH,
ID_L0_COMMAND_LIST_APPEND_MEMORY_RANGES_BARRIER,
ID_L0_COMMAND_LIST_APPEND_QUERY_KERNEL_TIMESTAMPS,
ID_L0_COMMAND_LIST_APPEND_SIGNAL_EVENT,
ID_L0_COMMAND_LIST_APPEND_WAIT_ON_EVENTS,
ID_L0_COMMAND_LIST_APPEND_WRITE_GLOBAL_TIMESTAMP,
ID_L0_COMMAND_LIST_CLOSE,
ID_L0_COMMAND_LIST_CREATE,
ID_L0_COMMAND_LIST_CREATE_IMMEDIATE,
ID_L0_COMMAND_LIST_DESTROY,
ID_L0_COMMAND_LIST_RESET,
ID_L0_COMMAND_QUEUE_CREATE,
ID_L0_COMMAND_QUEUE_DESTROY,
ID_L0_COMMAND_QUEUE_EXECUTE_COMMAND_LISTS,
ID_L0_COMMAND_QUEUE_SYNCHRONIZE,
ID_L0_CONTEXT_CREATE,
ID_L0_CONTEXT_DESTROY,
ID_L0_CONTEXT_EVICT_IMAGE,
ID_L0_CONTEXT_EVICT_MEMORY,
ID_L0_CONTEXT_GET_STATUS,
ID_L0_CONTEXT_MAKE_IMAGE_RESIDENT,
ID_L0_CONTEXT_MAKE_MEMORY_RESIDENT,
ID_L0_CONTEXT_SYSTEM_BARRIER,
ID_L0_DEVICE_CAN_ACCESS_PEER,
ID_L0_DEVICE_GET,
ID_L0_DEVICE_GET_CACHE_PROPERTIES,
ID_L0_DEVICE_GET_COMMAND_QUEUE_GROUP_PROPERTIES,
ID_L0_DEVICE_GET_COMPUTE_PROPERTIES,
ID_L0_DEVICE_GET_EXTERNAL_MEMORY_PROPERTIES,
ID_L0_DEVICE_GET_IMAGE_PROPERTIES,
ID_L0_DEVICE_GET_MEMORY_ACCESS_PROPERTIES,
ID_L0_DEVICE_GET_MEMORY_PROPERTIES,
ID_L0_DEVICE_GET_MODULE_PROPERTIES,
ID_L0_DEVICE_GET_P2P_PROPERTIES,
ID_L0_DEVICE_GET_PROPERTIES,
ID_L0_DEVICE_GET_STATUS,
ID_L0_DEVICE_GET_SUB_DEVICES,
ID_L0_DRIVER_GET,
ID_L0_DRIVER_GET_API_VERSION,
ID_L0_DRIVER_GET_EXTENSION_PROPERTIES,
ID_L0_DRIVER_GET_IPC_PROPERTIES,
ID_L0_DRIVER_GET_PROPERTIES,
ID_L0_EVENT_CREATE,
ID_L0_EVENT_DESTROY,
ID_L0_EVENT_HOST_RESET,
ID_L0_EVENT_HOST_SIGNAL,
ID_L0_EVENT_HOST_SYNCHRONIZE,
ID_L0_EVENT_POOL_CLOSE_IPC_HANDLE,
ID_L0_EVENT_POOL_CREATE,
ID_L0_EVENT_POOL_DESTROY,
ID_L0_EVENT_POOL_GET_IPC_HANDLE,
ID_L0_EVENT_POOL_OPEN_IPC_HANDLE,
ID_L0_EVENT_QUERY_KERNEL_TIMESTAMP,
ID_L0_EVENT_QUERY_STATUS,
ID_L0_FENCE_CREATE,
ID_L0_FENCE_DESTROY,
ID_L0_FENCE_HOST_SYNCHRONIZE,
ID_L0_FENCE_QUERY_STATUS,
ID_L0_FENCE_RESET,
ID_L0_IMAGE_CREATE,
ID_L0_IMAGE_DESTROY,
ID_L0_IMAGE_GET_PROPERTIES,
ID_L0_INIT,
ID_L0_KERNEL_CREATE,
ID_L0_KERNEL_DESTROY,
ID_L0_KERNEL_GET_INDIRECT_ACCESS,
ID_L0_KERNEL_GET_NAME,
ID_L0_KERNEL_GET_PROPERTIES,
ID_L0_KERNEL_GET_SOURCE_ATTRIBUTES,
ID_L0_KERNEL_SET_ARGUMENT_VALUE,
ID_L0_KERNEL_SET_CACHE_CONFIG,
ID_L0_KERNEL_SET_GROUP_SIZE,
ID_L0_KERNEL_SET_INDIRECT_ACCESS,
ID_L0_KERNEL_SUGGEST_GROUP_SIZE,
ID_L0_KERNEL_SUGGEST_MAX_COOPERATIVE_GROUP_COUNT,
ID_L0_MEM_ALLOC_DEVICE,
ID_L0_MEM_ALLOC_HOST,
ID_L0_MEM_ALLOC_SHARED,
ID_L0_MEM_CLOSE_IPC_HANDLE,
ID_L0_MEM_FREE,
ID_L0_MEM_GET_ADDRESS_RANGE,
ID_L0_MEM_GET_ALLOC_PROPERTIES,
ID_L0_MEM_GET_IPC_HANDLE,
ID_L0_MEM_OPEN_IPC_HANDLE,
ID_L0_MODULE_BUILD_LOG_DESTROY,
ID_L0_MODULE_BUILD_LOG_GET_STRING,
ID_L0_MODULE_CREATE,
ID_L0_MODULE_DESTROY,
ID_L0_MODULE_DYNAMIC_LINK,
ID_L0_MODULE_GET_FUNCTION_POINTER,
ID_L0_MODULE_GET_GLOBAL_POINTER,
ID_L0_MODULE_GET_KERNEL_NAMES,
ID_L0_MODULE_GET_NATIVE_BINARY,
ID_L0_MODULE_GET_PROPERTIES,
ID_L0_PHYSICAL_MEM_CREATE,
ID_L0_PHYSICAL_MEM_DESTROY,
ID_L0_SAMPLER_CREATE,
ID_L0_SAMPLER_DESTROY,
ID_L0_VIRTUAL_MEM_FREE,
ID_L0_VIRTUAL_MEM_GET_ACCESS_ATTRIBUTE,
ID_L0_VIRTUAL_MEM_MAP,
ID_L0_VIRTUAL_MEM_QUERY_PAGE_SIZE,
ID_L0_VIRTUAL_MEM_RESERVE,
ID_L0_VIRTUAL_MEM_SET_ACCESS_ATTRIBUTE,
ID_L0_VIRTUAL_MEM_UNMAP,
ID_L0S_DEVICE_ENUM_DIAGNOSTIC_TEST_SUITES,
ID_L0S_DEVICE_ENUM_ENGINE_GROUPS,
ID_L0S_DEVICE_ENUM_FABRIC_PORTS,
ID_L0S_DEVICE_ENUM_FANS,
ID_L0S_DEVICE_ENUM_FIRMWARES,
ID_L0S_DEVICE_ENUM_FREQUENCY_DOMAINS,
ID_L0S_DEVICE_ENUM_LEDS,
ID_L0S_DEVICE_ENUM_MEMORY_MODULES,
ID_L0S_DEVICE_ENUM_PERFORMANCE_FACTOR_DOMAINS,
ID_L0S_DEVICE_ENUM_POWER_DOMAINS,
ID_L0S_DEVICE_ENUM_PSUS,
ID_L0S_DEVICE_ENUM_RAS_ERROR_SETS,
ID_L0S_DEVICE_ENUM_SCHEDULERS,
ID_L0S_DEVICE_ENUM_STANDBY_DOMAINS,
ID_L0S_DEVICE_ENUM_TEMPERATURE_SENSORS,
ID_L0S_DEVICE_EVENT_REGISTER,
ID_L0S_DEVICE_GET_PROPERTIES,
ID_L0S_DEVICE_GET_STATE,
ID_L0S_DEVICE_PCI_GET_BARS,
ID_L0S_DEVICE_PCI_GET_PROPERTIES,
ID_L0S_DEVICE_PCI_GET_STATE,
ID_L0S_DEVICE_PCI_GET_STATS,
ID_L0S_DEVICE_PROCESSES_GET_STATE,
ID_L0S_DEVICE_RESET,
ID_L0S_DIAGNOSTICS_GET_PROPERTIES,
ID_L0S_DIAGNOSTICS_GET_TESTS,
ID_L0S_DIAGNOSTICS_RUN_TESTS,
ID_L0S_DRIVER_EVENT_LISTEN,
ID_L0S_ENGINE_GET_ACTIVITY,
ID_L0S_ENGINE_GET_PROPERTIES,
ID_L0S_FABRIC_PORT_GET_CONFIG,
ID_L0S_FABRIC_PORT_GET_LINK_TYPE,
ID_L0S_FABRIC_PORT_GET_PROPERTIES,
ID_L0S_FABRIC_PORT_GET_STATE,
ID_L0S_FABRIC_PORT_GET_THROUGHPUT,
ID_L0S_FABRIC_PORT_SET_CONFIG,
ID_L0S_FAN_GET_CONFIG,
ID_L0S_FAN_GET_PROPERTIES,
ID_L0S_FAN_GET_STATE,
ID_L0S_FAN_SET_DEFAULT_MODE,
ID_L0S_FAN_SET_FIXED_SPEED_MODE,
ID_L0S_FAN_SET_SPEED_TABLE_MODE,
ID_L0S_FIRMWARE_FLASH,
ID_L0S_FIRMWARE_GET_PROPERTIES,
ID_L0S_FREQUENCY_GET_AVAILABLE_CLOCKS,
ID_L0S_FREQUENCY_GET_PROPERTIES,
ID_L0S_FREQUENCY_GET_RANGE,
ID_L0S_FREQUENCY_GET_STATE,
ID_L0S_FREQUENCY_GET_THROTTLE_TIME,
ID_L0S_FREQUENCY_OC_GET_CAPABILITIES,
ID_L0S_FREQUENCY_OC_GET_FREQUENCY_TARGET,
ID_L0S_FREQUENCY_OC_GET_ICC_MAX,
ID_L0S_FREQUENCY_OC_GET_MODE,
ID_L0S_FREQUENCY_OC_GET_TJ_MAX,
ID_L0S_FREQUENCY_OC_GET_VOLTAGE_TARGET,
ID_L0S_FREQUENCY_OC_SET_FREQUENCY_TARGET,
ID_L0S_FREQUENCY_OC_SET_ICC_MAX,
ID_L0S_FREQUENCY_OC_SET_MODE,
ID_L0S_FREQUENCY_OC_SET_TJ_MAX,
ID_L0S_FREQUENCY_OC_SET_VOLTAGE_TARGET,
ID_L0S_FREQUENCY_SET_RANGE,
ID_L0S_LED_GET_PROPERTIES,
ID_L0S_LED_GET_STATE,
ID_L0S_LED_SET_COLOR,
ID_L0S_LED_SET_STATE,
ID_L0S_MEMORY_GET_BANDWIDTH,
ID_L0S_MEMORY_GET_PROPERTIES,
ID_L0S_MEMORY_GET_STATE,
ID_L0S_PERFORMANCE_FACTOR_GET_CONFIG,
ID_L0S_PERFORMANCE_FACTOR_GET_PROPERTIES,
ID_L0S_PERFORMANCE_FACTOR_SET_CONFIG,
ID_L0S_POWER_GET_ENERGY_COUNTER,
ID_L0S_POWER_GET_ENERGY_THRESHOLD,
ID_L0S_POWER_GET_LIMITS,
ID_L0S_POWER_GET_PROPERTIES,
ID_L0S_POWER_SET_ENERGY_THRESHOLD,
ID_L0S_POWER_SET_LIMITS,
ID_L0S_PSU_GET_PROPERTIES,
ID_L0S_PSU_GET_STATE,
ID_L0S_RAS_GET_CONFIG,
ID_L0S_RAS_GET_PROPERTIES,
ID_L0S_RAS_GET_STATE,
ID_L0S_RAS_SET_CONFIG,
ID_L0S_SCHEDULER_GET_CURRENT_MODE,
ID_L0S_SCHEDULER_GET_PROPERTIES,
ID_L0S_SCHEDULER_GET_TIMEOUT_MODE_PROPERTIES,
ID_L0S_SCHEDULER_GET_TIMESLICE_MODE_PROPERTIES,
ID_L0S_SCHEDULER_SET_COMPUTE_UNIT_DEBUG_MODE,
ID_L0S_SCHEDULER_SET_EXCLUSIVE_MODE,
ID_L0S_SCHEDULER_SET_TIMEOUT_MODE,
ID_L0S_SCHEDULER_SET_TIMESLICE_MODE,
ID_L0S_STANDBY_GET_MODE,
ID_L0S_STANDBY_GET_PROPERTIES,
ID_L0S_STANDBY_SET_MODE,
ID_L0S_TEMPERATURE_GET_CONFIG,
ID_L0S_TEMPERATURE_GET_PROPERTIES,
ID_L0S_TEMPERATURE_GET_STATE,
ID_L0S_TEMPERATURE_SET_CONFIG,
ID_L0T_COMMAND_LIST_APPEND_METRIC_MEMORY_BARRIER,
ID_L0T_COMMAND_LIST_APPEND_METRIC_QUERY_BEGIN,
ID_L0T_COMMAND_LIST_APPEND_METRIC_QUERY_END,
ID_L0T_COMMAND_LIST_APPEND_METRIC_STREAMER_MARKER,
ID_L0T_CONTEXT_ACTIVATE_METRIC_GROUPS,
ID_L0T_DEBUG_ACKNOWLEDGE_EVENT,
ID_L0T_DEBUG_ATTACH,
ID_L0T_DEBUG_DETACH,
ID_L0T_DEBUG_GET_REGISTER_SET_PROPERTIES,
ID_L0T_DEBUG_INTERRUPT,
ID_L0T_DEBUG_READ_EVENT,
ID_L0T_DEBUG_READ_MEMORY,
ID_L0T_DEBUG_READ_REGISTERS,
ID_L0T_DEBUG_RESUME,
ID_L0T_DEBUG_WRITE_MEMORY,
ID_L0T_DEBUG_WRITE_REGISTERS,
ID_L0T_DEVICE_GET_DEBUG_PROPERTIES,
ID_L0T_KERNEL_GET_PROFILE_INFO,
ID_L0T_METRIC_GET,
ID_L0T_METRIC_GET_PROPERTIES,
ID_L0T_METRIC_GROUP_CALCULATE_METRIC_VALUES,
ID_L0T_METRIC_GROUP_GET,
ID_L0T_METRIC_GROUP_GET_PROPERTIES,
ID_L0T_METRIC_QUERY_CREATE,
ID_L0T_METRIC_QUERY_DESTROY,
ID_L0T_METRIC_QUERY_GET_DATA,
ID_L0T_METRIC_QUERY_POOL_CREATE,
ID_L0T_METRIC_QUERY_POOL_DESTROY,
ID_L0T_METRIC_QUERY_RESET,
ID_L0T_METRIC_STREAMER_CLOSE,
ID_L0T_METRIC_STREAMER_OPEN,
ID_L0T_METRIC_STREAMER_READ_DATA,
ID_L0T_MODULE_GET_DEBUG_INFO,
ID_L0T_TRACER_EXP_CREATE,
ID_L0T_TRACER_EXP_DESTROY,
ID_L0T_TRACER_EXP_SET_ENABLED,
ID_L0T_TRACER_EXP_SET_EPILOGUES,
ID_L0T_TRACER_EXP_SET_PROLOGUES,
ID_L0_DEVICE_GET_GLOBAL_TIMESTAMPS,
ID_L0_DEVICE_RESERVE_CACHE,
ID_L0_DEVICE_SET_CACHE_ADVICE,
ID_L0_DRIVER_GET_EXTENSION_FUNCTION_ADDRESS,
ID_L0_GITS_INDIRECT_ALLOCATION_OFFSETS,
ID_L0_KERNEL_SET_GLOBAL_OFFSET_EXP,
ID_L0_COMMAND_LIST_APPEND_MEMORY_FILL_V1,
ID_L0_COMMAND_LIST_APPEND_MEMORY_COPY_REGION_V1,
ID_L0_MODULE_GET_FUNCTION_POINTER_V1,
ID_L0_CONTEXT_CREATE_EX,
ID_L0_EVENT_QUERY_TIMESTAMPS_EXP,
ID_L0_IMAGE_GET_MEMORY_PROPERTIES_EXP,
ID_L0_IMAGE_VIEW_CREATE_EXP,
ID_L0_KERNEL_SCHEDULING_HINT_EXP,
ID_L0S_DEVICE_GET_CARD_POWER_DOMAIN,
ID_L0S_DRIVER_EVENT_LISTEN_EX,
ID_L0T_METRIC_GROUP_CALCULATE_MULTIPLE_METRIC_VALUES_EXP,
ID_L0L_TRACER_CREATE,
ID_L0L_TRACER_DESTROY,
ID_L0L_TRACER_SET_ENABLED,
ID_L0L_TRACER_SET_EPILOGUES,
ID_L0L_TRACER_SET_PROLOGUES,
ID_L0_DEVICE_RESERVE_CACHE_EXT,
ID_L0_DEVICE_SET_CACHE_ADVICE_EXT,
ID_L0_MODULE_CREATE_V1,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY_FROM_MEMORY_EXT,
ID_L0_COMMAND_LIST_APPEND_IMAGE_COPY_TO_MEMORY_EXT,
ID_L0_COMMAND_LIST_HOST_SYNCHRONIZE,
ID_L0_DEVICE_GET_FABRIC_VERTEX_EXP,
ID_L0_DEVICE_PCI_GET_PROPERTIES_EXT,
ID_L0_DRIVER_GET_LAST_ERROR_DESCRIPTION,
ID_L0_EVENT_POOL_PUT_IPC_HANDLE,
ID_L0_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT,
ID_L0_FABRIC_EDGE_GET_EXP,
ID_L0_FABRIC_EDGE_GET_PROPERTIES_EXP,
ID_L0_FABRIC_EDGE_GET_VERTICES_EXP,
ID_L0_FABRIC_VERTEX_GET_DEVICE_EXP,
ID_L0_FABRIC_VERTEX_GET_EXP,
ID_L0_FABRIC_VERTEX_GET_PROPERTIES_EXP,
ID_L0_FABRIC_VERTEX_GET_SUB_VERTICES_EXP,
ID_L0_IMAGE_GET_ALLOC_PROPERTIES_EXT,
ID_L0_IMAGE_VIEW_CREATE_EXT,
ID_L0_MEM_FREE_EXT,
ID_L0_MEM_GET_FILE_DESCRIPTOR_FROM_IPC_HANDLE_EXP,
ID_L0_MEM_GET_IPC_HANDLE_FROM_FILE_DESCRIPTOR_EXP,
ID_L0_MEM_PUT_IPC_HANDLE,
ID_L0_MODULE_INSPECT_LINKAGE_EXT,
ID_L0S_DEVICE_ECC_AVAILABLE,
ID_L0S_DEVICE_ECC_CONFIGURABLE,
ID_L0S_DEVICE_ENUM_OVERCLOCK_DOMAINS,
ID_L0S_DEVICE_GET,
ID_L0S_DEVICE_GET_ECC_STATE,
ID_L0S_DEVICE_GET_OVERCLOCK_CONTROLS,
ID_L0S_DEVICE_GET_OVERCLOCK_DOMAINS,
ID_L0S_DEVICE_READ_OVERCLOCK_STATE,
ID_L0S_DEVICE_RESET_OVERCLOCK_SETTINGS,
ID_L0S_DEVICE_SET_ECC_STATE,
ID_L0S_DEVICE_SET_OVERCLOCK_WAIVER,
ID_L0S_DRIVER_GET,
ID_L0S_FABRIC_PORT_GET_FABRIC_ERROR_COUNTERS,
ID_L0S_INIT,
ID_L0S_OVERCLOCK_GET_CONTROL_CURRENT_VALUE,
ID_L0S_OVERCLOCK_GET_CONTROL_PENDING_VALUE,
ID_L0S_OVERCLOCK_GET_CONTROL_STATE,
ID_L0S_OVERCLOCK_GET_DOMAIN_CONTROL_PROPERTIES,
ID_L0S_OVERCLOCK_GET_DOMAIN_PROPERTIES,
ID_L0S_OVERCLOCK_GET_DOMAIN_VF_PROPERTIES,
ID_L0S_OVERCLOCK_GET_VF_POINT_VALUES,
ID_L0S_OVERCLOCK_SET_CONTROL_USER_VALUE,
ID_L0S_OVERCLOCK_SET_VF_POINT_VALUES,
ID_L0S_POWER_GET_LIMITS_EXT,
ID_L0S_POWER_SET_LIMITS_EXT,
ID_L0T_DEBUG_GET_THREAD_REGISTER_SET_PROPERTIES,
ID_L0T_METRIC_GROUP_GET_GLOBAL_TIMESTAMPS_EXP,
ID_L0_GITS_START_RECORDING,
ID_L0_GITS_STOP_RECORDING,
ID_L0_GET_COMMAND_LIST_PROC_ADDR_TABLE,
ID_L0_GET_COMMAND_QUEUE_PROC_ADDR_TABLE,
ID_L0_GET_CONTEXT_PROC_ADDR_TABLE,
ID_L0_GET_DEVICE_EXP_PROC_ADDR_TABLE,
ID_L0_GET_DEVICE_PROC_ADDR_TABLE,
ID_L0_GET_DRIVER_PROC_ADDR_TABLE,
ID_L0_GET_EVENT_EXP_PROC_ADDR_TABLE,
ID_L0_GET_EVENT_POOL_PROC_ADDR_TABLE,
ID_L0_GET_EVENT_PROC_ADDR_TABLE,
ID_L0_GET_FABRIC_EDGE_EXP_PROC_ADDR_TABLE,
ID_L0_GET_FABRIC_VERTEX_EXP_PROC_ADDR_TABLE,
ID_L0_GET_FENCE_PROC_ADDR_TABLE,
ID_L0_GET_GLOBAL_PROC_ADDR_TABLE,
ID_L0_GET_IMAGE_EXP_PROC_ADDR_TABLE,
ID_L0_GET_IMAGE_PROC_ADDR_TABLE,
ID_L0_GET_KERNEL_EXP_PROC_ADDR_TABLE,
ID_L0_GET_KERNEL_PROC_ADDR_TABLE,
ID_L0_GET_MEM_EXP_PROC_ADDR_TABLE,
ID_L0_GET_MEM_PROC_ADDR_TABLE,
ID_L0_GET_MODULE_BUILD_LOG_PROC_ADDR_TABLE,
ID_L0_GET_MODULE_PROC_ADDR_TABLE,
ID_L0_GET_PHYSICAL_MEM_PROC_ADDR_TABLE,
ID_L0_GET_SAMPLER_PROC_ADDR_TABLE,
ID_L0_GET_VIRTUAL_MEM_PROC_ADDR_TABLE,
ID_L0S_GET_DEVICE_PROC_ADDR_TABLE,
ID_L0S_GET_DIAGNOSTICS_PROC_ADDR_TABLE,
ID_L0S_GET_DRIVER_PROC_ADDR_TABLE,
ID_L0S_GET_ENGINE_PROC_ADDR_TABLE,
ID_L0S_GET_FABRIC_PORT_PROC_ADDR_TABLE,
ID_L0S_GET_FAN_PROC_ADDR_TABLE,
ID_L0S_GET_FIRMWARE_PROC_ADDR_TABLE,
ID_L0S_GET_FREQUENCY_PROC_ADDR_TABLE,
ID_L0S_GET_GLOBAL_PROC_ADDR_TABLE,
ID_L0S_GET_LED_PROC_ADDR_TABLE,
ID_L0S_GET_MEMORY_PROC_ADDR_TABLE,
ID_L0S_GET_OVERCLOCK_PROC_ADDR_TABLE,
ID_L0S_GET_PERFORMANCE_FACTOR_PROC_ADDR_TABLE,
ID_L0S_GET_POWER_PROC_ADDR_TABLE,
ID_L0S_GET_PSU_PROC_ADDR_TABLE,
ID_L0S_GET_RAS_PROC_ADDR_TABLE,
ID_L0S_GET_SCHEDULER_PROC_ADDR_TABLE,
ID_L0S_GET_STANDBY_PROC_ADDR_TABLE,
ID_L0S_GET_TEMPERATURE_PROC_ADDR_TABLE,
ID_L0T_GET_COMMAND_LIST_PROC_ADDR_TABLE,
ID_L0T_GET_CONTEXT_PROC_ADDR_TABLE,
ID_L0T_GET_DEBUG_PROC_ADDR_TABLE,
ID_L0T_GET_DEVICE_PROC_ADDR_TABLE,
ID_L0T_GET_KERNEL_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_GROUP_EXP_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_GROUP_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_QUERY_POOL_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_QUERY_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_STREAMER_PROC_ADDR_TABLE,
ID_L0T_GET_MODULE_PROC_ADDR_TABLE,
ID_L0T_GET_TRACER_EXP_PROC_ADDR_TABLE,
ID_L0_CONTEXT_EVICT_MEMORY_V1,
ID_L0_CONTEXT_MAKE_MEMORY_RESIDENT_V1,
ID_L0_DRIVER_RTAS_FORMAT_COMPATIBILITY_CHECK_EXP,
ID_L0_GET_DRIVER_EXP_PROC_ADDR_TABLE,
ID_L0_GET_RTAS_BUILDER_EXP_PROC_ADDR_TABLE,
ID_L0_GET_RTAS_PARALLEL_OPERATION_EXP_PROC_ADDR_TABLE,
ID_L0_MEM_GET_ATOMIC_ACCESS_ATTRIBUTE_EXP,
ID_L0_MEM_SET_ATOMIC_ACCESS_ATTRIBUTE_EXP,
ID_L0_RTAS_BUILDER_BUILD_EXP,
ID_L0_RTAS_BUILDER_CREATE_EXP,
ID_L0_RTAS_BUILDER_DESTROY_EXP,
ID_L0_RTAS_BUILDER_GET_BUILD_PROPERTIES_EXP,
ID_L0_RTAS_PARALLEL_OPERATION_CREATE_EXP,
ID_L0_RTAS_PARALLEL_OPERATION_DESTROY_EXP,
ID_L0_RTAS_PARALLEL_OPERATION_GET_PROPERTIES_EXP,
ID_L0_RTAS_PARALLEL_OPERATION_JOIN_EXP,
ID_L0S_DEVICE_RESET_EXT,
ID_L0S_ENGINE_GET_ACTIVITY_EXT,
ID_L0S_FABRIC_PORT_GET_MULTI_PORT_THROUGHPUT,
ID_L0T_METRIC_GROUP_CALCULATE_METRIC_EXPORT_DATA_EXP,
ID_L0T_METRIC_GROUP_GET_EXPORT_DATA_EXP,
ID_RESERVED_TOKEN_1,
ID_L0_DEVICE_GET_ROOT_DEVICE,
ID_L0S_DRIVER_GET_EXTENSION_FUNCTION_ADDRESS,
ID_L0S_DRIVER_GET_EXTENSION_PROPERTIES,
ID_L0S_FIRMWARE_GET_FLASH_PROGRESS,
ID_L0S_GET_RAS_EXP_PROC_ADDR_TABLE,
ID_L0S_RAS_CLEAR_STATE_EXP,
ID_L0S_RAS_GET_STATE_EXP,
ID_L0_GITS_ORIGINAL_QUEUE_FAMILY_INFO,
ID_L0_COMMAND_LIST_CREATE_CLONE_EXP,
ID_L0_COMMAND_LIST_GET_CONTEXT_HANDLE,
ID_L0_COMMAND_LIST_GET_DEVICE_HANDLE,
ID_L0_COMMAND_LIST_GET_NEXT_COMMAND_ID_EXP,
ID_L0_COMMAND_LIST_GET_ORDINAL,
ID_L0_COMMAND_LIST_IMMEDIATE_APPEND_COMMAND_LISTS_EXP,
ID_L0_COMMAND_LIST_IMMEDIATE_GET_INDEX,
ID_L0_COMMAND_LIST_IS_IMMEDIATE,
ID_L0_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_SIGNAL_EVENT_EXP,
ID_L0_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_WAIT_EVENTS_EXP,
ID_L0_COMMAND_LIST_UPDATE_MUTABLE_COMMANDS_EXP,
ID_L0_COMMAND_QUEUE_GET_INDEX,
ID_L0_COMMAND_QUEUE_GET_ORDINAL,
ID_L0_EVENT_GET_EVENT_POOL,
ID_L0_EVENT_GET_SIGNAL_SCOPE,
ID_L0_EVENT_GET_WAIT_SCOPE,
ID_L0_EVENT_POOL_GET_CONTEXT_HANDLE,
ID_L0_EVENT_POOL_GET_FLAGS,
ID_L0_GET_COMMAND_LIST_EXP_PROC_ADDR_TABLE,
ID_L0_IMAGE_GET_DEVICE_OFFSET_EXP,
ID_L0_MEM_GET_PITCH_FOR2D_IMAGE,
ID_L0S_DEVICE_ENUM_ACTIVE_VF_EXP,
ID_L0S_DEVICE_GET_SUB_DEVICE_PROPERTIES_EXP,
ID_L0S_DRIVER_GET_DEVICE_BY_UUID_EXP,
ID_L0S_FIRMWARE_GET_CONSOLE_LOGS,
ID_L0S_FIRMWARE_GET_SECURITY_VERSION_EXP,
ID_L0S_FIRMWARE_SET_SECURITY_VERSION_EXP,
ID_L0S_GET_DEVICE_EXP_PROC_ADDR_TABLE,
ID_L0S_GET_DRIVER_EXP_PROC_ADDR_TABLE,
ID_L0S_GET_FIRMWARE_EXP_PROC_ADDR_TABLE,
ID_L0S_GET_VF_MANAGEMENT_EXP_PROC_ADDR_TABLE,
ID_L0S_VF_MANAGEMENT_GET_VF_ENGINE_UTILIZATION_EXP,
ID_L0S_VF_MANAGEMENT_GET_VF_MEMORY_UTILIZATION_EXP,
ID_L0S_VF_MANAGEMENT_GET_VF_PROPERTIES_EXP,
ID_L0S_VF_MANAGEMENT_SET_VF_TELEMETRY_MODE_EXP,
ID_L0S_VF_MANAGEMENT_SET_VF_TELEMETRY_SAMPLING_INTERVAL_EXP,
ID_L0T_GET_METRIC_EXP_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_PROGRAMMABLE_EXP_PROC_ADDR_TABLE,
ID_L0T_METRIC_CREATE_FROM_PROGRAMMABLE_EXP,
ID_L0T_METRIC_DESTROY_EXP,
ID_L0T_METRIC_GROUP_ADD_METRIC_EXP,
ID_L0T_METRIC_GROUP_CLOSE_EXP,
ID_L0T_METRIC_GROUP_CREATE_EXP,
ID_L0T_METRIC_GROUP_DESTROY_EXP,
ID_L0T_METRIC_GROUP_REMOVE_METRIC_EXP,
ID_L0T_METRIC_PROGRAMMABLE_GET_EXP,
ID_L0T_METRIC_PROGRAMMABLE_GET_PARAM_INFO_EXP,
ID_L0T_METRIC_PROGRAMMABLE_GET_PARAM_VALUE_INFO_EXP,
ID_L0T_METRIC_PROGRAMMABLE_GET_PROPERTIES_EXP,
ID_L0_MEM_FREE_EXT_V1,
ID_L0_VIRTUAL_MEM_MAP_V1,
ID_L0_VIRTUAL_MEM_RESERVE_V1,
ID_L0_VIRTUAL_MEM_SET_ACCESS_ATTRIBUTE_V1,
ID_L0_VIRTUAL_MEM_UNMAP_V1,
ID_L0_VIRTUAL_MEM_FREE_V1,
ID_L0L_GET_TRACER_API_PROC_ADDR_TABLE,
ID_L0L_DISABLE_TRACING_LAYER,
ID_L0L_ENABLE_TRACING_LAYER,
ID_L0L_LOADER_GET_VERSIONS,
ID_L0L_SET_DRIVER_TEARDOWN,
ID_L0L_LOADER_TRANSLATE_HANDLE,
ID_L0_COMMAND_LIST_GET_NEXT_COMMAND_ID_WITH_KERNELS_EXP,
ID_L0_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_KERNELS_EXP,
ID_L0_INIT_DRIVERS,
ID_L0S_DEVICE_ENUM_ENABLED_VF_EXP,
ID_L0S_VF_MANAGEMENT_GET_VF_CAPABILITIES_EXP,
ID_L0S_VF_MANAGEMENT_GET_VF_ENGINE_UTILIZATION_EXP2,
ID_L0S_VF_MANAGEMENT_GET_VF_MEMORY_UTILIZATION_EXP2,
ID_L0T_DEVICE_CREATE_METRIC_GROUPS_FROM_METRICS_EXP,
ID_L0T_DEVICE_GET_CONCURRENT_METRIC_GROUPS_EXP,
ID_L0T_GET_DEVICE_EXP_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_DECODER_EXP_PROC_ADDR_TABLE,
ID_L0T_GET_METRIC_TRACER_EXP_PROC_ADDR_TABLE,
ID_L0T_METRIC_CREATE_FROM_PROGRAMMABLE_EXP2,
ID_L0T_METRIC_DECODER_CREATE_EXP,
ID_L0T_METRIC_DECODER_DESTROY_EXP,
ID_L0T_METRIC_DECODER_GET_DECODABLE_METRICS_EXP,
ID_L0T_METRIC_TRACER_CREATE_EXP,
ID_L0T_METRIC_TRACER_DECODE_EXP,
ID_L0T_METRIC_TRACER_DESTROY_EXP,
ID_L0T_METRIC_TRACER_DISABLE_EXP,
ID_L0T_METRIC_TRACER_ENABLE_EXP,
ID_L0T_METRIC_TRACER_READ_DATA_EXP,
ID_L0L_TRACER_COMMAND_LIST_APPEND_BARRIER_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_EVENT_RESET_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_FROM_MEMORY_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_FROM_MEMORY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_REGION_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_TO_MEMORY_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_IMAGE_COPY_TO_MEMORY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_LAUNCH_COOPERATIVE_KERNEL_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_LAUNCH_KERNEL_INDIRECT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_LAUNCH_KERNEL_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_LAUNCH_MULTIPLE_KERNELS_INDIRECT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEM_ADVISE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_COPY_FROM_CONTEXT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_COPY_REGION_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_COPY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_FILL_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_PREFETCH_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_MEMORY_RANGES_BARRIER_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_QUERY_KERNEL_TIMESTAMPS_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_SIGNAL_EVENT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_WAIT_ON_EVENTS_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_WRITE_GLOBAL_TIMESTAMP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_CLOSE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_CREATE_CLONE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_CREATE_IMMEDIATE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_GET_CONTEXT_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_GET_DEVICE_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_GET_NEXT_COMMAND_ID_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_GET_NEXT_COMMAND_ID_WITH_KERNELS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_GET_ORDINAL_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_HOST_SYNCHRONIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_IMMEDIATE_APPEND_COMMAND_LISTS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_IMMEDIATE_GET_INDEX_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_IS_IMMEDIATE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_RESET_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_KERNELS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_SIGNAL_EVENT_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_UPDATE_MUTABLE_COMMAND_WAIT_EVENTS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_UPDATE_MUTABLE_COMMANDS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_EXECUTE_COMMAND_LISTS_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_GET_INDEX_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_GET_ORDINAL_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_QUEUE_SYNCHRONIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_CREATE_EX_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_EVICT_IMAGE_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_EVICT_MEMORY_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_GET_STATUS_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_MAKE_IMAGE_RESIDENT_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_MAKE_MEMORY_RESIDENT_REGISTER_CALLBACK,
ID_L0L_TRACER_CONTEXT_SYSTEM_BARRIER_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_CAN_ACCESS_PEER_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_CACHE_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_COMMAND_QUEUE_GROUP_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_COMPUTE_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_EXTERNAL_MEMORY_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_FABRIC_VERTEX_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_GLOBAL_TIMESTAMPS_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_IMAGE_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_MEMORY_ACCESS_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_MEMORY_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_MODULE_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_P2P_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_ROOT_DEVICE_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_STATUS_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_GET_SUB_DEVICES_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_PCI_GET_PROPERTIES_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_RESERVE_CACHE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_SET_CACHE_ADVICE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_API_VERSION_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_EXTENSION_FUNCTION_ADDRESS_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_EXTENSION_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_IPC_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_LAST_ERROR_DESCRIPTION_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_GET_REGISTER_CALLBACK,
ID_L0L_TRACER_DRIVER_RTAS_FORMAT_COMPATIBILITY_CHECK_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_GET_EVENT_POOL_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_GET_SIGNAL_SCOPE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_GET_WAIT_SCOPE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_HOST_RESET_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_HOST_SIGNAL_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_HOST_SYNCHRONIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_CLOSE_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_GET_CONTEXT_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_GET_FLAGS_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_GET_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_OPEN_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_POOL_PUT_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_QUERY_KERNEL_TIMESTAMP_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_QUERY_KERNEL_TIMESTAMPS_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_QUERY_STATUS_REGISTER_CALLBACK,
ID_L0L_TRACER_EVENT_QUERY_TIMESTAMPS_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_EDGE_GET_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_EDGE_GET_PROPERTIES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_EDGE_GET_VERTICES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_VERTEX_GET_DEVICE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_VERTEX_GET_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_VERTEX_GET_PROPERTIES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FABRIC_VERTEX_GET_SUB_VERTICES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_FENCE_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_FENCE_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_FENCE_HOST_SYNCHRONIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_FENCE_QUERY_STATUS_REGISTER_CALLBACK,
ID_L0L_TRACER_FENCE_RESET_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_GET_ALLOC_PROPERTIES_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_GET_DEVICE_OFFSET_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_GET_MEMORY_PROPERTIES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_GET_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_VIEW_CREATE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_IMAGE_VIEW_CREATE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_INIT_DRIVERS_REGISTER_CALLBACK,
ID_L0L_TRACER_INIT_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_GET_INDIRECT_ACCESS_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_GET_NAME_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_GET_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_GET_SOURCE_ATTRIBUTES_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SCHEDULING_HINT_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SET_ARGUMENT_VALUE_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SET_CACHE_CONFIG_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SET_GLOBAL_OFFSET_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SET_GROUP_SIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SET_INDIRECT_ACCESS_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SUGGEST_GROUP_SIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_SUGGEST_MAX_COOPERATIVE_GROUP_COUNT_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_ALLOC_DEVICE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_ALLOC_HOST_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_ALLOC_SHARED_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_CLOSE_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_FREE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_FREE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_ADDRESS_RANGE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_ALLOC_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_ATOMIC_ACCESS_ATTRIBUTE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_FILE_DESCRIPTOR_FROM_IPC_HANDLE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_IPC_HANDLE_FROM_FILE_DESCRIPTOR_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_GET_PITCH_FOR2D_IMAGE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_OPEN_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_PUT_IPC_HANDLE_REGISTER_CALLBACK,
ID_L0L_TRACER_MEM_SET_ATOMIC_ACCESS_ATTRIBUTE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_BUILD_LOG_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_BUILD_LOG_GET_STRING_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_DYNAMIC_LINK_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_GET_FUNCTION_POINTER_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_GET_GLOBAL_POINTER_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_GET_KERNEL_NAMES_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_GET_NATIVE_BINARY_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_GET_PROPERTIES_REGISTER_CALLBACK,
ID_L0L_TRACER_MODULE_INSPECT_LINKAGE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_PHYSICAL_MEM_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_PHYSICAL_MEM_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_BUILDER_BUILD_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_BUILDER_CREATE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_BUILDER_DESTROY_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_BUILDER_GET_BUILD_PROPERTIES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_PARALLEL_OPERATION_CREATE_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_PARALLEL_OPERATION_DESTROY_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_PARALLEL_OPERATION_GET_PROPERTIES_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RTAS_PARALLEL_OPERATION_JOIN_EXP_REGISTER_CALLBACK,
ID_L0L_TRACER_RESET_ALL_CALLBACKS,
ID_L0L_TRACER_SAMPLER_CREATE_REGISTER_CALLBACK,
ID_L0L_TRACER_SAMPLER_DESTROY_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_FREE_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_GET_ACCESS_ATTRIBUTE_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_MAP_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_QUERY_PAGE_SIZE_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_RESERVE_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_SET_ACCESS_ATTRIBUTE_REGISTER_CALLBACK,
ID_L0L_TRACER_VIRTUAL_MEM_UNMAP_REGISTER_CALLBACK,
ID_L0_COMMAND_LIST_APPEND_SIGNAL_EXTERNAL_SEMAPHORE_EXT,
ID_L0_COMMAND_LIST_APPEND_WAIT_EXTERNAL_SEMAPHORE_EXT,
ID_L0_KERNEL_GET_BINARY_EXP,
ID_L0L_TRACER_COMMAND_LIST_APPEND_SIGNAL_EXTERNAL_SEMAPHORE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_COMMAND_LIST_APPEND_WAIT_EXTERNAL_SEMAPHORE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_IMPORT_EXTERNAL_SEMAPHORE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_DEVICE_RELEASE_EXTERNAL_SEMAPHORE_EXT_REGISTER_CALLBACK,
ID_L0L_TRACER_KERNEL_GET_BINARY_EXP_REGISTER_CALLBACK,
ID_L0S_VF_MANAGEMENT_GET_VF_CAPABILITIES_EXP2,
ID_RESERVED_TOKEN_2,
