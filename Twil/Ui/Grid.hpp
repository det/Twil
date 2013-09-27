#pragma once

#include "PartitionBox.hpp"
#include "Widget.hpp"

namespace Twil {
namespace Ui {

template<std::size_t Width, std::size_t Height, typename T>
class GridBaseT
{
private:
	using RowsT = PartitionBoxT<true, std::array<T, Width>>;
	using ColumnsT = PartitionBoxT<false, std::array<RowsT, Height>>;

	ColumnsT mColumns;

protected:
	ColumnsT & getWidget()
	{
		return mColumns;
	}

	ColumnsT const & getWidget() const
	{
		return mColumns;
	}

	void init(ContainerT & Parent, WindowBaseT & Window)
	{
		mColumns.init(Parent, Window);
	}

public:
	template<std::size_t X, std::size_t Y>
	T & getChild()
	{
		return mColumns.template getChild<X>().template getChild<Y>();
	}

	template<std::size_t X, std::size_t Y>
	T const & getChild() const
	{
		return mColumns.template getChild<X>().template getChild<Y>();
	}
};

template<std::size_t Width, std::size_t Height, typename T>
using GridT = WidgetAdaptorT<GridBaseT<Width, Height, T>>;

}
}
