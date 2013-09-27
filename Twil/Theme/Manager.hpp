#pragma once

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
#include "Gl/VertexArray.hpp"
#include "Vertex/Bitmap.hpp"
#include "Vertex/FillSolid.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <unordered_map>
#include <vector>

namespace Twil {
namespace Theme {

class ButtonT;
class LabelT;
class Window;

/// \brief Represents a loaded unicode glyph.
struct GlyphEntryT
{
	FT_Vector Bearings;
	FT_Vector Advance;
	FT_UInt Index;
	FT_Pos LsbDelta;
	FT_Pos RsbDelta;
	unsigned int Offset;
	std::uint16_t Width;
	std::uint16_t Height;
};

/// \brief Represents a loaded bitmap.
struct BitmapEntryT
{
	unsigned int Offset;
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
	GLuint mButtonCenterIn;
	GLuint mButtonLeftIn;
	GLuint mButtonRightIn;
	GLuint mButtonBottomIn;
	GLuint mButtonTopIn;
	GLuint mButtonSwIn;
	GLuint mButtonSeIn;
	GLuint mButtonNeIn;
	GLuint mButtonNwIn;
	GLuint mButtonCenterOut;
	GLuint mButtonLeftOut;
	GLuint mButtonRightOut;
	GLuint mButtonBottomOut;
	GLuint mButtonTopOut;
	GLuint mButtonSwOut;
	GLuint mButtonSeOut;
	GLuint mButtonNeOut;
	GLuint mButtonNwOut;

	BitmapEntryT const & loadBitmapEntry(char const *);
	GlyphEntryT const & loadGlyphEntry(Ft::FaceT &, char32_t);
	void generateButtonBitmaps();

public:	
	ManagerT();
	~ManagerT() noexcept;

	/// \brief Make sure the GUI is drawn on the next update call
	void markNeedsRedraw();

	/// \brief Draw the GUI if needed
	///
	/// \returns true if the GUI was drawn.
	bool update(std::uint16_t Width, std::uint16_t Height);
};

}
}
