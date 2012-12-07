#include "Gl/Program.hpp"

#include "Gl/Context.hpp"
#include "Gl/Shader.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Matrix4.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector4.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

Program::Program()
{
	mId = glCreateProgram();
}

Program::~Program()
{
	glDeleteProgram(mId);
}

Program::operator GLuint() const
{
	return mId;
}

void Program::attach(Gl::Shader const & shader)
{
	glAttachShader(mId, shader.mId);
}

void Program::link()
{
	glLinkProgram(mId);
	GLint IsLinked = 0;
	glGetProgramiv(mId, GL_LINK_STATUS, &IsLinked);
	if (!IsLinked) {
		GLint LogLength = 0;
		glGetProgramiv(mId, GL_INFO_LOG_LENGTH , &LogLength);
		std::basic_string<GLchar> Log((std::basic_string<GLchar>::size_type) LogLength, '\0');
		glGetProgramInfoLog(mId, LogLength, &LogLength, &Log[0]);
		std::cout << Log;
		throw std::runtime_error{"Program link error"};
	}
}

void Program::bindAttribLocation(GLuint Location, std::string const & Attrib)
{
	glBindAttribLocation(mId, Location, Attrib.c_str());
}

void Program::bindFragDataLocationIndexed(GLuint Color, GLuint Index, std::string const & Attrib)
{
	glBindFragDataLocationIndexed(mId, Color, Index, Attrib.c_str());
}

void Program::setUniform(GLint Location, GLboolean Transpose, Math::Matrix3 const & Value)
{
	glUniformMatrix3fv(Location, 1, Transpose, &Value.X.X);
}

void Program::setUniform(GLint Location, GLboolean Transpose, Math::Matrix4 const & Value)
{
	glUniformMatrix4fv(Location, 1, Transpose, &Value.X.X);
}

void Program::setUniform(GLint Location, float x, float y)
{
	glUniform2f(Location, x, y);
}

void Program::setUniform(GLint Location, float Value)
{
	glUniform1f(Location, Value);
}

void Program::setUniform(GLint Location, int Value)
{
	glUniform1i(Location, Value);
}

void Program::setUniform(GLint Location, float X, float Y, float Z, float W)
{
	glUniform4f(Location, X, Y, Z, W);
}

GLint Program::getLocation(std::string const & String) const
{
	return glGetUniformLocation(mId, String.c_str());
}

}
}

