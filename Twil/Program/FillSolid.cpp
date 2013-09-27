#include "FillSolid.hpp"

#include "Gl/Context.hpp"
#include "Gl/Shader.hpp"

namespace Twil {
namespace Program {

FillSolidT::FillSolidT()
{
	Gl::ShaderT Vertex(GL_VERTEX_SHADER);
	Vertex.loadFile("../Twil/Shader/FillSolid.vert");
	Vertex.compile();

	Gl::ShaderT Geometry(GL_GEOMETRY_SHADER);
	Geometry.loadFile("../Twil/Shader/FillSolid.geom");
	Geometry.compile();

	Gl::ShaderT Frag(GL_FRAGMENT_SHADER);
	Frag.loadFile("../Twil/Shader/FillSolid.frag");
	Frag.compile();

	glAttachShader(mProgram, Vertex);
	glAttachShader(mProgram, Geometry);
	glAttachShader(mProgram, Frag);

	mProgram.link();

	glUseProgram(mProgram);

	mScalingLoc = mProgram.getLocation("Scaling");
}

FillSolidT::operator GLuint() const
{
	return mProgram;
}

void FillSolidT::setScaling(float X, float Y)
{
	mProgram.setUniform(mScalingLoc, X, Y);
}

}
}
