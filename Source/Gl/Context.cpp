#include "Context.hpp"

#include "Platform/SymbolLoader.hpp"

#include <stdexcept>

namespace {

Twil::Gl::ContextT gContext;

void checkError()
{
#ifndef NDEBUG
	auto error = gContext.GetError();
	switch (error) {
	case GL_NO_ERROR:
		return;
	case GL_INVALID_ENUM:
		throw std::runtime_error("OpenGL Error: GL_INVALID_ENUM");
	case GL_INVALID_VALUE:
		throw std::runtime_error("OpenGL Error: GL_INVALID_VALUE");
	case GL_INVALID_OPERATION:
		throw std::runtime_error("OpenGL Error: GL_INVALID_OPERATION");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		throw std::runtime_error("OpenGL Error: GL_INVALID_FRAMEBUFFER_OPERATION");
	case GL_OUT_OF_MEMORY:
		throw std::runtime_error("OpenGL Error: GL_OUT_OF_MEMORY");
	case GL_STACK_UNDERFLOW:
		throw std::runtime_error("OpenGL Error: GL_STACK_UNDERFLOW");
	case GL_STACK_OVERFLOW:
		throw std::runtime_error("OpenGL Error: GL_STACK_OVERFLOW");
	}
#endif
}

}

void glCullFace(GLenum mode)
{
	gContext.CullFace(mode);
	checkError();
}

void glFrontFace(GLenum mode)
{
	gContext.FrontFace(mode);
	checkError();
}

void glHint(GLenum target, GLenum mode)
{
	gContext.Hint(target, mode);
	checkError();
}

void glLineWidth(GLfloat width)
{
	gContext.LineWidth(width);
	checkError();
}

void glPointSize(GLfloat size)
{
	gContext.PointSize(size);
	checkError();
}

void glPolygonMode(GLenum face, GLenum mode)
{
	gContext.PolygonMode(face, mode);
	checkError();
}

void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gContext.Scissor(x, y, width, height);
	checkError();
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
	gContext.TexParameterf(target, pname, param);
	checkError();
}

void glTexParameterfv(GLenum target, GLenum pname, GLfloat const * params)
{
	gContext.TexParameterfv(target, pname, params);
	checkError();
}

void glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	gContext.TexParameteri(target, pname, param);
	checkError();
}

void glTexParameteriv(GLenum target, GLenum pname, GLint const * params)
{
	gContext.TexParameteriv(target, pname, params);
	checkError();
}

void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexImage1D(target, level, internalformat, width, border, format, type, pixels);
	checkError();
}

void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	checkError();
}

void glDrawBuffer(GLenum mode)
{
	gContext.DrawBuffer(mode);
	checkError();
}

void glClear(GLbitfield mask)
{
	gContext.Clear(mask);
	checkError();
}

void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gContext.ClearColor(red, green, blue, alpha);
	checkError();
}

void glClearStencil(GLint s)
{
	gContext.ClearStencil(s);
	checkError();
}

void glClearDepth(GLclampd depth)
{
	gContext.ClearDepth(depth);
	checkError();
}

void glStencilMask(GLuint mask)
{
	gContext.StencilMask(mask);
	checkError();
}

void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	gContext.ColorMask(red, green, blue, alpha);
	checkError();
}

void glDepthMask(GLboolean flag)
{
	gContext.DepthMask(flag);
	checkError();
}

void glDisable(GLenum cap)
{
	gContext.Disable(cap);
	checkError();
}

void glEnable(GLenum cap)
{
	gContext.Enable(cap);
	checkError();
}

void glFinish()
{
	gContext.Finish();
	checkError();
}

void glFlush()
{
	gContext.Flush();
	checkError();
}

void glBlendFunc(GLenum sfactor, GLenum dfactor)
{
	gContext.BlendFunc(sfactor, dfactor);
	checkError();
}

void glLogicOp(GLenum opcode)
{
	gContext.LogicOp(opcode);
	checkError();
}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
	gContext.StencilFunc(func, ref, mask);
	checkError();
}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	gContext.StencilOp(fail, zfail, zpass);
	checkError();
}

void glDepthFunc(GLenum func)
{
	gContext.DepthFunc(func);
	checkError();
}

void glPixelStoref(GLenum pname, GLfloat param)
{
	gContext.PixelStoref(pname, param);
	checkError();
}

void glPixelStorei(GLenum pname, GLint param)
{
	gContext.PixelStorei(pname, param);
	checkError();
}

void glReadBuffer(GLenum mode)
{
	gContext.ReadBuffer(mode);
	checkError();
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels)
{
	gContext.ReadPixels(x, y, width, height, format, type, pixels);
	checkError();
}

void glGetBooleanv(GLenum pname, GLboolean * params)
{
	gContext.GetBooleanv(pname, params);
	checkError();
}

void glGetDoublev(GLenum pname, GLdouble * params)
{
	gContext.GetDoublev(pname, params);
	checkError();
}

GLenum glGetError()
{
	auto result = gContext.GetError();
	checkError();
	return result;
}

void glGetFloatv(GLenum pname, GLfloat * params)
{
	gContext.GetFloatv(pname, params);
	checkError();
}

void glGetIntegerv(GLenum pname, GLint * params)
{
	gContext.GetIntegerv(pname, params);
	checkError();
}

GLubyte const * glGetString(GLenum name)
{
	auto result = gContext.GetString(name);
	checkError();
	return result;
}

void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels)
{
	gContext.GetTexImage(target, level, format, type, pixels);
	checkError();
}

void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
	gContext.GetTexParameterfv(target, pname, params);
	checkError();
}

void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gContext.GetTexParameteriv(target, pname, params);
	checkError();
}

void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params)
{
	gContext.GetTexLevelParameterfv(target, level, pname, params);
	checkError();
}

void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params)
{
	gContext.GetTexLevelParameteriv(target, level, pname, params);
	checkError();
}

GLboolean glIsEnabled(GLenum cap)
{
	auto result = gContext.IsEnabled(cap);
	checkError();
	return result;
}

void glDepthRange(GLclampd near, GLclampd far)
{
	gContext.DepthRange(near, far);
	checkError();
}

void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	gContext.Viewport(x, y, width, height);
	checkError();
}

void glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
	gContext.DrawArrays(mode, first, count);
	checkError();
}

void glDrawElements(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices)
{
	gContext.DrawElements(mode, count, type, indices);
	checkError();
}

void glGetPointerv(GLenum pname, GLvoid * * params)
{
	gContext.GetPointerv(pname, params);
	checkError();
}

void glPolygonOffset(GLfloat factor, GLfloat units)
{
	gContext.PolygonOffset(factor, units);
	checkError();
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
	gContext.CopyTexImage1D(target, level, internalformat, x, y, width, border);
	checkError();
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
	gContext.CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	checkError();
}

void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
	gContext.CopyTexSubImage1D(target, level, xoffset, x, y, width);
	checkError();
}

void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gContext.CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	checkError();
}

void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexSubImage1D(target, level, xoffset, width, format, type, pixels);
	checkError();
}

void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	checkError();
}

void glBindTexture(GLenum target, GLuint texture)
{
	gContext.BindTexture(target, texture);
	checkError();
}

void glDeleteTextures(GLsizei n, GLuint const * textures)
{
	gContext.DeleteTextures(n, textures);
	checkError();
}

void glGenTextures(GLsizei n, GLuint * textures)
{
	gContext.GenTextures(n, textures);
	checkError();
}

GLboolean glIsTexture(GLuint texture)
{
	auto result = gContext.IsTexture(texture);
	checkError();
	return result;
}

void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	gContext.BlendColor(red, green, blue, alpha);
	checkError();
}

void glBlendEquation(GLenum mode)
{
	gContext.BlendEquation(mode);
	checkError();
}

void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices)
{
	gContext.DrawRangeElements(mode, start, end, count, type, indices);
	checkError();
}

void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
	checkError();
}

void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid const * pixels)
{
	gContext.TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
	checkError();
}

void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
	gContext.CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
	checkError();
}

void glActiveTexture(GLenum texture)
{
	gContext.ActiveTexture(texture);
	checkError();
}

void glSampleCoverage(GLclampf value, GLboolean invert)
{
	gContext.SampleCoverage(value, invert);
	checkError();
}

void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
	checkError();
}

void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	checkError();
}

void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
	checkError();
}

void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	checkError();
}

void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, GLvoid const * data)
{
	gContext.CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
	checkError();
}

void glGetCompressedTexImage(GLenum target, GLint level, GLvoid * img)
{
	gContext.GetCompressedTexImage(target, level, img);
	checkError();
}

void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
	gContext.BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	checkError();
}

void glMultiDrawArrays(GLenum mode, GLint const * first, GLsizei const * count, GLsizei primcount)
{
	gContext.MultiDrawArrays(mode, first, count, primcount);
	checkError();
}

void glMultiDrawElements(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount)
{
	gContext.MultiDrawElements(mode, count, type, indices, primcount);
	checkError();
}

void glPointParameterf(GLenum pname, GLfloat param)
{
	gContext.PointParameterf(pname, param);
	checkError();
}

void glPointParameterfv(GLenum pname, GLfloat const * params)
{
	gContext.PointParameterfv(pname, params);
	checkError();
}

void glPointParameteri(GLenum pname, GLint param)
{
	gContext.PointParameteri(pname, param);
	checkError();
}

void glPointParameteriv(GLenum pname, GLint const * params)
{
	gContext.PointParameteriv(pname, params);
	checkError();
}

void glGenQueries(GLsizei n, GLuint * ids)
{
	gContext.GenQueries(n, ids);
	checkError();
}

void glDeleteQueries(GLsizei n, GLuint const * ids)
{
	gContext.DeleteQueries(n, ids);
	checkError();
}

GLboolean glIsQuery(GLuint id)
{
	auto result = gContext.IsQuery(id);
	checkError();
	return result;
}

void glBeginQuery(GLenum target, GLuint id)
{
	gContext.BeginQuery(target, id);
	checkError();
}

void glEndQuery(GLenum target)
{
	gContext.EndQuery(target);
	checkError();
}

void glGetQueryiv(GLenum target, GLenum pname, GLint * params)
{
	gContext.GetQueryiv(target, pname, params);
	checkError();
}

void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params)
{
	gContext.GetQueryObjectiv(id, pname, params);
	checkError();
}

void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params)
{
	gContext.GetQueryObjectuiv(id, pname, params);
	checkError();
}

void glBindBuffer(GLenum target, GLuint buffer)
{
	gContext.BindBuffer(target, buffer);
	checkError();
}

void glDeleteBuffers(GLsizei n, GLuint const * buffers)
{
	gContext.DeleteBuffers(n, buffers);
	checkError();
}

void glGenBuffers(GLsizei n, GLuint * buffers)
{
	gContext.GenBuffers(n, buffers);
	checkError();
}

GLboolean glIsBuffer(GLuint buffer)
{
	auto result = gContext.IsBuffer(buffer);
	checkError();
	return result;
}

void glBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage)
{
	gContext.BufferData(target, size, data, usage);
	checkError();
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data)
{
	gContext.BufferSubData(target, offset, size, data);
	checkError();
}

void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data)
{
	gContext.GetBufferSubData(target, offset, size, data);
	checkError();
}

GLvoid * glMapBuffer(GLenum target, GLenum access)
{
	auto result = gContext.MapBuffer(target, access);
	checkError();
	return result;
}

GLboolean glUnmapBuffer(GLenum target)
{
	auto result = gContext.UnmapBuffer(target);
	checkError();
	return result;
}

void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gContext.GetBufferParameteriv(target, pname, params);
	checkError();
}

void glGetBufferPointerv(GLenum target, GLenum pname, GLvoid * * params)
{
	gContext.GetBufferPointerv(target, pname, params);
	checkError();
}

void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
	gContext.BlendEquationSeparate(modeRGB, modeAlpha);
	checkError();
}

void glDrawBuffers(GLsizei n, GLenum const * bufs)
{
	gContext.DrawBuffers(n, bufs);
	checkError();
}

void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
	gContext.StencilOpSeparate(face, sfail, dpfail, dppass);
	checkError();
}

void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
	gContext.StencilFuncSeparate(face, func, ref, mask);
	checkError();
}

void glStencilMaskSeparate(GLenum face, GLuint mask)
{
	gContext.StencilMaskSeparate(face, mask);
	checkError();
}

void glAttachShader(GLuint program, GLuint shader)
{
	gContext.AttachShader(program, shader);
	checkError();
}

void glBindAttribLocation(GLuint program, GLuint index, GLchar const * name)
{
	gContext.BindAttribLocation(program, index, name);
	checkError();
}

void glCompileShader(GLuint shader)
{
	gContext.CompileShader(shader);
	checkError();
}

GLuint glCreateProgram()
{
	auto result = gContext.CreateProgram();
	checkError();
	return result;
}

GLuint glCreateShader(GLenum type)
{
	auto result = gContext.CreateShader(type);
	checkError();
	return result;
}

void glDeleteProgram(GLuint program)
{
	gContext.DeleteProgram(program);
	checkError();
}

void glDeleteShader(GLuint shader)
{
	gContext.DeleteShader(shader);
	checkError();
}

void glDetachShader(GLuint program, GLuint shader)
{
	gContext.DetachShader(program, shader);
	checkError();
}

void glDisableVertexAttribArray(GLuint index)
{
	gContext.DisableVertexAttribArray(index);
	checkError();
}

void glEnableVertexAttribArray(GLuint index)
{
	gContext.EnableVertexAttribArray(index);
	checkError();
}

void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gContext.GetActiveAttrib(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name)
{
	gContext.GetActiveUniform(program, index, bufSize, length, size, type, name);
	checkError();
}

void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * obj)
{
	gContext.GetAttachedShaders(program, maxCount, count, obj);
	checkError();
}

GLint glGetAttribLocation(GLuint program, GLchar const * name)
{
	auto result = gContext.GetAttribLocation(program, name);
	checkError();
	return result;
}

void glGetProgramiv(GLuint program, GLenum pname, GLint * params)
{
	gContext.GetProgramiv(program, pname, params);
	checkError();
}

void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gContext.GetProgramInfoLog(program, bufSize, length, infoLog);
	checkError();
}

void glGetShaderiv(GLuint shader, GLenum pname, GLint * params)
{
	gContext.GetShaderiv(shader, pname, params);
	checkError();
}

void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gContext.GetShaderInfoLog(shader, bufSize, length, infoLog);
	checkError();
}

void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source)
{
	gContext.GetShaderSource(shader, bufSize, length, source);
	checkError();
}

GLint glGetUniformLocation(GLuint program, GLchar const * name)
{
	auto result = gContext.GetUniformLocation(program, name);
	checkError();
	return result;
}

void glGetUniformfv(GLuint program, GLint location, GLfloat * params)
{
	gContext.GetUniformfv(program, location, params);
	checkError();
}

void glGetUniformiv(GLuint program, GLint location, GLint * params)
{
	gContext.GetUniformiv(program, location, params);
	checkError();
}

void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params)
{
	gContext.GetVertexAttribdv(index, pname, params);
	checkError();
}

void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params)
{
	gContext.GetVertexAttribfv(index, pname, params);
	checkError();
}

void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params)
{
	gContext.GetVertexAttribiv(index, pname, params);
	checkError();
}

void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid * * pointer)
{
	gContext.GetVertexAttribPointerv(index, pname, pointer);
	checkError();
}

GLboolean glIsProgram(GLuint program)
{
	auto result = gContext.IsProgram(program);
	checkError();
	return result;
}

GLboolean glIsShader(GLuint shader)
{
	auto result = gContext.IsShader(shader);
	checkError();
	return result;
}

void glLinkProgram(GLuint program)
{
	gContext.LinkProgram(program);
	checkError();
}

void glShaderSource(GLuint shader, GLsizei count, GLchar const * * string, GLint const * length)
{
	gContext.ShaderSource(shader, count, string, length);
	checkError();
}

void glUseProgram(GLuint program)
{
	gContext.UseProgram(program);
	checkError();
}

void glUniform1f(GLint location, GLfloat v0)
{
	gContext.Uniform1f(location, v0);
	checkError();
}

void glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	gContext.Uniform2f(location, v0, v1);
	checkError();
}

void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gContext.Uniform3f(location, v0, v1, v2);
	checkError();
}

void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gContext.Uniform4f(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1i(GLint location, GLint v0)
{
	gContext.Uniform1i(location, v0);
	checkError();
}

void glUniform2i(GLint location, GLint v0, GLint v1)
{
	gContext.Uniform2i(location, v0, v1);
	checkError();
}

void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	gContext.Uniform3i(location, v0, v1, v2);
	checkError();
}

void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gContext.Uniform4i(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1fv(GLint location, GLsizei count, GLfloat const * value)
{
	gContext.Uniform1fv(location, count, value);
	checkError();
}

void glUniform2fv(GLint location, GLsizei count, GLfloat const * value)
{
	gContext.Uniform2fv(location, count, value);
	checkError();
}

void glUniform3fv(GLint location, GLsizei count, GLfloat const * value)
{
	gContext.Uniform3fv(location, count, value);
	checkError();
}

void glUniform4fv(GLint location, GLsizei count, GLfloat const * value)
{
	gContext.Uniform4fv(location, count, value);
	checkError();
}

void glUniform1iv(GLint location, GLsizei count, GLint const * value)
{
	gContext.Uniform1iv(location, count, value);
	checkError();
}

void glUniform2iv(GLint location, GLsizei count, GLint const * value)
{
	gContext.Uniform2iv(location, count, value);
	checkError();
}

void glUniform3iv(GLint location, GLsizei count, GLint const * value)
{
	gContext.Uniform3iv(location, count, value);
	checkError();
}

void glUniform4iv(GLint location, GLsizei count, GLint const * value)
{
	gContext.Uniform4iv(location, count, value);
	checkError();
}

void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix4fv(location, count, transpose, value);
	checkError();
}

void glValidateProgram(GLuint program)
{
	gContext.ValidateProgram(program);
	checkError();
}

void glVertexAttrib1d(GLuint index, GLdouble x)
{
	gContext.VertexAttrib1d(index, x);
	checkError();
}

void glVertexAttrib1dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttrib1dv(index, v);
	checkError();
}

void glVertexAttrib1f(GLuint index, GLfloat x)
{
	gContext.VertexAttrib1f(index, x);
	checkError();
}

void glVertexAttrib1fv(GLuint index, GLfloat const * v)
{
	gContext.VertexAttrib1fv(index, v);
	checkError();
}

void glVertexAttrib1s(GLuint index, GLshort x)
{
	gContext.VertexAttrib1s(index, x);
	checkError();
}

void glVertexAttrib1sv(GLuint index, GLshort const * v)
{
	gContext.VertexAttrib1sv(index, v);
	checkError();
}

void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
	gContext.VertexAttrib2d(index, x, y);
	checkError();
}

void glVertexAttrib2dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttrib2dv(index, v);
	checkError();
}

void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
	gContext.VertexAttrib2f(index, x, y);
	checkError();
}

void glVertexAttrib2fv(GLuint index, GLfloat const * v)
{
	gContext.VertexAttrib2fv(index, v);
	checkError();
}

void glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
	gContext.VertexAttrib2s(index, x, y);
	checkError();
}

void glVertexAttrib2sv(GLuint index, GLshort const * v)
{
	gContext.VertexAttrib2sv(index, v);
	checkError();
}

void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gContext.VertexAttrib3d(index, x, y, z);
	checkError();
}

void glVertexAttrib3dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttrib3dv(index, v);
	checkError();
}

void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
	gContext.VertexAttrib3f(index, x, y, z);
	checkError();
}

void glVertexAttrib3fv(GLuint index, GLfloat const * v)
{
	gContext.VertexAttrib3fv(index, v);
	checkError();
}

void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
	gContext.VertexAttrib3s(index, x, y, z);
	checkError();
}

void glVertexAttrib3sv(GLuint index, GLshort const * v)
{
	gContext.VertexAttrib3sv(index, v);
	checkError();
}

void glVertexAttrib4Nbv(GLuint index, GLbyte const * v)
{
	gContext.VertexAttrib4Nbv(index, v);
	checkError();
}

void glVertexAttrib4Niv(GLuint index, GLint const * v)
{
	gContext.VertexAttrib4Niv(index, v);
	checkError();
}

void glVertexAttrib4Nsv(GLuint index, GLshort const * v)
{
	gContext.VertexAttrib4Nsv(index, v);
	checkError();
}

void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
	gContext.VertexAttrib4Nub(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4Nubv(GLuint index, GLubyte const * v)
{
	gContext.VertexAttrib4Nubv(index, v);
	checkError();
}

void glVertexAttrib4Nuiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttrib4Nuiv(index, v);
	checkError();
}

void glVertexAttrib4Nusv(GLuint index, GLushort const * v)
{
	gContext.VertexAttrib4Nusv(index, v);
	checkError();
}

void glVertexAttrib4bv(GLuint index, GLbyte const * v)
{
	gContext.VertexAttrib4bv(index, v);
	checkError();
}

void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gContext.VertexAttrib4d(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttrib4dv(index, v);
	checkError();
}

void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	gContext.VertexAttrib4f(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4fv(GLuint index, GLfloat const * v)
{
	gContext.VertexAttrib4fv(index, v);
	checkError();
}

void glVertexAttrib4iv(GLuint index, GLint const * v)
{
	gContext.VertexAttrib4iv(index, v);
	checkError();
}

void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
	gContext.VertexAttrib4s(index, x, y, z, w);
	checkError();
}

void glVertexAttrib4sv(GLuint index, GLshort const * v)
{
	gContext.VertexAttrib4sv(index, v);
	checkError();
}

void glVertexAttrib4ubv(GLuint index, GLubyte const * v)
{
	gContext.VertexAttrib4ubv(index, v);
	checkError();
}

void glVertexAttrib4uiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttrib4uiv(index, v);
	checkError();
}

void glVertexAttrib4usv(GLuint index, GLushort const * v)
{
	gContext.VertexAttrib4usv(index, v);
	checkError();
}

void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid const * pointer)
{
	gContext.VertexAttribPointer(index, size, type, normalized, stride, pointer);
	checkError();
}

void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix2x3fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix3x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix2x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix4x2fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix3x4fv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.UniformMatrix4x3fv(location, count, transpose, value);
	checkError();
}

void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
	gContext.ColorMaski(index, r, g, b, a);
	checkError();
}

void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data)
{
	gContext.GetBooleani_v(target, index, data);
	checkError();
}

void glGetIntegeri_v(GLenum target, GLuint index, GLint * data)
{
	gContext.GetIntegeri_v(target, index, data);
	checkError();
}

void glEnablei(GLenum target, GLuint index)
{
	gContext.Enablei(target, index);
	checkError();
}

void glDisablei(GLenum target, GLuint index)
{
	gContext.Disablei(target, index);
	checkError();
}

GLboolean glIsEnabledi(GLenum target, GLuint index)
{
	auto result = gContext.IsEnabledi(target, index);
	checkError();
	return result;
}

void glBeginTransformFeedback(GLenum primitiveMode)
{
	gContext.BeginTransformFeedback(primitiveMode);
	checkError();
}

void glEndTransformFeedback(void)
{
	gContext.EndTransformFeedback();
	checkError();
}

void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
	gContext.BindBufferRange(target, index, buffer, offset, size);
	checkError();
}

void glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
	gContext.BindBufferBase(target, index, buffer);
	checkError();
}

void glTransformFeedbackVaryings(GLuint program, GLsizei count, GLchar const * * varyings, GLenum bufferMode)
{
	gContext.TransformFeedbackVaryings(program, count, varyings, bufferMode);
	checkError();
}

void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
	gContext.GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
	checkError();
}

void glClampColor(GLenum target, GLenum clamp)
{
	gContext.ClampColor(target, clamp);
	checkError();
}

void glBeginConditionalRender(GLuint id, GLenum mode)
{
	gContext.BeginConditionalRender(id, mode);
	checkError();
}

void glEndConditionalRender(void)
{
	gContext.EndConditionalRender();
	checkError();
}

void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gContext.VertexAttribIPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params)
{
	gContext.GetVertexAttribIiv(index, pname, params);
	checkError();
}

void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params)
{
	gContext.GetVertexAttribIuiv(index, pname, params);
	checkError();
}

void glVertexAttribI1i(GLuint index, GLint x)
{
	gContext.VertexAttribI1i(index, x);
	checkError();
}

void glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
	gContext.VertexAttribI2i(index, x, y);
	checkError();
}

void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
	gContext.VertexAttribI3i(index, x, y, z);
	checkError();
}

void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
	gContext.VertexAttribI4i(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1ui(GLuint index, GLuint x)
{
	gContext.VertexAttribI1ui(index, x);
	checkError();
}

void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
	gContext.VertexAttribI2ui(index, x, y);
	checkError();
}

void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
	gContext.VertexAttribI3ui(index, x, y, z);
	checkError();
}

void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
	gContext.VertexAttribI4ui(index, x, y, z, w);
	checkError();
}

void glVertexAttribI1iv(GLuint index, GLint const * v)
{
	gContext.VertexAttribI1iv(index, v);
	checkError();
}

void glVertexAttribI2iv(GLuint index, GLint const * v)
{
	gContext.VertexAttribI2iv(index, v);
	checkError();
}

void glVertexAttribI3iv(GLuint index, GLint const * v)
{
	gContext.VertexAttribI3iv(index, v);
	checkError();
}

void glVertexAttribI4iv(GLuint index, GLint const * v)
{
	gContext.VertexAttribI4iv(index, v);
	checkError();
}

void glVertexAttribI1uiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttribI1uiv(index, v);
	checkError();
}

void glVertexAttribI2uiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttribI2uiv(index, v);
	checkError();
}

void glVertexAttribI3uiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttribI3uiv(index, v);
	checkError();
}

void glVertexAttribI4uiv(GLuint index, GLuint const * v)
{
	gContext.VertexAttribI4uiv(index, v);
	checkError();
}

void glVertexAttribI4bv(GLuint index, GLbyte const * v)
{
	gContext.VertexAttribI4bv(index, v);
	checkError();
}

void glVertexAttribI4sv(GLuint index, GLshort const * v)
{
	gContext.VertexAttribI4sv(index, v);
	checkError();
}

void glVertexAttribI4ubv(GLuint index, GLubyte const * v)
{
	gContext.VertexAttribI4ubv(index, v);
	checkError();
}

void glVertexAttribI4usv(GLuint index, GLushort const * v)
{
	gContext.VertexAttribI4usv(index, v);
	checkError();
}

void glGetUniformuiv(GLuint program, GLint location, GLuint * params)
{
	gContext.GetUniformuiv(program, location, params);
	checkError();
}

void glBindFragDataLocation(GLuint program, GLuint color, GLchar const * name)
{
	gContext.BindFragDataLocation(program, color, name);
	checkError();
}

GLint glGetFragDataLocation(GLuint program, GLchar const * name)
{
	auto result = gContext.GetFragDataLocation(program, name);
	checkError();
	return result;
}

void glUniform1ui(GLint location, GLuint v0)
{
	gContext.Uniform1ui(location, v0);
	checkError();
}

void glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
	gContext.Uniform2ui(location, v0, v1);
	checkError();
}

void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gContext.Uniform3ui(location, v0, v1, v2);
	checkError();
}

void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gContext.Uniform4ui(location, v0, v1, v2, v3);
	checkError();
}

void glUniform1uiv(GLint location, GLsizei count, GLuint const * value)
{
	gContext.Uniform1uiv(location, count, value);
	checkError();
}

void glUniform2uiv(GLint location, GLsizei count, GLuint const * value)
{
	gContext.Uniform2uiv(location, count, value);
	checkError();
}

void glUniform3uiv(GLint location, GLsizei count, GLuint const * value)
{
	gContext.Uniform3uiv(location, count, value);
	checkError();
}

void glUniform4uiv(GLint location, GLsizei count, GLuint const * value)
{
	gContext.Uniform4uiv(location, count, value);
	checkError();
}

void glTexParameterIiv(GLenum target, GLenum pname, GLint const * params)
{
	gContext.TexParameterIiv(target, pname, params);
	checkError();
}

void glTexParameterIuiv(GLenum target, GLenum pname, GLuint const * params)
{
	gContext.TexParameterIuiv(target, pname, params);
	checkError();
}

void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params)
{
	gContext.GetTexParameterIiv(target, pname, params);
	checkError();
}

void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params)
{
	gContext.GetTexParameterIuiv(target, pname, params);
	checkError();
}

void glClearBufferiv(GLenum buffer, GLint drawbuffer, GLint const * value)
{
	gContext.ClearBufferiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferuiv(GLenum buffer, GLint drawbuffer, GLuint const * value)
{
	gContext.ClearBufferuiv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfv(GLenum buffer, GLint drawbuffer, GLfloat const * value)
{
	gContext.ClearBufferfv(buffer, drawbuffer, value);
	checkError();
}

void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
	gContext.ClearBufferfi(buffer, drawbuffer, depth, stencil);
	checkError();
}

GLubyte const * glGetStringi (GLenum name, GLuint index)
{
	auto result = gContext.GetStringi (name, index);
	checkError();
	return result;
}

void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
	gContext.DrawArraysInstanced(mode, first, count, primcount);
	checkError();
}

void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount)
{
	gContext.DrawElementsInstanced(mode, count, type, indices, primcount);
	checkError();
}

void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
	gContext.TexBuffer(target, internalformat, buffer);
	checkError();
}

void glPrimitiveRestartIndex(GLuint index)
{
	gContext.PrimitiveRestartIndex(index);
	checkError();
}

void glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
{
	gContext.GetInteger64i_v(target, index, data);
	checkError();
}

void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
{
	gContext.GetBufferParameteri64v(target, pname, params);
	checkError();
}

void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
	gContext.FramebufferTexture(target, attachment, texture, level);
	checkError();
}

void glVertexAttribDivisor(GLuint index, GLuint divisor)
{
	gContext.VertexAttribDivisor(index, divisor);
	checkError();
}

void glMinSampleShading(GLclampf value)
{
	gContext.MinSampleShading(value);
	checkError();
}

void glBlendEquationi(GLuint buf, GLenum mode)
{
	gContext.BlendEquationi(buf, mode);
	checkError();
}

void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gContext.BlendEquationSeparatei(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
	gContext.BlendFunci(buf, src, dst);
	checkError();
}

void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gContext.BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

GLboolean glIsRenderbuffer(GLuint renderbuffer)
{
	auto result = gContext.IsRenderbuffer(renderbuffer);
	checkError();
	return result;
}

void glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
	gContext.BindRenderbuffer(target, renderbuffer);
	checkError();
}

void glDeleteRenderbuffers(GLsizei n, GLuint const * renderbuffers)
{
	gContext.DeleteRenderbuffers(n, renderbuffers);
	checkError();
}

void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
	gContext.GenRenderbuffers(n, renderbuffers);
	checkError();
}

void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	gContext.RenderbufferStorage(target, internalformat, width, height);
	checkError();
}

void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
	gContext.GetRenderbufferParameteriv(target, pname, params);
	checkError();
}

GLboolean glIsFramebuffer(GLuint framebuffer)
{
	auto result = gContext.IsFramebuffer(framebuffer);
	checkError();
	return result;
}

void glBindFramebuffer(GLenum target, GLuint framebuffer)
{
	gContext.BindFramebuffer(target, framebuffer);
	checkError();
}

void glDeleteFramebuffers(GLsizei n, GLuint const * framebuffers)
{
	gContext.DeleteFramebuffers(n, framebuffers);
	checkError();
}

void glGenFramebuffers(GLsizei n, GLuint * framebuffers)
{
	gContext.GenFramebuffers(n, framebuffers);
	checkError();
}

GLenum glCheckFramebufferStatus(GLenum target)
{
	auto result = gContext.CheckFramebufferStatus(target);
	checkError();
	return result;
}

void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gContext.FramebufferTexture1D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
	gContext.FramebufferTexture2D(target, attachment, textarget, texture, level);
	checkError();
}

void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
	gContext.FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
	checkError();
}

void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
	gContext.FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	checkError();
}

void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
	gContext.GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	checkError();
}

void glGenerateMipmap(GLenum target)
{
	gContext.GenerateMipmap(target);
	checkError();
}

void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	gContext.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	checkError();
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
	gContext.RenderbufferStorageMultisample(target, samples, internalformat, width, height);
	checkError();
}

void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
	gContext.FramebufferTextureLayer(target, attachment, texture, level, layer);
	checkError();
}

GLvoid * glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
	auto result = gContext.MapBufferRange(target, offset, length, access);
	checkError();
	return result;
}

void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	gContext.FlushMappedBufferRange(target, offset, length);
	checkError();
}

void glBindVertexArray(GLuint array)
{
	gContext.BindVertexArray(array);
	checkError();
}

void glDeleteVertexArrays(GLsizei n, GLuint const * arrays)
{
	gContext.DeleteVertexArrays(n, arrays);
	checkError();
}

void glGenVertexArrays(GLsizei n, GLuint * arrays)
{
	gContext.GenVertexArrays(n, arrays);
	checkError();
}

GLboolean glIsVertexArray(GLuint array)
{
	auto result = gContext.IsVertexArray(array);
	checkError();
	return result;
}

void glGetUniformIndices(GLuint program, GLsizei uniformCount, GLchar const * * uniformNames, GLuint * uniformIndices)
{
	gContext.GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
	checkError();
}

void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, GLuint const * uniformIndices, GLenum pname, GLint * params)
{
	gContext.GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
	checkError();
}

void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName)
{
	gContext.GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
	checkError();
}

GLuint glGetUniformBlockIndex(GLuint program, GLchar const * uniformBlockName)
{
	auto result = gContext.GetUniformBlockIndex(program, uniformBlockName);
	checkError();
	return result;
}

void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params)
{
	gContext.GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
	checkError();
}

void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
{
	gContext.GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
	checkError();
}

void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
	gContext.UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	checkError();
}

void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
	gContext.CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	checkError();
}

void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gContext.DrawElementsBaseVertex(mode, count, type, indices, basevertex);
	checkError();
}

void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, GLvoid const * indices, GLint basevertex)
{
	gContext.DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
	checkError();
}

void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, GLvoid const * indices, GLsizei primcount, GLint basevertex)
{
	gContext.DrawElementsInstancedBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glMultiDrawElementsBaseVertex(GLenum mode, GLsizei const * count, GLenum type, GLvoid const * * indices, GLsizei primcount, GLint const * basevertex)
{
	gContext.MultiDrawElementsBaseVertex(mode, count, type, indices, primcount, basevertex);
	checkError();
}

void glProvokingVertex(GLenum mode)
{
	gContext.ProvokingVertex(mode);
	checkError();
}

GLsync glFenceSync(GLenum condition, GLbitfield flags)
{
	auto result = gContext.FenceSync(condition, flags);
	checkError();
	return result;
}

GLboolean glIsSync(GLsync sync)
{
	auto result = gContext.IsSync(sync);
	checkError();
	return result;
}

void glDeleteSync(GLsync sync)
{
	gContext.DeleteSync(sync);
	checkError();
}

GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	auto result = gContext.ClientWaitSync(sync, flags, timeout);
	checkError();
	return result;
}

void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
	gContext.WaitSync(sync, flags, timeout);
	checkError();
}

void glGetInteger64v(GLenum pname, GLint64 *params)
{
	gContext.GetInteger64v(pname, params);
	checkError();
}

void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
	gContext.GetSynciv(sync, pname, bufSize, length, values);
	checkError();
}

void glTexImage2DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
	gContext.TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
	checkError();
}

void glTexImage3DMultisample(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
	gContext.TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
	checkError();
}

void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val)
{
	gContext.GetMultisamplefv(pname, index, val);
	checkError();
}

void glSampleMaski(GLuint index, GLbitfield mask)
{
	gContext.SampleMaski(index, mask);
	checkError();
}

void glBlendEquationiARB(GLuint buf, GLenum mode)
{
	gContext.BlendEquationiARB(buf, mode);
	checkError();
}

void glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
	gContext.BlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
	checkError();
}

void glBlendFunciARB(GLuint buf, GLenum src, GLenum dst)
{
	gContext.BlendFunciARB(buf, src, dst);
	checkError();
}

void glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	gContext.BlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
	checkError();
}

void glMinSampleShadingARB(GLclampf value)
{
	gContext.MinSampleShadingARB(value);
	checkError();
}

void glNamedStringARB(GLenum type, GLint namelen, GLchar const * name, GLint stringlen, GLchar const * string)
{
	gContext.NamedStringARB(type, namelen, name, stringlen, string);
	checkError();
}

void glDeleteNamedStringARB(GLint namelen, GLchar const * name)
{
	gContext.DeleteNamedStringARB(namelen, name);
	checkError();
}

void glCompileShaderIncludeARB(GLuint shader, GLsizei count, GLchar const * * path, GLint const * length)
{
	gContext.CompileShaderIncludeARB(shader, count, path, length);
	checkError();
}

GLboolean glIsNamedStringARB(GLint namelen, GLchar const * name)
{
	auto result = gContext.IsNamedStringARB(namelen, name);
	checkError();
	return result;
}

void glGetNamedStringARB(GLint namelen, GLchar const * name, GLsizei bufSize, GLint * stringlen, GLchar * string)
{
	gContext.GetNamedStringARB(namelen, name, bufSize, stringlen, string);
	checkError();
}

void glGetNamedStringivARB(GLint namelen, GLchar const * name, GLenum pname, GLint * params)
{
	gContext.GetNamedStringivARB(namelen, name, pname, params);
	checkError();
}

void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, GLchar const * name)
{
	gContext.BindFragDataLocationIndexed(program, colorNumber, index, name);
	checkError();
}

GLint glGetFragDataIndex(GLuint program, GLchar const * name)
{
	auto result = gContext.GetFragDataIndex(program, name);
	checkError();
	return result;
}

void glGenSamplers(GLsizei count, GLuint * samplers)
{
	gContext.GenSamplers(count, samplers);
	checkError();
}

void glDeleteSamplers(GLsizei count, GLuint const * samplers)
{
	gContext.DeleteSamplers(count, samplers);
	checkError();
}

GLboolean glIsSampler(GLuint sampler)
{
	auto result = gContext.IsSampler(sampler);
	checkError();
	return result;
}

void glBindSampler(GLuint unit, GLuint sampler)
{
	gContext.BindSampler(unit, sampler);
	checkError();
}

void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
	gContext.SamplerParameteri(sampler, pname, param);
	checkError();
}

void glSamplerParameteriv(GLuint sampler, GLenum pname, GLint const * param)
{
	gContext.SamplerParameteriv(sampler, pname, param);
	checkError();
}

void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
	gContext.SamplerParameterf(sampler, pname, param);
	checkError();
}

void glSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat const * param)
{
	gContext.SamplerParameterfv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIiv(GLuint sampler, GLenum pname, GLint const * param)
{
	gContext.SamplerParameterIiv(sampler, pname, param);
	checkError();
}

void glSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint const * param)
{
	gContext.SamplerParameterIuiv(sampler, pname, param);
	checkError();
}

void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params)
{
	gContext.GetSamplerParameteriv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params)
{
	gContext.GetSamplerParameterIiv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params)
{
	gContext.GetSamplerParameterfv(sampler, pname, params);
	checkError();
}

void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params)
{
	gContext.GetSamplerParameterIuiv(sampler, pname, params);
	checkError();
}

void glQueryCounter(GLuint id, GLenum target)
{
	gContext.QueryCounter(id, target);
	checkError();
}

void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params)
{
	gContext.GetQueryObjecti64v(id, pname, params);
	checkError();
}

void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params)
{
	gContext.GetQueryObjectui64v(id, pname, params);
	checkError();
}

void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gContext.VertexAttribP1ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gContext.VertexAttribP1uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gContext.VertexAttribP2ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gContext.VertexAttribP2uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gContext.VertexAttribP3ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gContext.VertexAttribP3uiv(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
	gContext.VertexAttribP4ui(index, type, normalized, value);
	checkError();
}

void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, GLuint const * value)
{
	gContext.VertexAttribP4uiv(index, type, normalized, value);
	checkError();
}

void glDrawArraysIndirect(GLenum mode, GLvoid const * indirect)
{
	gContext.DrawArraysIndirect(mode, indirect);
	checkError();
}

void glDrawElementsIndirect(GLenum mode, GLenum type, GLvoid const * indirect)
{
	gContext.DrawElementsIndirect(mode, type, indirect);
	checkError();
}

void glUniform1d(GLint location, GLdouble x)
{
	gContext.Uniform1d(location, x);
	checkError();
}

void glUniform2d(GLint location, GLdouble x, GLdouble y)
{
	gContext.Uniform2d(location, x, y);
	checkError();
}

void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
	gContext.Uniform3d(location, x, y, z);
	checkError();
}

void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gContext.Uniform4d(location, x, y, z, w);
	checkError();
}

void glUniform1dv(GLint location, GLsizei count, GLdouble const * value)
{
	gContext.Uniform1dv(location, count, value);
	checkError();
}

void glUniform2dv(GLint location, GLsizei count, GLdouble const * value)
{
	gContext.Uniform2dv(location, count, value);
	checkError();
}

void glUniform3dv(GLint location, GLsizei count, GLdouble const * value)
{
	gContext.Uniform3dv(location, count, value);
	checkError();
}

void glUniform4dv(GLint location, GLsizei count, GLdouble const * value)
{
	gContext.Uniform4dv(location, count, value);
	checkError();
}

void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix2x3dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix2x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix3x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix3x4dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix4x2dv(location, count, transpose, value);
	checkError();
}

void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.UniformMatrix4x3dv(location, count, transpose, value);
	checkError();
}

void glGetUniformdv(GLuint program, GLint location, GLdouble * params)
{
	gContext.GetUniformdv(program, location, params);
	checkError();
}

GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gContext.GetSubroutineUniformLocation(program, shadertype, name);
	checkError();
	return result;
}

GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, GLchar const * name)
{
	auto result = gContext.GetSubroutineIndex(program, shadertype, name);
	checkError();
	return result;
}

void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values)
{
	gContext.GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
	checkError();
}

void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gContext.GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name)
{
	gContext.GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
	checkError();
}

void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, GLuint const * indices)
{
	gContext.UniformSubroutinesuiv(shadertype, count, indices);
	checkError();
}

void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params)
{
	gContext.GetUniformSubroutineuiv(shadertype, location, params);
	checkError();
}

void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values)
{
	gContext.GetProgramStageiv(program, shadertype, pname, values);
	checkError();
}

void glPatchParameteri(GLenum pname, GLint value)
{
	gContext.PatchParameteri(pname, value);
	checkError();
}

void glPatchParameterfv(GLenum pname, GLfloat const * values)
{
	gContext.PatchParameterfv(pname, values);
	checkError();
}

void glBindTransformFeedback(GLenum target, GLuint id)
{
	gContext.BindTransformFeedback(target, id);
	checkError();
}

void glDeleteTransformFeedbacks(GLsizei n, GLuint const * ids)
{
	gContext.DeleteTransformFeedbacks(n, ids);
	checkError();
}

void glGenTransformFeedbacks(GLsizei n, GLuint * ids)
{
	gContext.GenTransformFeedbacks(n, ids);
	checkError();
}

GLboolean glIsTransformFeedback(GLuint id)
{
	auto result = gContext.IsTransformFeedback(id);
	checkError();
	return result;
}

void glPauseTransformFeedback(void)
{
	gContext.PauseTransformFeedback();
	checkError();
}

void glResumeTransformFeedback(void)
{
	gContext.ResumeTransformFeedback();
	checkError();
}

void glDrawTransformFeedback(GLenum mode, GLuint id)
{
	gContext.DrawTransformFeedback(mode, id);
	checkError();
}

void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
	gContext.DrawTransformFeedbackStream(mode, id, stream);
	checkError();
}

void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
	gContext.BeginQueryIndexed(target, index, id);
	checkError();
}

void glEndQueryIndexed(GLenum target, GLuint index)
{
	gContext.EndQueryIndexed(target, index);
	checkError();
}

void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params)
{
	gContext.GetQueryIndexediv(target, index, pname, params);
	checkError();
}

void glReleaseShaderCompiler(void)
{
	gContext.ReleaseShaderCompiler();
	checkError();
}

void glShaderBinary(GLsizei count, GLuint const * shaders, GLenum binaryformat, GLvoid const * binary, GLsizei length)
{
	gContext.ShaderBinary(count, shaders, binaryformat, binary, length);
	checkError();
}

void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision)
{
	gContext.GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
	checkError();
}

void glDepthRangef(GLclampf n, GLclampf f)
{
	gContext.DepthRangef(n, f);
	checkError();
}

void glClearDepthf(GLclampf d)
{
	gContext.ClearDepthf(d);
	checkError();
}

void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary)
{
	gContext.GetProgramBinary(program, bufSize, length, binaryFormat, binary);
	checkError();
}

void glProgramBinary(GLuint program, GLenum binaryFormat, GLvoid const * binary, GLsizei length)
{
	gContext.ProgramBinary(program, binaryFormat, binary, length);
	checkError();
}

void glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
	gContext.ProgramParameteri(program, pname, value);
	checkError();
}

void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
	gContext.UseProgramStages(pipeline, stages, program);
	checkError();
}

void glActiveShaderProgram(GLuint pipeline, GLuint program)
{
	gContext.ActiveShaderProgram(pipeline, program);
	checkError();
}

GLuint glCreateShaderProgramv(GLenum type, GLsizei count, GLchar const * * strings)
{
	auto result = gContext.CreateShaderProgramv(type, count, strings);
	checkError();
	return result;
}

void glBindProgramPipeline(GLuint pipeline)
{
	gContext.BindProgramPipeline(pipeline);
	checkError();
}

void glDeleteProgramPipelines(GLsizei n, GLuint const * pipelines)
{
	gContext.DeleteProgramPipelines(n, pipelines);
	checkError();
}

void glGenProgramPipelines(GLsizei n, GLuint * pipelines)
{
	gContext.GenProgramPipelines(n, pipelines);
	checkError();
}

GLboolean glIsProgramPipeline(GLuint pipeline)
{
	auto result = gContext.IsProgramPipeline(pipeline);
	checkError();
	return result;
}

void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params)
{
	gContext.GetProgramPipelineiv(pipeline, pname, params);
	checkError();
}

void glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
	gContext.ProgramUniform1i(program, location, v0);
	checkError();
}

void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gContext.ProgramUniform1iv(program, location, count, value);
	checkError();
}

void glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
	gContext.ProgramUniform1f(program, location, v0);
	checkError();
}

void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gContext.ProgramUniform1fv(program, location, count, value);
	checkError();
}

void glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
	gContext.ProgramUniform1d(program, location, v0);
	checkError();
}

void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gContext.ProgramUniform1dv(program, location, count, value);
	checkError();
}

void glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
	gContext.ProgramUniform1ui(program, location, v0);
	checkError();
}

void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gContext.ProgramUniform1uiv(program, location, count, value);
	checkError();
}

void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
	gContext.ProgramUniform2i(program, location, v0, v1);
	checkError();
}

void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gContext.ProgramUniform2iv(program, location, count, value);
	checkError();
}

void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
	gContext.ProgramUniform2f(program, location, v0, v1);
	checkError();
}

void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gContext.ProgramUniform2fv(program, location, count, value);
	checkError();
}

void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
	gContext.ProgramUniform2d(program, location, v0, v1);
	checkError();
}

void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gContext.ProgramUniform2dv(program, location, count, value);
	checkError();
}

void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
	gContext.ProgramUniform2ui(program, location, v0, v1);
	checkError();
}

void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gContext.ProgramUniform2uiv(program, location, count, value);
	checkError();
}

void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
	gContext.ProgramUniform3i(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gContext.ProgramUniform3iv(program, location, count, value);
	checkError();
}

void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	gContext.ProgramUniform3f(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gContext.ProgramUniform3fv(program, location, count, value);
	checkError();
}

void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
	gContext.ProgramUniform3d(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gContext.ProgramUniform3dv(program, location, count, value);
	checkError();
}

void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	gContext.ProgramUniform3ui(program, location, v0, v1, v2);
	checkError();
}

void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gContext.ProgramUniform3uiv(program, location, count, value);
	checkError();
}

void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	gContext.ProgramUniform4i(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, GLint const * value)
{
	gContext.ProgramUniform4iv(program, location, count, value);
	checkError();
}

void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	gContext.ProgramUniform4f(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, GLfloat const * value)
{
	gContext.ProgramUniform4fv(program, location, count, value);
	checkError();
}

void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
	gContext.ProgramUniform4d(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, GLdouble const * value)
{
	gContext.ProgramUniform4dv(program, location, count, value);
	checkError();
}

void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	gContext.ProgramUniform4ui(program, location, v0, v1, v2, v3);
	checkError();
}

void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, GLuint const * value)
{
	gContext.ProgramUniform4uiv(program, location, count, value);
	checkError();
}

void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLfloat const * value)
{
	gContext.ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	checkError();
}

void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, GLdouble const * value)
{
	gContext.ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	checkError();
}

void glValidateProgramPipeline(GLuint pipeline)
{
	gContext.ValidateProgramPipeline(pipeline);
	checkError();
}

void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
{
	gContext.GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
	checkError();
}

void glVertexAttribL1d(GLuint index, GLdouble x)
{
	gContext.VertexAttribL1d(index, x);
	checkError();
}

void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
	gContext.VertexAttribL2d(index, x, y);
	checkError();
}

void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
	gContext.VertexAttribL3d(index, x, y, z);
	checkError();
}

void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
	gContext.VertexAttribL4d(index, x, y, z, w);
	checkError();
}

void glVertexAttribL1dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttribL1dv(index, v);
	checkError();
}

void glVertexAttribL2dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttribL2dv(index, v);
	checkError();
}

void glVertexAttribL3dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttribL3dv(index, v);
	checkError();
}

void glVertexAttribL4dv(GLuint index, GLdouble const * v)
{
	gContext.VertexAttribL4dv(index, v);
	checkError();
}

void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid const * pointer)
{
	gContext.VertexAttribLPointer(index, size, type, stride, pointer);
	checkError();
}

void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params)
{
	gContext.GetVertexAttribLdv(index, pname, params);
	checkError();
}

void glViewportArrayv(GLuint first, GLsizei count, GLfloat const * v)
{
	gContext.ViewportArrayv(first, count, v);
	checkError();
}

void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	gContext.ViewportIndexedf(index, x, y, w, h);
	checkError();
}

void glViewportIndexedfv(GLuint index, GLfloat const * v)
{
	gContext.ViewportIndexedfv(index, v);
	checkError();
}

void glScissorArrayv(GLuint first, GLsizei count, GLint const * v)
{
	gContext.ScissorArrayv(first, count, v);
	checkError();
}

void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
	gContext.ScissorIndexed(index, left, bottom, width, height);
	checkError();
}

void glScissorIndexedv(GLuint index, GLint const * v)
{
	gContext.ScissorIndexedv(index, v);
	checkError();
}

void glDepthRangeArrayv(GLuint first, GLsizei count, GLclampd const * v)
{
	gContext.DepthRangeArrayv(first, count, v);
	checkError();
}

void glDepthRangeIndexed(GLuint index, GLclampd n, GLclampd f)
{
	gContext.DepthRangeIndexed(index, n, f);
	checkError();
}

void glGetFloati_v(GLenum target, GLuint index, GLfloat * data)
{
	gContext.GetFloati_v(target, index, data);
	checkError();
}

void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data)
{
	gContext.GetDoublei_v(target, index, data);
	checkError();
}

GLsync glCreateSyncFromCLeventARB(struct _cl_context * context, struct _cl_event * event, GLbitfield flags)
{
	auto result = gContext.CreateSyncFromCLeventARB(context, event, flags);
	checkError();
	return result;
}

void glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, GLuint const * ids, GLboolean enabled)
{
	gContext.DebugMessageControlARB(source, type, severity, count, ids, enabled);
	checkError();
}

void glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const * buf)
{
	gContext.DebugMessageInsertARB(source, type, id, severity, length, buf);
	checkError();
}

void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, GLvoid const * userParam)
{
	gContext.DebugMessageCallbackARB(callback, userParam);
	checkError();
}

GLuint glGetDebugMessageLogARB(GLuint count, GLsizei bufsize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
	auto result = gContext.GetDebugMessageLogARB(count, bufsize, sources, types, ids, severities, lengths, messageLog);
	checkError();
	return result;
}

GLenum glGetGraphicsResetStatusARB(void)
{
	auto result = gContext.GetGraphicsResetStatusARB();
	checkError();
	return result;
}

void glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v)
{
	gContext.GetnMapdvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v)
{
	gContext.GetnMapfvARB(target, query, bufSize, v);
	checkError();
}

void glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint * v)
{
	gContext.GetnMapivARB(target, query, bufSize, v);
	checkError();
}

void glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat * values)
{
	gContext.GetnPixelMapfvARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint * values)
{
	gContext.GetnPixelMapuivARB(map, bufSize, values);
	checkError();
}

void glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort * values)
{
	gContext.GetnPixelMapusvARB(map, bufSize, values);
	checkError();
}

void glGetnPolygonStippleARB(GLsizei bufSize, GLubyte * pattern)
{
	gContext.GetnPolygonStippleARB(bufSize, pattern);
	checkError();
}

void glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * table)
{
	gContext.GetnColorTableARB(target, format, type, bufSize, table);
	checkError();
}

void glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, GLvoid * image)
{
	gContext.GetnConvolutionFilterARB(target, format, type, bufSize, image);
	checkError();
}

void glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, GLvoid * row, GLsizei columnBufSize, GLvoid * column, GLvoid * span)
{
	gContext.GetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
	checkError();
}

void glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gContext.GetnHistogramARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, GLvoid * values)
{
	gContext.GetnMinmaxARB(target, reset, format, type, bufSize, values);
	checkError();
}

void glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * img)
{
	gContext.GetnTexImageARB(target, level, format, type, bufSize, img);
	checkError();
}

void glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid * data)
{
	gContext.ReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
	checkError();
}

void glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, GLvoid * img)
{
	gContext.GetnCompressedTexImageARB(target, lod, bufSize, img);
	checkError();
}

void glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
	gContext.GetnUniformfvARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
	gContext.GetnUniformivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
	gContext.GetnUniformuivARB(program, location, bufSize, params);
	checkError();
}

void glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
	gContext.GetnUniformdvARB(program, location, bufSize, params);
	checkError();
}

void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei primcount, GLuint baseinstance)
{
	gContext.DrawArraysInstancedBaseInstance(mode, first, count, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLuint baseinstance)
{
	gContext.DrawElementsInstancedBaseInstance(mode, count, type,  indices, primcount, baseinstance);
	checkError();
}

void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount, GLint basevertex, GLuint baseinstance)
{
	gContext.DrawElementsInstancedBaseVertexBaseInstance(mode, count, type,  indices, primcount, basevertex, baseinstance);
	checkError();
}

void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei primcount)
{
	gContext.DrawTransformFeedbackInstanced(mode, id, primcount);
	checkError();
}

void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei primcount)
{
	gContext.DrawTransformFeedbackStreamInstanced(mode, id, stream, primcount);
	checkError();
}

void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params)
{
	gContext.GetInternalformativ(target, internalformat, pname, bufSize, params);
	checkError();
}

void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params)
{
	gContext.GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
	checkError();
}

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
	gContext.BindImageTexture(unit, texture, level, layered, layer, access, format);
	checkError();
}

void glMemoryBarrier(GLbitfield barriers)
{
	gContext.MemoryBarrier(barriers);
	checkError();
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gContext.TexStorage1D(target, levels, internalformat, width);
	checkError();
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gContext.TexStorage2D(target, levels, internalformat, width, height);
	checkError();
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gContext.TexStorage3D(target, levels, internalformat, width, height, depth);
	checkError();
}

void glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
	gContext.TextureStorage1DEXT(texture, target, levels, internalformat, width);
	checkError();
}

void glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
	gContext.TextureStorage2DEXT(texture, target, levels, internalformat, width, height);
	checkError();
}

void glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
	gContext.TextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
	checkError();
}


namespace Twil {
namespace Gl {

void ContextT::initialize()
{
	Platform::SymbolLoaderT Loader;
	Loader.loadSymbolGL(gContext.CullFace, "glCullFace");
	Loader.loadSymbolGL(gContext.FrontFace, "glFrontFace");
	Loader.loadSymbolGL(gContext.Hint, "glHint");
	Loader.loadSymbolGL(gContext.LineWidth, "glLineWidth");
	Loader.loadSymbolGL(gContext.PointSize, "glPointSize");
	Loader.loadSymbolGL(gContext.PolygonMode, "glPolygonMode");
	Loader.loadSymbolGL(gContext.Scissor, "glScissor");
	Loader.loadSymbolGL(gContext.TexParameterf, "glTexParameterf");
	Loader.loadSymbolGL(gContext.TexParameterfv, "glTexParameterfv");
	Loader.loadSymbolGL(gContext.TexParameteri, "glTexParameteri");
	Loader.loadSymbolGL(gContext.TexParameteriv, "glTexParameteriv");
	Loader.loadSymbolGL(gContext.TexImage1D, "glTexImage1D");
	Loader.loadSymbolGL(gContext.TexImage2D, "glTexImage2D");
	Loader.loadSymbolGL(gContext.DrawBuffer, "glDrawBuffer");
	Loader.loadSymbolGL(gContext.Clear, "glClear");
	Loader.loadSymbolGL(gContext.ClearColor, "glClearColor");
	Loader.loadSymbolGL(gContext.ClearStencil, "glClearStencil");
	Loader.loadSymbolGL(gContext.ClearDepth, "glClearDepth");
	Loader.loadSymbolGL(gContext.StencilMask, "glStencilMask");
	Loader.loadSymbolGL(gContext.ColorMask, "glColorMask");
	Loader.loadSymbolGL(gContext.DepthMask, "glDepthMask");
	Loader.loadSymbolGL(gContext.Disable, "glDisable");
	Loader.loadSymbolGL(gContext.Enable, "glEnable");
	Loader.loadSymbolGL(gContext.Finish, "glFinish");
	Loader.loadSymbolGL(gContext.Flush, "glFlush");
	Loader.loadSymbolGL(gContext.BlendFunc, "glBlendFunc");
	Loader.loadSymbolGL(gContext.LogicOp, "glLogicOp");
	Loader.loadSymbolGL(gContext.StencilFunc, "glStencilFunc");
	Loader.loadSymbolGL(gContext.StencilOp, "glStencilOp");
	Loader.loadSymbolGL(gContext.DepthFunc, "glDepthFunc");
	Loader.loadSymbolGL(gContext.PixelStoref, "glPixelStoref");
	Loader.loadSymbolGL(gContext.PixelStorei, "glPixelStorei");
	Loader.loadSymbolGL(gContext.ReadBuffer, "glReadBuffer");
	Loader.loadSymbolGL(gContext.ReadPixels, "glReadPixels");
	Loader.loadSymbolGL(gContext.GetBooleanv, "glGetBooleanv");
	Loader.loadSymbolGL(gContext.GetDoublev, "glGetDoublev");
	Loader.loadSymbolGL(gContext.GetError, "glGetError");
	Loader.loadSymbolGL(gContext.GetFloatv, "glGetFloatv");
	Loader.loadSymbolGL(gContext.GetIntegerv, "glGetIntegerv");
	Loader.loadSymbolGL(gContext.GetString, "glGetString");
	Loader.loadSymbolGL(gContext.GetTexImage, "glGetTexImage");
	Loader.loadSymbolGL(gContext.GetTexParameterfv, "glGetTexParameterfv");
	Loader.loadSymbolGL(gContext.GetTexParameteriv, "glGetTexParameteriv");
	Loader.loadSymbolGL(gContext.GetTexLevelParameterfv, "glGetTexLevelParameterfv");
	Loader.loadSymbolGL(gContext.GetTexLevelParameteriv, "glGetTexLevelParameteriv");
	Loader.loadSymbolGL(gContext.IsEnabled, "glIsEnabled");
	Loader.loadSymbolGL(gContext.DepthRange, "glDepthRange");
	Loader.loadSymbolGL(gContext.Viewport, "glViewport");
	Loader.loadSymbolGL(gContext.DrawArrays, "glDrawArrays");
	Loader.loadSymbolGL(gContext.DrawElements, "glDrawElements");
	Loader.loadSymbolGL(gContext.GetPointerv, "glGetPointerv");
	Loader.loadSymbolGL(gContext.PolygonOffset, "glPolygonOffset");
	Loader.loadSymbolGL(gContext.CopyTexImage1D, "glCopyTexImage1D");
	Loader.loadSymbolGL(gContext.CopyTexImage2D, "glCopyTexImage2D");
	Loader.loadSymbolGL(gContext.CopyTexSubImage1D, "glCopyTexSubImage1D");
	Loader.loadSymbolGL(gContext.CopyTexSubImage2D, "glCopyTexSubImage2D");
	Loader.loadSymbolGL(gContext.TexSubImage1D, "glTexSubImage1D");
	Loader.loadSymbolGL(gContext.TexSubImage2D, "glTexSubImage2D");
	Loader.loadSymbolGL(gContext.BindTexture, "glBindTexture");
	Loader.loadSymbolGL(gContext.DeleteTextures, "glDeleteTextures");
	Loader.loadSymbolGL(gContext.GenTextures, "glGenTextures");
	Loader.loadSymbolGL(gContext.IsTexture, "glIsTexture");
	Loader.loadSymbol(gContext.BlendColor, "glBlendColor");
	Loader.loadSymbol(gContext.BlendEquation, "glBlendEquation");
	Loader.loadSymbol(gContext.DrawRangeElements, "glDrawRangeElements");
	Loader.loadSymbol(gContext.TexImage3D, "glTexImage3D");
	Loader.loadSymbol(gContext.TexSubImage3D, "glTexSubImage3D");
	Loader.loadSymbol(gContext.CopyTexSubImage3D, "glCopyTexSubImage3D");
	Loader.loadSymbol(gContext.ActiveTexture, "glActiveTexture");
	Loader.loadSymbol(gContext.SampleCoverage, "glSampleCoverage");
	Loader.loadSymbol(gContext.CompressedTexImage3D, "glCompressedTexImage3D");
	Loader.loadSymbol(gContext.CompressedTexImage2D, "glCompressedTexImage2D");
	Loader.loadSymbol(gContext.CompressedTexImage1D, "glCompressedTexImage1D");
	Loader.loadSymbol(gContext.CompressedTexSubImage3D, "glCompressedTexSubImage3D");
	Loader.loadSymbol(gContext.CompressedTexSubImage2D, "glCompressedTexSubImage2D");
	Loader.loadSymbol(gContext.CompressedTexSubImage1D, "glCompressedTexSubImage1D");
	Loader.loadSymbol(gContext.GetCompressedTexImage, "glGetCompressedTexImage");
	Loader.loadSymbol(gContext.BlendFuncSeparate, "glBlendFuncSeparate");
	Loader.loadSymbol(gContext.MultiDrawArrays, "glMultiDrawArrays");
	Loader.loadSymbol(gContext.MultiDrawElements, "glMultiDrawElements");
	Loader.loadSymbol(gContext.PointParameterf, "glPointParameterf");
	Loader.loadSymbol(gContext.PointParameterfv, "glPointParameterfv");
	Loader.loadSymbol(gContext.PointParameteri, "glPointParameteri");
	Loader.loadSymbol(gContext.PointParameteriv, "glPointParameteriv");
	Loader.loadSymbol(gContext.GenQueries, "glGenQueries");
	Loader.loadSymbol(gContext.DeleteQueries, "glDeleteQueries");
	Loader.loadSymbol(gContext.IsQuery, "glIsQuery");
	Loader.loadSymbol(gContext.BeginQuery, "glBeginQuery");
	Loader.loadSymbol(gContext.EndQuery, "glEndQuery");
	Loader.loadSymbol(gContext.GetQueryiv, "glGetQueryiv");
	Loader.loadSymbol(gContext.GetQueryObjectiv, "glGetQueryObjectiv");
	Loader.loadSymbol(gContext.VertexAttribP1ui, "glVertexAttribP1ui");
	Loader.loadSymbol(gContext.VertexAttribP1uiv, "glVertexAttribP1uiv");
	Loader.loadSymbol(gContext.VertexAttribP2ui, "glVertexAttribP2ui");
	Loader.loadSymbol(gContext.VertexAttribP2uiv, "glVertexAttribP2uiv");
	Loader.loadSymbol(gContext.VertexAttribP3ui, "glVertexAttribP3ui");
	Loader.loadSymbol(gContext.VertexAttribP3uiv, "glVertexAttribP3uiv");
	Loader.loadSymbol(gContext.VertexAttribP4ui, "glVertexAttribP4ui");
	Loader.loadSymbol(gContext.VertexAttribP4uiv, "glVertexAttribP4uiv");
	Loader.loadSymbol(gContext.GetQueryObjectuiv, "glGetQueryObjectuiv");
	Loader.loadSymbol(gContext.BindBuffer, "glBindBuffer");
	Loader.loadSymbol(gContext.DeleteBuffers, "glDeleteBuffers");
	Loader.loadSymbol(gContext.GenBuffers, "glGenBuffers");
	Loader.loadSymbol(gContext.IsBuffer, "glIsBuffer");
	Loader.loadSymbol(gContext.BufferData, "glBufferData");
	Loader.loadSymbol(gContext.BufferSubData, "glBufferSubData");
	Loader.loadSymbol(gContext.GetBufferSubData, "glGetBufferSubData");
	Loader.loadSymbol(gContext.MapBuffer, "glMapBuffer");
	Loader.loadSymbol(gContext.UnmapBuffer, "glUnmapBuffer");
	Loader.loadSymbol(gContext.GetBufferParameteriv, "glGetBufferParameteriv");
	Loader.loadSymbol(gContext.GetBufferPointerv, "glGetBufferPointerv");
	Loader.loadSymbol(gContext.BlendEquationSeparate, "glBlendEquationSeparate");
	Loader.loadSymbol(gContext.DrawBuffers, "glDrawBuffers");
	Loader.loadSymbol(gContext.StencilOpSeparate, "glStencilOpSeparate");
	Loader.loadSymbol(gContext.StencilFuncSeparate, "glStencilFuncSeparate");
	Loader.loadSymbol(gContext.StencilMaskSeparate, "glStencilMaskSeparate");
	Loader.loadSymbol(gContext.AttachShader, "glAttachShader");
	Loader.loadSymbol(gContext.BindAttribLocation, "glBindAttribLocation");
	Loader.loadSymbol(gContext.CompileShader, "glCompileShader");
	Loader.loadSymbol(gContext.CreateProgram, "glCreateProgram");
	Loader.loadSymbol(gContext.CreateShader, "glCreateShader");
	Loader.loadSymbol(gContext.DeleteProgram, "glDeleteProgram");
	Loader.loadSymbol(gContext.DeleteShader, "glDeleteShader");
	Loader.loadSymbol(gContext.DetachShader, "glDetachShader");
	Loader.loadSymbol(gContext.DisableVertexAttribArray, "glDisableVertexAttribArray");
	Loader.loadSymbol(gContext.EnableVertexAttribArray, "glEnableVertexAttribArray");
	Loader.loadSymbol(gContext.GetActiveAttrib, "glGetActiveAttrib");
	Loader.loadSymbol(gContext.GetActiveUniform, "glGetActiveUniform");
	Loader.loadSymbol(gContext.GetAttachedShaders, "glGetAttachedShaders");
	Loader.loadSymbol(gContext.GetAttribLocation, "glGetAttribLocation");
	Loader.loadSymbol(gContext.GetProgramiv, "glGetProgramiv");
	Loader.loadSymbol(gContext.GetProgramInfoLog, "glGetProgramInfoLog");
	Loader.loadSymbol(gContext.GetShaderiv, "glGetShaderiv");
	Loader.loadSymbol(gContext.GetShaderInfoLog, "glGetShaderInfoLog");
	Loader.loadSymbol(gContext.GetShaderSource, "glGetShaderSource");
	Loader.loadSymbol(gContext.GetUniformLocation, "glGetUniformLocation");
	Loader.loadSymbol(gContext.GetUniformfv, "glGetUniformfv");
	Loader.loadSymbol(gContext.GetUniformiv, "glGetUniformiv");
	Loader.loadSymbol(gContext.GetVertexAttribdv, "glGetVertexAttribdv");
	Loader.loadSymbol(gContext.GetVertexAttribfv, "glGetVertexAttribfv");
	Loader.loadSymbol(gContext.GetVertexAttribiv, "glGetVertexAttribiv");
	Loader.loadSymbol(gContext.GetVertexAttribPointerv, "glGetVertexAttribPointerv");
	Loader.loadSymbol(gContext.IsProgram, "glIsProgram");
	Loader.loadSymbol(gContext.IsShader, "glIsShader");
	Loader.loadSymbol(gContext.LinkProgram, "glLinkProgram");
	Loader.loadSymbol(gContext.ShaderSource, "glShaderSource");
	Loader.loadSymbol(gContext.UseProgram, "glUseProgram");
	Loader.loadSymbol(gContext.Uniform1f, "glUniform1f");
	Loader.loadSymbol(gContext.Uniform2f, "glUniform2f");
	Loader.loadSymbol(gContext.Uniform3f, "glUniform3f");
	Loader.loadSymbol(gContext.Uniform4f, "glUniform4f");
	Loader.loadSymbol(gContext.Uniform1i, "glUniform1i");
	Loader.loadSymbol(gContext.Uniform2i, "glUniform2i");
	Loader.loadSymbol(gContext.Uniform3i, "glUniform3i");
	Loader.loadSymbol(gContext.Uniform4i, "glUniform4i");
	Loader.loadSymbol(gContext.Uniform1fv, "glUniform1fv");
	Loader.loadSymbol(gContext.Uniform2fv, "glUniform2fv");
	Loader.loadSymbol(gContext.Uniform3fv, "glUniform3fv");
	Loader.loadSymbol(gContext.Uniform4fv, "glUniform4fv");
	Loader.loadSymbol(gContext.Uniform1iv, "glUniform1iv");
	Loader.loadSymbol(gContext.Uniform2iv, "glUniform2iv");
	Loader.loadSymbol(gContext.Uniform3iv, "glUniform3iv");
	Loader.loadSymbol(gContext.Uniform4iv, "glUniform4iv");
	Loader.loadSymbol(gContext.UniformMatrix2fv, "glUniformMatrix2fv");
	Loader.loadSymbol(gContext.UniformMatrix3fv, "glUniformMatrix3fv");
	Loader.loadSymbol(gContext.UniformMatrix4fv, "glUniformMatrix4fv");
	Loader.loadSymbol(gContext.ValidateProgram, "glValidateProgram");
	Loader.loadSymbol(gContext.VertexAttrib1d, "glVertexAttrib1d");
	Loader.loadSymbol(gContext.VertexAttrib1dv, "glVertexAttrib1dv");
	Loader.loadSymbol(gContext.VertexAttrib1f, "glVertexAttrib1f");
	Loader.loadSymbol(gContext.VertexAttrib1fv, "glVertexAttrib1fv");
	Loader.loadSymbol(gContext.VertexAttrib1s, "glVertexAttrib1s");
	Loader.loadSymbol(gContext.VertexAttrib1sv, "glVertexAttrib1sv");
	Loader.loadSymbol(gContext.VertexAttrib2d, "glVertexAttrib2d");
	Loader.loadSymbol(gContext.VertexAttrib2dv, "glVertexAttrib2dv");
	Loader.loadSymbol(gContext.VertexAttrib2f, "glVertexAttrib2f");
	Loader.loadSymbol(gContext.VertexAttrib2fv, "glVertexAttrib2fv");
	Loader.loadSymbol(gContext.VertexAttrib2s, "glVertexAttrib2s");
	Loader.loadSymbol(gContext.VertexAttrib2sv, "glVertexAttrib2sv");
	Loader.loadSymbol(gContext.VertexAttrib3d, "glVertexAttrib3d");
	Loader.loadSymbol(gContext.VertexAttrib3dv, "glVertexAttrib3dv");
	Loader.loadSymbol(gContext.VertexAttrib3f, "glVertexAttrib3f");
	Loader.loadSymbol(gContext.VertexAttrib3fv, "glVertexAttrib3fv");
	Loader.loadSymbol(gContext.VertexAttrib3s, "glVertexAttrib3s");
	Loader.loadSymbol(gContext.VertexAttrib3sv, "glVertexAttrib3sv");
	Loader.loadSymbol(gContext.VertexAttrib4Nbv, "glVertexAttrib4Nbv");
	Loader.loadSymbol(gContext.VertexAttrib4Niv, "glVertexAttrib4Niv");
	Loader.loadSymbol(gContext.VertexAttrib4Nsv, "glVertexAttrib4Nsv");
	Loader.loadSymbol(gContext.VertexAttrib4Nub, "glVertexAttrib4Nub");
	Loader.loadSymbol(gContext.VertexAttrib4Nubv, "glVertexAttrib4Nubv");
	Loader.loadSymbol(gContext.VertexAttrib4Nuiv, "glVertexAttrib4Nuiv");
	Loader.loadSymbol(gContext.VertexAttrib4Nusv, "glVertexAttrib4Nusv");
	Loader.loadSymbol(gContext.VertexAttrib4bv, "glVertexAttrib4bv");
	Loader.loadSymbol(gContext.VertexAttrib4d, "glVertexAttrib4d");
	Loader.loadSymbol(gContext.VertexAttrib4dv, "glVertexAttrib4dv");
	Loader.loadSymbol(gContext.VertexAttrib4f, "glVertexAttrib4f");
	Loader.loadSymbol(gContext.VertexAttrib4fv, "glVertexAttrib4fv");
	Loader.loadSymbol(gContext.VertexAttrib4iv, "glVertexAttrib4iv");
	Loader.loadSymbol(gContext.VertexAttrib4s, "glVertexAttrib4s");
	Loader.loadSymbol(gContext.VertexAttrib4sv, "glVertexAttrib4sv");
	Loader.loadSymbol(gContext.VertexAttrib4ubv, "glVertexAttrib4ubv");
	Loader.loadSymbol(gContext.VertexAttrib4uiv, "glVertexAttrib4uiv");
	Loader.loadSymbol(gContext.VertexAttrib4usv, "glVertexAttrib4usv");
	Loader.loadSymbol(gContext.VertexAttribPointer, "glVertexAttribPointer");
	Loader.loadSymbol(gContext.UniformMatrix2x3fv, "glUniformMatrix2x3fv");
	Loader.loadSymbol(gContext.UniformMatrix3x2fv, "glUniformMatrix3x2fv");
	Loader.loadSymbol(gContext.UniformMatrix2x4fv, "glUniformMatrix2x4fv");
	Loader.loadSymbol(gContext.UniformMatrix4x2fv, "glUniformMatrix4x2fv");
	Loader.loadSymbol(gContext.UniformMatrix3x4fv, "glUniformMatrix3x4fv");
	Loader.loadSymbol(gContext.UniformMatrix4x3fv, "glUniformMatrix4x3fv");
	Loader.loadSymbol(gContext.ColorMaski, "glColorMaski");
	Loader.loadSymbol(gContext.GetBooleani_v, "glGetBooleani_v");
	Loader.loadSymbol(gContext.GetIntegeri_v, "glGetIntegeri_v");
	Loader.loadSymbol(gContext.Enablei, "glEnablei");
	Loader.loadSymbol(gContext.Disablei, "glDisablei");
	Loader.loadSymbol(gContext.IsEnabledi, "glIsEnabledi");
	Loader.loadSymbol(gContext.BeginTransformFeedback, "glBeginTransformFeedback");
	Loader.loadSymbol(gContext.EndTransformFeedback, "glEndTransformFeedback");
	Loader.loadSymbol(gContext.BindBufferRange, "glBindBufferRange");
	Loader.loadSymbol(gContext.BindBufferBase, "glBindBufferBase");
	Loader.loadSymbol(gContext.TransformFeedbackVaryings, "glTransformFeedbackVaryings");
	Loader.loadSymbol(gContext.GetTransformFeedbackVarying, "glGetTransformFeedbackVarying");
	Loader.loadSymbol(gContext.ClampColor, "glClampColor");
	Loader.loadSymbol(gContext.BeginConditionalRender, "glBeginConditionalRender");
	Loader.loadSymbol(gContext.EndConditionalRender, "glEndConditionalRender");
	Loader.loadSymbol(gContext.VertexAttribIPointer, "glVertexAttribIPointer");
	Loader.loadSymbol(gContext.GetVertexAttribIiv, "glGetVertexAttribIiv");
	Loader.loadSymbol(gContext.GetVertexAttribIuiv, "glGetVertexAttribIuiv");
	Loader.loadSymbol(gContext.VertexAttribI1i, "glVertexAttribI1i");
	Loader.loadSymbol(gContext.VertexAttribI2i, "glVertexAttribI2i");
	Loader.loadSymbol(gContext.VertexAttribI3i, "glVertexAttribI3i");
	Loader.loadSymbol(gContext.VertexAttribI4i, "glVertexAttribI4i");
	Loader.loadSymbol(gContext.VertexAttribI1ui, "glVertexAttribI1ui");
	Loader.loadSymbol(gContext.VertexAttribI2ui, "glVertexAttribI2ui");
	Loader.loadSymbol(gContext.VertexAttribI3ui, "glVertexAttribI3ui");
	Loader.loadSymbol(gContext.VertexAttribI4ui, "glVertexAttribI4ui");
	Loader.loadSymbol(gContext.VertexAttribI1iv, "glVertexAttribI1iv");
	Loader.loadSymbol(gContext.VertexAttribI2iv, "glVertexAttribI2iv");
	Loader.loadSymbol(gContext.VertexAttribI3iv, "glVertexAttribI3iv");
	Loader.loadSymbol(gContext.VertexAttribI4iv, "glVertexAttribI4iv");
	Loader.loadSymbol(gContext.VertexAttribI1uiv, "glVertexAttribI1uiv");
	Loader.loadSymbol(gContext.VertexAttribI2uiv, "glVertexAttribI2uiv");
	Loader.loadSymbol(gContext.VertexAttribI3uiv, "glVertexAttribI3uiv");
	Loader.loadSymbol(gContext.VertexAttribI4uiv, "glVertexAttribI4uiv");
	Loader.loadSymbol(gContext.VertexAttribI4bv, "glVertexAttribI4bv");
	Loader.loadSymbol(gContext.VertexAttribI4sv, "glVertexAttribI4sv");
	Loader.loadSymbol(gContext.VertexAttribI4ubv, "glVertexAttribI4ubv");
	Loader.loadSymbol(gContext.VertexAttribI4usv, "glVertexAttribI4usv");
	Loader.loadSymbol(gContext.GetUniformuiv, "glGetUniformuiv");
	Loader.loadSymbol(gContext.BindFragDataLocation, "glBindFragDataLocation");
	Loader.loadSymbol(gContext.GetFragDataLocation, "glGetFragDataLocation");
	Loader.loadSymbol(gContext.Uniform1ui, "glUniform1ui");
	Loader.loadSymbol(gContext.Uniform2ui, "glUniform2ui");
	Loader.loadSymbol(gContext.Uniform3ui, "glUniform3ui");
	Loader.loadSymbol(gContext.Uniform4ui, "glUniform4ui");
	Loader.loadSymbol(gContext.Uniform1uiv, "glUniform1uiv");
	Loader.loadSymbol(gContext.Uniform2uiv, "glUniform2uiv");
	Loader.loadSymbol(gContext.Uniform3uiv, "glUniform3uiv");
	Loader.loadSymbol(gContext.Uniform4uiv, "glUniform4uiv");
	Loader.loadSymbol(gContext.TexParameterIiv, "glTexParameterIiv");
	Loader.loadSymbol(gContext.TexParameterIuiv, "glTexParameterIuiv");
	Loader.loadSymbol(gContext.GetTexParameterIiv, "glGetTexParameterIiv");
	Loader.loadSymbol(gContext.GetTexParameterIuiv, "glGetTexParameterIuiv");
	Loader.loadSymbol(gContext.ClearBufferiv, "glClearBufferiv");
	Loader.loadSymbol(gContext.ClearBufferuiv, "glClearBufferuiv");
	Loader.loadSymbol(gContext.ClearBufferfv, "glClearBufferfv");
	Loader.loadSymbol(gContext.ClearBufferfi, "glClearBufferfi");
	Loader.loadSymbol(gContext.GetStringi, "glGetStringi");
	Loader.loadSymbol(gContext.DrawArraysInstanced, "glDrawArraysInstanced");
	Loader.loadSymbol(gContext.DrawElementsInstanced, "glDrawElementsInstanced");
	Loader.loadSymbol(gContext.TexBuffer, "glTexBuffer");
	Loader.loadSymbol(gContext.PrimitiveRestartIndex, "glPrimitiveRestartIndex");
	Loader.loadSymbol(gContext.GetInteger64i_v, "glGetInteger64i_v");
	Loader.loadSymbol(gContext.GetBufferParameteri64v, "glGetBufferParameteri64v");
	Loader.loadSymbol(gContext.FramebufferTexture, "glFramebufferTexture");
	Loader.loadSymbol(gContext.VertexAttribDivisor, "glVertexAttribDivisor");
	Loader.loadSymbol(gContext.MinSampleShading, "glMinSampleShading");
	Loader.loadSymbol(gContext.BlendEquationi, "glBlendEquationi");
	Loader.loadSymbol(gContext.BlendEquationSeparatei, "glBlendEquationSeparatei");
	Loader.loadSymbol(gContext.BlendFunci, "glBlendFunci");
	Loader.loadSymbol(gContext.BlendFuncSeparatei, "glBlendFuncSeparatei");
	Loader.loadSymbol(gContext.IsRenderbuffer, "glIsRenderbuffer");
	Loader.loadSymbol(gContext.BindRenderbuffer, "glBindRenderbuffer");
	Loader.loadSymbol(gContext.DeleteRenderbuffers, "glDeleteRenderbuffers");
	Loader.loadSymbol(gContext.GenRenderbuffers, "glGenRenderbuffers");
	Loader.loadSymbol(gContext.RenderbufferStorage, "glRenderbufferStorage");
	Loader.loadSymbol(gContext.GetRenderbufferParameteriv, "glGetRenderbufferParameteriv");
	Loader.loadSymbol(gContext.IsFramebuffer, "glIsFramebuffer");
	Loader.loadSymbol(gContext.BindFramebuffer, "glBindFramebuffer");
	Loader.loadSymbol(gContext.DeleteFramebuffers, "glDeleteFramebuffers");
	Loader.loadSymbol(gContext.GenFramebuffers, "glGenFramebuffers");
	Loader.loadSymbol(gContext.CheckFramebufferStatus, "glCheckFramebufferStatus");
	Loader.loadSymbol(gContext.FramebufferTexture1D, "glFramebufferTexture1D");
	Loader.loadSymbol(gContext.FramebufferTexture2D, "glFramebufferTexture2D");
	Loader.loadSymbol(gContext.FramebufferTexture3D, "glFramebufferTexture3D");
	Loader.loadSymbol(gContext.FramebufferRenderbuffer, "glFramebufferRenderbuffer");
	Loader.loadSymbol(gContext.GetFramebufferAttachmentParameteriv, "glGetFramebufferAttachmentParameteriv");
	Loader.loadSymbol(gContext.GenerateMipmap, "glGenerateMipmap");
	Loader.loadSymbol(gContext.BlitFramebuffer, "glBlitFramebuffer");
	Loader.loadSymbol(gContext.RenderbufferStorageMultisample, "glRenderbufferStorageMultisample");
	Loader.loadSymbol(gContext.FramebufferTextureLayer, "glFramebufferTextureLayer");
	Loader.loadSymbol(gContext.MapBufferRange, "glMapBufferRange");
	Loader.loadSymbol(gContext.FlushMappedBufferRange, "glFlushMappedBufferRange");
	Loader.loadSymbol(gContext.BindVertexArray, "glBindVertexArray");
	Loader.loadSymbol(gContext.DeleteVertexArrays, "glDeleteVertexArrays");
	Loader.loadSymbol(gContext.GenVertexArrays, "glGenVertexArrays");
	Loader.loadSymbol(gContext.IsVertexArray, "glIsVertexArray");
	Loader.loadSymbol(gContext.GetUniformIndices, "glGetUniformIndices");
	Loader.loadSymbol(gContext.GetActiveUniformsiv, "glGetActiveUniformsiv");
	Loader.loadSymbol(gContext.GetActiveUniformName, "glGetActiveUniformName");
	Loader.loadSymbol(gContext.GetUniformBlockIndex, "glGetUniformBlockIndex");
	Loader.loadSymbol(gContext.GetActiveUniformBlockiv, "glGetActiveUniformBlockiv");
	Loader.loadSymbol(gContext.GetActiveUniformBlockName, "glGetActiveUniformBlockName");
	Loader.loadSymbol(gContext.UniformBlockBinding, "glUniformBlockBinding");
	Loader.loadSymbol(gContext.CopyBufferSubData, "glCopyBufferSubData");
	Loader.loadSymbol(gContext.DrawElementsBaseVertex, "glDrawElementsBaseVertex");
	Loader.loadSymbol(gContext.DrawRangeElementsBaseVertex, "glDrawRangeElementsBaseVertex");
	Loader.loadSymbol(gContext.DrawElementsInstancedBaseVertex, "glDrawElementsInstancedBaseVertex");
	Loader.loadSymbol(gContext.MultiDrawElementsBaseVertex, "glMultiDrawElementsBaseVertex");
	Loader.loadSymbol(gContext.ProvokingVertex, "glProvokingVertex");
	Loader.loadSymbol(gContext.FenceSync, "glFenceSync");
	Loader.loadSymbol(gContext.IsSync, "glIsSync");
	Loader.loadSymbol(gContext.DeleteSync, "glDeleteSync");
	Loader.loadSymbol(gContext.ClientWaitSync, "glClientWaitSync");
	Loader.loadSymbol(gContext.WaitSync, "glWaitSync");
	Loader.loadSymbol(gContext.GetInteger64v, "glGetInteger64v");
	Loader.loadSymbol(gContext.GetSynciv, "glGetSynciv");
	Loader.loadSymbol(gContext.TexImage2DMultisample, "glTexImage2DMultisample");
	Loader.loadSymbol(gContext.TexImage3DMultisample, "glTexImage3DMultisample");
	Loader.loadSymbol(gContext.GetMultisamplefv, "glGetMultisamplefv");
	Loader.loadSymbol(gContext.SampleMaski, "glSampleMaski");
	Loader.loadSymbol(gContext.BlendEquationiARB, "glBlendEquationiARB");
	Loader.loadSymbol(gContext.BlendEquationSeparateiARB, "glBlendEquationSeparateiARB");
	Loader.loadSymbol(gContext.BlendFunciARB, "glBlendFunciARB");
	Loader.loadSymbol(gContext.BlendFuncSeparateiARB, "glBlendFuncSeparateiARB");
	Loader.loadSymbol(gContext.MinSampleShadingARB, "glMinSampleShadingARB");
	Loader.loadSymbol(gContext.NamedStringARB, "glNamedStringARB");
	Loader.loadSymbol(gContext.DeleteNamedStringARB, "glDeleteNamedStringARB");
	Loader.loadSymbol(gContext.CompileShaderIncludeARB, "glCompileShaderIncludeARB");
	Loader.loadSymbol(gContext.IsNamedStringARB, "glIsNamedStringARB");
	Loader.loadSymbol(gContext.GetNamedStringARB, "glGetNamedStringARB");
	Loader.loadSymbol(gContext.GetNamedStringivARB, "glGetNamedStringivARB");
	Loader.loadSymbol(gContext.BindFragDataLocationIndexed, "glBindFragDataLocationIndexed");
	Loader.loadSymbol(gContext.GetFragDataIndex, "glGetFragDataIndex");
	Loader.loadSymbol(gContext.GenSamplers, "glGenSamplers");
	Loader.loadSymbol(gContext.DeleteSamplers, "glDeleteSamplers");
	Loader.loadSymbol(gContext.IsSampler, "glIsSampler");
	Loader.loadSymbol(gContext.BindSampler, "glBindSampler");
	Loader.loadSymbol(gContext.SamplerParameteri, "glSamplerParameteri");
	Loader.loadSymbol(gContext.SamplerParameteriv, "glSamplerParameteriv");
	Loader.loadSymbol(gContext.SamplerParameterf, "glSamplerParameterf");
	Loader.loadSymbol(gContext.SamplerParameterfv, "glSamplerParameterfv");
	Loader.loadSymbol(gContext.SamplerParameterIiv, "glSamplerParameterIiv");
	Loader.loadSymbol(gContext.SamplerParameterIuiv, "glSamplerParameterIuiv");
	Loader.loadSymbol(gContext.GetSamplerParameteriv, "glGetSamplerParameteriv");
	Loader.loadSymbol(gContext.GetSamplerParameterIiv, "glGetSamplerParameterIiv");
	Loader.loadSymbol(gContext.GetSamplerParameterfv, "glGetSamplerParameterfv");
	Loader.loadSymbol(gContext.GetSamplerParameterIuiv, "glGetSamplerParameterIuiv");
	Loader.loadSymbol(gContext.QueryCounter, "glQueryCounter");
	Loader.loadSymbol(gContext.GetQueryObjecti64v, "glGetQueryObjecti64v");
	Loader.loadSymbol(gContext.GetQueryObjectui64v, "glGetQueryObjectui64v");
	Loader.loadSymbol(gContext.DrawArraysIndirect, "glDrawArraysIndirect");
	Loader.loadSymbol(gContext.DrawElementsIndirect, "glDrawElementsIndirect");
	Loader.loadSymbol(gContext.Uniform1d, "glUniform1d");
	Loader.loadSymbol(gContext.Uniform2d, "glUniform2d");
	Loader.loadSymbol(gContext.Uniform3d, "glUniform3d");
	Loader.loadSymbol(gContext.Uniform4d, "glUniform4d");
	Loader.loadSymbol(gContext.Uniform1dv, "glUniform1dv");
	Loader.loadSymbol(gContext.Uniform2dv, "glUniform2dv");
	Loader.loadSymbol(gContext.Uniform3dv, "glUniform3dv");
	Loader.loadSymbol(gContext.Uniform4dv, "glUniform4dv");
	Loader.loadSymbol(gContext.UniformMatrix2dv, "glUniformMatrix2dv");
	Loader.loadSymbol(gContext.UniformMatrix3dv, "glUniformMatrix3dv");
	Loader.loadSymbol(gContext.UniformMatrix4dv, "glUniformMatrix4dv");
	Loader.loadSymbol(gContext.UniformMatrix2x3dv, "glUniformMatrix2x3dv");
	Loader.loadSymbol(gContext.UniformMatrix2x4dv, "glUniformMatrix2x4dv");
	Loader.loadSymbol(gContext.UniformMatrix3x2dv, "glUniformMatrix3x2dv");
	Loader.loadSymbol(gContext.UniformMatrix3x4dv, "glUniformMatrix3x4dv");
	Loader.loadSymbol(gContext.UniformMatrix4x2dv, "glUniformMatrix4x2dv");
	Loader.loadSymbol(gContext.UniformMatrix4x3dv, "glUniformMatrix4x3dv");
	Loader.loadSymbol(gContext.GetUniformdv, "glGetUniformdv");
	Loader.loadSymbol(gContext.GetSubroutineUniformLocation, "glGetSubroutineUniformLocation");
	Loader.loadSymbol(gContext.GetSubroutineIndex, "glGetSubroutineIndex");
	Loader.loadSymbol(gContext.GetActiveSubroutineUniformiv, "glGetActiveSubroutineUniformiv");
	Loader.loadSymbol(gContext.GetActiveSubroutineUniformName, "glGetActiveSubroutineUniformName");
	Loader.loadSymbol(gContext.GetActiveSubroutineName, "glGetActiveSubroutineName");
	Loader.loadSymbol(gContext.UniformSubroutinesuiv, "glUniformSubroutinesuiv");
	Loader.loadSymbol(gContext.GetUniformSubroutineuiv, "glGetUniformSubroutineuiv");
	Loader.loadSymbol(gContext.GetProgramStageiv, "glGetProgramStageiv");
	Loader.loadSymbol(gContext.PatchParameteri, "glPatchParameteri");
	Loader.loadSymbol(gContext.PatchParameterfv, "glPatchParameterfv");
	Loader.loadSymbol(gContext.BindTransformFeedback, "glBindTransformFeedback");
	Loader.loadSymbol(gContext.DeleteTransformFeedbacks, "glDeleteTransformFeedbacks");
	Loader.loadSymbol(gContext.GenTransformFeedbacks, "glGenTransformFeedbacks");
	Loader.loadSymbol(gContext.IsTransformFeedback, "glIsTransformFeedback");
	Loader.loadSymbol(gContext.PauseTransformFeedback, "glPauseTransformFeedback");
	Loader.loadSymbol(gContext.ResumeTransformFeedback, "glResumeTransformFeedback");
	Loader.loadSymbol(gContext.DrawTransformFeedback, "glDrawTransformFeedback");
	Loader.loadSymbol(gContext.DrawTransformFeedbackStream, "glDrawTransformFeedbackStream");
	Loader.loadSymbol(gContext.BeginQueryIndexed, "glBeginQueryIndexed");
	Loader.loadSymbol(gContext.EndQueryIndexed, "glEndQueryIndexed");
	Loader.loadSymbol(gContext.GetQueryIndexediv, "glGetQueryIndexediv");
	Loader.loadSymbol(gContext.ReleaseShaderCompiler, "glReleaseShaderCompiler");
	Loader.loadSymbol(gContext.ShaderBinary, "glShaderBinary");
	Loader.loadSymbol(gContext.GetShaderPrecisionFormat, "glGetShaderPrecisionFormat");
	Loader.loadSymbol(gContext.DepthRangef, "glDepthRangef");
	Loader.loadSymbol(gContext.ClearDepthf, "glClearDepthf");
	Loader.loadSymbol(gContext.GetProgramBinary, "glGetProgramBinary");
	Loader.loadSymbol(gContext.ProgramBinary, "glProgramBinary");
	Loader.loadSymbol(gContext.ProgramParameteri, "glProgramParameteri");
	Loader.loadSymbol(gContext.UseProgramStages, "glUseProgramStages");
	Loader.loadSymbol(gContext.ActiveShaderProgram, "glActiveShaderProgram");
	Loader.loadSymbol(gContext.CreateShaderProgramv, "glCreateShaderProgramv");
	Loader.loadSymbol(gContext.BindProgramPipeline, "glBindProgramPipeline");
	Loader.loadSymbol(gContext.DeleteProgramPipelines, "glDeleteProgramPipelines");
	Loader.loadSymbol(gContext.GenProgramPipelines, "glGenProgramPipelines");
	Loader.loadSymbol(gContext.IsProgramPipeline, "glIsProgramPipeline");
	Loader.loadSymbol(gContext.GetProgramPipelineiv, "glGetProgramPipelineiv");
	Loader.loadSymbol(gContext.ProgramUniform1i, "glProgramUniform1i");
	Loader.loadSymbol(gContext.ProgramUniform1iv, "glProgramUniform1iv");
	Loader.loadSymbol(gContext.ProgramUniform1f, "glProgramUniform1f");
	Loader.loadSymbol(gContext.ProgramUniform1fv, "glProgramUniform1fv");
	Loader.loadSymbol(gContext.ProgramUniform1d, "glProgramUniform1d");
	Loader.loadSymbol(gContext.ProgramUniform1dv, "glProgramUniform1dv");
	Loader.loadSymbol(gContext.ProgramUniform1ui, "glProgramUniform1ui");
	Loader.loadSymbol(gContext.ProgramUniform1uiv, "glProgramUniform1uiv");
	Loader.loadSymbol(gContext.ProgramUniform2i, "glProgramUniform2i");
	Loader.loadSymbol(gContext.ProgramUniform2iv, "glProgramUniform2iv");
	Loader.loadSymbol(gContext.ProgramUniform2f, "glProgramUniform2f");
	Loader.loadSymbol(gContext.ProgramUniform2fv, "glProgramUniform2fv");
	Loader.loadSymbol(gContext.ProgramUniform2d, "glProgramUniform2d");
	Loader.loadSymbol(gContext.ProgramUniform2dv, "glProgramUniform2dv");
	Loader.loadSymbol(gContext.ProgramUniform2ui, "glProgramUniform2ui");
	Loader.loadSymbol(gContext.ProgramUniform2uiv, "glProgramUniform2uiv");
	Loader.loadSymbol(gContext.ProgramUniform3i, "glProgramUniform3i");
	Loader.loadSymbol(gContext.ProgramUniform3iv, "glProgramUniform3iv");
	Loader.loadSymbol(gContext.ProgramUniform3f, "glProgramUniform3f");
	Loader.loadSymbol(gContext.ProgramUniform3fv, "glProgramUniform3fv");
	Loader.loadSymbol(gContext.ProgramUniform3d, "glProgramUniform3d");
	Loader.loadSymbol(gContext.ProgramUniform3dv, "glProgramUniform3dv");
	Loader.loadSymbol(gContext.ProgramUniform3ui, "glProgramUniform3ui");
	Loader.loadSymbol(gContext.ProgramUniform3uiv, "glProgramUniform3uiv");
	Loader.loadSymbol(gContext.ProgramUniform4i, "glProgramUniform4i");
	Loader.loadSymbol(gContext.ProgramUniform4iv, "glProgramUniform4iv");
	Loader.loadSymbol(gContext.ProgramUniform4f, "glProgramUniform4f");
	Loader.loadSymbol(gContext.ProgramUniform4fv, "glProgramUniform4fv");
	Loader.loadSymbol(gContext.ProgramUniform4d, "glProgramUniform4d");
	Loader.loadSymbol(gContext.ProgramUniform4dv, "glProgramUniform4dv");
	Loader.loadSymbol(gContext.ProgramUniform4ui, "glProgramUniform4ui");
	Loader.loadSymbol(gContext.ProgramUniform4uiv, "glProgramUniform4uiv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2fv, "glProgramUniformMatrix2fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3fv, "glProgramUniformMatrix3fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4fv, "glProgramUniformMatrix4fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2dv, "glProgramUniformMatrix2dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3dv, "glProgramUniformMatrix3dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4dv, "glProgramUniformMatrix4dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2x3fv, "glProgramUniformMatrix2x3fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3x2fv, "glProgramUniformMatrix3x2fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2x4fv, "glProgramUniformMatrix2x4fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4x2fv, "glProgramUniformMatrix4x2fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3x4fv, "glProgramUniformMatrix3x4fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4x3fv, "glProgramUniformMatrix4x3fv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2x3dv, "glProgramUniformMatrix2x3dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3x2dv, "glProgramUniformMatrix3x2dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix2x4dv, "glProgramUniformMatrix2x4dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4x2dv, "glProgramUniformMatrix4x2dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix3x4dv, "glProgramUniformMatrix3x4dv");
	Loader.loadSymbol(gContext.ProgramUniformMatrix4x3dv, "glProgramUniformMatrix4x3dv");
	Loader.loadSymbol(gContext.ValidateProgramPipeline, "glValidateProgramPipeline");
	Loader.loadSymbol(gContext.GetProgramPipelineInfoLog, "glGetProgramPipelineInfoLog");
	Loader.loadSymbol(gContext.VertexAttribL1d, "glVertexAttribL1d");
	Loader.loadSymbol(gContext.VertexAttribL2d, "glVertexAttribL2d");
	Loader.loadSymbol(gContext.VertexAttribL3d, "glVertexAttribL3d");
	Loader.loadSymbol(gContext.VertexAttribL4d, "glVertexAttribL4d");
	Loader.loadSymbol(gContext.VertexAttribL1dv, "glVertexAttribL1dv");
	Loader.loadSymbol(gContext.VertexAttribL2dv, "glVertexAttribL2dv");
	Loader.loadSymbol(gContext.VertexAttribL3dv, "glVertexAttribL3dv");
	Loader.loadSymbol(gContext.VertexAttribL4dv, "glVertexAttribL4dv");
	Loader.loadSymbol(gContext.VertexAttribLPointer, "glVertexAttribLPointer");
	Loader.loadSymbol(gContext.GetVertexAttribLdv, "glGetVertexAttribLdv");
	Loader.loadSymbol(gContext.ViewportArrayv, "glViewportArrayv");
	Loader.loadSymbol(gContext.ViewportIndexedf, "glViewportIndexedf");
	Loader.loadSymbol(gContext.ViewportIndexedfv, "glViewportIndexedfv");
	Loader.loadSymbol(gContext.ScissorArrayv, "glScissorArrayv");
	Loader.loadSymbol(gContext.ScissorIndexed, "glScissorIndexed");
	Loader.loadSymbol(gContext.ScissorIndexedv, "glScissorIndexedv");
	Loader.loadSymbol(gContext.DepthRangeArrayv, "glDepthRangeArrayv");
	Loader.loadSymbol(gContext.DepthRangeIndexed, "glDepthRangeIndexed");
	Loader.loadSymbol(gContext.GetFloati_v, "glGetFloati_v");
	Loader.loadSymbol(gContext.GetDoublei_v, "glGetDoublei_v");
	Loader.loadSymbol(gContext.CreateSyncFromCLeventARB, "glCreateSyncFromCLeventARB");
	Loader.loadSymbol(gContext.DebugMessageControlARB, "glDebugMessageControlARB");
	Loader.loadSymbol(gContext.DebugMessageInsertARB, "glDebugMessageInsertARB");
	Loader.loadSymbol(gContext.DebugMessageCallbackARB, "glDebugMessageCallbackARB");
	Loader.loadSymbol(gContext.GetDebugMessageLogARB, "glGetDebugMessageLogARB");
	Loader.loadSymbol(gContext.GetGraphicsResetStatusARB, "glGetGraphicsResetStatusARB");
	Loader.loadSymbol(gContext.GetnMapdvARB, "glGetnMapdvARB");
	Loader.loadSymbol(gContext.GetnMapfvARB, "glGetnMapfvARB");
	Loader.loadSymbol(gContext.GetnMapivARB, "glGetnMapivARB");
	Loader.loadSymbol(gContext.GetnPixelMapfvARB, "glGetnPixelMapfvARB");
	Loader.loadSymbol(gContext.GetnPixelMapuivARB, "glGetnPixelMapuivARB");
	Loader.loadSymbol(gContext.GetnPixelMapusvARB, "glGetnPixelMapusvARB");
	Loader.loadSymbol(gContext.GetnPolygonStippleARB, "glGetnPolygonStippleARB");
	Loader.loadSymbol(gContext.GetnColorTableARB, "glGetnColorTableARB");
	Loader.loadSymbol(gContext.GetnConvolutionFilterARB, "glGetnConvolutionFilterARB");
	Loader.loadSymbol(gContext.GetnSeparableFilterARB, "glGetnSeparableFilterARB");
	Loader.loadSymbol(gContext.GetnHistogramARB, "glGetnHistogramARB");
	Loader.loadSymbol(gContext.GetnMinmaxARB, "glGetnMinmaxARB");
	Loader.loadSymbol(gContext.GetnTexImageARB, "glGetnTexImageARB");
	Loader.loadSymbol(gContext.ReadnPixelsARB, "glReadnPixelsARB");
	Loader.loadSymbol(gContext.GetnCompressedTexImageARB, "glGetnCompressedTexImageARB");
	Loader.loadSymbol(gContext.GetnUniformfvARB, "glGetnUniformfvARB");
	Loader.loadSymbol(gContext.GetnUniformivARB, "glGetnUniformivARB");
	Loader.loadSymbol(gContext.GetnUniformuivARB, "glGetnUniformuivARB");
	Loader.loadSymbol(gContext.GetnUniformdvARB, "glGetnUniformdvARB");
	Loader.loadSymbol(gContext.DrawArraysInstancedBaseInstance, "glDrawArraysInstancedBaseInstance");
	Loader.loadSymbol(gContext.DrawElementsInstancedBaseInstance, "glDrawElementsInstancedBaseInstance");
	Loader.loadSymbol(gContext.DrawElementsInstancedBaseVertexBaseInstance, "glDrawElementsInstancedBaseVertexBaseInstance");
	Loader.loadSymbol(gContext.DrawTransformFeedbackInstanced, "glDrawTransformFeedbackInstanced");
	Loader.loadSymbol(gContext.DrawTransformFeedbackStreamInstanced, "glDrawTransformFeedbackStreamInstanced");
	Loader.loadSymbol(gContext.GetInternalformativ, "glGetInternalformativ");
	Loader.loadSymbol(gContext.GetActiveAtomicCounterBufferiv, "glGetActiveAtomicCounterBufferiv");
	Loader.loadSymbol(gContext.BindImageTexture, "glBindImageTexture");
	Loader.loadSymbol(gContext.MemoryBarrier, "glMemoryBarrier");
	Loader.loadSymbol(gContext.TexStorage1D, "glTexStorage1D");
	Loader.loadSymbol(gContext.TexStorage2D, "glTexStorage2D");
	Loader.loadSymbol(gContext.TexStorage3D, "glTexStorage3D");
	Loader.loadSymbol(gContext.TextureStorage1DEXT, "glTextureStorage1DEXT");
	Loader.loadSymbol(gContext.TextureStorage2DEXT, "glTextureStorage2DEXT");
	Loader.loadSymbol(gContext.TextureStorage3DEXT, "glTextureStorage3DEXT");
}

}
}
