#pragma once

#include "Data/Memory.hpp"
#include "Gl/Context.hpp"

#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	std::unique_ptr<GLubyte[]> mBytes;
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
