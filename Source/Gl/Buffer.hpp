#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

class Buffer {
	private:
	GLuint mId;

	public:
	Buffer();
	~Buffer();

	operator GLuint() const;
};

}
}
