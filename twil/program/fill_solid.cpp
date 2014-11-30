#include "fill_solid.hpp"

#include "gl/context.hpp"
#include "gl/shader.hpp"

namespace twil {
namespace program {

FillSolid::FillSolid()
{
	gl::Shader vertex(GL_VERTEX_SHADER);
	vertex.LoadFile("shader/fill_solid.vert");
	vertex.Compile();

	gl::Shader geometry(GL_GEOMETRY_SHADER);
	geometry.LoadFile("shader/fill_solid.geom");
	geometry.Compile();

	gl::Shader frag(GL_FRAGMENT_SHADER);
	frag.LoadFile("shader/fill_solid.frag");
	frag.Compile();

	glAttachShader(program_, vertex);
	glAttachShader(program_, geometry);
	glAttachShader(program_, frag);

	program_.Link();

	glUseProgram(program_);

	scaling_loc_ = program_.GetLocation("scaling");
}

FillSolid::operator std::uint32_t() const
{
	return program_;
}

void FillSolid::SetScaling(float x, float y)
{
	program_.SetUniform(scaling_loc_, x, y);
}

}
}
