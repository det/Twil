#pragma once

#include "ManagerFwd.hpp"

#include "ButtonFwd.hpp"
#include "LabelFwd.hpp"
#include "Settings.hpp"
#include "StreamArray.hpp"
#include "TextureArray.hpp"
#include "Ft/Bitmap.hpp"
#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Outline.hpp"
#include "Ft/Stroker.hpp"
#include "Ft/Size.hpp"
#include "Program/Bitmap.hpp"
#include "Program/FillSolid.hpp"
#include "Program/OutlineGradient.hpp"
#include "Gl/Context.hpp"
#include "Ui/WindowBaseFwd.hpp"
#include "Vertex/Bitmap.hpp"
#include "Vertex/FillSolid.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace Twil {
namespace Theme {

/// \brief Represents a loaded unicode glyph.
struct GlyphEntryT
{
	FT_Vector Bearings;
	FT_Vector Advance;
	FT_UInt Index;
	FT_Pos LsbDelta;
	FT_Pos RsbDelta;
	std::uint32_t Offset;
	std::uint16_t Width;
	std::uint16_t Height;
};

/// \brief Represents a loaded bitmap.
struct BitmapEntryT
{
	std::uint32_t Offset;
	std::uint16_t Width;
	std::uint16_t Height;
};

/// \brief Manages all rendering for the theme.
class ManagerT
{
	static_assert(Settings::Manager::NumBuffers != 0, "Settings::Manager::NumBuffers cannot be 0");
	friend class ButtonT;
	friend class ImageT;
	friend class LabelT;

	ManagerT(ManagerT const &) = delete;
	ManagerT & operator =(ManagerT const &) = delete;

private:
	static std::size_t const mNumBuffers = Settings::Manager::NumBuffers;

	Ui::WindowBaseT & mWindow;

	Ft::LibraryT mLibrary;
	Ft::BitmapT mBitmap;
	Ft::OutlineT mOutline;
	Ft::StrokerT mStroker;
	Ft::FaceT mLabelFace;
	Ft::SizeT mLabelSize;

	TextureArrayT mRedTexture;
	TextureArrayT mRgbaTexture;
	StreamArrayT<Vertex::BitmapT> mBitmapArray;
	StreamArrayT<Vertex::FillSolidT> mSolidArray;
	StreamArrayT<Vertex::OutlineGradientT> mOutlineArray;

	GLsync mFences[mNumBuffers];
	std::size_t mFenceIndex = 0;

	Program::BitmapT mBitmapProgram;
	Program::FillSolidT mFillSolidProgram;
	Program::OutlineGradientT mOutlineGradientProgram;

	std::unordered_map<char const *, BitmapEntryT> mBitmapEntries;
	std::unordered_map<char32_t, GlyphEntryT> mFontEntries;

	bool mNeedsRedraw;

	// Button offsets
	std::uint32_t mButtonCenterIn;
	std::uint32_t mButtonLeftIn;
	std::uint32_t mButtonRightIn;
	std::uint32_t mButtonBottomIn;
	std::uint32_t mButtonTopIn;
	std::uint32_t mButtonSwIn;
	std::uint32_t mButtonSeIn;
	std::uint32_t mButtonNeIn;
	std::uint32_t mButtonNwIn;
	std::uint32_t mButtonCenterOut;
	std::uint32_t mButtonLeftOut;
	std::uint32_t mButtonRightOut;
	std::uint32_t mButtonBottomOut;
	std::uint32_t mButtonTopOut;
	std::uint32_t mButtonSwOut;
	std::uint32_t mButtonSeOut;
	std::uint32_t mButtonNeOut;
	std::uint32_t mButtonNwOut;

	std::int16_t mButtonHorizontalCornerSize;
	std::int16_t mButtonVerticalCornerSize;

	BitmapEntryT const & loadBitmapEntry(char const *);
	GlyphEntryT const & loadGlyphEntry(Ft::FaceT &, char32_t);
	void setupButton();

public:
	ManagerT(Ui::WindowBaseT & Window);
	~ManagerT() noexcept;

	/// \brief Make sure the GUI is drawn on the next update call
	void markNeedsRedraw();

	/// \brief Draw the GUI if needed
	///
	/// \returns true if the GUI was drawn.
	bool update(std::int16_t Width, std::int16_t Height);
};

}
}
