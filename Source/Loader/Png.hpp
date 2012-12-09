#pragma once

#include <png.h>
#include <string>
#include <GL3/gl3.h>

namespace Twil {
namespace Loader {

class Png
{
	private:
	GLuint mId;

	public:
	void Load(std::string const &);

	void Bind() const;
};

}
}
