#include "manager.hpp"

#include "scaling.hpp"
#include "loader/png.hpp"
#include "ui/window_base.hpp"

namespace twil {
namespace theme {

Manager::Manager(ui::WindowBase & window)
:
	window_{window},
	bitmap_{library_},
	stroker_{library_},
	label_face_{library_, settings::label::font, 0},
	label_size_{
		label_face_,
		static_cast<FT_UInt32>(window_.ConvertDipToPixelX(theme::settings::label::size)),
		static_cast<FT_UInt32>(window_.ConvertDipToPixelY(theme::settings::label::size))},
	red_texture_{GL_R8},
	rgba_texture_{GL_RGBA8},
	needs_redraw_{false}
{
	// We arent actually waiting for anything, but we need valid fences in the arrays
	for (std::size_t i = 0; i != num_buffers_; ++i)
	{
		fences_[i] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	// Default GL state
	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetupButton();
}

Manager::~Manager() noexcept
{
	for (std::size_t i = 0; i != num_buffers_; ++i) glDeleteSync(fences_[i]);
}

void Manager::SetupButton()
{
	ui::Pixel horizontal_roundness = window_.ConvertDipToPixelX(settings::button::roundness);
	ui::Pixel vertical_roundness = window_.ConvertDipToPixelY(settings::button::roundness);
	ui::Pixel horizontal_border_size = window_.ConvertDipToPixelX(settings::button::border_width);
	ui::Pixel vertical_border_size = window_.ConvertDipToPixelY(settings::button::border_width);

	ui::Pixel horizontal_pos1 = 0;
	ui::Pixel horizontal_pos2 = horizontal_pos1 + horizontal_border_size;
	ui::Pixel horizontal_pos3 = horizontal_pos2 + horizontal_roundness;
	ui::Pixel horizontal_pos4 = horizontal_pos3 + 1;
	ui::Pixel horizontal_pos5 = horizontal_pos4 + horizontal_roundness;

	ui::Pixel vertical_pos1 = 0;
	ui::Pixel vertical_pos2 = vertical_pos1 + vertical_border_size;
	ui::Pixel vertical_pos3 = vertical_pos2 + vertical_roundness;
	ui::Pixel vertical_pos4 = vertical_pos3 + 1;
	ui::Pixel vertical_pos5 = vertical_pos4 + vertical_roundness;

	ui::Pixel bitmap_width = horizontal_border_size * 2 + horizontal_roundness * 2 + 1;
	ui::Pixel bitmap_height = vertical_border_size * 2 + vertical_roundness * 2 + 1;
	ui::Pixel horizontal_corner_size = horizontal_border_size + horizontal_roundness;
	ui::Pixel vertical_corner_size = vertical_border_size + vertical_roundness;

	FT_Pos horizontal_fix2 = horizontal_pos2 * 64;
	FT_Pos horizontal_fix3 = horizontal_pos3 * 64;
	FT_Pos horizontal_fix4 = horizontal_pos4 * 64;
	FT_Pos horizontal_fix5 = horizontal_pos5 * 64;

	FT_Pos vertical_fix2 = vertical_pos2 * 64;
	FT_Pos vertical_fix3 = vertical_pos3 * 64;
	FT_Pos vertical_fix4 = vertical_pos4 * 64;
	FT_Pos vertical_fix5 = vertical_pos5 * 64;

	FT_Vector a{horizontal_fix3, vertical_fix2};
	FT_Vector b{horizontal_fix2, vertical_fix2};
	FT_Vector c{horizontal_fix2, vertical_fix3};
	FT_Vector d{horizontal_fix2, vertical_fix4};
	FT_Vector e{horizontal_fix2, vertical_fix5};
	FT_Vector f{horizontal_fix3, vertical_fix5};
	FT_Vector g{horizontal_fix4, vertical_fix5};
	FT_Vector h{horizontal_fix5, vertical_fix5};
	FT_Vector i{horizontal_fix5, vertical_fix4};
	FT_Vector j{horizontal_fix5, vertical_fix3};
	FT_Vector k{horizontal_fix5, vertical_fix2};
	FT_Vector l{horizontal_fix4, vertical_fix2};

	outline_.Clear();
	outline_.BeginContour(a);
	outline_.MoveQuadratic(b, c);
	outline_.MoveLine(d);
	outline_.MoveQuadratic(e, f);
	outline_.MoveLine(g);
	outline_.MoveQuadratic(h, i);
	outline_.MoveLine(j);
	outline_.MoveQuadratic(k, l);
	outline_.MoveLine(a);
	outline_.EndContour();

	// In
	bitmap_.Resize(bitmap_width, bitmap_height);
	bitmap_.Render(outline_);

	button_center_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos3, 1, 1));
	button_bottom_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos1, 1, vertical_corner_size));
	button_top_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos4, 1, vertical_corner_size));
	button_left_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos3, horizontal_corner_size, 1));
	button_right_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos3, horizontal_corner_size, 1));
	button_sw_in_ = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos1, horizontal_corner_size, vertical_corner_size));
	button_se_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos1, horizontal_corner_size, vertical_corner_size));
	button_ne_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos4, horizontal_corner_size, vertical_corner_size));
	button_nw_in = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos4, horizontal_corner_size, vertical_corner_size));

	// Out
	outline_.Transform({65536 * vertical_border_size, 0, 0, 65536 * horizontal_border_size});
	stroker_.SetOptions(64 * horizontal_border_size * vertical_border_size, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	stroker_.Set(outline_);
	outline_.Clear();
	outline_.Append(stroker_, FT_STROKER_BORDER_LEFT);
	outline_.Transform({65536 / vertical_border_size, 0, 0, 65536 / horizontal_border_size});
	bitmap_.Render(outline_);

	button_center_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos3, 1, 1));
	button_bottom_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos1, 1, vertical_corner_size));
	button_top_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos3, vertical_pos4, 1, vertical_corner_size));
	button_left_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos3, horizontal_corner_size, 1));
	button_right_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos3, horizontal_corner_size, 1));
	button_sw_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos1, horizontal_corner_size, vertical_corner_size));
	button_se_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos1, horizontal_corner_size, vertical_corner_size));
	button_ne_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos4, vertical_pos4, horizontal_corner_size, vertical_corner_size));
	button_nw_out = red_texture_.Append(bitmap_.GetSubRange(horizontal_pos1, vertical_pos4, horizontal_corner_size, vertical_corner_size));

	button_horizontal_corner_size_ = horizontal_corner_size;
	button_vertical_corner_size_ = vertical_corner_size;
}

BitmapEntry const & Manager::LoadBitmapEntry(char const * path)
{
	auto iter = bitmap_entries_.find(path);
	if (iter != bitmap_entries_.end()) return iter->second;

	loader::Png image{path};

	std::uint16_t width = window_.ScaleX(image.GetWidth());
	std::uint16_t height = window_.ScaleY(image.GetHeight());
	auto allocation = rgba_texture_.Allocate(width * height * 4);
	std::uint32_t offset = allocation.second / 4;

	CatmullRomFilter filter;
	Scale(
		image.begin(), image.GetWidth(), image.GetHeight(),
		allocation.first, width, height, 4, filter);

	BitmapEntry entry{offset, width, height};
	auto pair = bitmap_entries_.insert({path, entry});
	return pair.first->second;
}

GlyphEntry const & Manager::LoadGlyphEntry(ft::Face & face, char32_t codepoint)
{
	// If the codepoint is already cached, we are done
	auto iter = font_entries_.find(codepoint);
	if (iter != end(font_entries_)) return iter->second;

	// Load this codepoint's glyph
	auto index = face.GetCharIndex(codepoint);
	face.LoadGlyph(index);
	auto box = face.GetCBox();
	auto advance = face.GetAdvance();
	auto lsb_delta = face.GetLsbDelta();
	auto rsb_delta = face.GetRsbDelta();
	std::uint16_t width = (box.xMax - box.xMin) / 64;
	std::uint16_t height = (box.yMax - box.yMin) / 64;
	FT_Vector bearings{box.xMin, box.yMin};

	// Move the glyph to the origin and draw
	face.Translate(-box.xMin, -box.yMin);
	bitmap_.Resize(width, height);
	bitmap_.Render(face);
	std::uint32_t offset = red_texture_.Append(bitmap_.begin(), bitmap_.end());

	// Return entry
	GlyphEntry entry{bearings, advance, index, lsb_delta, rsb_delta, offset, width, height};
	auto pair = font_entries_.insert({codepoint, entry});
	return pair.first->second;
}

void Manager::MarkNeedsRedraw()
{
	needs_redraw_ = true;
}

bool Manager::Update(ui::Pixel width, ui::Pixel height)
{
	needs_redraw_ |= solid_array_.CheckNeedsRedraw();
	needs_redraw_ |= outline_array_.CheckNeedsRedraw();
	needs_redraw_ |= bitmap_array_.CheckNeedsRedraw();

	if (!needs_redraw_ || width <= 0 || height <= 0) return false;

	std::uint32_t res = glClientWaitSync(fences_[fence_index_], 0, 10000000); // wait at most 10ms
	if (res == GL_WAIT_FAILED || res == GL_TIMEOUT_EXPIRED) return false;
	glDeleteSync(fences_[fence_index_]);

	red_texture_.Update();
	rgba_texture_.Update();
	solid_array_.Update(fence_index_);
	outline_array_.Update(fence_index_);
	bitmap_array_.Update(fence_index_);

	float scaling_x = 2.0f / width;
	float scaling_y = 2.0f / height;
	float red = float(settings::window::background_color.red) / 255.0f;
	float green = float(settings::window::background_color.green) / 255.0f;
	float blue = float(settings::window::background_color.blue) / 255.0f;
	float alpha = float(settings::window::background_color.alpha) / 255.0f;
	glViewport(0, 0, width, height);
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_BUFFER, red_texture_.GetTexture());

	glUseProgram(outline_gradient_program_);
	outline_gradient_program_.SetScaling(scaling_x, scaling_y);
	outline_array_.draw(fence_index_);
	glUseProgram(0);

	glUseProgram(fill_solid_program);
	fill_solid_program.SetScaling(scaling_x, scaling_y);
	solid_array_.draw(fence_index_);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	glBindTexture(GL_TEXTURE_BUFFER, rgba_texture_.GetTexture());

	glUseProgram(bitmap_program);
	bitmap_program.SetScaling(scaling_x, scaling_y);
	bitmap_array_.draw(fence_index_);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	fences_[fence_index_] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	++fence_index_;
	fence_index_ %= num_buffers_;
	needs_redraw_ = false;
	return true;
}

}
}

