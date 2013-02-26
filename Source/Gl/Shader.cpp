#include "Shader.hpp"

#include "Context.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Twil {
namespace Gl {

ShaderT::ShaderT(GLenum Type)
{
	mId = glCreateShader(Type);
}

ShaderT::~ShaderT()
{
	glDeleteShader(mId);
}

ShaderT::operator GLuint() const
{
	return mId;
}

void ShaderT::loadFile(char const * Path)
{
	std::ifstream File;
	File.open(Path, std::ios::in);
	if (!File.is_open()) throw std::runtime_error{"Unable to open shader"};
	File.seekg(0, std::ios_base::end);
	auto Pos = File.tellg();
	if (Pos < 0) throw std::runtime_error{"Unable to read shader"};
	auto Length = static_cast<std::size_t>(Pos);
	File.seekg(0, std::ios_base::beg);
	std::vector<GLchar> Data(Length);
	File.read(Data.data(), Pos);
	File.close();

	GLchar const * Sources = Data.data();
	GLint const Lengths = Length;
	glShaderSource(mId, 1, &Sources, &Lengths);
}

void ShaderT::compile()
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
