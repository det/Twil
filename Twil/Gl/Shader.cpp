#include "Shader.hpp"

#include "Context.hpp"
#include "Data/Memory.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Twil {
namespace Gl {

ShaderT::ShaderT(std::uint32_t Type)
{
	mId = glCreateShader(Type);
}

ShaderT::~ShaderT() noexcept
{
	glDeleteShader(mId);
}

ShaderT::operator std::uint32_t() const
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
	auto Buffer = Data::allocUnique<char>(static_cast<std::size_t>(Pos));
	File.read(Buffer.get(), Pos);
	File.close();

	char const * Sources[] = {Buffer.get()};
	std::int32_t const Lengths[] = {static_cast<std::int32_t>(Pos)};
	glShaderSource(mId, 1, Sources, Lengths);
}

void ShaderT::compile()
{
	glCompileShader(mId);
	std::int32_t IsCompiled = 0;
	glGetShaderiv(mId, GL_COMPILE_STATUS, &IsCompiled);

	if (!IsCompiled)
	{
		std::int32_t LogLength = 0;
		glGetShaderiv(mId, GL_INFO_LOG_LENGTH , &LogLength);
		if (LogLength < 1) throw std::runtime_error{"Shader compile error, unable to retrieve log"};
		auto Log = Data::allocUnique<char>(LogLength);
		glGetShaderInfoLog(mId, LogLength, &LogLength, Log.get());
		std::cerr << Log.get();
		throw std::runtime_error{"Shader compile error"};
	}
}

}
}
