#include "Program.hpp"

#include "Context.hpp"
#include "Shader.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

ProgramT::ProgramT()
{
	mId = glCreateProgram();
}

ProgramT::~ProgramT()
{
	glDeleteProgram(mId);
}

ProgramT::operator GLuint() const
{
	return mId;
}

void ProgramT::attach(ShaderT const & Shader)
{
	glAttachShader(mId, Shader.mId);
}

void ProgramT::link()
{
	glLinkProgram(mId);
	GLint IsLinked = 0;
	glGetProgramiv(mId, GL_LINK_STATUS, &IsLinked);
	if (!IsLinked) {
		GLint LogLength = 0;
		glGetProgramiv(mId, GL_INFO_LOG_LENGTH , &LogLength);
		std::vector<GLchar> Log(LogLength);
		glGetProgramInfoLog(mId, LogLength, &LogLength, Log.data());
		std::cout << Log.data();
		throw std::runtime_error{"Program link error"};
	}
}

void ProgramT::setUniform(GLint Location, float x, float y)
{
	glUniform2f(Location, x, y);
}

void ProgramT::setUniform(GLint Location, float Value)
{
	glUniform1f(Location, Value);
}

void ProgramT::setUniform(GLint Location, int Value)
{
	glUniform1i(Location, Value);
}

void ProgramT::setUniform(GLint Location, float X, float Y, float Z, float W)
{
	glUniform4f(Location, X, Y, Z, W);
}

GLint ProgramT::getLocation(char const * String) const
{
	return glGetUniformLocation(mId, String);
}

}
}

