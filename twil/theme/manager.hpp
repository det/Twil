#pragma once

#include "manager.hxx"

#include "button.hxx"
#include "label.hxx"
#include "image.hxx"
#include "settings.hpp"
#include "stream_array.hpp"
#include "texture_array.hpp"
#include "ft/bitmap.hpp"
#include "ft/face.hpp"
#include "ft/library.hpp"
#include "ft/outline.hpp"
#include "ft/stroker.hpp"
#include "ft/size.hpp"
#include "program/bitmap.hpp"
#include "program/fill_solid.hpp"
#include "program/outline_gradient.hpp"
#include "gl/context.hpp"
#include "ui/window_base.hxx"
#include "ui/unit.hxx"
#include "vertex/bitmap.hpp"
#include "vertex/fill_solid.hpp"
#include "vertex/outline_gradient.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace twil {
namespace theme {

/// \brief Represents a loaded unicode glyph.
struct GlyphEntry
{
	FT_Vector bearings;
	FT_Vector advance;
	FT_UInt index;
	FT_Pos lsb_delta;
	FT_Pos rsb_delta;
	std::uint32_t offset;
	std::uint16_t width;
	std::uint16_t height;
};

/// \brief Represents a loaded bitmap.
struct BitmapEntry
{
	std::uint32_t offset;
	std::uint16_t width;
	std::uint16_t height;
};

/// \brief Manages all rendering for the theme.
class Manager
{
	static_assert(settings::manager::num_buffers != 0, "Settings::Manager::NumBuffers cannot be 0");
	friend Button;
	friend Image;
	friend Label;

	Manager(Manager const &) = delete;
	Manager & operator =(Manager const &) = delete;

private:
	static std::size_t const num_buffers_ = settings::manager::num_buffers;

	ui::WindowBase & window_;

	ft::Library library_;
	ft::Bitmap bitmap_;
	ft::Outline outline_;
	ft::Stroker stroker_;
	ft::Face label_face_;
	ft::Size label_size_;

	TextureArray red_texture_;
	TextureArray rgba_texture_;
	StreamArray<vertex::Bitmap> bitmap_array_;
	StreamArray<vertex::FillSolid> solid_array_;
	StreamArray<vertex::OutlineGradient> outline_array_;

	GLsync fences_[num_buffers_];
	std::size_t fence_index_ = 0;

	program::Bitmap bitmap_program;
	program::FillSolid fill_solid_program;
	program::OutlineGradient outline_gradient_program_;

	std::unordered_map<char const *, BitmapEntry> bitmap_entries_;
	std::unordered_map<char32_t, GlyphEntry> font_entries_;

	bool needs_redraw_;

	// Button offsets
	std::uint32_t button_center_in;
	std::uint32_t button_left_in;
	std::uint32_t button_right_in;
	std::uint32_t button_bottom_in;
	std::uint32_t button_top_in;
	std::uint32_t button_sw_in_;
	std::uint32_t button_se_in;
	std::uint32_t button_ne_in;
	std::uint32_t button_nw_in;
	std::uint32_t button_center_out;
	std::uint32_t button_left_out;
	std::uint32_t button_right_out;
	std::uint32_t button_bottom_out;
	std::uint32_t button_top_out;
	std::uint32_t button_sw_out;
	std::uint32_t button_se_out;
	std::uint32_t button_ne_out;
	std::uint32_t button_nw_out;

	ui::Pixel button_horizontal_corner_size_;
	ui::Pixel button_vertical_corner_size_;

	BitmapEntry const & LoadBitmapEntry(char const *);
	GlyphEntry const & LoadGlyphEntry(ft::Face &, char32_t);
	void SetupButton();

public:
	Manager(ui::WindowBase & window);
	~Manager() noexcept;

	/// \brief Make sure the GUI is drawn on the next update call
	void MarkNeedsRedraw();

	/// \brief Draw the GUI if needed
	///
	/// \returns true if the GUI was drawn.
	bool Update(ui::Pixel width, ui::Pixel height);
};

}
}
