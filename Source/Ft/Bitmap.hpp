#pragma once

#include <cstddef>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include <iterator>
#include <utility>

namespace Twil {
namespace Ft {

class Library;
class Outline;
class Face;
class SubBitmapIterator;

class Bitmap
{
	private:
	Ft::Library & mLibrary;
	FT_Bitmap mId;
	std::size_t mCapacity;

	public:
	Bitmap(Ft::Library &);
	~Bitmap();

	int getWidth();
	int getRows();

	void resize(unsigned short width, unsigned short height);
	void render(Ft::Outline &);
	void render(Ft::Face &);

	std::size_t size();
	unsigned char const * data();
	unsigned char const * begin();
	unsigned char const * end();

	std::pair<SubBitmapIterator, SubBitmapIterator> getSubRange(unsigned short x, unsigned short y, unsigned short width, unsigned short height);
};

class SubBitmapIterator : public std::iterator<std::input_iterator_tag, unsigned char>
{
	friend class Ft::Bitmap;

	private:
	unsigned char const * mPointer;
	std::size_t mRowAdvance;
	std::size_t mWidth;
	std::size_t mRowCount;

	public:
	SubBitmapIterator();
	SubBitmapIterator & operator++();
	bool operator==(SubBitmapIterator const &);
	bool operator!=(SubBitmapIterator const &);
	unsigned char operator*();
};

}
}
