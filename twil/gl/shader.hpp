#pragma once

#include "shader.hxx"

#include "context.hpp"
#include "program.hxx"

#include <string>

namespace twil {
namespace gl {

/// \brief Container for an OpenGL Shader.
class Shader
{
	Shader(Shader const &) = delete;
	Shader & operator =(Shader const &) = delete;

private:
	GLuint id_;

public:
	/// \param type The Shader type, as defined by glCreateShader().
	Shader(GLenum type);
	~Shader() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;

	/// \brief Uploads shader source to OpenGL
	///
	/// \param path The file path to read from.
	void LoadFile(char const * path);

	/// \brief Compiles the currently loaded source.
	///
	/// \throws std::runtime_error on error.
	void Compile();
};

}
}
