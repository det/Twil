#pragma once

namespace twil {
namespace ui {

template<typename First, typename Second>
class SplitBoxBase;

template<typename First, typename Second>
class SplitBoxHorizontal;

template<typename First, typename Second>
class SplitBoxVertical;

template<bool is_horizontal, bool is_first_static, typename First, typename Second>
class SplitBox;

}
}
