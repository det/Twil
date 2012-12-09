#include "Theme/Manager.hpp"

#include "Ft/Size.hpp"
#include "Math/Matrix2.hpp"
#include "Math/Matrix3.hpp"

#include <iostream>

namespace Twil {
namespace Theme {

Manager::Manager() :
	mBitmap{mLibrary},
	mOutline{mLibrary},
	mStroker{mLibrary},
	mLabelFace{mLibrary, "Font/DejaVuSans-Bold.ttf", 0},
	mLabelSize{mLabelFace, 13.75 * 64}
{
	// Default GL state
	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate button bitmaps
	FT_Pos Roundness = 4 * 64;
	FT_Pos Left = 1 * 64;
	FT_Pos Bottom = 1 * 64;
	FT_Pos Right = 10 * 64;
	FT_Pos Top = 10 * 64;

	FT_Vector A{Left + Roundness, Bottom};
	FT_Vector B{Left, Bottom};
	FT_Vector C{Left, Bottom + Roundness};
	FT_Vector D{Left, Top - Roundness};
	FT_Vector E{Left, Top};
	FT_Vector F{Left + Roundness, Top};
	FT_Vector G{Right - Roundness, Top};
	FT_Vector H{Right, Top};
	FT_Vector I{Right, Top - Roundness};
	FT_Vector J{Right, Bottom + Roundness};
	FT_Vector K{Right, Bottom};
	FT_Vector L{Right - Roundness, Bottom};

	mOutline.clear();
	mOutline.beginPath(A);
	mOutline.addQuadratic(B, C);
	mOutline.addLine(D);
	mOutline.addQuadratic(E, F);
	mOutline.addLine(G);
	mOutline.addQuadratic(H, I);
	mOutline.addLine(J);
	mOutline.addQuadratic(K, L);
	mOutline.addLine(A);
	mOutline.endPath();

	// Button inside
	mBitmap.resize(11, 11);
	mBitmap.render(mOutline);

	mButtonCenterInside = mTexture.add(mBitmap.getSubRange(6, 6, 1, 1));
	mButtonBottomInside = mTexture.add(mBitmap.getSubRange(5, 0, 1, 5));
	mButtonTopInside = mTexture.add(mBitmap.getSubRange(5, 6, 1, 5));
	mButtonLeftInside = mTexture.add(mBitmap.getSubRange(0, 5, 5, 1));
	mButtonRightInside = mTexture.add(mBitmap.getSubRange(6, 5, 5, 1));
	mButtonSwInside = mTexture.add(mBitmap.getSubRange(0, 0, 5, 5));
	mButtonSeInside = mTexture.add(mBitmap.getSubRange(6, 0, 5, 5));
	mButtonNeInside = mTexture.add(mBitmap.getSubRange(6, 6, 5, 5));
	mButtonNwInside = mTexture.add(mBitmap.getSubRange(0, 6, 5, 5));

	// Button outline
	mStroker.setOptions(64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	mStroker.set(mOutline);
	mOutline.clear();
	mOutline.add(mStroker, FT_STROKER_BORDER_LEFT);
	mBitmap.render(mOutline);

	mButtonCenterOutside = mTexture.add(mBitmap.getSubRange(6, 6, 1, 1));
	mButtonBottomOutside = mTexture.add(mBitmap.getSubRange(5, 0, 1, 5));
	mButtonTopOutside = mTexture.add(mBitmap.getSubRange(5, 6, 1, 5));
	mButtonLeftOutside = mTexture.add(mBitmap.getSubRange(0, 5, 5, 1));
	mButtonRightOutside = mTexture.add(mBitmap.getSubRange(6, 5, 5, 1));
	mButtonSwOutside = mTexture.add(mBitmap.getSubRange(0, 0, 5, 5));
	mButtonSeOutside = mTexture.add(mBitmap.getSubRange(6, 0, 5, 5));
	mButtonNeOutside = mTexture.add(mBitmap.getSubRange(6, 6, 5, 5));
	mButtonNwOutside = mTexture.add(mBitmap.getSubRange(0, 6, 5, 5));
}

Theme::GlyphEntry const & Manager::loadGlyphEntry(Ft::Face & Face, char32_t Codepoint)
{
	// If the codepoint is already cached, we are done
	auto Iter = mFontEntries.find(Codepoint);
	if (Iter != end(mFontEntries)) return Iter->second;

	// Load this codepoint's glyph
	auto Index = Face.getCharIndex(Codepoint);
	Face.loadGlyph(Index);
	auto Box = Face.getCBox();
	auto Advance = Face.getAdvance();
	auto LsbDelta = Face.getLsbDelta();
	auto RsbDelta = Face.getRsbDelta();
	unsigned short Width = (Box.xMax - Box.xMin) / 64;
	unsigned short Height = (Box.yMax - Box.yMin) / 64;
	FT_Vector Bearings{Box.xMin, Box.yMin};

	Face.translate(-Box.xMin, -Box.yMin);

	mBitmap.resize(Width, Height);
	mBitmap.render(Face);
	unsigned int Offset = mTexture.add(mBitmap.begin(), mBitmap.end());

	// Return entry
	Theme::GlyphEntry Entry{Bearings, Advance, Index, LsbDelta, RsbDelta, Offset, Width, Height};
	auto Pair = mFontEntries.insert({Codepoint, Entry});
	return Pair.first->second;
}

void Manager::renderWindow()
{
	glClearColor(230.0/255.0, 229.0/255.0, 228.0/255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Manager::beginRender(unsigned short Width, unsigned short Height)
{
	mMatrix = Math::Matrix3::Ortho(Width, Height);
	glViewport(0, 0, Width, Height);
}

void Manager::finishRender()
{
	mTexture.upload();
	mSolidArray.upload();
	mOutlineArray.upload();

	glBindTexture(GL_TEXTURE_BUFFER, mTexture);

	glUseProgram(mOutlineGradient);
	mOutlineGradient.setModelView(mMatrix);
	glBindVertexArray(mOutlineArray);
	glDrawArrays(GL_POINTS, 0, mOutlineArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glUseProgram(mFillSolid);
	mFillSolid.setModelView(mMatrix);
	glBindVertexArray(mSolidArray);
	glDrawArrays(GL_POINTS, 0, mSolidArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	mSolidArray.clear();
	mOutlineArray.clear();
}

}
}

