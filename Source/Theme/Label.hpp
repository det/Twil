#pragma once

#include <string>
#include <vector>
#include "Vertex/FillSolid.hpp"

namespace Twil {
namespace Theme {

class Manager;

class Label {
	private:
	Theme::Manager & mManager;
	std::vector<Vertex::FillSolid> mVertices;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;

	public:
	Label(Theme::Manager &);
	void setText(std::u32string const &);
	void render();

	unsigned short getWidth();
	unsigned short getHeight();
};

}
}
