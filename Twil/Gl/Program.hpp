#pragma once

#include "Context.hpp"

#include <string>

namespace Twil {
namespace Gl {

class ShaderT;

/// \brief Container for an OpenGL Program.
class ProgramT
{
	ProgramT(ProgramT const &) = delete;
	ProgramT & operator =(ProgramT const &) = delete;

	private:
	GLuint mId;

	public:
	ProgramT();
	~ProgramT();

	/// \brief Implicit conversion operator so it can be used in gl* functions.
	operator GLuint() const;

	/// \brief Attach a shader.
	void attach(ShaderT const & Shader);

	/// \brief Link the program.
	///
	/// \throws std::runtime_error on error.
	void link();

	/// \brief Sets a uniform int.
	static void setUniform(GLint Location, int X);

	/// \brief Sets a uniform float.
	static void setUniform(GLint Location, float X);

	/// \brief Sets a uniform vec2.
	static void setUniform(GLint Location, float X, float Y);

	/// \brief Sets a uniform vec4.
	static void setUniform(GLint Location, float X, float Y, float Z, float W);

	/// \returns The Location of a uniform.
	GLint getLocation(char const * String) const;
};

}
}
