#pragma once

#include <cstdint>

namespace Twil {
namespace Ui {

/// \brief Provides a layout that centers things.
///
/// To be used as a template parameter to fixed size widgets.
class CenteredT
{
	private:
	std::int16_t mLeft = 0;
	std::int16_t mRight = 0;
	std::int16_t mBottom = 0;
	std::int16_t mTop = 0;
	std::int16_t mClipLeft = 0;
	std::int16_t mClipRight = 0;
	std::int16_t mClipBottom = 0;
	std::int16_t mClipTop = 0;

	public:
	std::int16_t getLayoutLeft(std::int16_t Width) const;
	std::int16_t getLayoutBottom(std::int16_t Height) const;

	std::int16_t getLayoutClipLeft() const;
	std::int16_t getLayoutClipRight() const;
	std::int16_t getLayoutClipBottom() const;
	std::int16_t getLayoutClipTop() const;

	void moveX(std::int16_t X);
	void moveY(std::int16_t Y);

	void resizeWidth(std::int16_t X);
	void resizeHeight(std::int16_t Y);

	void setClipLeft(std::int16_t X);
	void setClipRight(std::int16_t X);
	void setClipBottom(std::int16_t Y);
	void setClipTop(std::int16_t Y);

	std::int16_t getLeft() const;
	std::int16_t getRight() const;
	std::int16_t getBottom() const;
	std::int16_t getTop() const;

	std::int16_t getClipLeft() const;
	std::int16_t getClipRight() const;
	std::int16_t getClipBottom() const;
	std::int16_t getClipTop() const;
};

}
}
