#include "Shader.hpp"

#include "Context.hpp"
#include "Data/Memory.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

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
	File.seekg(0, std::ios_base::beg);
	auto Buffer = Data::makeArray<GLchar>(static_cast<std::size_t>(Pos));
	File.read(Buffer.get(), Pos);
	File.close();

	GLchar const * Sources[] = {Buffer.get()};
	GLint const Lengths[] = {static_cast<GLint>(Pos)};
	glShaderSource(mId, 1, Sources, Lengths);
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
		auto Log = Data::makeArray<GLchar>(LogLength);
		glGetShaderInfoLog(mId, LogLength, &LogLength, Log.get());
		std::cerr << Log.get();
		throw std::runtime_error{"Shader compile error"};
	}
}

}
}
