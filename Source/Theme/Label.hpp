#pragma once

#include <string>
#include <vector>
#include "Vertex/FillSolid.hpp"

namespace Twil {
namespace Theme {

class Manager;

class Label
{
	private:
	Theme::Manager & mManager;
	std::vector<Vertex::FillSolid> mVertices;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	Label(Theme::Manager &);

	void setText(std::u32string const &);
	void move(signed short, signed short);
	void render();

	unsigned short getWidth();
	unsigned short getHeight();
};

}
}
