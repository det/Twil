#pragma once

namespace Twil {
namespace Ui {

template<bool, bool>
class DrawableContainer;

template<>
class DrawableContainer<true, true>
{
	public:
	virtual ~DrawableContainer() {}
};


template<>
class DrawableContainer<false, false>
{
	public:
	virtual ~DrawableContainer() {}
	virtual void handleChildWidthChanged() = 0;
	virtual void handleChildHeightChanged() = 0;
};


}
}
