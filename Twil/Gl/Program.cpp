#include "Program.hpp"

#include "Shader.hpp"
#include "Data/Memory.hpp"

#include <iostream>
#include <stdexcept>

namespace Twil {
namespace Gl {

ProgramT::ProgramT()
{
	mId = glCreateProgram();
}

ProgramT::~ProgramT() noexcept
{
	glDeleteProgram(mId);
}

ProgramT::operator std::uint32_t() const
{
	return mId;
}

void ProgramT::attach(ShaderT const & Shader)
{
	glAttachShader(mId, Shader);
}

void ProgramT::link()
{
	glLinkProgram(mId);
	std::int32_t IsLinked = 0;
	glGetProgramiv(mId, GL_LINK_STATUS, &IsLinked);
	if (!IsLinked)
	{
		std::int32_t LogLength = 0;
		glGetProgramiv(mId, GL_INFO_LOG_LENGTH , &LogLength);
		auto Log = Data::allocUnique<char>(LogLength);
		glGetProgramInfoLog(mId, LogLength, &LogLength, Log.get());
		std::cerr << Log.get();
		throw std::runtime_error{"Program link error"};
	}
}

void ProgramT::setUniform(std::int32_t Location, float x, float y)
{
	glUniform2f(Location, x, y);
}

void ProgramT::setUniform(std::int32_t Location, float Value)
{
	glUniform1f(Location, Value);
}

void ProgramT::setUniform(std::int32_t Location, int Value)
{
	glUniform1i(Location, Value);
}

void ProgramT::setUniform(std::int32_t Location, float X, float Y, float Z, float W)
{
	glUniform4f(Location, X, Y, Z, W);
}

std::int32_t ProgramT::getLocation(char const * String) const
{
	return glGetUniformLocation(mId, String);
}

}
}

