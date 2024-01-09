// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2024 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#pragma once

/*
  The purpose of this file is to provide OpenGL specific functionality that does interact
  with the OpenGL driver. Utility that captures frame buffer content are one such example.
*/

#include "timer.h"

#include <string>
#include <deque>
#include <filesystem>

#include "openglTypes.h"
#include "tools.h"

#ifndef BUILD_FOR_CCODE
#include "argument.h"
#endif
namespace gits {
namespace OpenGL {
GLenum GetTextureTarget(GLint name);
bool ReadPixelsWrapper(GLint x,
                       GLint y,
                       GLint width,
                       GLint height,
                       GLenum format,
                       GLenum type,
                       GLvoid* data,
                       GLenum readbuffer,
                       bool msaa);
#ifdef BUILD_FOR_CCODE
bool IsEsProfile();
#endif
void capture_drawbuffer(const std::filesystem::path& directory,
                        const std::string& file_name,
                        bool force_back_buffer,
                        bool dump_depth = true,
                        bool dump_stencil = true);
std::filesystem::path GetPathForImageDumping();
void FrameBufferSave(unsigned frameNumber);
#ifdef GITS_PLATFORM_WINDOWS
void ScreenshotSave(unsigned frameNumber, HWND hWND);
#endif
void capture_bound_texture2D(GLenum target,
                             const std::filesystem::path& directory,
                             const std::string& file_name);
#ifndef BUILD_FOR_CCODE
void RestoreFramebufferEXT(
    GLuint targetFBO, GLenum format, GLsizei height, GLsizei width, CBinaryResource& resource);
void RestoreFramebuffer(
    GLuint targetFBO, GLenum format, GLsizei height, GLsizei width, CBinaryResource& resource);
#endif
unsigned texUnpackRowSize(GLenum format, GLenum type, GLint texWidth = 0);
unsigned getTexImageSize(GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type);
unsigned TexDataSize(GLenum format, GLenum type, GLsizei width, GLsizei height, GLsizei depth);
unsigned CompressedTexDataSize(GLsizei width, GLsizei height, GLsizei depth, GLsizei imageSize);
unsigned BitmapDataSize(GLsizei width, GLsizei height);
GLint BoundBuffer(GLenum target);
GLint BoundTexture(GLenum target);
GLenum MapAccessBitFieldToEnum(GLbitfield access);
GLbitfield MapAccessEnumToBitField(GLenum access);

std::string GetCurrentProgramShaderText(GLenum shtype);
std::string GetShaderSource(GLint name);
void GetUniformArraySizeAndOffset(
    GLuint program, const GLchar* name, GLint location, GLint& arraySize, GLint& offset);

#ifndef BUILD_FOR_CCODE
void SaveProgramBinary(GLuint program, hash_t hash);
void RestoreProgramBinary(GLuint program, hash_t hash);
#endif

class PackPixelStoreStateStash {
  std::map<GLenum, GLint> _data;

public:
  PackPixelStoreStateStash();
  void Restore();
  const std::map<GLenum, GLint>& Data() {
    return _data;
  }
};

class UnPackPixelStoreStateStash {
  std::map<GLenum, GLint> _data;

public:
  UnPackPixelStoreStateStash();
  void Restore();
  const std::map<GLenum, GLint>& Data() {
    return _data;
  }
};

class PackPixelBufferBindStateStash {
  GLint _data;

public:
  PackPixelBufferBindStateStash();
  void Restore();
  GLint Data() {
    return _data;
  }
};

class DrawBuffersStateStash {
  std::vector<GLint> _data;

public:
  DrawBuffersStateStash();
  void Restore();
  const std::vector<GLint>& Data() {
    return _data;
  }
};

class ReadBufferStateStash {
  GLenum _data;

public:
  ReadBufferStateStash();
  void Restore();
  GLenum Data() {
    return _data;
  }
};

class FboBindStateStash {
  std::map<GLenum, GLint> _data;
  bool _extFboBlitSupport;

public:
  FboBindStateStash();
  void Restore();
  const std::map<GLenum, GLint>& Data() {
    return _data;
  }
  GLenum ReadTarget();
  GLenum DrawTarget();
  GLint ReadName(); //Returns GL_READ_FRAMEBUFFER bound name
  GLint DrawName(); //Returns GL_DRAW_FRAMEBUFFER bound name
};

class RboBindStateStash {
  GLint _data;

public:
  RboBindStateStash();
  void Restore();
  GLint Data() {
    return _data;
  }
};

class TextureBindStateStash {
  struct {
    GLint name;
    GLenum target;
  } _data;

public:
  TextureBindStateStash(GLenum target);
  void Restore();
  GLint Data() {
    return _data.name;
  }
};

class ScissorStateStash {
  std::vector<int> _data; //x, y, width, height, enabled
public:
  ScissorStateStash();
  void Restore();
  std::vector<int> Data() {
    return _data;
  }
};

typedef std::vector<GLuint> CNameVector; // Stores names generated by glGen/glCreate

class BufferStateStash {
  static const GLuint bufferTargetCount = 6;
  static const GLenum bufferBindingTargets[bufferTargetCount];
  CNameVector _data;

public:
  BufferStateStash();
  void Restore();
};

class MapBuffer {
  GLenum _target;
  void* _ptr;

public:
  MapBuffer(GLenum target, GLint buffer);
  MapBuffer(const MapBuffer& other) = delete;
  MapBuffer& operator=(const MapBuffer& other) = delete;
  ~MapBuffer();
  void* Data() {
    return _ptr;
  }
};

class GLQueryWrapper {
  struct Data {
    GLuint queryObj;
    GLuint drawNr;
    GLint result;
    bool ended;
    bool clearOrBlit;
    Data(GLuint queryobj, GLuint drawnr)
        : queryObj(queryobj), drawNr(drawnr), result(-1), ended(false), clearOrBlit(false) {}
  };

  GLenum _queryType;
  std::vector<Data> _queries;
  GLQueryWrapper() {}

public:
  GLQueryWrapper(GLenum type) : _queryType(type) {}
  void Begin(GLuint drawnr, bool clearblit);
  void End();
  void GetResults();
  void PrintToLog();
};

//Helper class for unique glsl names generation (programs shaders names scope)
class GLSLUnique {
private:
  static std::set<GLuint>& UsedNames() { //Keep all used shader names
    typedef std::set<GLuint> name_set;
    INIT_NEW_STATIC_OBJ(usedNames, name_set);
    return usedNames;
  }
  GLSLUnique() {}

public:
  static void UseName(GLuint name) {
    UsedNames().insert(name);
  }
  static GLuint GenUniqueName() { //Generates unique shader name
    UsedNames().insert((*UsedNames().rbegin()) + 1);
    return (*UsedNames().rbegin());
  }
};

//Depth GL_FLOAT format to GL_RGB/GL_RGBA data converter
std::vector<uint8_t> DepthToRgbSpectrum(std::vector<GLfloat>& depthData, bool alpha);
std::vector<uint8_t> DepthToRgbGrey(std::vector<GLfloat>& depthData, bool alpha);
std::vector<uint8_t> DepthToRgb(std::vector<GLfloat>& depthData, bool alpha);

//Stencil GL_UNSIGNED_INT_24_8 format to GL_RGB/GL_RGBA data converter
std::vector<uint8_t> StencilToRgb(std::vector<uint32_t>& depthStencilData, bool alpha);

bool MakeCurrentIfDrawableExists(void* context);
bool SetCurrentContext(void* context);
void* GetCurrentContextAPI();
TBuffersState ESBufferState();

bool IsGlGetTexImagePresentOnGLES();
bool IsGlGetCompressedTexImagePresentOnGLES();

bool IsGlGetTexAndCompressedTexImagePresentOnGLES();

class StatePrinter {
  class Object {
  public:
    virtual void Write() = 0;
    virtual ~Object() {}
  };
  class RBO : public Object {
    GLint _name;
    GLenum _internalFormat;
    GLint _msaaSamples;

  public:
    RBO(GLint name);
    void Write();
  };
  class Texture : public Object {
    GLint _name;
    GLenum _target;
    GLenum _internalFormat;
    GLint _msaaSamples;
    GLenum _texture;

  public:
    Texture(GLenum target, GLint name, GLenum texture);
    void Write();
  };
  class FBO : public Object {
    GLint _name;
    GLenum _target;
    std::map<GLenum, std::shared_ptr<Object>> _attachments;

  public:
    FBO(GLenum target, GLint name);
    void Write();
  };
  class GLSLPrograms : public Object {
    GLint _name;

  public:
    GLSLPrograms(GLint name) : _name(name) {}
    void Write();
  };
  class GLSLPipelines : public Object {
    GLint _name;

  public:
    GLSLPipelines(GLint name) : _name(name) {}
    void Write();
  };
  class ARBProgram : public Object {
    GLenum _target;
    GLint _name;

  public:
    ARBProgram(GLenum target, GLint name) : _target(target), _name(name) {}
    void Write();
  };
  class BoundBuffers : public Object {
    GLenum _target;
    GLint _buffer;

  public:
    BoundBuffers(GLenum target, GLint buffer) : _target(target), _buffer(buffer){};
    void Write();
  };
  std::vector<std::shared_ptr<Object>> _objects;

public:
  StatePrinter();
  void PrintToLog();
};

//CGLLog is specialized CLog converting GLenum values into strings
class CGLLog : public gits::CLog {
public:
  CGLLog(LogLevel lvl, LogStyle style);
  template <class T>
  CGLLog& operator<<(const T& t);
  CGLLog& operator<<(const char c);
  CGLLog& operator<<(const unsigned char c);
  CGLLog& operator<<(const char* c);
  CGLLog& operator<<(char* c);
  CGLLog& operator<<(const unsigned char* c);
  CGLLog& operator<<(const unsigned int glenum);
  CGLLog& operator<<(PIXELFORMATDESCRIPTOR& pfd);
  CGLLog& operator<<(manip t);
};
// See common/include/log.h for explanations of these macros.
#define GLLog1(lvl)                                                                                \
  if (gits::ShouldLog(gits::LogLevel::lvl))                                                        \
  gits::OpenGL::CGLLog(gits::LogLevel::lvl, gits::LogStyle::NORMAL)
#define GLLog2(lvl, style)                                                                         \
  if (gits::ShouldLog(gits::LogLevel::lvl))                                                        \
  gits::OpenGL::CGLLog(gits::LogLevel::lvl, gits::LogStyle::style)
// Workaround for a MSVC bug, see https://stackoverflow.com/a/5134656/
#define EXPAND(x) x
// Magic to call different variants based on the number of arguments.
#define GET_OVERLOAD(PLACEHOLDER1, PLACEHOLDER2, NAME, ...) NAME
#define GLLog(...)                                          EXPAND(GET_OVERLOAD(__VA_ARGS__, GLLog2, GLLog1)(__VA_ARGS__))

template <class T>
CGLLog& CGLLog::operator<<(const T& t) {
  _buffer << t;
  return *this;
}

void CleanResources();
void DestroyContext(void* ctx);
void DestroyAllContexts();

size_t GetPatchParameterValuesCount(GLenum pname);

GLenum GetTargetOfTextureOrCrash(GLuint name);
} // namespace OpenGL
} // namespace gits
