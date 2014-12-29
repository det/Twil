#pragma once

#include "settings.hxx"

#include "attribute/color4b.hpp"
#include "ui/unit.hpp"

#include <cstdint>
#include <cstdlib>

namespace twil {
namespace theme {

namespace settings {

using namespace ui::udl;

namespace manager {

std::size_t const num_buffers = 4;

}

namespace button {

constexpr ui::Rgba border_color{0.37_color, 0.37_color, 0.37_color, 1.0_color};
constexpr ui::Rgba top_down_color{0.75_color, 0.75_color, 0.75_color, 1.0_color};
constexpr ui::Rgba bottom_down_color{0.44_color, 0.44_color, 0.44_color, 1.0_color};
constexpr ui::Rgba top_up_color{1.0_color, 1.0_color, 1.0_color, 1.0_color};
constexpr ui::Rgba bottom_up_color{0.62_color, 0.62_color, 0.62_color, 1.0_color};

constexpr ui::Dip border_width = 1_dip;
constexpr ui::Dip roundness = 4_dip;
constexpr ui::Dip left_margin = 3_dip;
constexpr ui::Dip right_margin = 3_dip;
constexpr ui::Dip top_margin = 3_dip;
constexpr ui::Dip bottom_margin = 3_dip;
constexpr ui::Dip base_width_margin = 12_dip;
constexpr ui::Dip base_height_margin = 12_dip;

}

namespace label {

constexpr char const * font{"../twil/font/deja_vu_sans-bold.ttf"};
constexpr ui::Dip size = 17_dip;

}

namespace window {

constexpr ui::Rgba background_color{0.87_color, 0.87_color, 0.87_color, 1.0_color};

}

}
}
}
