#pragma once

#include <GL3/gl3.h>

namespace Twil {
namespace Gl {

class VertexArray {
	private:
	GLuint mId;

	public:
	VertexArray();
	~VertexArray();

	operator GLuint() const;
};

}
}
