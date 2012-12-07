#include "Program/OutlineGradient.hpp"

#include "Gl/Context.hpp"
#include "Math/Vector4.hpp"
#include "Gl/Shader.hpp"

namespace Twil {
namespace Program {

OutlineGradient::OutlineGradient()
{
	Gl::Shader Vertex(GL_VERTEX_SHADER);
	Vertex.loadFile("Shader/OutlineGradient.vert");
	Vertex.compile();

	Gl::Shader Geometry(GL_GEOMETRY_SHADER);
	Geometry.loadFile("Shader/OutlineGradient.geom");
	Geometry.compile();

	Gl::Shader Frag(GL_FRAGMENT_SHADER);
	Frag.loadFile("Shader/OutlineGradient.frag");
	Frag.compile();

	glAttachShader(mProgram, Vertex);
	glAttachShader(mProgram, Geometry);
	glAttachShader(mProgram, Frag);

	mProgram.link();
	glUseProgram(mProgram);

	mModelViewLoc = mProgram.getLocation("ModelView");
}

OutlineGradient::operator GLuint() const
{
	return mProgram;
}

void OutlineGradient::setModelView(Math::Matrix3 const & ModelView)
{
	mProgram.setUniform(mModelViewLoc, false, ModelView);
}

}
}
