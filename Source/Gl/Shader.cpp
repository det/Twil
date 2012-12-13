#include "Gl/Shader.hpp"

#include "Gl/Context.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Twil {
namespace Gl {

Shader::Shader(GLenum Type)
{
	mId = glCreateShader(Type);
}

Shader::~Shader()
{
	glDeleteShader(mId);
}

Shader::operator GLuint()
{
	return mId;
}

void Shader::loadFile(std::string const & Path)
{
	std::ifstream File;
	File.open(Path, std::ios::in);
	if (!File.is_open()) throw std::runtime_error{"Unable to open shader"};
	File.seekg(0, std::ios_base::end);
	auto Pos = File.tellg();
	if (Pos < 0) throw std::runtime_error{"Unable to read shader"};
	auto Length = static_cast<std::size_t>(Pos);
	File.seekg(0, std::ios_base::beg);
	std::basic_string<GLchar> Data(Length, '\0');
	File.read(&Data[0], Pos);
	File.close();

	std::vector<GLchar const *> Sources{&Data[0]};
	std::vector<GLint> Lengths{Length};
	glShaderSource(mId, 1, &Sources[0], &Lengths[0]);
}

void Shader::compile()
{
	glCompileShader(mId);
	GLint IsCompiled = 0;
	glGetShaderiv(mId, GL_COMPILE_STATUS, &IsCompiled);

	if (!IsCompiled) {
		GLint LogLength = 0;
		glGetShaderiv(mId, GL_INFO_LOG_LENGTH , &LogLength);
		if (LogLength < 1) throw std::runtime_error{"Shader compile error, unable to retrieve log"};
		std::basic_string<GLchar> Log(static_cast<std::size_t>(LogLength), '\0');
		glGetShaderInfoLog(mId, LogLength, &LogLength, &Log[0]);
		std::cout << Log;
		throw std::runtime_error{"Shader compile error"};
	}
}

}
}
