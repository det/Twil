#include "outline_gradient.hpp"

#include "gl/context.hpp"
#include "gl/shader.hpp"

namespace twil {
namespace program {

OutlineGradient::OutlineGradient()
{
	gl::Shader vertex(GL_VERTEX_SHADER);
	vertex.LoadFile("shader/outline_gradient.vert");
	vertex.Compile();

	gl::Shader geometry(GL_GEOMETRY_SHADER);
	geometry.LoadFile("shader/outline_gradient.geom");
	geometry.Compile();

	gl::Shader frag(GL_FRAGMENT_SHADER);
	frag.LoadFile("shader/outline_gradient.frag");
	frag.Compile();

	glAttachShader(program_, vertex);
	glAttachShader(program_, geometry);
	glAttachShader(program_, frag);

	program_.Link();
	glUseProgram(program_);

	scaling_loc_ = program_.GetLocation("scaling");
}

OutlineGradient::operator std::uint32_t() const
{
	return program_;
}

void OutlineGradient::SetScaling(float x, float y)
{
	program_.SetUniform(scaling_loc_, x, y);
}

}
}
