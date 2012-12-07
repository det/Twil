#pragma once

#include "Gl/Context.hpp"
#include "Gl/Texture.hpp"

namespace Twil {
namespace Gl {

template<GLenum Target, GLenum Unit>
class TextureBind {
	public:
	TextureBind(Gl::Texture &);
	~TextureBind();
};

template<GLenum Target, GLenum Unit>
TextureBind<Target, Unit>::TextureBind(Gl::Texture & Texture)
{
	glActiveTexture(Unit);
	glBindTexture(Target, Texture);
}

template<GLenum Target, GLenum Unit>
TextureBind<Target, Unit>::~TextureBind()
{
	glActiveTexture(Unit);
	glBindTexture(Target, 0);
}

}
}
