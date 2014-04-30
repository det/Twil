#pragma once

#include "PngFwd.hpp"

#include "Data/Memory.hpp"

#include <cstdint>

namespace Twil {
namespace Loader {

class PngT
{
private:
	std::unique_ptr<std::uint8_t[]> mBytes;
	std::uint16_t mWidth;
	std::uint16_t mHeight;

public:
	PngT(char const *);

	std::uint16_t getWidth() const;
	std::uint16_t getHeight() const;
	std::uint8_t const * begin() const;
	std::uint8_t const * end() const;
};

}
}
