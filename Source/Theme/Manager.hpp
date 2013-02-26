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
#include "Program/FillSolid.hpp"
#include "Program/OutlineGradient.hpp"
#include "Gl/Context.hpp"
#include "Gl/VertexArray.hpp"
#include "Vertex/FillSolid.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <unordered_map>
#include <vector>

namespace Twil {
namespace Theme {

class ButtonT;
class LabelT;
class Window;

/// \brief Represents a loaded Unicode glyph.
struct GlyphEntryT
{
	FT_Vector Bearings;
	FT_Vector Advance;
	FT_UInt Index;
	FT_Pos LsbDelta;
	FT_Pos RsbDelta;
	unsigned int Offset;
	unsigned short Width;
	unsigned short Height;
};

/// \brief Manages all rendering for the theme.
class ManagerT
{
	friend class ButtonT;
	friend class LabelT;

	private:
	Ft::LibraryT mLibrary;
	Ft::BitmapT mBitmap;
	Ft::OutlineT mOutline;
	Ft::StrokerT mStroker;
	Ft::FaceT mLabelFace;
	Ft::SizeT mLabelSize;

	TextureArrayT mTexture;
	StreamArrayT<Vertex::FillSolidT> mSolidArray;
	StreamArrayT<Vertex::OutlineGradientT> mOutlineArray;

	Program::FillSolidT mFillSolid;
	Program::OutlineGradientT mOutlineGradient;

	std::unordered_map<char32_t, GlyphEntryT> mFontEntries;

	// Button offsets
	GLuint mButtonCenterInside;
	GLuint mButtonLeftInside;
	GLuint mButtonRightInside;
	GLuint mButtonBottomInside;
	GLuint mButtonTopInside;
	GLuint mButtonSwInside;
	GLuint mButtonSeInside;
	GLuint mButtonNeInside;
	GLuint mButtonNwInside;
	GLuint mButtonCenterOutside;
	GLuint mButtonLeftOutside;
	GLuint mButtonRightOutside;
	GLuint mButtonBottomOutside;
	GLuint mButtonTopOutside;
	GLuint mButtonSwOutside;
	GLuint mButtonSeOutside;
	GLuint mButtonNeOutside;
	GLuint mButtonNwOutside;

	GlyphEntryT const & loadGlyphEntry(Ft::FaceT &, char32_t);
	void generateButtonBitmaps();

	public:	
	ManagerT();

	void draw(unsigned short Width, unsigned short Height);

	/// \brief Draw the GUI.
	///
	/// All Theme objects must queue their vertex data each time before this is called.
};

}
}
