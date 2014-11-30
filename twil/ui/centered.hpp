#pragma once

#include "centered.hxx"

#include "unit.hxx"

#include <cstdint>

namespace twil {
namespace ui {

/// \brief Provides a layout that centers things.
///
/// To be used as a template parameter to fixed size widgets.
class Centered
{
private:
	Dip left_ = 0;
	Dip right_ = 0;
	Dip bottom_ = 0;
	Dip top_ = 0;
	Dip clip_left_ = 0;
	Dip clip_right_ = 0;
	Dip clip_bottom_ = 0;
	Dip clip_top_ = 0;

public:
	Dip GetLayoutLeft(Dip width) const;
	Dip GetLayoutBottom(Dip height) const;

	Dip GetLayoutClipLeft() const;
	Dip GetLayoutClipRight() const;
	Dip GetLayoutClipBottom() const;
	Dip GetLayoutClipTop() const;

	void MoveX(Dip x);
	void MoveY(Dip y);

	void ResizeWidth(Dip x);
	void ResizeHeight(Dip y);

	void SetClipLeft(Dip x);
	void SetClipRight(Dip x);
	void SetClipBottom(Dip y);
	void SetClipTop(Dip y);

	Dip GetLeft() const;
	Dip GetRight() const;
	Dip GetBottom() const;
	Dip GetTop() const;

	Dip GetClipLeft() const;
	Dip GetClipRight() const;
	Dip GetClipBottom() const;
	Dip GetClipTop() const;
};

}
}
