#pragma once

#include "SettingsFwd.hpp"

#include "Attribute/Color4b.hpp"
#include "Ui/Unit.hpp"

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

Ui::DipT const BorderWidth = 1_dip;
Ui::DipT const Roundness = 4_dip;
Ui::DipT const LeftMargin = 3_dip;
Ui::DipT const RightMargin = 3_dip;
Ui::DipT const TopMargin = 3_dip;
Ui::DipT const BottomMargin = 3_dip;
Ui::DipT const BaseWidthMargin = 12_dip;
Ui::DipT const BaseHeightMargin = 12_dip;

}

namespace Label {

char const * const Font{"../Twil/Font/DejaVuSans-Bold.ttf"};
Ui::DipT const Size = 17_dip;

}

namespace Window {

Attribute::Color4bT const BackgroundColor{223, 223, 223, 255};

}

}
}
}
