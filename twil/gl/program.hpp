#pragma once

#include "program.hxx"

#include "context.hpp"
#include "shader.hxx"

#include <string>

namespace twil {
namespace gl {

/// \brief Container for an OpenGL Program.
class Program
{
	Program(Program const &) = delete;
	Program & operator =(Program const &) = delete;

private:
	GLuint id_;

public:
	Program();
	~Program() noexcept;

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;

	/// \brief Attach a shader.
	void Attach(Shader const & Shader);

	/// \brief Link the program.
	///
	/// \throws std::runtime_error on error.
	void Link();

	/// \brief Sets a uniform int.
	static void SetUniform(GLint location, int x);

	/// \brief Sets a uniform float.
	static void SetUniform(GLint location, float x);

	/// \brief Sets a uniform vec2.
	static void SetUniform(GLint location, float x, float y);

	/// \brief Sets a uniform vec4.
	static void SetUniform(GLint location, float x, float y, float z, float w);

	/// \returns The Location of a uniform.
	GLint GetLocation(char const * string) const;
};

}
}
