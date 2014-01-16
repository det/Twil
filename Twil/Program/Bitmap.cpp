#include "Bitmap.hpp"

#include "Gl/Context.hpp"
#include "Gl/Shader.hpp"

namespace Twil {
namespace Program {

BitmapT::BitmapT()
{
	Gl::ShaderT Vertex(GL_VERTEX_SHADER);
	Vertex.loadFile("../Twil/Shader/Bitmap.vert");
	Vertex.compile();

	Gl::ShaderT Geometry(GL_GEOMETRY_SHADER);
	Geometry.loadFile("../Twil/Shader/Bitmap.geom");
	Geometry.compile();

	Gl::ShaderT Frag(GL_FRAGMENT_SHADER);
	Frag.loadFile("../Twil/Shader/Bitmap.frag");
	Frag.compile();

	glAttachShader(mProgram, Vertex);
	glAttachShader(mProgram, Geometry);
	glAttachShader(mProgram, Frag);

	mProgram.link();

	glUseProgram(mProgram);

	mScalingLoc = mProgram.getLocation("Scaling");
}

BitmapT::operator std::uint32_t() const
{
	return mProgram;
}

void BitmapT::setScaling(float X, float Y)
{
	mProgram.setUniform(mScalingLoc, X, Y);
}

}
}
