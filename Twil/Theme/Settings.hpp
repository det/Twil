#pragma once

#include "Attribute/Color4b.hpp"

#include <cstdint>
#include <cstdlib>

namespace Twil {
namespace Theme {

namespace Settings {

namespace Global {

float const HorizontalScale = 1.0f;
float const VerticalScale = 1.0f;

}

namespace Manager {

std::size_t const NumBuffers = 4;

}

namespace Button {

Attribute::Color4bT const BorderColor{127, 127, 127, 255};
Attribute::Color4bT const TopDownColor{191, 191, 191, 255};
Attribute::Color4bT const BottomDownColor{111, 111, 111, 255};
Attribute::Color4bT const TopUpColor{255, 255, 255, 255};
Attribute::Color4bT const BottomUpColor{159, 159, 159, 255};

float const BorderWidth = 1.0f;
float const Roundness = 4.0f;
float const LeftMargin = 3.0f;
float const RightMargin = 3.0f;
float const TopMargin = 3.0f;
float const BottomMargin = 3.0f;
float const BaseWidthMargin = 12.0f;
float const BaseHeightMargin = 12.0f;

}

namespace Label {

char const * const Font{"../Twil/Font/DejaVuSans-Bold.ttf"};
std::int32_t const Size = 13 * 64;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{223, 223, 223, 255};

}

}
}
}
