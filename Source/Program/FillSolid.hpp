#pragma once

#include "Gl/Program.hpp"

#include <GL3/gl3.h>

namespace Twil {
namespace Program {

#undef FillSolid

class FillSolid
{
	private:
	Gl::Program mProgram;
	GLint mModelViewLoc;

	public:
	FillSolid();

	operator GLuint() const;
	void setModelView(Math::Matrix3 const &);
};

}
}
