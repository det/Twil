#pragma once

#include "CenteredFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

/// \brief Provides a layout that centers things.
///
/// To be used as a template parameter to fixed size widgets.
class CenteredT
{
private:
	float mLeft = 0;
	float mRight = 0;
	float mBottom = 0;
	float mTop = 0;
	float mClipLeft = 0;
	float mClipRight = 0;
	float mClipBottom = 0;
	float mClipTop = 0;

public:
	float getLayoutLeft(float Width) const;
	float getLayoutBottom(float Height) const;

	float getLayoutClipLeft() const;
	float getLayoutClipRight() const;
	float getLayoutClipBottom() const;
	float getLayoutClipTop() const;

	void moveX(float X);
	void moveY(float Y);

	void resizeWidth(float X);
	void resizeHeight(float Y);

	void setClipLeft(float X);
	void setClipRight(float X);
	void setClipBottom(float Y);
	void setClipTop(float Y);

	float getLeft() const;
	float getRight() const;
	float getBottom() const;
	float getTop() const;

	float getClipLeft() const;
	float getClipRight() const;
	float getClipBottom() const;
	float getClipTop() const;
};

}
}
