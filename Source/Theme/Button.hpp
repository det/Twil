#pragma once

#include "Vertex/OutlineGradient.hpp"

#include <vector>

namespace Twil {
namespace Theme {

class Manager;

class Button
{
	private:
	Theme::Manager & mManager;
	std::vector<Vertex::OutlineGradient> mVertices;
	signed short mX = 0;
	signed short mY = 0;
	unsigned short mWidth = 0;
	unsigned short mHeight = 0;
	bool mIsDown = false;

	public:
	Button(Theme::Manager &);
	void setIsDown(bool);
	void resize(unsigned short, unsigned short);
	void move(signed short, signed short);
	void render();

	short getChildX();
	short getChildY();
	unsigned short getChildWidth();
	unsigned short getChildHeight();
	unsigned short getFitWidth(unsigned short);
	unsigned short getFitHeight(unsigned short);
};

}
}
