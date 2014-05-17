#pragma once

#include "CenteredFwd.hpp"
#include "DipFwd.hpp"

#include <cstdint>

namespace Twil {
namespace Ui {

/// \brief Provides a layout that centers things.
///
/// To be used as a template parameter to fixed size widgets.
class CenteredT
{
private:
	DipT mLeft = 0;
	DipT mRight = 0;
	DipT mBottom = 0;
	DipT mTop = 0;
	DipT mClipLeft = 0;
	DipT mClipRight = 0;
	DipT mClipBottom = 0;
	DipT mClipTop = 0;

public:
	DipT getLayoutLeft(DipT Width) const;
	DipT getLayoutBottom(DipT Height) const;

	DipT getLayoutClipLeft() const;
	DipT getLayoutClipRight() const;
	DipT getLayoutClipBottom() const;
	DipT getLayoutClipTop() const;

	void moveX(DipT X);
	void moveY(DipT Y);

	void resizeWidth(DipT X);
	void resizeHeight(DipT Y);

	void setClipLeft(DipT X);
	void setClipRight(DipT X);
	void setClipBottom(DipT Y);
	void setClipTop(DipT Y);

	DipT getLeft() const;
	DipT getRight() const;
	DipT getBottom() const;
	DipT getTop() const;

	DipT getClipLeft() const;
	DipT getClipRight() const;
	DipT getClipBottom() const;
	DipT getClipTop() const;
};

}
}
