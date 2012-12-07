#pragma once

#include "Gl/Program.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Program {

class OutlineGradient {
	private:
	Gl::Program mProgram;
	GLint mModelViewLoc;

	public:	
	OutlineGradient();

	operator GLuint() const;
	void setModelView(Math::Matrix3 const &);
};

}
}
