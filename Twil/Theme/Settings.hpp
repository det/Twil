#pragma once

#include "SettingsFwd.hpp"

#include "Attribute/Color4b.hpp"
#include "Ui/Dip.hpp"

#include <cstdint>
#include <cstdlib>

namespace Twil {
namespace Theme {

namespace Settings {

using namespace Ui::Operator;

namespace Manager {

std::size_t const NumBuffers = 4;

}

namespace Button {

Attribute::Color4bT const BorderColor{95, 95, 95, 255};
Attribute::Color4bT const TopDownColor{191, 191, 191, 255};
Attribute::Color4bT const BottomDownColor{111, 111, 111, 255};
Attribute::Color4bT const TopUpColor{255, 255, 255, 255};
Attribute::Color4bT const BottomUpColor{159, 159, 159, 255};

Ui::DipT const BorderWidth = 1_dips;
Ui::DipT const Roundness = 4_dips;
Ui::DipT const LeftMargin = 3_dips;
Ui::DipT const RightMargin = 3_dips;
Ui::DipT const TopMargin = 3_dips;
Ui::DipT const BottomMargin = 3_dips;
Ui::DipT const BaseWidthMargin = 12_dips;
Ui::DipT const BaseHeightMargin = 12_dips;

}

namespace Label {

char const * const Font{"../Twil/Font/DejaVuSans-Bold.ttf"};
Ui::DipT const Size = 17_dips;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{223, 223, 223, 255};

}

}
}
}
