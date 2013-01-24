#include "Manager.hpp"

namespace Twil {
namespace Theme {

ManagerT::ManagerT() :
	mBitmap{mLibrary},
	mOutline{mLibrary},
	mStroker{mLibrary},
	mLabelFace{mLibrary, "Font/DejaVuSans-Bold.ttf", 0},
	mLabelSize{mLabelFace, 880}
{
	// Default GL state
	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	generateButtonBitmaps();
}


void ManagerT::generateButtonBitmaps()
{
	signed short Roundness = Settings::Button::Roundness;

	signed short BorderSize = 1;
	signed short CornerSize = 1 + Roundness;
	signed short BitmapSize = BorderSize * 2 + CornerSize * 2 + 1;

	signed short Pos1 = 0;
	signed short Pos2 = Pos1 + 1;
	signed short Pos3 = Pos2 + Roundness;
	signed short Pos4 = Pos3 + 1;
	signed short Pos5 = Pos4 + Roundness;

	FT_Pos Fix2 = Pos2 * 64;
	FT_Pos Fix3 = Pos3 * 64;
	FT_Pos Fix4 = Pos4 * 64;
	FT_Pos Fix5 = Pos5 * 64;

	FT_Vector A{Fix3, Fix2};
	FT_Vector B{Fix2, Fix2};
	FT_Vector C{Fix2, Fix3};
	FT_Vector D{Fix2, Fix4};
	FT_Vector E{Fix2, Fix5};
	FT_Vector F{Fix3, Fix5};
	FT_Vector G{Fix4, Fix5};
	FT_Vector H{Fix5, Fix5};
	FT_Vector I{Fix5, Fix4};
	FT_Vector J{Fix5, Fix3};
	FT_Vector K{Fix5, Fix2};
	FT_Vector L{Fix4, Fix2};

	mOutline.clear();
	mOutline.beginContour(A);
	mOutline.moveQuadratic(B, C);
	mOutline.moveLine(D);
	mOutline.moveQuadratic(E, F);
	mOutline.moveLine(G);
	mOutline.moveQuadratic(H, I);
	mOutline.moveLine(J);
	mOutline.moveQuadratic(K, L);
	mOutline.moveLine(A);
	mOutline.endContour();

	// Inside
	mBitmap.resize(BitmapSize, BitmapSize);
	mBitmap.render(mOutline);

	mButtonCenterInside = mTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomInside = mTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopInside = mTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftInside = mTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightInside = mTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwInside = mTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeInside = mTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeInside = mTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwInside = mTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));

	// Outline
	mStroker.setOptions(1 * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	mStroker.set(mOutline);
	mOutline.clear();
	mOutline.append(mStroker, FT_STROKER_BORDER_LEFT);
	mBitmap.render(mOutline);

	mButtonCenterOutside = mTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomOutside = mTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopOutside = mTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftOutside = mTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightOutside = mTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwOutside = mTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeOutside = mTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeOutside = mTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwOutside = mTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));
}

GlyphEntryT const & ManagerT::loadGlyphEntry(Ft::FaceT & Face, char32_t Codepoint)
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
	unsigned int Offset = mTexture.append(mBitmap.begin(), mBitmap.end());

	// Return entry
	GlyphEntryT Entry{Bearings, Advance, Index, LsbDelta, RsbDelta, Offset, Width, Height};
	auto Pair = mFontEntries.insert({Codepoint, Entry});
	return Pair.first->second;
}

void ManagerT::draw(unsigned short Width, unsigned short Height)
{
	if (Width == 0 || Height == 0) return;
	float ScalingX = 2.0 / Width;
	float ScalingY = 2.0 / Height;
	float Red = float(Settings::Window::BackgroundColor.Red) / 255.0;
	float Green = float(Settings::Window::BackgroundColor.Green) / 255.0;
	float Blue = float(Settings::Window::BackgroundColor.Blue) / 255.0;
	float Alpha = float(Settings::Window::BackgroundColor.Alpha) / 255.0;
	glViewport(0, 0, Width, Height);
	glClearColor(Red, Green, Blue, Alpha);
	glClear(GL_COLOR_BUFFER_BIT);

	mTexture.upload();
	mSolidArray.upload();
	mOutlineArray.upload();

	glBindTexture(GL_TEXTURE_BUFFER, mTexture);

	glUseProgram(mOutlineGradient);
	mOutlineGradient.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mOutlineArray);
	glDrawArrays(GL_POINTS, 0, mOutlineArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glUseProgram(mFillSolid);
	mFillSolid.setScaling(ScalingX, ScalingY);
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

