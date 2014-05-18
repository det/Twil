#pragma once

#include "ButtonFwd.hpp"

#include "Drawable.hpp"
#include "Ui/UnitFwd.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <cstdint>

namespace Twil {
namespace Theme {

/// \brief Responsible for drawing a button.
class ButtonT
:
	public DrawableT<Vertex::OutlineGradientT>
{
	ButtonT(ButtonT const &) = delete;
	ButtonT & operator =(ButtonT const &) = delete;

private:
	Ui::WindowBaseT * mWindow;
	Ui::DipT mLeft = 0;
	Ui::DipT mBottom = 0;
	Ui::DipT mRight = 0.0f;
	Ui::DipT mTop = 0.0f;
	Ui::DipT mClipLeft = 0.0f;
	Ui::DipT mClipBottom = 0.0f;
	Ui::DipT mClipRight = 0.0f;
	Ui::DipT mClipTop = 0.0f;
	bool mIsDown = false;

public:
	ButtonT() = default;
	void init(Ui::WindowBaseT &);

	/// \brief Sets whether the button is up or down.
	void setIsDown(bool IsDown);

	/// \returns The left margin for the theme.
	Ui::DipT getLeftMargin() const;

	/// \returns The right margin for the theme.
	Ui::DipT getRightMargin() const;

	/// \returns The bottom margin for the theme.
	Ui::DipT getBottomMargin() const;

	/// \returns The top margin for the theme.
	Ui::DipT getTopMargin() const;

	// Drawable
	void draw(Vertex::OutlineGradientT *) const final;

	// Widget
	void moveX(Ui::DipT);
	void moveY(Ui::DipT);

	void resizeWidth(Ui::DipT);
	void resizeHeight(Ui::DipT);

	void setClipLeft(Ui::DipT);
	void setClipBottom(Ui::DipT);
	void setClipRight(Ui::DipT);
	void setClipTop(Ui::DipT);

	Ui::DipT getLeft() const;
	Ui::DipT getBottom() const;
	Ui::DipT getRight() const;
	Ui::DipT getTop() const;

	Ui::DipT getClipLeft() const;
	Ui::DipT getClipRight() const;
	Ui::DipT getClipBottom() const;
	Ui::DipT getClipTop() const;

	Ui::DipT getBaseWidth(Ui::DipT) const;
	Ui::DipT getBaseHeight(Ui::DipT) const;
};

}
}
