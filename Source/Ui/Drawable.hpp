#pragma once

namespace Twil {

namespace Math {
struct Vector2;
}

namespace Ui {

class Drawable {
	public:
	virtual ~Drawable() {};
	virtual void handleResized(unsigned short, unsigned short) = 0;
	virtual void draw() = 0;
};

}
}
