#pragma once

#include "Vertex/OutlineGradient.hpp"

#include <vector>

namespace Twil {
namespace Theme {

class Manager;

class Button {
	private:
	Theme::Manager & mManager;
	std::vector<Vertex::OutlineGradient> mVertices;

	public:
	Button(Theme::Manager &);
	void update(unsigned short, unsigned short, bool);
	void render();
};

}
}
