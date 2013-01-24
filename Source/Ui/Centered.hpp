#pragma once

namespace Twil {
namespace Ui {

/// \brief Provides a layout that centers things.
///
/// To be used as a template parameter to fixed size widgets.
class CenteredT
{
	private:
	signed short mLeft = 0;
	signed short mRight = 0;
	signed short mBottom = 0;
	signed short mTop = 0;
	signed short mClipLeft = 0;
	signed short mClipRight = 0;
	signed short mClipBottom = 0;
	signed short mClipTop = 0;

	public:
	signed short getLayoutLeft(signed short Width) const;
	signed short getLayoutBottom(signed short Height) const;

	signed short getLayoutClipLeft() const;
	signed short getLayoutClipRight() const;

	signed short getLayoutClipBottom() const;
	signed short getLayoutClipTop() const;

	void moveX(signed short X);
	void moveY(signed short Y);

	void resizeWidth(signed short X);
	void resizeHeight(signed short Y);

	void setClipLeft(signed short X);
	void setClipRight(signed short X);
	void setClipBottom(signed short Y);
	void setClipTop(signed short Y);

	signed short getLeft() const;
	signed short getRight() const;
	signed short getBottom() const;
	signed short getTop() const;
};

}
}
