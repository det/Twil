#pragma once

#include <string>
#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

class Program;

class Shader
{
	friend class Gl::Program;

	private:
	GLuint mId;

	public:	
	Shader(GLenum);
	~Shader();

	operator GLuint();

	void loadFile(std::string const &);
	void compile();
};

}
}
