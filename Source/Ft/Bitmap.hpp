#pragma once

#include <cstddef>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <iterator>
#include <utility>

namespace Twil {
namespace Ft {

class LibraryT;
class OutlineT;
class FaceT;

/// \brief An iterator that operates on a sub rectangle of a Twil::Ft::BitmapT.
class SubBitmapIteratorT : public std::iterator<std::input_iterator_tag, unsigned char>
{
	friend class BitmapT;

	private:
	unsigned char const * mPointer;
	std::size_t mPitch;
	std::size_t mWidth;
	std::size_t mRowCount;

	SubBitmapIteratorT(
		unsigned char const * Pointer, std::size_t Pitch,
		std::size_t Width, std::size_t RowCount
	);

	public:
	SubBitmapIteratorT & operator++();
	bool operator==(SubBitmapIteratorT const &);
	bool operator!=(SubBitmapIteratorT const &);
	unsigned char operator*() const;
};

/// \brief An 8 bit FreeType bitmap used as a target for rendering operations.
class BitmapT
{
	private:
	LibraryT * mLibrary;
	FT_Bitmap mId;
	std::size_t mCapacity;

	// Non copyable
	BitmapT(BitmapT &) = delete;
	BitmapT & operator=(BitmapT &) = delete;

	public:
	/// \brief Construct a 0 size bitmap.
	BitmapT(LibraryT & Library);

	~BitmapT();

	/// \returns The width in bytes;
	int getWidth() const;

	/// \returns The height in bytes;
	int getRows() const;

	/// \brief Resize to the specified size and initialize all bytes to 0.
	void resize(std::size_t Width, std::size_t Height);

	/// \brief Render an outline.
	///
	/// Behaviour is undefined if the outline is outside the bitmap.
	void render(OutlineT & Outline);

	/// \brief Render a face.
	///
	/// Behaviour is undefined if the face is outside the bitmap.
	void render(FaceT & Face);

	/// \returns The size of the bitmap in bytes.
	std::size_t size() const;

	/// \returns A pointer to the first byte of the bitmap, or nullptr if it is size 0.
	unsigned char const * data() const;

	/// \returns The begin iterator for the bytes of the bitmap.
	unsigned char const * begin() const;

	/// \returns The end iterator for the bytes of the bitmap.
	unsigned char const * end() const;

	/// \returns A pair of begin and end iterators for the bytes of a sub-rectangle of the bitmap.
	std::pair<SubBitmapIteratorT, SubBitmapIteratorT> getSubRange(
		std::size_t X, std::size_t Y,
		std::size_t Width, std::size_t Height
	);
};

}
}
