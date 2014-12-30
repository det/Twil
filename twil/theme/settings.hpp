#pragma once

#include "settings.hxx"

#include "ui/rgba.hpp"
#include "ui/unit.hpp"

#include <cstdint>
#include <cstdlib>

namespace twil {
namespace theme {

namespace settings {

using namespace ui::udl;

namespace manager {

constexpr std::size_t num_buffers = 4;

}

namespace button {

constexpr ui::Rgba border_color{0.37, 0.37, 0.37, 1.0};
constexpr ui::Rgba top_down_color{0.75, 0.75, 0.75, 1.0};
constexpr ui::Rgba bottom_down_color{0.44, 0.44, 0.44, 1.0};
constexpr ui::Rgba top_up_color{1.0, 1.0, 1.0, 1.0};
constexpr ui::Rgba bottom_up_color{0.62, 0.62, 0.62, 1.0};

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

constexpr ui::Rgba background_color{0.87, 0.87, 0.87, 1.0};

}

}
}
}
