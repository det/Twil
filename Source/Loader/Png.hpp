#pragma once

#include "Data/Memory.hpp"

#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	std::unique_ptr<unsigned char[]> mBytes;
	unsigned short mWidth;
	unsigned short mHeight;

	public:
	PngT(char const *);

	unsigned short getWidth() const;
	unsigned short getHeight() const;
	unsigned char const * begin() const;
	unsigned char const * end() const;
};

}
}
