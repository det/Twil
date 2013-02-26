#pragma once

#include "Context.hpp"

#include <string>

namespace Twil {
namespace Gl {

class ProgramT;

/// \brief Container for an OpenGL Shader.
class ShaderT
{
	private:
	GLuint mId;

	// Non copyable
	ShaderT(ShaderT &) = delete;
	ShaderT & operator=(ShaderT &) = delete;

	public:
	/// \param Type The Shader type, as defined by glCreateShader().
	ShaderT(GLenum Type);
	~ShaderT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;

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
