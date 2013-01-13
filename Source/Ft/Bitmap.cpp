#include "Ft/Bitmap.hpp"

#include "Ft/Library.hpp"
#include "Ft/Outline.hpp"
#include "Ft/Face.hpp"

#include FT_SIZES_H
#include <algorithm>
#include <iostream>

namespace {

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
	FT_Raster_Params Params{}; // zero-initialize
	Params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	Params.gray_spans = renderSpans;
	Params.user = &Bitmap;
	FT_Outline_Render(Library, &Outline, &Params);
}

}

namespace Twil {
namespace Ft {

Bitmap::Bitmap(Ft::Library & Library) :
	mLibrary(Library), // Gcc bug prevents brace initialization syntax here
	mId{}, // Zero initialize
	mCapacity{0}
{
	mId.pixel_mode = FT_PIXEL_MODE_GRAY;
	mId.num_grays = 256;;
}

void Bitmap::resize(unsigned short Width, unsigned short Height)
{
	mId.width = Width;
	mId.rows = Height;
	mId.pitch = Width;
	auto Size = std::max(Width, Height);
	if (mCapacity < Size) {
		if (mCapacity == 0) mCapacity = 1;
		while (mCapacity < Size) mCapacity *= 2;
		delete[] mId.buffer;
		mId.buffer = new unsigned char[mCapacity * mCapacity];
	}
	std::fill(mId.buffer, mId.buffer + Width * Height, 0);
}

void Bitmap::render(Ft::Outline & Outline)
{
	renderOutline(mLibrary.mId, Outline.mId, mId);
}

void Bitmap::render(Ft::Face & Face)
{
	renderOutline(mLibrary.mId, Face.mId->glyph->outline, mId);
}

Bitmap::~Bitmap()
{
	delete[] mId.buffer;
}

int Bitmap::getWidth()
{
	return mId.width;
}

int Bitmap::getRows()
{
	return mId.rows;
}

std::size_t Bitmap::size()
{
	return std::size_t(mId.pitch * mId.rows);
}

unsigned char const * Bitmap::data()
{
	return mId.buffer;
}

unsigned char const * Bitmap::begin()
{
	return mId.buffer;
}

unsigned char const * Bitmap::end()
{
	return mId.buffer + size();
}

SubBitmapIterator::SubBitmapIterator() :
	mPointer{nullptr},
	mRowAdvance{0},
	mWidth{0},
	mRowCount{0}
{}

std::pair<Ft::SubBitmapIterator, Ft::SubBitmapIterator> Bitmap::getSubRange(unsigned short x, unsigned short y, unsigned short width, unsigned short height)
{
	SubBitmapIterator Begin;
	SubBitmapIterator End;

	Begin.mPointer = mId.buffer + x + mId.pitch * y;
	Begin.mRowAdvance = mId.pitch - width + 1;
	Begin.mWidth = width - 1;
	Begin.mRowCount = width - 1;

	End.mPointer = Begin.mPointer + mId.pitch * height;
	return {Begin, End};
}

Ft::SubBitmapIterator & SubBitmapIterator::operator++()
{
	if (mRowCount == 0) {
		mPointer += mRowAdvance;
		mRowCount = mWidth;
	}
	else {
		--mRowCount;
		++mPointer;
	}
	return *this;
}

bool SubBitmapIterator::operator==(Ft::SubBitmapIterator const & other)
{
	return mPointer == other.mPointer;
}

bool SubBitmapIterator::operator!=(Ft::SubBitmapIterator const & other)
{
	return mPointer != other.mPointer;
}

unsigned char SubBitmapIterator::operator*()
{
	return *mPointer;
}

}
}
