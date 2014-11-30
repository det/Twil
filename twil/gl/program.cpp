#include "program.hpp"

#include "shader.hpp"

#include <memory>
#include <iostream>
#include <stdexcept>

namespace twil {
namespace gl {

Program::Program()
{
	id_ = glCreateProgram();
}

Program::~Program() noexcept
{
	glDeleteProgram(id_);
}

Program::operator GLuint() const
{
	return id_;
}

void Program::Attach(Shader const & shader)
{
	glAttachShader(id_, shader);
}

void Program::Link()
{
	glLinkProgram(id_);
	GLint is_linked = 0;
	glGetProgramiv(id_, GL_LINK_STATUS, &is_linked);
	if (!is_linked)
	{
		GLint log_length = 0;
		glGetProgramiv(id_, GL_INFO_LOG_LENGTH , &log_length);
		std::unique_ptr<GLchar[]> log{new GLchar[log_length]};
		glGetProgramInfoLog(id_, log_length, &log_length, log.get());
		std::cerr << log.get();
		throw std::runtime_error{"Program link error"};
	}
}

void Program::SetUniform(GLint location, float x, float y)
{
	glUniform2f(location, x, y);
}

void Program::SetUniform(GLint location, float value)
{
	glUniform1f(location, value);
}

void Program::SetUniform(GLint location, int value)
{
	glUniform1i(location, value);
}

void Program::SetUniform(GLint location, float x, float y, float z, float w)
{
	glUniform4f(location, x, y, z, w);
}

GLint Program::GetLocation(char const * string) const
{
	return glGetUniformLocation(id_, string);
}

}
}

