#pragma once

#include "Attribute/Color4b.hpp"

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

signed short const Roundness = 4;
signed short const LeftMargin = 3;
signed short const RightMargin = 3;
signed short const TopMargin = 3;
signed short const BottomMargin = 3;
signed short const BaseWidthMargin = 12;
signed short const BaseHeightMargin = 12;

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
