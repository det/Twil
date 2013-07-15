#pragma once

#include "Attribute/Color4b.hpp"

#include <cstdint>
#include <cstdlib>

namespace Twil {
namespace Theme {
namespace Settings {

namespace Manager {

std::size_t const NumBuffers = 3;

}

namespace Button {

Attribute::Color4bT const BorderColor{127, 127, 127, 255};
Attribute::Color4bT const TopDownColor{191, 191, 191, 255};
Attribute::Color4bT const BottomDownColor{111, 111, 111, 255};
Attribute::Color4bT const TopUpColor{255, 255, 255, 255};
Attribute::Color4bT const BottomUpColor{159, 159, 159, 255};

std::int16_t const Roundness = 4;
std::int16_t const LeftMargin = 3;
std::int16_t const RightMargin = 3;
std::int16_t const TopMargin = 3;
std::int16_t const BottomMargin = 3;
std::int16_t const BaseWidthMargin = 12;
std::int16_t const BaseHeightMargin = 12;

}

namespace Label {

char const * const Font{"Font/DejaVuSans-Bold.ttf"};
unsigned const Size = 880;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{230, 229, 228, 255};

}

}
}
}
