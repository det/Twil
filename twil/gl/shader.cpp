#include "shader.hpp"

#include "context.hpp"

#include <fstream>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace twil {
namespace gl {

Shader::Shader(GLenum type)
{
	id_ = glCreateShader(type);
}

Shader::~Shader() noexcept
{
	glDeleteShader(id_);
}

Shader::operator GLuint() const
{
	return id_;
}

void Shader::LoadFile(char const * path)
{
	std::ifstream file;
	file.open(path, std::ios::in);
	if (!file.is_open()) throw std::runtime_error{"Unable to open shader"};
	file.seekg(0, std::ios_base::end);
	auto pos = file.tellg();
	if (pos < 0) throw std::runtime_error{"Unable to read shader"};
	file.seekg(0, std::ios_base::beg);
	std::unique_ptr<GLchar[]> buffer{new GLchar[static_cast<std::size_t>(pos)]};
	file.read(buffer.get(), pos);
	file.close();

	GLchar const * sources[] = {buffer.get()};
	GLint const lengths[] = {static_cast<GLint>(pos)};
	glShaderSource(id_, 1, sources, lengths);
}

void Shader::Compile()
{
	glCompileShader(id_);
	GLint is_compiled = 0;
	glGetShaderiv(id_, GL_COMPILE_STATUS, &is_compiled);

	if (!is_compiled)
	{
		GLint log_length = 0;
		glGetShaderiv(id_, GL_INFO_LOG_LENGTH , &log_length);
		if (log_length < 1) throw std::runtime_error{"Shader compile error, unable to retrieve log"};
		std::unique_ptr<GLchar[]> log{new GLchar[log_length]};
		glGetShaderInfoLog(id_, log_length, &log_length, log.get());
		std::cerr << log.get();
		throw std::runtime_error{"Shader compile error"};
	}
}

}
}
