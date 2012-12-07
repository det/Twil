#pragma once

#include "Ft/Bitmap.hpp"
#include "Ft/Face.hpp"
#include "Ft/Library.hpp"
#include "Ft/Outline.hpp"
#include "Ft/Stroker.hpp"
#include "Ft/Size.hpp"
#include "Math/Matrix3.hpp"
#include "Program/FillSolid.hpp"
#include "Program/OutlineGradient.hpp"
#include "Gl/Buffer.hpp"
#include "Gl/Context.hpp"
#include "Gl/StreamArray.hpp"
#include "Gl/TextureArray.hpp"
#include "Gl/VertexArray.hpp"
#include "Vertex/FillSolid.hpp"
#include "Vertex/OutlineGradient.hpp"

#include <unordered_map>
#include <vector>

namespace Twil {
namespace Theme {

class Button;
class Label;
class Window;

struct GlyphEntry {
	FT_Vector Size;
	FT_Vector Bearings;
	FT_Vector Advance;
	FT_UInt Index;
	FT_Pos LsbDelta;
	FT_Pos RsbDelta;
	std::size_t Offset;
};

class Manager {
	friend class Button;
	friend class Label;

	private:
	Ft::Library mLibrary;
	Ft::Bitmap mBitmap;
	Ft::Outline mOutline;
	Ft::Stroker mStroker;
	Ft::Face mLabelFace;
	Ft::Size mLabelSize;

	Gl::TextureArray mTexture;
	Gl::StreamArray<Vertex::FillSolid> mSolidArray;
	Gl::StreamArray<Vertex::OutlineGradient> mOutlineArray;

	Program::FillSolid mFillSolid;
	Program::OutlineGradient mOutlineGradient;

	Math::Matrix3 mMatrix;
	std::unordered_map<char32_t, GlyphEntry> mFontEntries;

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

	GlyphEntry const & loadGlyphEntry(Ft::Face &, char32_t);

	public:	
	Manager();

	void beginRender(unsigned short Width, unsigned short Height);
	void finishRender();
	void renderWindow();
};

}
}
