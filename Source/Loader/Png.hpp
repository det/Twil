#pragma once

#include "Gl/Context.hpp"

#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	GLubyte * mBytes;
	unsigned short mWidth;
	unsigned short mHeight;

	public:
	PngT(char const *);
	~PngT();

	unsigned short getWidth();
	unsigned short getHeight();
	GLubyte * begin();
	GLubyte * end();
};

}
}
