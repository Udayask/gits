#!/usr/bin/python

# ===================== begin_copyright_notice ============================
#
# Copyright (C) 2023-2024 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
# ===================== end_copyright_notice ==============================

from generator_vulkan import (
    get_functions,
    get_structs,
    get_enums,
    FuncType,
    FuncLevel,
    Token,
    Argument,
    ReturnValue,
    VkStruct,
    Field,
    VkEnum,
    Enumerator,
)

from datetime import datetime
from pathlib import Path
from typing import TypeVar
import copy
import inspect
import platform
import re
import shutil
import textwrap

import mako.template
import mako.exceptions



Versioned = TypeVar('Versioned', Token, VkStruct)  # Enums aren't versioned.


AUTO_GENERATED_HEADER = f"""
//
// FILE AUTO-GENERATED BY THE GITS CODE GENERATOR. DO NOT MODIFY DIRECTLY.
// GENERATED ON: {datetime.now()}
//
""".strip('\n')


# Vulkan types categorized
# TODO: these are almost constants, should names be in ALL_CAPS?

vulkan_flags: list[str] = ['VkFlags']
vulkan_flags64: list[str] = ['VkFlags64']
for enum in get_enums():
    if 'FlagBits' in enum.name:
        flags_name = enum.name.replace('FlagBits', 'Flags')
        if enum.size == 64:
            vulkan_flags64.append(flags_name)
        else:
            vulkan_flags.append(flags_name)

# Flags that are used in functions or structs, but are not listed in generator.
# We assume they are 32 bits wide.
# TODO: Add them to the generator (as *FlagBits enums).
vk_used_unknown_flags: list[str] = [
    'VkAccelerationStructureMotionInfoFlagsNV',
    'VkAccelerationStructureMotionInstanceFlagsNV',
    'VkBufferViewCreateFlags',
    'VkCommandPoolTrimFlags',
    'VkDebugUtilsMessengerCallbackDataFlagsEXT',
    'VkDebugUtilsMessengerCreateFlagsEXT',
    'VkDescriptorPoolResetFlags',
    'VkDescriptorUpdateTemplateCreateFlags',
    'VkDeviceCreateFlags',
    'VkDeviceMemoryReportFlagsEXT',
    'VkDirectDriverLoadingFlagsLUNARG',
    'VkDisplayModeCreateFlagsKHR',
    'VkDisplaySurfaceCreateFlagsKHR',
    'VkHeadlessSurfaceCreateFlagsEXT',
    'VkIOSSurfaceCreateFlagsMVK',
    'VkMacOSSurfaceCreateFlagsMVK',
    'VkMemoryMapFlags',
    'VkMemoryUnmapFlagsKHR',
    'VkPipelineCoverageModulationStateCreateFlagsNV',
    'VkPipelineCoverageReductionStateCreateFlagsNV',
    'VkPipelineCoverageToColorStateCreateFlagsNV',
    'VkPipelineDiscardRectangleStateCreateFlagsEXT',
    'VkPipelineDynamicStateCreateFlags',
    'VkPipelineInputAssemblyStateCreateFlags',
    'VkPipelineMultisampleStateCreateFlags',
    'VkPipelineRasterizationConservativeStateCreateFlagsEXT',
    'VkPipelineRasterizationDepthClipStateCreateFlagsEXT',
    'VkPipelineRasterizationStateCreateFlags',
    'VkPipelineRasterizationStateStreamCreateFlagsEXT',
    'VkPipelineTessellationStateCreateFlags',
    'VkPipelineVertexInputStateCreateFlags',
    'VkPipelineViewportStateCreateFlags',
    'VkPipelineViewportSwizzleStateCreateFlagsNV',
    'VkQueryPoolCreateFlags',
    'VkValidationCacheCreateFlagsEXT',
    'VkVideoBeginCodingFlagsKHR',
    'VkVideoDecodeFlagsKHR',
    'VkVideoEncodeFlagsKHR',
    'VkVideoEncodeRateControlFlagsKHR',
    'VkVideoEndCodingFlagsKHR',
    'VkVideoSessionParametersCreateFlagsKHR',
    'VkWaylandSurfaceCreateFlagsKHR',
    'VkWin32SurfaceCreateFlagsKHR',
    'VkXcbSurfaceCreateFlagsKHR',
    'VkXlibSurfaceCreateFlagsKHR',
]
vulkan_flags += vk_used_unknown_flags

vulkan_uint32: list[str] = vulkan_flags + [
    'uint32_t',
    'bool32_t',
    'VkBool32',
]
vulkan_uint64: list[str] = vulkan_flags64 + [
    'VkDeviceSize',
    'VkDeviceAddress',
]

vulkan_union: list[str] = []
for struct in get_structs():
  if struct.type == 'union':
    vulkan_union.append(struct.name.rstrip('_'))

vulkan_other_primitives: list[str] = [
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
    "nullptr",
]

vulkan_enums: list[str] = [enum.name for enum in get_enums()]

# TODO: Remove the rstrip once '_' is removed from struct names in generator data.
vulkan_structs: list[str] = [struct.name.rstrip('_') for struct in get_structs()]

primitive_types: list[str] = (
    vulkan_enums
    + vulkan_uint32
    + vulkan_uint64
    + vulkan_union
    + vulkan_other_primitives
)


opaque_dispatchable_handles: list[str] = [
    "VkInstance",
    "VkPhysicalDevice",
    "VkDevice",
    "VkQueue",
    "VkCommandBuffer",
]

opaque_nondispatchable_handles: list[str] = [
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
    'VkAccelerationStructureKHR',
    'VkDeferredOperationKHR',
]

other_opaque_handles: list[str] = [
    "HANDLE",
    "HWND",
    "HINSTANCE",
    "HMONITOR",
]

opaque_handles: list[str] = (
    opaque_dispatchable_handles
    + opaque_nondispatchable_handles
    + other_opaque_handles
)

vulkan_mapped_types: list[str] = opaque_dispatchable_handles
vulkan_mapped_types_nondisp: list[str] = opaque_nondispatchable_handles


# Data for CCode

types_needing_name_registration: list[str] = [
    "StringArray",
    "ByteStringArray",
]

types_not_needing_declaration: list[str] = (
    [
        "NullWrapper",
        "VoidPtr",
    ]
    + vulkan_enums
    + vulkan_uint32
    + vulkan_uint64
    + vulkan_other_primitives
    + opaque_handles
)


def version_suffix(version: int) -> str:
    """Return a version suffix (like '_V1'), empty for version 0."""
    if version <= 0:
        return ''
    else:
        return f'_V{version}'

def make_id(name: str, version: int) -> str:
    """Return an ID (like 'ID_GL_BEGIN_V1')."""
    id_ = re.sub('([a-z])([A-Z])', r'\g<1>_\g<2>', name)
    id_ = re.sub('([0-9])D', r'_\g<1>D_', id_)
    id_ = id_.rstrip('_').upper()

    return f'ID_{id_}{version_suffix(version)}'

def make_cname(name: str, version: int) -> str:
    """Return a Cname (like 'CglBegin_V1')."""
    return f'C{name}{version_suffix(version)}'

def make_ctype(type_name: str, wrap_type: str = '') -> str:
    """Return a Ctype (like 'Cfloat::CSArray')."""
    if wrap_type:  # Wrap types override deduced Ctypes.
        return wrap_type

    type_name = type_name.replace('const ', '')

    if type_name in vulkan_uint32:
        return 'Cuint32_t'
    elif type_name in vulkan_uint64:
        return 'Cuint64_t'

    if '*' in type_name:
        type_name = type_name.strip(' *')
        if type_name in vulkan_structs:
            return f'C{type_name}'
        else:
            return f'C{type_name}::CSArray'

    return f'C{type_name}'

def make_func_type_flags(func_type: FuncType) -> str:
    """Convert FuncType into GITS' C++ representation string."""
    return ' | '.join(f'GITS_VULKAN_{flag.name}_APITYPE' for flag in func_type)

def get_indent(s: str) -> str:
    """Return the base indentation of given code as a string."""
    # In case of multiline strings, first line should be the least indented.
    match = re.match(r'\s*', s)
    if match is None:
        return ''
    else:
        return match.group()

def wrap_in_if(condition: str, code: str, indent: str = '  ') -> str:
    """Wrap a multiline string in a C++ if statement."""

    orig_indent = get_indent(code)

    # So we don't double orig_indent when indenting everything at the end.
    # Dedent doesn't accept amount, but it should dedent exactly by orig_indent.
    dedented_code = textwrap.dedent(code)

    # Indent by one level.
    indented_code = textwrap.indent(dedented_code, indent)

    if_statement = f'if ({condition}) {{\n{indented_code}\n}}'

    # Indent everything by original indent amount.
    return textwrap.indent(if_statement, orig_indent)

def split_functions_by_level(
    vk_functions: list[Token],
) -> dict[FuncLevel, list[Token]]:
    """
    Separate Vulkan functions (tokens) by their level.

    Parameters:
        vk_functions: List of Vulkan functions of various levels.

    Returns:
        A dict, mapping levels to lists of functions of each level.
    """
    functions_by_level: dict[FuncLevel, list[Token]] = {}
    functions_by_level[FuncLevel.PROTOTYPE] = []
    functions_by_level[FuncLevel.GLOBAL] = []
    functions_by_level[FuncLevel.INSTANCE] = []
    functions_by_level[FuncLevel.DEVICE] = []

    for token in vk_functions:
        functions_by_level[token.level].append(token)

    return functions_by_level

def without_older_versions(input: list[Versioned]) -> list[Versioned]:
    """
    Filter out older versions of Vulkan tokens or structs from a list.

    Parameters:
        input: List of tokens or structs.

    Returns:
        A list containing only newest versions of items from input.
    """
    newest_token_versions: dict[str, Versioned] = {}

    for item in input:
        newest_so_far: Versioned | None = newest_token_versions.get(item.name)
        if newest_so_far is None or newest_so_far.version < item.version:
            newest_token_versions[item.name] = item

    return list(newest_token_versions.values())

def dependency_ordered(structs: list[VkStruct]) -> list[VkStruct]:
    """
    Order structs by putting dependencies first.

    If given struct S contains structs A and B, A and B will be ordered before
    S to avoid undeclared identifier errors in C++ code.

    To avoid duplicates, only newest struct versions are kept.

    Parameters:
        structs: List of structs to be ordered by dependencies.

    Returns:
        A copy of `structs`, reordered to avoid undeclared identifier errors.

    """
    structs = without_older_versions(structs)

    result: list[VkStruct] = []

    struct_type_names: set[str] = set((s.name for s in structs))
    declared_structs: list[str] = []
    while len(declared_structs) < len(structs):
        for struct in structs:
            if struct.name not in declared_structs:
                to_declare: list[str] = []  # Dependencies.
                for field in struct.fields:
                    if (field.type not in declared_structs) and (field.type in struct_type_names):
                        to_declare.append(field.type)
                if len(to_declare) == 0:
                    result.append(struct)
                    declared_structs.append(struct.name)

    return result

def make_struct_field_type_cast(type: str) -> str:
    """
    Return a C++ type cast for given struct type, if appropriate.

    If type is a *Flags uint, cast it to a *FlagBits enum.
    """
    if 'Flags' in type:
        corresponding_enum = type.replace('Flags', 'FlagBits')
        if corresponding_enum in vulkan_enums:
            return f'({corresponding_enum})'

    return ''

def make_struct_field_log_code(field: Field) -> str:
    """Return C++ code for logging a Field."""
    result = f'" {field.name}: "'

    type_cast = make_struct_field_type_cast(field.type)

    if field.name == 'pNext':
        result += ' << (PNextPointerTypeTag)c.pNext << ", " << '
    elif field.count is not None:
        additional_conditions = ''
        if '[' not in field.type:  # Skip nullptr check for arrays on the stack.
            additional_conditions += f' && (c.{field.name} != nullptr)'
        if field.log_condition is not None:
            additional_conditions += f' && ({field.log_condition})'

        count: str = field.count
        if not count.isdigit():
            count = f'c.{count}'

        result += inspect.cleandoc(f'''
            ;
              if ((isTraceDataOptPresent(TraceData::VK_STRUCTS)){additional_conditions}) {{
                *this << "{{";
                for (uint32_t i = 0; i < (uint32_t){count}; ++i) {{
                  *this << " [" << i << "]:" << {type_cast}c.{field.name}[i];
                }}
                *this << " }}";
              }} else {{
                *this << (void*)c.{field.name};
              }}
            ''')
        result += '\n'
        result += '  *this << ", " << '
    else:
        result += f' << {type_cast}c.{field.name} << ", " << '

    return result

def make_struct_log_code(fields: list[Field]) -> str:
    """Return C++ code for logging Fields of a VkStruct."""
    fields_str = '*this << "{" << '

    field: Field
    for field in fields:
        fields_str += make_struct_field_log_code(field)

    fields_str = fields_str.removesuffix(' << ", " << ')
    fields_str += ' << " }";'

    fields_str = fields_str.replace('", " << " ', '", ')
    fields_str = fields_str.replace('"{" << " ', '"{ ')

    return fields_str

def split_arrays_from_name(name_with_array: str) -> tuple[str, str]:
    """
    Separate array declarations from variable or type name.

    Parameters:
        name_with_array: Name that may contain array declarations.

    Returns:
        Tuple of (name, array). Examples:

        'baseAndCount [2]' -> ('baseAndCount', '[2]')
        'matrix[3][4]' -> ('matrix', '[3][4]')
    """
    array_regex: str = r'\[[0-9_]+\]'
    matches = re.findall(array_regex, name_with_array)
    if matches:
        name: str = re.sub(array_regex, '', name_with_array)
        arrays: str = ''.join(matches)
    else:
        name: str = name_with_array
        arrays: str = ''

    return (name.strip(), arrays.strip())

def args_to_str(
    args: list[Argument],
    format_string: str,
    rstrip_string: str = '',
) -> str:
    """
    Format Vulkan function call arguments as string.

    Each argument will get square brackets and their contents removed, then
    `format_string.format(...)` will be run on it. The results will all get
    concatenated and returned.

    Placeholder strings supported for formatting are:
        name: Name with array part removed.
        type: Type with array part removed.
        array: Array declaration (or empty string) extracted from name or type.
        wrap_params: wrap_params from generator (if present) or name (described above).
        ctype: Name of the class wrapping this argument, e.g. `CVkDevice`.

    Parameters:
        args: Parameters of the Vulkan function.
        format_string: Format of one argument, with placeholders like '{name}'.
        rstrip_string: String to rstrip the result with; defaults to ''.

    Returns:
        A C++ arguments string. Examples:

            'int foo, float bar[2], bool baz'
            '*_foo, *_bar, *_baz'
    """

    args_str = ''

    arg: Argument
    for arg in args:
        # Argument name or type can contain an array declaration, like 'baseAndCount[2]'
        # in OpenGL or 'VkFragmentShadingRateCombinerOpKHR[2]' in Vulkan.
        name: str
        name_array: str
        type: str
        type_array: str
        name, name_array = split_arrays_from_name(arg.name)
        type, type_array = split_arrays_from_name(arg.type)
        assert not (name_array and type_array), (
            "Argument name and type can't both have array declarations.")
        array: str = name_array or type_array

        wrap_type: str = arg.wrap_type or ''
        wrap_params: str = arg.wrap_params or name
        ctype: str = make_ctype(type, wrap_type)

        args_str += format_string.format(
            name=name,
            type=type,
            array=array,
            wrap_params=wrap_params,
            ctype=ctype,
        )

    return args_str.rstrip(rstrip_string)

def arg_call(
    token: Token,
    *,  # Force keyword args, as calls with positional bools are cryptic.
    add_retval: bool,
    recording: bool = False,
    wrap: bool = False,
) -> str:
    """Return arguments formatted for a call, like '(return_value, a, b)'."""
    args_str = ''

    if add_retval and token.return_value.type != 'void':
        args_str += 'return_value, '

    args_str += args_to_str(token.args, '{name}, ')

    if recording:
        args_str += 'Recording(_recorder), '

    if wrap:
        args_str += '_recorder, '

    return f"({args_str.strip(', ')})"

def driver_definition(token: Token) -> str:
    """Return a Token's C++ definition for the driver file."""
    ret_type: str = token.return_value.type
    if ret_type == 'void':
        ret_type = 'void_t'

    custom = 'CUSTOM_' if token.custom_driver else ''

    first_argument_name = ''
    if token.level in (FuncLevel.INSTANCE, FuncLevel.DEVICE):
        first_argument_name = f', {token.args[0].name}'

    params: str = args_to_str(token.args, '{type} {name}{array}, ', ', ')
    args: str = arg_call(token, add_retval=False)

    macro_name = f'VK_{custom}{token.level.name}_LEVEL_FUNCTION'
    macro_args = f'({ret_type}, {token.name}, ({params}), {args}{first_argument_name})'

    return macro_name + macro_args

def driver_call(token: Token) -> str:
    """
    Create a string containing a driver call (for gitsPluginPrePostAuto.cpp).

    Parameters:
        token: data for one version of a token

    Returns:
        A C++ driver call string. Examples:

        'wrapper.Drivers().gl.glAccum(op, value);'
        'execWrap_glGetIntegerv(pname, data);'
        'auto return_value = wrapper.Drivers().gl.glMapBuffer(target, access);'
    """

    has_retval: bool = token.return_value.type != 'void'
    retval_assignment = 'auto return_value = ' if has_retval else ''

    exec_wrap: bool = token.interceptor_exec_override is True
    function_prefix = 'execWrap_' if exec_wrap else 'wrapper.Drivers().gl.'

    driver_args: str = arg_call(token, add_retval=False)

    return f'{retval_assignment}{function_prefix}{token.name}{driver_args};'

def mako_write(inpath: str | Path, outpath: str | Path, **kwargs) -> int:
    """Render a Mako template into a file."""
    # Objects used by all (or almost all) Mako templates.
    common_objects = {
        'FuncType': FuncType,
        'FuncLevel': FuncLevel,
        'Token': Token,
        'Argument': Argument,
        'ReturnValue': ReturnValue,
        'VkStruct': VkStruct,
        'Field': Field,
        'VkEnum': VkEnum,
        'Enumerator': Enumerator,
        'AUTO_GENERATED_HEADER': AUTO_GENERATED_HEADER,
    }

    inpath = Path(inpath)
    outpath = Path(outpath)

    try:
        print(f"Generating {outpath}...")
        template = mako.template.Template(filename=str(inpath))
        rendered = template.render(**(common_objects | kwargs))
        rendered = re.sub(r'\r\n', r'\n', rendered)

        destination = Path('..') / outpath
        with destination.open(mode='w') as fout:
            fout.write(rendered)
    except Exception:
        traceback = mako.exceptions.RichTraceback()
        for filename, lineno, function, line in traceback.traceback:
            print(f"{filename}({lineno}) : error in {function}")
            print(line, "\n")
        print(f"{traceback.error.__class__.__name__}: {traceback.error}")
        return -1
    return 0

def update_token_ids(
    id_file_path: str | Path,
    destination_subpath: str | Path,
    functions: list[Token]
) -> None:
    """
    Append new token IDs (if any) to an ID file.

    Parameters:
        id_file_path: Path to the ID file.
        destination_subpath: Path to copy the file to; relative to parent directory.
        functions: List of tokens to generate IDs from.
    """
    id_file_path = Path(id_file_path)
    destination_subpath = Path(destination_subpath)

    existing_ids: set[str] = set()
    with id_file_path.open(mode='r') as id_file:
        for line in id_file:
            if line.startswith('ID'):
                existing_id: str = line.strip(',\n')
                existing_ids.add(existing_id)

    new_ids = ''
    for token in functions:
        token_id: str = make_id(token.name, token.version)
        if token_id not in existing_ids:
            new_ids += token_id + ',\n'

    if not new_ids:
        print(f"File {id_file_path} is up to date.")
    else:
        print(f"Adding new IDs to {id_file_path} ...")
        with id_file_path.open(mode='a') as id_file:
            id_file.write(new_ids)

    destination = Path('..') / destination_subpath
    print(f"Copying {id_file_path} to {destination_subpath} ...")
    shutil.copy2(id_file_path, destination)


def main() -> None:
    """Generate all the files."""
    all_tokens: list[Token] = get_functions()
    enabled_tokens: list[Token] = [f for f in all_tokens if f.enabled]
    newest_tokens: list[Token] = without_older_versions(all_tokens)

    all_structs: list[VkStruct] = get_structs()
    enabled_structs: list[VkStruct] = [s for s in all_structs if s.enabled]

    all_enums: list[VkEnum] = get_enums()
    # Enums are always enabled.

    update_token_ids('vulkanIDs.h', 'common/include', functions=enabled_tokens)

    vulkan_layer_bin_path: str = ''
    match platform.system():
        case 'Windows':
            vulkan_layer_bin_path = '.\\\\VkLayer_vulkan_GITS_recorder.dll'
        case 'Linux':
            vulkan_layer_bin_path = './libVkLayer_vulkan_GITS_recorder.so'
        case other_system:
            raise NotImplementedError(
                f"Path to Vulkan layer dynamic library is unknown for system '{other_system}'.")
    mako_write(
        'templates/VkLayer_vulkan_GITS_recorder.json.mako',
        'layer/VkLayer_vulkan_GITS_recorder.json',
        vulkan_layer_bin_path=vulkan_layer_bin_path,
    )

    mako_write(
        'templates/vkX.def.mako',
        'layer/vkLayer.def',
        library_name='VkLayer_vulkan_GITS_recorder.dll',
        vk_functions=newest_tokens,
    )

    mako_write(
        'templates/vkX.def.mako',
        'interceptor/vkPlugin.def',
        library_name='vulkan-1.dll',
        vk_functions=newest_tokens,
    )

    mako_write(
        'templates/vulkanDriversAuto.inl.mako',
        'common/include/vulkanDriversAuto.inl',
        args_to_str=args_to_str,
        arg_call=arg_call,
        driver_definition=driver_definition,
        functions_by_level=split_functions_by_level(newest_tokens),
    )

    mako_write(
        'templates/vulkanIDswitch.h.mako',
        'common/include/vulkanIDswitch.h',
        make_id=make_id,
        make_cname=make_cname,
        vk_functions=enabled_tokens,
    )

    mako_write(
        'templates/vulkanLogAuto.inl.mako',
        'common/include/vulkanLogAuto.inl',
        version_suffix=version_suffix,
        vk_structs=dependency_ordered(all_structs),
        vk_enums=all_enums,
        vulkan_mapped_types_nondisp=vulkan_mapped_types_nondisp,
        vulkan_mapped_types=vulkan_mapped_types,
    )

    mako_write(
        'templates/vulkanLogAuto.cpp.mako',
        'common/vulkanLogAuto.cpp',
        version_suffix=version_suffix,
        make_struct_log_code=make_struct_log_code,
        vk_structs=dependency_ordered(all_structs),
        vk_enums=all_enums,
        vulkan_mapped_types_nondisp=vulkan_mapped_types_nondisp,
        vulkan_mapped_types=vulkan_mapped_types,
    )

    mako_write(
        'templates/vulkanRecorderWrapperXAuto.h.mako',
        'recorder/include/vulkanRecorderWrapperIfaceAuto.h',
        args_to_str=args_to_str,
        is_iface=True,
        vk_functions=newest_tokens,
    )

    mako_write(
        'templates/vulkanRecorderWrapperXAuto.h.mako',
        'recorder/include/vulkanRecorderWrapperAuto.h',
        args_to_str=args_to_str,
        is_iface=False,
        vk_functions=newest_tokens,
    )

if __name__ == '__main__':
    main()