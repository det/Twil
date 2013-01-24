#pragma once

#include "Attribute/Color4b.hpp"

namespace Twil {
namespace Theme {
namespace Settings {

namespace Button {

Attribute::Color4bT const BorderColor{127, 127, 127, 255};
Attribute::Color4bT const TopDownColor{191, 191, 191, 255};
Attribute::Color4bT const BottomDownColor{111, 111, 111, 255};
Attribute::Color4bT const TopUpColor{255, 255, 255, 255};
Attribute::Color4bT const BottomUpColor{159, 159, 159, 255};

signed short const Roundness = 4;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{230, 229, 228, 255};

}

}
}
}
