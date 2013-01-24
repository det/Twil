#pragma once

#include <png.h>
#include <string>
#include <GL3/gl3.h>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	GLuint mId;

	public:
	void Load(char const *);

	void Bind() const;
};

}
}
