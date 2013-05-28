#include "OutlineGradient.hpp"

#include "Gl/Context.hpp"
#include "Gl/Shader.hpp"

namespace Twil {
namespace Program {

OutlineGradientT::OutlineGradientT()
{
	Gl::ShaderT Vertex(GL_VERTEX_SHADER);
	Vertex.loadFile("Shader/OutlineGradient.vert");
	Vertex.compile();

	Gl::ShaderT Geometry(GL_GEOMETRY_SHADER);
	Geometry.loadFile("Shader/OutlineGradient.geom");
	Geometry.compile();

	Gl::ShaderT Frag(GL_FRAGMENT_SHADER);
	Frag.loadFile("Shader/OutlineGradient.frag");
	Frag.compile();

	glAttachShader(mProgram, Vertex);
	glAttachShader(mProgram, Geometry);
	glAttachShader(mProgram, Frag);

	mProgram.link();
	glUseProgram(mProgram);

	mScalingLoc = mProgram.getLocation("Scaling");
}

OutlineGradientT::operator GLuint() const
{
	return mProgram;
}

void OutlineGradientT::setScaling(float X, float Y)
{
	mProgram.setUniform(mScalingLoc, X, Y);
}

}
}
