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

attribute::Color4B const border_color{95, 95, 95, 255};
attribute::Color4B const top_down_color{191, 191, 191, 255};
attribute::Color4B const bottom_down_color{111, 111, 111, 255};
attribute::Color4B const top_up_color{255, 255, 255, 255};
attribute::Color4B const bottom_up_color{159, 159, 159, 255};

ui::Dip const border_width = 1_dip;
ui::Dip const roundness = 4_dip;
ui::Dip const left_margin = 3_dip;
ui::Dip const right_margin = 3_dip;
ui::Dip const top_margin = 3_dip;
ui::Dip const bottom_margin = 3_dip;
ui::Dip const base_width_margin = 12_dip;
ui::Dip const base_height_margin = 12_dip;

}

namespace label {

char const * const font{"../twil/font/deja_vu_sans-bold.ttf"};
ui::Dip const size = 17_dip;

}

namespace window {

attribute::Color4B const background_color{223, 223, 223, 255};

}

}
}
}
