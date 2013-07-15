#pragma once

#include "Data/Memory.hpp"

#include <string>

namespace Twil {
namespace Loader {

class PngT
{
	private:
	std::unique_ptr<unsigned char[]> mBytes;
	std::uint16_t mWidth;
	std::uint16_t mHeight;

	public:
	PngT(char const *);

	std::uint16_t getWidth() const;
	std::uint16_t getHeight() const;
	unsigned char const * begin() const;
	unsigned char const * end() const;
};

}
}
