#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

class Texture {
	private:
	public:
	GLuint mId;

	public:
	Texture();
	~Texture();

	operator GLuint() const;
};

}
}
