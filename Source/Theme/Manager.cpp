#include "Manager.hpp"

#include "Loader/Png.hpp"

namespace Twil {
namespace Theme {

ManagerT::ManagerT() :
	mBitmap{mLibrary},
	mOutline{mLibrary},
	mStroker{mLibrary},
	mLabelFace{mLibrary, Settings::Label::Font, 0},
	mLabelSize{mLabelFace, Settings::Label::Size},
	mRedTexture{GL_R8},
	mRgbaTexture{GL_RGBA8}
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
	signed short CornerSize = BorderSize + Roundness;
	signed short BitmapSize = BorderSize * 2 + 1 + CornerSize * 2;

	signed short Pos1 = 0;
	signed short Pos2 = Pos1 + BorderSize;
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

	mButtonCenterInside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomInside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopInside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftInside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightInside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwInside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeInside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeInside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwInside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));

	// Outline
	mStroker.setOptions(BorderSize * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	mStroker.set(mOutline);
	mOutline.clear();
	mOutline.append(mStroker, FT_STROKER_BORDER_LEFT);
	mBitmap.render(mOutline);

	mButtonCenterOutside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomOutside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopOutside = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftOutside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightOutside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwOutside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeOutside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeOutside = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwOutside = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));
}

BitmapEntryT const & ManagerT::loadBitmapEntry(char const * Path)
{
	auto Iter = mBitmapEntries.find(Path);
	if (Iter != mBitmapEntries.end()) return Iter->second;

	Loader::PngT Image{Path};
	unsigned int Offset = mRgbaTexture.append(Image.begin(), Image.end()) / 4;

	BitmapEntryT Entry{Offset, Image.getWidth(), Image.getHeight()};
	auto Pair = mBitmapEntries.insert({Path, Entry});
	return Pair.first->second;
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
	unsigned int Offset = mRedTexture.append(mBitmap.begin(), mBitmap.end());

	// Return entry
	GlyphEntryT Entry{Bearings, Advance, Index, LsbDelta, RsbDelta, Offset, Width, Height};
	auto Pair = mFontEntries.insert({Codepoint, Entry});
	return Pair.first->second;
}

void ManagerT::draw(unsigned short Width, unsigned short Height)
{
	if (Width == 0 || Height == 0) return;

	mRedTexture.upload();
	mRgbaTexture.upload();
	mSolidArray.update();
	mOutlineArray.update();
	mBitmapArray.update();

	float ScalingX = 2.0 / Width;
	float ScalingY = 2.0 / Height;
	float Red = float(Settings::Window::BackgroundColor.Red) / 255.0;
	float Green = float(Settings::Window::BackgroundColor.Green) / 255.0;
	float Blue = float(Settings::Window::BackgroundColor.Blue) / 255.0;
	float Alpha = float(Settings::Window::BackgroundColor.Alpha) / 255.0;
	glViewport(0, 0, Width, Height);
	glClearColor(Red, Green, Blue, Alpha);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_BUFFER, mRedTexture);

	glUseProgram(mOutlineGradientProgram);
	mOutlineGradientProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mOutlineArray);
	glDrawArrays(GL_POINTS, 0, mOutlineArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glUseProgram(mFillSolidProgram);
	mFillSolidProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mSolidArray);
	glDrawArrays(GL_POINTS, 0, mSolidArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	glBindTexture(GL_TEXTURE_BUFFER, mRgbaTexture);

	glUseProgram(mBitmapProgram);
	mBitmapProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mBitmapArray);
	glDrawArrays(GL_POINTS, 0, mBitmapArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);
}

}
}

