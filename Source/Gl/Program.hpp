#pragma once

#include <string>
#include <GL3/gl3.h>

namespace Twil {

namespace Math {
struct Matrix3;
struct Matrix4;
struct Vector2;
struct Vector4;
}

namespace Gl {

class Shader;

class Program
{
	private:
	GLuint mId;

	public:
	Program();
	~Program();

	operator GLuint() const;

	void attach(Gl::Shader const &);
	void link();
	void bindAttribLocation(GLuint, std::string const &);
	void bindFragDataLocationIndexed(GLuint, GLuint, std::string const &);
	static void setUniform(GLint, GLboolean, Math::Matrix3 const &);
	static void setUniform(GLint, GLboolean, Math::Matrix4 const &);
	static void setUniform(GLint, float, float, float, float);
	static void setUniform(GLint, float, float);
	static void setUniform(GLint, float);
	static void setUniform(GLint, int);

	GLint getLocation(std::string const &) const;
};

}
}
