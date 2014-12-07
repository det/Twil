#pragma once

#include "png.hxx"

#include <cstdint>
#include <memory>

namespace twil {
namespace loader {

class Png
{
private:
	std::unique_ptr<std::uint16_t[]> bytes_;
	std::uint16_t width_;
	std::uint16_t height_;

public:
	Png(char const *);

	std::uint16_t GetWidth() const;
	std::uint16_t GetHeight() const;
	std::uint16_t const * begin() const;
	std::uint16_t const * end() const;
};

}
}
