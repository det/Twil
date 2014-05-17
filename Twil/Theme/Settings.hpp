#pragma once

#include "SettingsFwd.hpp"

#include "Attribute/Color4b.hpp"
#include "Ui/Operator.hpp"

#include <cstdint>
#include <cstdlib>

namespace Twil {
namespace Theme {

namespace Settings {

using namespace Operator;

namespace Manager {

std::size_t const NumBuffers = 4;

}

namespace Button {

Attribute::Color4bT const BorderColor{95, 95, 95, 255};
Attribute::Color4bT const TopDownColor{191, 191, 191, 255};
Attribute::Color4bT const BottomDownColor{111, 111, 111, 255};
Attribute::Color4bT const TopUpColor{255, 255, 255, 255};
Attribute::Color4bT const BottomUpColor{159, 159, 159, 255};

std::int32_t const BorderWidth = 1_dips;
std::int32_t const Roundness = 4_dips;
std::int32_t const LeftMargin = 3_dips;
std::int32_t const RightMargin = 3_dips;
std::int32_t const TopMargin = 3_dips;
std::int32_t const BottomMargin = 3_dips;
std::int32_t const BaseWidthMargin = 12_dips;
std::int32_t const BaseHeightMargin = 12_dips;

}

namespace Label {

char const * const Font{"../Twil/Font/DejaVuSans-Bold.ttf"};
std::int32_t const Size = 17_dips;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{223, 223, 223, 255};

}

}
}
}
