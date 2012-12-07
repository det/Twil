#include "Program/FillSolid.hpp"

#include "Gl/Context.hpp"
#include "Gl/Shader.hpp"
#include "Math/Vector4.hpp"
#include "Vertex/FillSolid.hpp"

namespace Twil {
namespace Program {

FillSolid::FillSolid()
{
	Gl::Shader Vertex(GL_VERTEX_SHADER);
	Vertex.loadFile("Shader/FillSolid.vert");
	Vertex.compile();

	Gl::Shader Geometry(GL_GEOMETRY_SHADER);
	Geometry.loadFile("Shader/FillSolid.geom");
	Geometry.compile();

	Gl::Shader Frag(GL_FRAGMENT_SHADER);
	Frag.loadFile("Shader/FillSolid.frag");
	Frag.compile();

	glAttachShader(mProgram, Vertex);
	glAttachShader(mProgram, Geometry);
	glAttachShader(mProgram, Frag);

	mProgram.link();

	glUseProgram(mProgram);

	mModelViewLoc = mProgram.getLocation("ModelView");
}

FillSolid::operator GLuint() const
{
	return mProgram;
}

void FillSolid::setModelView(Math::Matrix3 const & ModelView)
{
	mProgram.setUniform(mModelViewLoc, false, ModelView);
}

}
}
