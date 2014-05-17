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
	std::int32_t mLeft = 0;
	std::int32_t mRight = 0;
	std::int32_t mBottom = 0;
	std::int32_t mTop = 0;
	std::int32_t mClipLeft = 0;
	std::int32_t mClipRight = 0;
	std::int32_t mClipBottom = 0;
	std::int32_t mClipTop = 0;

public:
	std::int32_t getLayoutLeft(std::int32_t Width) const;
	std::int32_t getLayoutBottom(std::int32_t Height) const;

	std::int32_t getLayoutClipLeft() const;
	std::int32_t getLayoutClipRight() const;
	std::int32_t getLayoutClipBottom() const;
	std::int32_t getLayoutClipTop() const;

	void moveX(std::int32_t X);
	void moveY(std::int32_t Y);

	void resizeWidth(std::int32_t X);
	void resizeHeight(std::int32_t Y);

	void setClipLeft(std::int32_t X);
	void setClipRight(std::int32_t X);
	void setClipBottom(std::int32_t Y);
	void setClipTop(std::int32_t Y);

	std::int32_t getLeft() const;
	std::int32_t getRight() const;
	std::int32_t getBottom() const;
	std::int32_t getTop() const;

	std::int32_t getClipLeft() const;
	std::int32_t getClipRight() const;
	std::int32_t getClipBottom() const;
	std::int32_t getClipTop() const;
};

}
}
