#pragma once

#include "SizeFwd.hpp"

#include "FaceFwd.hpp"

#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H

namespace Twil {
namespace Ft {

/// \brief A FreeType font face size.
class SizeT
{
	friend class FaceT;

	SizeT(SizeT const &) = delete;
	SizeT & operator =(SizeT const &) = delete;

private:
	FT_Size mId;

public:
	/// \brief Load a size for a font face
	/// \param Face The font face to load the size from.
	/// \param Size The size to load in 26.6 fixpoint.
	/// \throws std::runtime_error If the size cant be loaded for the font face.
	SizeT(FaceT & Face, std::int16_t Width, std::int16_t Height);
	~SizeT() noexcept;

	/// \returns The height in 26.6 fixpoint.
	FT_Short getHeight() const;

	/// \returns The descender in 26.6 fixpoint.
	FT_Short getDescender() const;

	/// \returns The ascender in 26.6 fixpoint.
	FT_Short getAscender() const;
};

}
}
