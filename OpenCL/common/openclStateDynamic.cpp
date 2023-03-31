// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

/**
* @file   openclStateDynamic.cpp
*
* @brief Definition of OpenCL common part library implementation.
*
*/

#include "openclStateDynamic.h"
#include "gits.h"
#include "openclTools.h"

namespace gits {
namespace OpenCL {
namespace {
uint64_t GetUniqueStateID() {
  static uint64_t stateID = 0;
  return ++stateID;
}
} // namespace

CStateDynamic::CStateDynamic() {}

CStateDynamic::~CStateDynamic() {
  layoutBuilder.SaveLayoutToJsonFile();
}

CStateDynamic& CStateDynamic::Get() {
  static CStateDynamic ptr = CStateDynamic();
  return ptr;
}

std::set<std::string> CCLPlatformIDState::GetExtensionFunctions() const {
  return _extensionFunctions;
}

void CCLPlatformIDState::AddExtensionFunction(const char* name) {
  _extensionFunctions.insert(std::string(name));
}

bool CCLPlatformIDState::ExtensionFunctionExists(const char* name) const {
  return _extensionFunctions.count(std::string(name)) > 0;
}

void CCLPlatformIDState::AddDevice(const cl_device_id& device, const cl_device_type& deviceType) {
  _devices[device] = deviceType;
}

cl_device_id CCLPlatformIDState::GetDeviceType(const cl_device_type& deviceType) const {
  for (const auto& it : _devices) {
    if (it.second == deviceType) {
      return it.first;
    }
  }
  return nullptr;
}

void CCLPlatformIDState::SetIntelPlatform() {
  _isIntelPlatform = true;
}

bool CCLPlatformIDState::IsIntelPlatform() const {
  return _isIntelPlatform;
}

CCLDeviceIDState::CCLDeviceIDState() : platform(nullptr), type(0) {}

CCLDeviceIDState::CCLDeviceIDState(cl_device_id parentDevice,
                                   const cl_device_partition_property* properties)
    : CCLDeviceIDState() {
  this->parentDevice = parentDevice;
  if (properties == nullptr) {
    return;
  }
  for (auto i = 0u; properties[i] != 0; i += 2) {
    this->properties.push_back(properties[i]);
    this->properties.push_back(properties[i + 1]);
  }
  this->properties.push_back(0);
}

CCLDeviceIDState::CCLDeviceIDState(cl_platform_id platform, cl_device_type type)
    : platform(platform), type(type) {}

CCLContextState::CCLContextState(bool fromType,
                                 const cl_context_properties* properties,
                                 const cl_device_type type)
    : devices(0), type(type), fromType(fromType), fakeQueue(nullptr) {
  if (properties == nullptr) {
    return;
  }

  for (size_t i = 0; properties[i] != 0; i += 2) {
    auto type_ = properties[i];
    if (type_ == CL_CONTEXT_PLATFORM) {
      platform = reinterpret_cast<cl_platform_id>(properties[i + 1]);
    }
    this->properties.push_back(properties[i]);
    this->properties.push_back(properties[i + 1]);
  }
  this->properties.push_back(0);
}

CCLEventState::CCLEventState()
    : isGLSharingEvent(false), isDXSharingEvent(false), isUserEvent(false) {}

CCLCommandQueueState::CCLCommandQueueState(cl_context context,
                                           cl_device_id device,
                                           cl_command_queue_properties queue_properties)
    : context(context),
      device(device),
      commandQueue2_0(false),
      queueProperties1_2(queue_properties) {}

CCLCommandQueueState::CCLCommandQueueState(cl_context context,
                                           cl_device_id device,
                                           const cl_queue_properties* properties)
    : context(context), device(device), commandQueue2_0(true) {
  if (properties) {
    for (size_t i = 0; properties[i] != 0; i += 2) {
      this->properties2_0.push_back(properties[i]);
      this->properties2_0.push_back(properties[i + 1]);
    }
  }
  this->properties2_0.push_back(0);
}

CCLKernelState::CCLKernelState() {}

CCLKernelState::CCLKernelState(const cl_program program, const char* name)
    : program(program), name(name), indirectUsmTypes(0) {
  programState = SD()._programStates[program];
  programState->Retain();
}

void CCLKernelState::SetArgument(cl_uint index, size_t size, const void* value) {
  args[index].type = KernelArgType::pointer;
  if (value) {
    // make sure the pointer won't be overridden
    if (size == sizeof(cl_mem) || size == sizeof(cl_sampler)) {
      uintptr_t ptr_value = *reinterpret_cast<const uintptr_t*>(value);
      if (ptr_value != 0) {
        pointers.push_back(std::make_unique<uintptr_t>());
        std::memcpy(pointers.back().get(), value, sizeof(uintptr_t));
        value = pointers.back().get();
        if (SD()._memStates.find((cl_mem)ptr_value) != SD()._memStates.end()) {
          args[index].type = KernelArgType::mem;
        } else if (SD()._samplerStates.find((cl_sampler)ptr_value) != SD()._samplerStates.end()) {
          args[index].type = KernelArgType::sampler;
        }
      }
    }
    if (size != 0 && (Config::IsRecorder() || !stream_older_than(GITS_OPENCL_SET_USM_ARG))) {
      auto* ptr_value = reinterpret_cast<void*>(*reinterpret_cast<const uintptr_t*>(value));
      auto* ptr = GetSvmOrUsmFromRegion(ptr_value).first;
      if (SD().CheckIfUSMAllocExists(ptr)) {
        args[index].type = KernelArgType::usm;
      }
      if (SD().CheckIfSVMAllocExists(ptr)) {
        args[index].type = KernelArgType::svm;
      }
    }
  }
  args[index].argValue = value;
  args[index].argSize = size;
}

const CCLKernelState::ArgInfo& CCLKernelState::GetArgument(cl_uint index) const {
  return args.at(index);
}

const std::map<cl_uint, CCLKernelState::ArgInfo>& CCLKernelState::GetArguments() const {
  return args;
}

void CCLKernelState::ClearArguments() {
  args.clear();
}

void CCLKernelState::SetArgType(const cl_uint& index, const KernelArgType& type) {
  args[index].type = type;
}

void CCLKernelState::SetArgSetType(const cl_uint& index, const KernelSetType& type) {
  args[index].kernelSetType = type;
}

CCLProgramState::CCLProgramState() {}

CCLProgramState::CCLProgramState(cl_context context,
                                 cl_uint num,
                                 const char** sources,
                                 const size_t* lengths,
                                 std::string filename)
    : _uniqueStateID(GetUniqueStateID()),
      _context(context),
      _num_devices(0),
      _filename(std::move(filename)) {
  Sources(num, sources, lengths);
  _headerIncludeNames =
      GetStringsWithRegex(*sources, R"((?<=^#include)\s*["<]([^">]+))", "\\s*[<\"]*");
  _hasHeaders = !_headerIncludeNames.empty();
}

CCLProgramState::CCLProgramState(cl_context context,
                                 cl_uint num,
                                 const cl_device_id* device_list,
                                 const unsigned char** binaries,
                                 const size_t* lengths)
    : _uniqueStateID(GetUniqueStateID()), _context(context), _num_devices(num) {
  _deviceList.assign(device_list, device_list + num);
  Binaries(num, binaries, lengths);
}

CCLProgramState::CCLProgramState(cl_context context, const void* il, const size_t length)
    : _uniqueStateID(GetUniqueStateID()), _context(context) {
  IL(il, length);
}

CCLProgramState::CCLProgramState(cl_context context,
                                 cl_uint num,
                                 const cl_device_id* device_list,
                                 const char* kernelNames)
    : _uniqueStateID(GetUniqueStateID()),
      _context(context),
      _num_devices(num),
      _kernelNames(kernelNames ? kernelNames : "") {
  _deviceList.assign(device_list, device_list + num);
}

CCLProgramState::CCLProgramState(cl_context context,
                                 cl_uint num,
                                 const cl_program* inputPrograms,
                                 const char* options)
    : _uniqueStateID(GetUniqueStateID()),
      _context(context),
      _num_devices(0),
      _inputPrograms(inputPrograms, inputPrograms + num),
      _buildOptions(options ? options : "") {
  for (const auto& prog : _inputPrograms) {
    if (SD()._programStates.find(prog) == SD()._programStates.end()) {
      throw EOperationFailed(EXCEPTION_MESSAGE);
    }
    _stateProgs[prog] = SD()._programStates.at(prog);
  }
}

void CCLProgramState::BuildProgram(cl_uint num_devices, const char* options) {
  _num_devices = num_devices;
  if (options != nullptr) {
    _buildOptions.assign(options);
  }
}

void CCLProgramState::CompileProgram(cl_uint num_devices,
                                     cl_uint num,
                                     const cl_program* inputHeaders,
                                     const char** headerIncludeNames,
                                     const char* options) {
  _num_devices = num_devices;
  if (num > 0) {
    _inputHeaders.assign(inputHeaders, inputHeaders + num);
    _headerIncludeNames.assign(headerIncludeNames, headerIncludeNames + num);
    // TODO: throw exception if one of these is nullptr?
  }
  if (options != nullptr) {
    _buildOptions.assign(options);
  }
}

void CCLProgramState::GetProgramInfoBinarySizes(size_t size, void* value) {
  if (value != nullptr) {
    const auto* v = reinterpret_cast<size_t*>(value);
    _binarySizes.assign(v, v + (size / sizeof(size_t)));
  }
}

void CCLProgramState::GetProgramInfoNumDevices(cl_uint num_devices) {
  _num_devices = num_devices;
}

void CCLProgramState::GetProgramInfoBinaries(const size_t& size, void* value) {
  const auto nDevices = size / sizeof(uint8_t*);
  auto* ptr = reinterpret_cast<const uint8_t**>(value);
  if (Config::IsRecorder()) {
    _binaryHash = HashBinaryData(nDevices, ptr, _binarySizes.data());
  } else {
    Binaries(nDevices, ptr, _binarySizes.data());
  }
}

const cl_context CCLProgramState::Context() const {
  return _context;
}

const std::string CCLProgramState::BuildOptions() const {
  return _buildOptions;
}

const cl_device_id* CCLProgramState::DeviceList() const {
  return _deviceList.data();
}

const char** CCLProgramState::Sources() {
  UpdateSourcePtrs();
  return _cStrArray.data();
}

const unsigned char** CCLProgramState::Binaries() {
  UpdateBinariesPtrs();
  return _cBinArray.data();
}

const size_t* CCLProgramState::SourceLengths() const {
  return _sourceLengths.data();
}

const cl_uint CCLProgramState::SourcesCount() {
  UpdateSourcePtrs();
  return static_cast<cl_uint>(_cStrArray.size());
}

const std::string CCLProgramState::Filename() const {
  return _filename;
}

const bool CCLProgramState::IsIL() const {
  return _il;
}

const std::vector<std::string> CCLProgramState::HeaderIncludeNames() const {
  return _headerIncludeNames;
}

const bool CCLProgramState::HasHeaders() const {
  return _hasHeaders;
}

const size_t* CCLProgramState::BinarySizes() const {
  return _binarySizes.data();
}

const size_t CCLProgramState::BinariesCount() const {
  int i = 0;
  for (auto size : _binarySizes) {
    if (size > 0) {
      i++;
    }
  }
  return i;
}

const cl_uint CCLProgramState::DevicesCount() const {
  return _num_devices;
}

const std::string CCLProgramState::KernelNames() const {
  return _kernelNames;
}

const std::vector<cl_program> CCLProgramState::InputProgramList() const {
  return _inputPrograms;
}

const std::vector<cl_program> CCLProgramState::InputHeaders() const {
  return _inputHeaders;
}

void CCLProgramState::ReallocBinaries() {
  for (unsigned i = 0; i < _num_devices; i++) {
    if (_binarySizes[i] > 0) {
      _binaries.push_back(ustring(_binarySizes[i], 0));
    }
  }
}

void CCLProgramState::Sources(const cl_uint num, const char** sources, const size_t* lengths) {
  _sources.assign(sources, sources + num);
  Update(num, lengths);
}

void CCLProgramState::Binaries(const cl_uint num,
                               const unsigned char* const* binaries,
                               const size_t* lengths) {
  isBinary = true;
  _binaries.resize(num);
  for (cl_uint i = 0; i < num; i++) {
    _binaries[i].assign(binaries[i], binaries[i] + lengths[i]);
  }
  _il = false;
  UpdateBinaries(num, lengths);
}

void CCLProgramState::IL(const void* il, const size_t length) {
  const unsigned char* ilBuffer = static_cast<const unsigned char*>(il);
  _binaries.resize(1);
  _binaries[0].assign(ilBuffer, ilBuffer + length);
  _il = true;
  UpdateBinaries(1, &length);
}

void CCLProgramState::Update(cl_uint num, const size_t* lengths) {
  if (num > 0) {
    if (lengths != nullptr) {
      _sourceLengths = std::vector<size_t>(lengths, lengths + num);
    }
  }
}

void CCLProgramState::UpdateSourcePtrs() {
  _cStrArray.clear();
  for (auto& source : _sources) {
    _cStrArray.push_back(source.c_str());
  }
}

void CCLProgramState::UpdateBinaries(cl_uint num, const size_t* lengths) {
  if (num > 0) {
    if (lengths != nullptr) {
      _binarySizes = std::vector<size_t>(lengths, lengths + num);
    }
  }
}

void CCLProgramState::UpdateBinariesPtrs() {
  _cBinArray.clear();
  for (auto& binary : _binaries) {
    _cBinArray.push_back(binary.c_str());
  }
}

const std::unordered_map<cl_program, std::shared_ptr<CCLProgramState>> CCLProgramState::
    GetProgramStates() const {
  return _stateProgs;
}

void CCLProgramState::AppendGlobalPointer(void* globalPtr) {
  _globalPtrs.push_back(globalPtr);
}

std::vector<void*> CCLProgramState::GetGlobalPointers() const {
  return _globalPtrs;
}

void CCLProgramState::SetBuildOptions(const std::string& options) {
  _buildOptions = options;
}

void CCLProgramState::SetProgramBinaryHash(const std::vector<uint64_t>& hash) {
  _binaryHash = hash;
}

std::vector<uint64_t> CCLProgramState::GetBinaryHash() const {
  return _binaryHash;
}

cl_program CCLProgramState::GetBinaryLinkedProgram() const {
  return _prebuiltProgram;
}

void CCLProgramState::SetBinaryLinkedProgram(const cl_program& program) {
  _prebuiltProgram = program;
}

CCLSamplerState::CCLSamplerState(cl_context context,
                                 cl_bool normalized_coords,
                                 cl_addressing_mode addressing_mode,
                                 cl_filter_mode filter_mode)
    : context(context),
      normalized_coords(normalized_coords),
      addressing_mode(addressing_mode),
      filter_mode(filter_mode),
      crateSamplerWithProperties(false) {}

CCLSamplerState::CCLSamplerState(cl_context context, const cl_sampler_properties* properties)
    : context(context), crateSamplerWithProperties(true) {
  if (properties) {
    for (size_t i = 0; properties[i] != 0; i += 2) {
      this->properties.push_back(properties[i]);
      this->properties.push_back(properties[i + 1]);
    }
  }
  this->properties.push_back(0);
}

CCLMemState::CCLMemState() : context(nullptr), flags(0), size(0) {}

CCLMemState::CCLMemState(cl_context context, cl_mem_flags flags, size_t size, void* host_ptr)
    : context(context),
      flags(flags),
      size(size),
      buffer(true),
      image(false),
      pipe(false),
      pipe_packet_size(0),
      pipe_max_packets(0) {
  index = ++count();
}

CCLMemState::CCLMemState(cl_context context,
                         cl_mem_properties_intel* props,
                         size_t size,
                         void* host_ptr)
    : context(context),
      flags(0),
      intel_mem_properties(props, props + GetNullTermArraySize(props, 2) + 1),
      size(size),
      buffer(true),
      image(false),
      pipe(false),
      pipe_packet_size(0),
      pipe_max_packets(0) {
  index = ++count();
}

CCLMemState::CCLMemState(cl_context context,
                         cl_mem_flags flags,
                         size_t size,
                         const cl_image_format* image_format,
                         const cl_image_desc* image_desc,
                         void* host_ptr)
    : context(context),
      flags(flags),
      size(size),
      buffer(false),
      image(true),
      pipe(false),
      pipe_packet_size(0),
      pipe_max_packets(0) {
  index = ++count();
  this->image_format = *image_format;
  this->image_desc = *image_desc;
}

CCLMemState::CCLMemState(cl_context context,
                         cl_mem_properties_intel* props,
                         size_t size,
                         const cl_image_format* image_format,
                         const cl_image_desc* image_desc,
                         void* host_ptr)
    : context(context),
      flags(0),
      intel_mem_properties(props, props + GetNullTermArraySize(props, 2) + 1),
      size(size),
      buffer(false),
      image(true),
      pipe(false),
      pipe_packet_size(0),
      pipe_max_packets(0) {
  index = ++count();
  this->image_format = *image_format;
  this->image_desc = *image_desc;
}

CCLMemState::CCLMemState(cl_mem buffer,
                         cl_mem_flags flags,
                         cl_buffer_create_type buffer_create_type,
                         const void* buffer_create_info)
    : context(nullptr),
      flags(flags),
      bufferObj(buffer),
      buffer_create_type(buffer_create_type),
      buffer(false),
      image(false),
      pipe(false) {
  index = ++count();
  if (buffer_create_type == CL_BUFFER_CREATE_TYPE_REGION) {
    const cl_buffer_region* region = static_cast<const cl_buffer_region*>(buffer_create_info);
    size = region->size;
    origin = region->origin;
  }
}

CCLMemState::CCLMemState(cl_context context,
                         cl_mem_flags flags,
                         cl_uint pipe_packet_size,
                         cl_uint pipe_max_packets,
                         const cl_pipe_properties* properties)
    : context(context),
      flags(flags),
      buffer(false),
      image(false),
      pipe(true),
      pipe_packet_size(pipe_packet_size),
      pipe_max_packets(pipe_max_packets) {
  index = ++count();
  if (properties) {
    for (size_t i = 0; properties[i] != 0; i += 2) {
      this->pipe_properties.push_back(properties[i]);
      this->pipe_properties.push_back(properties[i + 1]);
    }
  }
  this->pipe_properties.push_back(0);
}

CCLSVMAllocState::CCLSVMAllocState(cl_context context,
                                   cl_svm_mem_flags flags,
                                   size_t size,
                                   cl_uint alignment)
    : context(context),
      flags(flags),
      size(size),
      alignment(alignment),
      sniffedRegionHandle(nullptr) {}

CCLUSMAllocState::CCLUSMAllocState(cl_context context,
                                   cl_mem_properties_intel* properties,
                                   size_t size,
                                   cl_uint alignment,
                                   UnifiedMemoryType type)
    : context(context), size(size), alignment(alignment), type(type), sniffedRegionHandle(nullptr) {
  if (properties) {
    for (size_t i = 0; properties[i] != 0; i += 2) {
      this->properties.push_back(properties[i]);
      this->properties.push_back(properties[i + 1]);
    }
  }
  this->properties.push_back(0);
}

CCLUSMAllocState::CCLUSMAllocState(cl_context context,
                                   cl_device_id device,
                                   cl_mem_properties_intel* properties,
                                   size_t size,
                                   cl_uint alignment,
                                   UnifiedMemoryType type)
    : CCLUSMAllocState(context, properties, size, alignment, type) {
  this->device = device;
}

CCLUSMAllocState::CCLUSMAllocState(cl_device_id device,
                                   size_t size,
                                   UnifiedMemoryType type,
                                   cl_program program,
                                   const char* global_variable_name)
    : CCLUSMAllocState(nullptr, device, nullptr, size, 0, type) {
  this->program = program;
  this->global_variable_name = global_variable_name;
}

CCLMappedBufferState::CCLMappedBufferState() : buffer(0) {}

CCLMappedBufferState::CCLMappedBufferState(const size_t& size,
                                           const cl_mem& buffer,
                                           const cl_command_queue& commandQueue,
                                           const cl_map_flags& mapFlags)
    : size(size),
      bufferObj(buffer),
      buffer(size, '\0'),
      commandQueue(commandQueue),
      mapFlags(mapFlags) {}

LayoutBuilder::LayoutBuilder()
    : _layout(),
      _kernelState(nullptr),
      _latestFileName(""),
      _argNumber(0),
      _enqueueCallNumber(0),
      _buffer(true) {}

void LayoutBuilder::UpdateLayout(const CCLKernelState& ks, int enqNum, int argNum) {
  _kernelState = &ks;
  _argNumber = argNum;
  const auto& arg = ks.GetArgument(argNum);
  if (_enqueueCallNumber != enqNum) {
    AddBuildOptions(ks);
    _SaveBuildOptions();
    _enqueueCallNumber = enqNum;
  }
  if (arg.type == KernelArgType::mem) {
    const auto& memState =
        SD().GetMemState(*reinterpret_cast<const cl_mem*>(arg.argValue), EXCEPTION_MESSAGE);
    if (memState.image) {
      _image_desc = memState.image_desc;
      _image_format = memState.image_format;
      _buffer = false;
      return _AddImage();
    }
  }
  _buffer = true;
  return _AddBuffer();
}

std::string LayoutBuilder::GetFileName() {
  return _latestFileName;
}

void LayoutBuilder::SaveLayoutToJsonFile() {
  if (_layout.empty()) {
    return;
  }
  const auto& cfg = Config::Get();
  bfs::path path =
      (cfg.player.outputDir.empty() ? cfg.common.streamDir / "dump" : cfg.player.outputDir) /
      "layout.json";
  SaveJsonFile(_layout, path);
}

std::string LayoutBuilder::_GetKeyName() {
  std::stringstream ss;
  ss << _kernelState->name << ".clEnqueueNDRangeKernel." << _enqueueCallNumber << ".arg_"
     << _argNumber;
  return ss.str();
}

void LayoutBuilder::AddBuildOptions(const CCLKernelState& ks) {
  _kernelState = &ks;
  if (_kernelState->programState->isBinary) {
    return;
  }

  std::string options = _kernelState->programState->BuildOptions();
  if (Config::Get().IsRecorder()) {
    options = AppendKernelArgInfoOption(options);
    options = AppendStreamPathToIncludePath(options, _kernelState->programState->HasHeaders());
  }
  _buildOptions[ks.name] = options;
}

void LayoutBuilder::_SaveBuildOptions() {
  std::string key(_kernelState->name + ".build_options");
  std::string pathToBuildOptions(_layout.get<std::string>(key, ""));
  if (pathToBuildOptions.empty() && _buildOptions[_kernelState->name] != "") {
    _layout.add(key, _buildOptions[_kernelState->name]);
  }
}

std::string LayoutBuilder::_BuildFileName() {
  static int fileCounter = 1;
  std::stringstream fileName;
  _buffer ? fileName << "NDRangeBuffer_" << _enqueueCallNumber << "_arg_" << _argNumber << "_"
                     << fileCounter++
          : fileName << "NDRangeImage_" << _enqueueCallNumber << "_arg_" << _argNumber << "_"
                     << fileCounter++;
  _latestFileName = fileName.str();
  return _latestFileName;
}

void LayoutBuilder::_AddBuffer() {
  _layout.add(_GetKeyName(), _BuildFileName());
}

void LayoutBuilder::_AddImage() {
  boost::property_tree::ptree ptTemp, imageDescription;
  std::array<size_t, 3> sizes = GetSimplifiedImageSizes(_image_desc);
  size_t width = sizes[0], height = sizes[1], depth = sizes[2];
  std::string image_type = get_texel_format_string(GetTexelToConvertFromImageFormat(_image_format));

  imageDescription.add("image_type", image_type);
  imageDescription.add("image_width", width);
  imageDescription.add("image_height", height);
  imageDescription.add("image_depth", depth);

  ptTemp.add_child(_BuildFileName(), imageDescription);
  _layout.add_child(_GetKeyName(), ptTemp);
}
} // namespace OpenCL
} // namespace gits
