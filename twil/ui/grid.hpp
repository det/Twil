#pragma once

#include "grid.hxx"

#include "partition_box.hpp"

namespace twil {
namespace ui {

template<std::size_t width, std::size_t height, typename T>
class GridBase
{
private:
	using Rows = PartitionBox<true, std::array<T, width>>;
	using Columns = PartitionBox<false, std::array<Rows, height>>;

	Columns columns_;

protected:
	Columns & GetWidget()
	{
		return columns_;
	}

	Columns const & GetWidget() const
	{
		return columns_;
	}

	void Init(Container & parent, WindowBase & window)
	{
		columns_.Init(parent, window);
	}

public:
	template<std::size_t x, std::size_t y>
	T & GetChild()
	{
		return columns_.template GetChild<x>().template GetChild<y>();
	}

	template<std::size_t x, std::size_t y>
	T const & GetChild() const
	{
		return columns_.template GetChild<x>().template GetChild<y>();
	}
};

}
}
