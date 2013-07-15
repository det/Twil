#include "Manager.hpp"

#include "Loader/Png.hpp"

#include <iostream>

namespace Twil {
namespace Theme {

ManagerT::ManagerT()
:
	mBitmap{mLibrary},
	mStroker{mLibrary},
	mLabelFace{mLibrary, Settings::Label::Font, 0},
	mLabelSize{mLabelFace, Settings::Label::Size},
	mRedTexture{GL_R8},
	mRgbaTexture{GL_RGBA8},
	mNeedsRedraw{false}
{
	// We arent actually waiting for anything, but we need valid fences in the arrays
	for (std::size_t I = 0; I != mNumBuffers; ++I)
	{
		mFences[I] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	}

	// Default GL state
	glEnable(GL_BLEND);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	generateButtonBitmaps();
}

ManagerT::~ManagerT()
{
	for (std::size_t I = 0; I != mNumBuffers; ++I) glDeleteSync(mFences[I]);
}

void ManagerT::generateButtonBitmaps()
{
	std::int16_t Roundness = Settings::Button::Roundness;

	std::int16_t BorderSize = 1;
	std::int16_t CornerSize = BorderSize + Roundness;
	std::int16_t BitmapSize = BorderSize * 2 + 1 + CornerSize * 2;

	std::int16_t Pos1 = 0;
	std::int16_t Pos2 = Pos1 + BorderSize;
	std::int16_t Pos3 = Pos2 + Roundness;
	std::int16_t Pos4 = Pos3 + 1;
	std::int16_t Pos5 = Pos4 + Roundness;

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

	// In
	mBitmap.resize(BitmapSize, BitmapSize);
	mBitmap.render(mOutline);

	mButtonCenterIn = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomIn = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopIn = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftIn = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightIn = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwIn = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeIn = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeIn = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwIn = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));

	// Outline
	mStroker.setOptions(BorderSize * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	mStroker.set(mOutline);
	mOutline.clear();
	mOutline.append(mStroker, FT_STROKER_BORDER_LEFT);
	mBitmap.render(mOutline);

	mButtonCenterOut = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos3, BorderSize, BorderSize));
	mButtonBottomOut = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos1, BorderSize, CornerSize));
	mButtonTopOut = mRedTexture.append(mBitmap.getSubRange(Pos3, Pos4, BorderSize, CornerSize));
	mButtonLeftOut = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos3, CornerSize, BorderSize));
	mButtonRightOut = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos3, CornerSize, BorderSize));
	mButtonSwOut = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos1, CornerSize, CornerSize));
	mButtonSeOut = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos1, CornerSize, CornerSize));
	mButtonNeOut = mRedTexture.append(mBitmap.getSubRange(Pos4, Pos4, CornerSize, CornerSize));
	mButtonNwOut = mRedTexture.append(mBitmap.getSubRange(Pos1, Pos4, CornerSize, CornerSize));
}

BitmapEntryT const & ManagerT::loadBitmapEntry(char const * Path)
{
	auto Iter = mBitmapEntries.find(Path);
	if (Iter != mBitmapEntries.end()) return Iter->second;

	Loader::PngT Image{Path};
	// The offset that OpenGL needs is pixel offset, not the byte offset, so divide by 4
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
	std::uint16_t Width = (Box.xMax - Box.xMin) / 64;
	std::uint16_t Height = (Box.yMax - Box.yMin) / 64;
	FT_Vector Bearings{Box.xMin, Box.yMin};

	// Move the glyph to the origin and draw
	Face.translate(-Box.xMin, -Box.yMin);
	mBitmap.resize(Width, Height);
	mBitmap.render(Face);
	unsigned int Offset = mRedTexture.append(mBitmap.begin(), mBitmap.end());

	// Return entry
	GlyphEntryT Entry{Bearings, Advance, Index, LsbDelta, RsbDelta, Offset, Width, Height};
	auto Pair = mFontEntries.insert({Codepoint, Entry});
	return Pair.first->second;
}

void ManagerT::markNeedsRedraw()
{
	mNeedsRedraw = true;
}

bool ManagerT::update(std::uint16_t Width, std::uint16_t Height)
{
	mNeedsRedraw |= mSolidArray.checkNeedsRedraw();
	mNeedsRedraw |= mOutlineArray.checkNeedsRedraw();
	mNeedsRedraw |= mBitmapArray.checkNeedsRedraw();

	if (!mNeedsRedraw || Width == 0 || Height == 0) return false;

	GLenum Result = glClientWaitSync(mFences[mFenceIndex], 0, 10000000); // wait at most 10ms
	if (Result == GL_WAIT_FAILED || Result == GL_TIMEOUT_EXPIRED) return false;
	glDeleteSync(mFences[mFenceIndex]);

	mRedTexture.update();
	mRgbaTexture.update();
	mSolidArray.update(mFenceIndex);
	mOutlineArray.update(mFenceIndex);
	mBitmapArray.update(mFenceIndex);

	float ScalingX = 2.0 / Width;
	float ScalingY = 2.0 / Height;
	float Red = float(Settings::Window::BackgroundColor.Red) / 255.0;
	float Green = float(Settings::Window::BackgroundColor.Green) / 255.0;
	float Blue = float(Settings::Window::BackgroundColor.Blue) / 255.0;
	float Alpha = float(Settings::Window::BackgroundColor.Alpha) / 255.0;
	glViewport(0, 0, Width, Height);
	glClearColor(Red, Green, Blue, Alpha);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_BUFFER, mRedTexture.getTexture());

	glUseProgram(mOutlineGradientProgram);
	mOutlineGradientProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mOutlineArray.getVertexArray(mFenceIndex));
	glDrawArrays(GL_POINTS, 0, mOutlineArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glUseProgram(mFillSolidProgram);
	mFillSolidProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mSolidArray.getVertexArray(mFenceIndex));
	glDrawArrays(GL_POINTS, 0, mSolidArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	glBindTexture(GL_TEXTURE_BUFFER, mRgbaTexture.getTexture());

	glUseProgram(mBitmapProgram);
	mBitmapProgram.setScaling(ScalingX, ScalingY);
	glBindVertexArray(mBitmapArray.getVertexArray(mFenceIndex));
	glDrawArrays(GL_POINTS, 0, mBitmapArray.getSize());
	glBindVertexArray(0);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	mFences[mFenceIndex] = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

	++mFenceIndex;
	mFenceIndex %= mNumBuffers;
	mNeedsRedraw = false;
	return true;
}

}
}

