#pragma once

#include "Context.hpp"

#include <string>

namespace Twil {
namespace Gl {

class ProgramT;

/// \brief Container for an OpenGL Shader.
class ShaderT
{
	ShaderT(ShaderT const &) = delete;
	ShaderT & operator =(ShaderT const &) = delete;

private:
	std::uint32_t mId;

public:
	/// \param Type The Shader type, as defined by glCreateShader().
	ShaderT(std::uint32_t Type);
	~ShaderT() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator std::uint32_t() const;

	/// \brief Uploads shader source to OpenGL
	///
	/// \param Path The file path to read from.
	void loadFile(char const * Path);

	/// \brief Compiles the currently loaded source.
	///
	/// \throws std::runtime_error on error.
	void compile();
};

}
}
