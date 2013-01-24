#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_SIZES_H

namespace Twil {
namespace Ft {

class FaceT;

/// \brief A FreeType font face size.
class SizeT
{
	friend class FaceT;

	private:
	FT_Size mId;

	// Non copyable
	SizeT(SizeT &) = delete;
	SizeT & operator=(SizeT &) = delete;

	public:
	/// \brief Load a size for a font face
	/// \param Face The font face to load the size from.
	/// \param Size The size to load in 26.6 fixpoint.
	/// \throws std::runtime_error If the size cant be loaded for the font face.
	SizeT(FaceT & Face, FT_F26Dot6 SizeT);
	~SizeT();

	/// \returns The height in 26.6 fixpoint.
	FT_Short getHeight() const;

	/// \returns The descender in 26.6 fixpoint.
	FT_Short getDescender() const;

	/// \returns The ascender in 26.6 fixpoint.
	FT_Short getAscender() const;
};

}
}
