// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

/**
* @file   vulkanDrivers.cpp
*
* @brief
*/
#include "openclDrivers.h"
#include "openclTracing.h"
#ifndef BUILD_FOR_CCODE
#include "openclStateDynamic.h"
#include "openclArgumentsAuto.h"
#include "openclTools.h"
#include "lua_bindings.h"

#include <tuple>
#include <type_traits>
#endif

#include "config.h"
#include "gits.h"

DISABLE_WARNINGS
#include <boost/filesystem/path.hpp>
ENABLE_WARNINGS

namespace gits {
namespace OpenCL {
#ifndef BUILD_FOR_CCODE
struct Tracer {
  template <class T>
  NOINLINE void trace_ret(T r) {
    if (ShouldLog(level)) {
      COclLog(level, NO_PREFIX) << " = " << r;
    }
  }

  template <class T>
  NOINLINE void trace_ret(T* r) {
    if (r == nullptr) {
      if (ShouldLog(level)) {
        COclLog(level, NO_PREFIX) << " = nullptr";
      }
    } else {
      if (ShouldLog(level)) {
#ifdef GITS_PLATFORM_LINUX
        COclLog(level, NO_PREFIX) << " = " << r;
#else
        COclLog(level, NO_PREFIX) << " = 0x" << r;
#endif
      }
    }
  }

  NOINLINE void trace_ret(cl_int r) {
    if (ShouldLog(level)) {
      COclLog(level, NO_PREFIX) << " = " << CLResultToString(r);
    }
  }

  NOINLINE void trace_ret(void_t r) {
    if (ShouldLog(level)) {
      COclLog(level, NO_PREFIX) << "";
    }
  }

  template <class T>
  NOINLINE void trace_ret_lua(T r) {
    trace_name();
    if (ShouldLog(level)) {
      COclLog(level, RAW) << " Lua end";
    }
    trace_ret(r);
  }

  void print_args(COclLog& s) {}

  NOINLINE void print_args(COclLog& s, const char* t) {
    if (t == nullptr) {
      s << "nullptr";
    } else {
      s << "\"" << t << "\"";
    }
  }

  template <class T>
  NOINLINE void print_args(COclLog& s, T* t) {
    if (t == nullptr) {
      s << "nullptr";
    } else {
#ifdef GITS_PLATFORM_LINUX
      s << t;
#else
      s << "0x" << t;
#endif
    }
  }

  template <class T>
  NOINLINE typename std::enable_if<!std::is_base_of<TOclType, T>::value>::type print_args(
      COclLog& s, T t) {
    s << t;
  }

  template <class T>
  NOINLINE typename std::enable_if<std::is_base_of<TOclType, T>::value>::type print_args(COclLog& s,
                                                                                         T t) {
    s << t.ToString();
  }

  template <class Head, class... Rest>
  NOINLINE void print_args(COclLog& s, Head h, Rest... r) {
    print_args(s, h);
    s << ", ";
    print_args(s, r...);
  }

  Tracer(const char* nameStr) : name(nameStr) {}

  template <class... Args>
  NOINLINE void trace(Args... args) {
    if (ShouldLog(level)) {
      auto log = COclLog(level, RAW);
      log << "(";
      print_args(log, args...);
      log << ")";
    }
  }

  template <class... Args>
  NOINLINE void trace_lua(Args... args) {
    if (ShouldLog(level)) {
      auto log = COclLog(level, NO_PREFIX);
      log << "(";
      print_args(log, args...);
      log << ") Lua begin";
    }
  }

  NOINLINE void trace_name() {
    if (ShouldLog(level)) {
      auto log = COclLog(level, NO_NEWLINE);
      log << name;
    }
  }

private:
  const char* name;
  const LogLevel level = LogLevel::INFO;
};
#endif

namespace {
#ifdef BUILD_FOR_CCODE
bool CheckIntelGPUPlatform(const cl_platform_id& platform) {
  constexpr char intelPlatformVendorName[] = "Intel(R) Corporation";
  constexpr size_t intelPlatformVendorNameSize =
      sizeof(intelPlatformVendorName) / sizeof(intelPlatformVendorName[0]);
  size_t platformNameSize = 0;
  cl_int result =
      drvOcl.clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, 0, nullptr, &platformNameSize);
  if (result != CL_SUCCESS || platformNameSize != intelPlatformVendorNameSize) {
    return false;
  }
  char platformName[intelPlatformVendorNameSize];
  result = drvOcl.clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, intelPlatformVendorNameSize,
                                    platformName, nullptr);
  if (result == CL_SUCCESS && strcmp(platformName, intelPlatformVendorName) == 0) {
    cl_uint num_devices = 0;
    result = drvOcl.clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, nullptr, &num_devices);
    return result == CL_SUCCESS && num_devices > 0;
  }
  return false;
}
#endif
cl_platform_id GetPlatform(const char* functionName) {
#ifndef BUILD_FOR_CCODE
  const auto platformStates = SD()._platformIDStates;
  cl_platform_id firstGPUPlatform = nullptr;
  cl_platform_id firstNonGPUPlatform = nullptr;
  for (const auto& state : platformStates) {
    const auto exists = state.second->ExtensionFunctionExists(functionName);
    if (exists) {
      const bool isGPU = state.second->GetDeviceType(CL_DEVICE_TYPE_GPU);
      if (isGPU && CheckIntelPlatform(state.first)) {
        return state.first;
      } else if (isGPU && firstGPUPlatform == nullptr) {
        firstGPUPlatform = state.first;
      } else if (firstNonGPUPlatform == nullptr) {
        firstNonGPUPlatform = state.first;
      }
    }
  }
  if (firstGPUPlatform != nullptr) {
    return firstGPUPlatform;
  } else if (firstNonGPUPlatform != nullptr) {
    return firstNonGPUPlatform;
  }

  for (const auto& state : platformStates) {
    if (CheckIntelPlatform(state.first) &&
        state.second->GetDeviceType(CL_DEVICE_TYPE_GPU) != nullptr) {
      return state.first;
    }
  }
  return platformStates.empty() ? nullptr : platformStates.begin()->first;
#else
  // Temporary workaround for ccode compilation.
  (void)functionName;
  cl_uint numberOfPlatforms = 0;
  cl_int result = drvOcl.clGetPlatformIDs(0, nullptr, &numberOfPlatforms);
  if (result != CL_SUCCESS) {
    return nullptr;
  }
  std::vector<cl_platform_id> platforms(numberOfPlatforms);
  result = drvOcl.clGetPlatformIDs(numberOfPlatforms, platforms.data(), nullptr);
  if (result != CL_SUCCESS) {
    return nullptr;
  }
  for (const auto& platform : platforms) {
    if (CheckIntelGPUPlatform(platform)) {
      return platform;
    }
  }
  return platforms.empty() ? nullptr : platforms[0];
#endif
}
NOINLINE bool load_ocl_function_generic(void*& func, const char* name) {
  auto lib = drvOcl.Library();
  if (lib == nullptr) {
    return false;
  }
  func = dl::load_symbol(lib, name);
  if (func == nullptr) {
    if (drvOcl.clGetExtensionFunctionAddressForPlatform != nullptr) {
      const auto platform = GetPlatform(name);
      func = drvOcl.clGetExtensionFunctionAddressForPlatform(platform, name);
      if (func == nullptr) {
        Log(ERR) << name << " not found";
        return false;
      }
    } else {
      Log(ERR) << name << " not found";
      return false;
    }
  }

  return true;
}

template <class T>
bool load_ocl_function(T& func, const char* name) {
  return load_ocl_function_generic(reinterpret_cast<void*&>(func), name);
}
} // namespace

void COclDriver::Initialize() {
  if (_initialized) {
    return;
  }
  boost::filesystem::path path;
  path = gits::Config::Get().common.libClPath;
  Log(INFO) << "Initializing OpenCL API";
  _lib = dl::open_library(path.string().c_str());
  if (_lib == nullptr) {
    Log(ERR) << dl::last_error();
  }
  _initialized = true;
}

static bool bypass_luascript;

#ifndef BUILD_FOR_CCODE

static NOINLINE lua_State* GetLuaState() {
  return CGits::Instance().GetLua().get();
}

#define LUA_FUNCTION_EXISTS(function) lua::FunctionExists(function, GetLuaState())
#else
#define LUA_FUNCTION_EXISTS(function) false
#endif

NOINLINE bool UseTracing(const char* func) {
  const auto& cfg = Config::Get();
  return (gits::ShouldLog(gits::LogLevel::TRACE)) ||
         (cfg.common.useEvents && LUA_FUNCTION_EXISTS(func)) ||
         (!cfg.player.traceSelectedFrames.empty());
}

NOINLINE void LogFunctionBeforeContext(const char* func) {
  Log(WARN) << "Function " << func << " not found in OpenCL library";
}

#ifndef BUILD_FOR_CCODE

#define SPECIAL_FUNCTION(type, name, decl_args, call_args, trace_args, err_fun, drv_name)          \
  type STDCALL special_##name decl_args {                                                          \
    bool doTrace = ShouldLog(TRACE);                                                               \
    auto tracer = Tracer(#name);                                                                   \
    type gits_ret = (type)0;                                                                       \
    bool call_orig = true;                                                                         \
    if (doTrace)                                                                                   \
      tracer.trace_name();                                                                         \
    if (Config::Get().common.useEvents && !bypass_luascript) {                                     \
      auto L = GetLuaState();                                                                      \
      bool exists = !doTrace || lua::FunctionExists(#name, L);                                     \
      if (exists) {                                                                                \
        if (doTrace)                                                                               \
          tracer.trace_lua trace_args;                                                             \
        boost::unique_lock<boost::recursive_mutex> lock(gits::lua::luaMutex);                      \
        LUA_CALL_FUNCTION(L, #name, call_args, decl_args)                                          \
        call_orig = false;                                                                         \
        int top = lua_gettop(L);                                                                   \
        gits_ret = lua::lua_to<type>(L, top);                                                      \
        lua_pop(L, top);                                                                           \
        if (doTrace)                                                                               \
          tracer.trace_ret_lua(gits_ret);                                                          \
      }                                                                                            \
    }                                                                                              \
    if (call_orig) {                                                                               \
      if (doTrace)                                                                                 \
        tracer.trace trace_args;                                                                   \
      gits_ret = drv_name.orig_##name call_args;                                                   \
      if (doTrace)                                                                                 \
        tracer.trace_ret(gits_ret);                                                                \
    }                                                                                              \
                                                                                                   \
    return gits_ret;                                                                               \
  }

using namespace lua;

#define LUA_FUNCTION(RET, NAME, ARGS_DECL, DRV)                                                    \
  int lua_##NAME(lua_State* L) {                                                                   \
    boost::unique_lock<boost::recursive_mutex> lock(gits::lua::luaMutex);                          \
    int top = lua_gettop(L);                                                                       \
    if (top != Argnum<RET ARGS_DECL>::value)                                                       \
      luaL_error(L, "invalid number of parameters");                                               \
                                                                                                   \
    FuncToTuple<RET ARGS_DECL>::type args;                                                         \
    fill_tuple(L, args);                                                                           \
    bypass_luascript = true;                                                                       \
    RET ret = call_tuple<RET>(gits::OpenCL::DRV.NAME, args);                                       \
    bypass_luascript = false;                                                                      \
    gits::lua::lua_push(L, ret);                                                                   \
                                                                                                   \
    return 1;                                                                                      \
  }

#else

#define SPECIAL_FUNCTION(type, name, decl_args, call_args, trace_args, err_fun, drv_name)          \
  type STDCALL special_##name decl_args {                                                          \
    return (type)0;                                                                                \
  }

#define LUA_FUNCTION(RET, NAME, ARGS_DECL, DRV)                                                    \
  int lua_##NAME(struct lua_State* L) {                                                            \
    return 1;                                                                                      \
  }

#endif

#define LUA_OCL_FUNCTION(b, c, d, e, f) LUA_FUNCTION(b, c, d, drvOcl)

#define SPECIAL_OCL_FUNCTION(b, c, d, e, f) SPECIAL_FUNCTION(b, c, d, e, f, OCLErrorLog, drvOcl)

#define DEFAULT_FUNCTION(type, name, decl_args, call_args, trace_args, load_func, drv_name)        \
  type STDCALL default_##name decl_args {                                                          \
    if (!load_func(drv_name.name, #name)) {                                                        \
      LogFunctionBeforeContext(#name);                                                             \
      return (type)0;                                                                              \
    }                                                                                              \
    drv_name.orig_##name = drv_name.name;                                                          \
    if (UseTracing(#name))                                                                         \
      drv_name.name = special_##name;                                                              \
    return drv_name.name call_args;                                                                \
  }

#define DEFAULT_OCL_FUNCTION(b, c, d, e, f)                                                        \
  DEFAULT_FUNCTION(b, c, d, e, f, load_ocl_function, drvOcl)
OCL_FUNCTIONS(SPECIAL_)
OCL_FUNCTIONS(DEFAULT_)
OCL_FUNCTIONS(LUA_)

#ifndef BUILD_FOR_CCODE
#define LUA_EXPORT_OCL_FUNCTION(b, c, d, e, f) {#c, lua_##c},

namespace {
int export_CLStatusToStr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 1) {
    luaL_error(L, "invalid number of parameters");
  }

  int status = lua_to<int>(L, 1);
  std::string str = gits::OpenCL::CLResultToString(status);
  lua_pushstring(L, str.c_str());
  return 1;
}

// callbacks support
struct CLCallbackProxy {
  lua_State* state;
  int funcID;
  int threadID;
  void* userData;
};

// event
std::function<void(cl_event, cl_int, void*)> CreateEventCallbackWrapper(lua_State* L,
                                                                        int function) {
  return [=](cl_event t0, cl_int t1, void* t2) -> void {
    lua_rawgeti(L, LUA_REGISTRYINDEX, function);
    lua_push(L, t0);
    lua_push(L, t1);
    lua_push(L, t2);
    if (lua_pcall(L, 3, 0, 0) != 0) {
      RaiseHookError("CLEventCallback", L);
    }
  };
}

void CL_CALLBACK EventCallback(cl_event e, cl_int s, void* ud) {
  if (ud != nullptr) {
    CLCallbackProxy* proxy = static_cast<CLCallbackProxy*>(ud);
    ud = proxy->userData;
    // This is called from a different thread, so GITS' exception handlers
    // won't catch it.
    try {
      CreateEventCallbackWrapper(proxy->state, proxy->funcID)(e, s, ud);
    } catch (std::runtime_error& e) {
      OclLog(ERR) << e.what();
      delete proxy;
      return;
    }
    delete proxy;
  } else {
    OclLog(WARN) << "CLEventCallback: something went wrong with sending data to callback function.";
  }
}

int export_EventCallbackPtr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 0) {
    luaL_error(L, "invalid number of parameters");
  }

  lua_pushlightuserdata(L, (void*)EventCallback);
  return 1;
}

// memobj
std::function<void(cl_mem, void*)> CreateMemObjCallbackWrapper(lua_State* L, int function) {
  return [=](cl_mem t0, void* t1) -> void {
    lua_rawgeti(L, LUA_REGISTRYINDEX, function);
    lua_push(L, t0);
    lua_push(L, t1);
    if (lua_pcall(L, 2, 0, 0) != 0) {
      RaiseHookError("CLMemObjCallback", L);
    }
  };
}

void CL_CALLBACK MemObjCallback(cl_mem m, void* ud) {
  if (ud != nullptr) {
    CLCallbackProxy* proxy = static_cast<CLCallbackProxy*>(ud);
    ud = proxy->userData;
    // This is called from a different thread, so GITS' exception handlers
    // won't catch it.
    try {
      CreateMemObjCallbackWrapper(proxy->state, proxy->funcID)(m, ud);
    } catch (std::runtime_error& e) {
      OclLog(ERR) << e.what();
      delete proxy;
      return;
    }
    delete proxy;
  } else {
    OclLog(WARN)
        << "CLMemObjCallback: something went wrong with sending data to callback function.";
  }
}

int export_MemObjCallbackPtr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 0) {
    luaL_error(L, "invalid number of parameters");
  }

  lua_pushlightuserdata(L, (void*)MemObjCallback);
  return 1;
}

// program
std::function<void(cl_program, void*)> CreateProgramCallbackWrapper(lua_State* L, int function) {
  return [=](cl_program t0, void* t1) -> void {
    lua_rawgeti(L, LUA_REGISTRYINDEX, function);
    lua_push(L, t0);
    lua_push(L, t1);
    if (lua_pcall(L, 2, 0, 0) != 0) {
      RaiseHookError("CLProgramCallback", L);
    }
  };
}

void CL_CALLBACK ProgramCallback(cl_program p, void* ud) {
  if (ud != nullptr) {
    CLCallbackProxy* proxy = static_cast<CLCallbackProxy*>(ud);
    ud = proxy->userData;
    // This is called from a different thread, so GITS' exception handlers
    // won't catch it.
    try {
      CreateProgramCallbackWrapper(proxy->state, proxy->funcID)(p, ud);
    } catch (std::runtime_error& e) {
      OclLog(ERR) << e.what();
      delete proxy;
      return;
    }
    delete proxy;
  } else {
    OclLog(WARN)
        << "CLProgramCallback: something went wrong with sending data to callback function.";
  }
}

int export_ProgramCallbackPtr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 0) {
    luaL_error(L, "invalid number of parameters");
  }

  lua_pushlightuserdata(L, (void*)ProgramCallback);
  return 1;
}

// context
std::function<void(const char*, const void*, size_t, void*)> CreateContextCallbackWrapper(
    lua_State* L, int function) {
  return [=](const char* t0, const void* t1, size_t t2, void* t3) -> void {
    lua_rawgeti(L, LUA_REGISTRYINDEX, function);
    lua_push(L, t0);
    lua_push(L, t1);
    lua_push(L, t2);
    lua_push(L, t3);
    if (lua_pcall(L, 4, 0, 0) != 0) {
      RaiseHookError("CLContextCallback", L);
    }
  };
}

void CL_CALLBACK ContextCallback(const char* ei, const void* pi, size_t cb, void* ud) {
  if (ud != nullptr) {
    CLCallbackProxy* proxy = static_cast<CLCallbackProxy*>(ud);
    ud = proxy->userData;
    // This is called from a different thread, so GITS' exception handlers
    // won't catch it.
    try {
      CreateContextCallbackWrapper(proxy->state, proxy->funcID)(ei, pi, cb, ud);
    } catch (std::runtime_error& e) {
      OclLog(ERR) << e.what();
      delete proxy;
      return;
    }
    delete proxy;
  } else {
    OclLog(WARN)
        << "CLContextCallback: something went wrong with sending data to callback function.";
  }
}

int export_ContextCallbackPtr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 0) {
    luaL_error(L, "invalid number of parameters");
  }

  lua_pushlightuserdata(L, (void*)ContextCallback);
  return 1;
}

// SVM free
std::function<void(cl_command_queue, cl_uint, void**, void*)> CreateSVMFreeCallbackWrapper(
    lua_State* L, int function) {
  return [=](cl_command_queue t0, cl_uint t1, void** t2, void* t3) -> void {
    lua_rawgeti(L, LUA_REGISTRYINDEX, function);
    lua_push(L, t0);
    lua_push(L, t1);
    lua_push(L, t2);
    lua_push(L, t3);
    if (lua_pcall(L, 4, 0, 0) != 0) {
      RaiseHookError("CLSVMFreeCallback", L);
    }
  };
}

void CL_CALLBACK SVMFreeCallback(cl_command_queue cq, cl_uint n, void** p, void* ud) {
  if (ud != nullptr) {
    CLCallbackProxy* proxy = static_cast<CLCallbackProxy*>(ud);
    ud = proxy->userData;
    // This is called from a different thread, so GITS' exception handlers
    // won't catch it.
    try {
      CreateSVMFreeCallbackWrapper(proxy->state, proxy->funcID)(cq, n, p, ud);
    } catch (std::runtime_error& e) {
      OclLog(ERR) << e.what();
      delete proxy;
      return;
    }
    delete proxy;
  } else {
    OclLog(WARN)
        << "CLSVMFreeCallback: something went wrong with sending data to callback function.";
  }
}

int export_SVMFreeCallbackPtr(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 0) {
    luaL_error(L, "invalid number of parameters");
  }

  lua_pushlightuserdata(L, (void*)SVMFreeCallback);
  return 1;
}

// setting callback Lua function and user data
int export_CallbackData(lua_State* L) {
  int top = lua_gettop(L);
  if (top != 2) {
    luaL_error(L, "invalid number of parameters");
  }
  auto user_data = lua_to<void**>(L, 2);
  lua_pop(L, 1); // required to get ref to function
  int function = luaL_ref(L, LUA_REGISTRYINDEX);

  lua_State* state = lua_newthread(L);
  int thread = luaL_ref(L, LUA_REGISTRYINDEX);
  // XXX: (kkasper) potential leak, but I have no idea how to do it better
  CLCallbackProxy* proxy = new CLCallbackProxy;
  proxy->state = state;
  proxy->funcID = function;
  proxy->threadID = thread;
  proxy->userData = user_data;

  lua_pushlightuserdata(L, (void*)proxy);
  return 1;
}
} // namespace

const luaL_Reg exports[] = {{"statusToStr", export_CLStatusToStr},
                            {"getEventCallbackPtr", export_EventCallbackPtr},
                            {"getMemObjCallbackPtr", export_MemObjCallbackPtr},
                            {"getProgramCallbackPtr", export_ProgramCallbackPtr},
                            {"getContextCallbackPtr", export_ContextCallbackPtr},
                            {"getSVMFreeCallbackPtr", export_SVMFreeCallbackPtr},
                            {"setCallbackData", export_CallbackData},
                            OCL_FUNCTIONS(LUA_EXPORT_){nullptr, nullptr}};
#endif

void RegisterLuaDriverFunctions() {
#ifndef BUILD_FOR_CCODE
  auto L = CGits::Instance().GetLua();
  luaL_newlib(L.get(), exports);
  lua_setglobal(L.get(), "drvCl");
#endif
}

COclDriver::COclDriver() : _initialized(false), _lib(nullptr) {
#define INITIALIZE_OCL_FUNCTION(b, c, d, e, f) drvOcl.c = default_##c;
  OCL_FUNCTIONS(INITIALIZE_)
#undef INITIALIZE_OCL_FUNCTION

#if !defined(BUILD_FOR_CCODE)
  CGits::Instance().RegisterLuaFunctionsRegistrator(RegisterLuaDriverFunctions);
#endif
}

COclDriver::~COclDriver() {
  dl::close_library(_lib);
}

COclDriver drvOcl;
} // namespace OpenCL
} // namespace gits
