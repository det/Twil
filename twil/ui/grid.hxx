#pragma once

#include <cstdlib>

#include "widget.hpp"

namespace twil {
namespace ui {

template<std::size_t Width, std::size_t Height, typename T>
class GridBase;

template<std::size_t width, std::size_t height, typename T>
using Grid = WidgetAdaptor<GridBase<width, height, T>>;

}
}
