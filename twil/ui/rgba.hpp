#pragma once

#include "rgba.hxx"

#include "attribute/color4h.hpp"

namespace twil {
namespace ui {

struct Rgba
:
	attribute::Color4H
{
	constexpr
	Rgba(float red_, float green_, float blue_, float alpha_)
	:
	attribute::Color4H{
		static_cast<GLushort>(red_ * 8192.0f + 4096.0f),
		static_cast<GLushort>(green_ * 8192.0f + 4096.0f),
		static_cast<GLushort>(blue_ * 8192.0f + 4096.0f),
		static_cast<GLushort>(alpha_ * 65535.0f)}
	{}
};

}
}
