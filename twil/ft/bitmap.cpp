#include "bitmap.hpp"

#include "library.hpp"
#include "outline.hpp"
#include "face.hpp"


#include <algorithm>

#include FT_SIZES_H

namespace {

// Render using bottom left origin, does no bounds checking
void RenderSpans(int y, int count, FT_Span const * spans, void * user)
{
	auto & bitmap = *static_cast<FT_Bitmap *>(user);
	std::for_each(spans, spans + count, [&](FT_Span const & Span)
	{
		auto first = bitmap.buffer + bitmap.pitch * y + Span.x;
		std::fill(first, first + Span.len, Span.coverage);
	});
}

void RenderOutline(FT_Library & library, FT_Outline & outline, FT_Bitmap & bitmap)
{
	FT_Raster_Params params{};
	params.flags = FT_RASTER_FLAG_AA | FT_RASTER_FLAG_DIRECT;
	params.gray_spans = RenderSpans;
	params.user = &bitmap;
	FT_Outline_Render(library, &outline, &params);
}

}

namespace twil {
namespace ft {

// SubBitmapIterator

SubBitmapIterator::SubBitmapIterator(
	std::uint8_t const * pointer,
	std::size_t pitch,
	std::size_t width,
	std::size_t row_count)
:
	pointer_{pointer},
	pitch_{pitch},
	width_{width},
	row_count_{row_count}
{}

SubBitmapIterator & SubBitmapIterator::operator++()
{
	if (row_count_ == 0)
	{
		pointer_ += pitch_;
		row_count_ = width_;
	}
	else
	{
		--row_count_;
		++pointer_;
	}
	return *this;
}

bool SubBitmapIterator::operator==(SubBitmapIterator const & other)
{
	return pointer_ == other.pointer_;
}

bool SubBitmapIterator::operator!=(SubBitmapIterator const & other)
{
	return pointer_ != other.pointer_;
}

std::uint8_t SubBitmapIterator::operator*() const
{
	return *pointer_;
}

// Bitmap

Bitmap::Bitmap(Library & library)
:
	library_{&library},
	id_{},
	capacity_{0}
{
	id_.pixel_mode = FT_PIXEL_MODE_GRAY;
	id_.num_grays = 256;
}

void Bitmap::Resize(std::size_t width, std::size_t height)
{
	id_.width = width;
	id_.rows = height;
	id_.pitch = width;

	auto size = std::max(width, height);

	if (size == 0)
	{
		delete[] id_.buffer;
		id_.buffer = nullptr;
		capacity_ = 0;
		return;
	}

	if (capacity_ < size)
	{
		if (capacity_ == 0) capacity_ = 1;
		while (capacity_ < size) capacity_ *= 2;
		delete[] id_.buffer;
		id_.buffer = new std::uint8_t[capacity_ * capacity_];
	}

	std::fill(id_.buffer, id_.buffer + width * height, 0);
}

void Bitmap::Render(Outline & outline)
{
	RenderOutline(library_->id_, outline.id_, id_);
}

void Bitmap::Render(Face & Face)
{
	RenderOutline(library_->id_, Face.id_->glyph->outline, id_);
}

Bitmap::~Bitmap() noexcept
{
	delete[] id_.buffer;
}

int Bitmap::GetWidth() const
{
	return id_.width;
}

int Bitmap::GetRows() const
{
	return id_.rows;
}

std::size_t Bitmap::size() const
{
	return id_.pitch * id_.rows;
}

std::uint8_t const * Bitmap::data() const
{
	return id_.buffer;
}

std::uint8_t const * Bitmap::begin() const
{
	return id_.buffer;
}

std::uint8_t const * Bitmap::end() const
{
	return id_.buffer + size();
}

Bitmap::Range Bitmap::GetSubRange(
	std::size_t x, std::size_t y,
	std::size_t width, std::size_t height)
{
	SubBitmapIterator first{
		id_.buffer + x + id_.pitch * y,
		id_.pitch - width + 1,
		width - 1,
		width - 1};

	SubBitmapIterator last{
		first.pointer_ + id_.pitch * height,
		0,
		0,
		0};

	return {first, last};
}

}
}
