#pragma once

#include "Data/UniqueArray.hpp"
#include "Gl/Context.hpp"

#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	Data::UniqueArrayT<GLubyte> mBytes;
	unsigned short mWidth;
	unsigned short mHeight;

	public:
	PngT(char const *);

	unsigned short getWidth();
	unsigned short getHeight();
	GLubyte * begin();
	GLubyte * end();
};

}
}
