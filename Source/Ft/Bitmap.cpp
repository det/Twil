#include "Bitmap.hpp"

#include "Library.hpp"
#include "Outline.hpp"
#include "Face.hpp"

#include FT_SIZES_H
#include <algorithm>

namespace {

// Render using bottom left origin, does no bounds checking
void renderSpans(int Y, int Count, FT_Span const * Spans, void * User)
{
	auto & Bitmap = *static_cast<FT_Bitmap *>(User);
	std::for_each(Spans, Spans + Count, [&](FT_Span const & Span) {
		auto First = Bitmap.buffer + Bitmap.pitch * Y + Span.x;
		std::fill(First, First + Span.len, Span.coverage);
	});
}

void renderOutline(FT_Library & Library, FT_Outline & Outline, FT_Bitmap & Bitmap)
{
	FT_Raster_Params Params{};
	Params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	Params.gray_spans = renderSpans;
	Params.user = &Bitmap;
	FT_Outline_Render(Library, &Outline, &Params);
}

}

namespace Twil {
namespace Ft {

// SubBitmapIterator

SubBitmapIteratorT::SubBitmapIteratorT(
	unsigned char const * Pointer, std::size_t Pitch,
	std::size_t Width, std::size_t RowCount
) :
	mPointer{Pointer},
	mPitch{Pitch},
	mWidth{Width},
	mRowCount{RowCount}
{}

SubBitmapIteratorT & SubBitmapIteratorT::operator++()
{
	if (mRowCount == 0) {
		mPointer += mPitch;
		mRowCount = mWidth;
	}
	else {
		--mRowCount;
		++mPointer;
	}
	return *this;
}

bool SubBitmapIteratorT::operator==(SubBitmapIteratorT const & other)
{
	return mPointer == other.mPointer;
}

bool SubBitmapIteratorT::operator!=(SubBitmapIteratorT const & other)
{
	return mPointer != other.mPointer;
}

unsigned char SubBitmapIteratorT::operator*() const
{
	return *mPointer;
}

// Bitmap

BitmapT::BitmapT(LibraryT & Library) :
	mLibrary{&Library},
	mId{},
	mCapacity{0}
{
	mId.pixel_mode = FT_PIXEL_MODE_GRAY;
	mId.num_grays = 256;
}

void BitmapT::resize(std::size_t Width, std::size_t Height)
{
	mId.width = Width;
	mId.rows = Height;
	mId.pitch = Width;

	auto Size = std::max(Width, Height);
	if (Size == 0) {
		delete[] mId.buffer;
		mId.buffer = nullptr;
		return;
	}

	if (mCapacity < Size) {
		if (mCapacity == 0) mCapacity = 1;
		while (mCapacity < Size) mCapacity *= 2;
		delete[] mId.buffer;
		mId.buffer = new unsigned char[mCapacity * mCapacity];
	}
	std::fill(mId.buffer, mId.buffer + Width * Height, 0);
}

void BitmapT::render(OutlineT & Outline)
{
	renderOutline(mLibrary->mId, Outline.mId, mId);
}

void BitmapT::render(FaceT & Face)
{
	renderOutline(mLibrary->mId, Face.mId->glyph->outline, mId);
}

BitmapT::~BitmapT()
{
	delete[] mId.buffer;
}

int BitmapT::getWidth() const
{
	return mId.width;
}

int BitmapT::getRows() const
{
	return mId.rows;
}

std::size_t BitmapT::size() const
{
	return std::size_t(mId.pitch * mId.rows);
}

unsigned char const * BitmapT::data() const
{
	return mId.buffer;
}

unsigned char const * BitmapT::begin() const
{
	return mId.buffer;
}

unsigned char const * BitmapT::end() const
{
	return mId.buffer + size();
}

std::pair<SubBitmapIteratorT, SubBitmapIteratorT> BitmapT::getSubRange(
	std::size_t X, std::size_t Y,
	std::size_t Width, std::size_t Height
)
{
	SubBitmapIteratorT Begin {
		mId.buffer + X + mId.pitch * Y,
		mId.pitch - Width + 1,
		Width - 1,
		Width - 1
	};

	SubBitmapIteratorT End {
		Begin.mPointer + mId.pitch * Height,
		0,
		0,
		0
	};

	return {Begin, End};
}

}
}
