#include "Manager.hpp"

#include "Loader/Png.hpp"
#include "Ui/WindowBase.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace Twil {
namespace Theme {

ManagerT::ManagerT(Ui::WindowBaseT & Window)
:
	mWindow{Window},
	mBitmap{mLibrary},
	mStroker{mLibrary},
	mLabelFace{mLibrary, Settings::Label::Font, 0},
	mLabelSize{
		mLabelFace,
		static_cast<FT_UInt32>(mWindow.convertDipToPixelX(Theme::Settings::Label::Size)),
		static_cast<FT_UInt32>(mWindow.convertDipToPixelY(Theme::Settings::Label::Size))},
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

	setupButton();
}

ManagerT::~ManagerT() noexcept
{
	for (std::size_t I = 0; I != mNumBuffers; ++I) glDeleteSync(mFences[I]);
}

void ManagerT::setupButton()
{
	Ui::PixelT HorizontalRoundness = mWindow.convertDipToPixelX(Settings::Button::Roundness);
	Ui::PixelT VerticalRoundness = mWindow.convertDipToPixelY(Settings::Button::Roundness);
	Ui::PixelT HorizontalBorderSize = mWindow.convertDipToPixelX(Settings::Button::BorderWidth);
	Ui::PixelT VerticalBorderSize = mWindow.convertDipToPixelY(Settings::Button::BorderWidth);

	Ui::PixelT HorizontalPos1 = 0;
	Ui::PixelT HorizontalPos2 = HorizontalPos1 + HorizontalBorderSize;
	Ui::PixelT HorizontalPos3 = HorizontalPos2 + HorizontalRoundness;
	Ui::PixelT HorizontalPos4 = HorizontalPos3 + 1;
	Ui::PixelT HorizontalPos5 = HorizontalPos4 + HorizontalRoundness;

	Ui::PixelT VerticalPos1 = 0;
	Ui::PixelT VerticalPos2 = VerticalPos1 + VerticalBorderSize;
	Ui::PixelT VerticalPos3 = VerticalPos2 + VerticalRoundness;
	Ui::PixelT VerticalPos4 = VerticalPos3 + 1;
	Ui::PixelT VerticalPos5 = VerticalPos4 + VerticalRoundness;

	Ui::PixelT BitmapWidth = HorizontalBorderSize * 2 + HorizontalRoundness * 2 + 1;
	Ui::PixelT BitmapHeight = VerticalBorderSize * 2 + VerticalRoundness * 2 + 1;
	Ui::PixelT HorizontalCornerSize = HorizontalBorderSize + HorizontalRoundness;
	Ui::PixelT VerticalCornerSize = VerticalBorderSize + VerticalRoundness;

	FT_Pos HorizontalFix2 = HorizontalPos2 * 64;
	FT_Pos HorizontalFix3 = HorizontalPos3 * 64;
	FT_Pos HorizontalFix4 = HorizontalPos4 * 64;
	FT_Pos HorizontalFix5 = HorizontalPos5 * 64;

	FT_Pos VerticalFix2 = VerticalPos2 * 64;
	FT_Pos VerticalFix3 = VerticalPos3 * 64;
	FT_Pos VerticalFix4 = VerticalPos4 * 64;
	FT_Pos VerticalFix5 = VerticalPos5 * 64;

	FT_Vector A{HorizontalFix3, VerticalFix2};
	FT_Vector B{HorizontalFix2, VerticalFix2};
	FT_Vector C{HorizontalFix2, VerticalFix3};
	FT_Vector D{HorizontalFix2, VerticalFix4};
	FT_Vector E{HorizontalFix2, VerticalFix5};
	FT_Vector F{HorizontalFix3, VerticalFix5};
	FT_Vector G{HorizontalFix4, VerticalFix5};
	FT_Vector H{HorizontalFix5, VerticalFix5};
	FT_Vector I{HorizontalFix5, VerticalFix4};
	FT_Vector J{HorizontalFix5, VerticalFix3};
	FT_Vector K{HorizontalFix5, VerticalFix2};
	FT_Vector L{HorizontalFix4, VerticalFix2};

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
	mBitmap.resize(BitmapWidth, BitmapHeight);
	mBitmap.render(mOutline);

	mButtonCenterIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos3, 1, 1));
	mButtonBottomIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos1, 1, VerticalCornerSize));
	mButtonTopIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos4, 1, VerticalCornerSize));
	mButtonLeftIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos3, HorizontalCornerSize, 1));
	mButtonRightIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos3, HorizontalCornerSize, 1));
	mButtonSwIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos1, HorizontalCornerSize, VerticalCornerSize));
	mButtonSeIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos1, HorizontalCornerSize, VerticalCornerSize));
	mButtonNeIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos4, HorizontalCornerSize, VerticalCornerSize));
	mButtonNwIn = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos4, HorizontalCornerSize, VerticalCornerSize));

	// Out
	mOutline.transform({65536 * VerticalBorderSize, 0, 0, 65536 * HorizontalBorderSize});
	mStroker.setOptions(64 * HorizontalBorderSize * VerticalBorderSize, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
	mStroker.set(mOutline);
	mOutline.clear();
	mOutline.append(mStroker, FT_STROKER_BORDER_LEFT);
	mOutline.transform({65536 / VerticalBorderSize, 0, 0, 65536 / HorizontalBorderSize});
	mBitmap.render(mOutline);

	mButtonCenterOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos3, 1, 1));
	mButtonBottomOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos1, 1, VerticalCornerSize));
	mButtonTopOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos3, VerticalPos4, 1, VerticalCornerSize));
	mButtonLeftOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos3, HorizontalCornerSize, 1));
	mButtonRightOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos3, HorizontalCornerSize, 1));
	mButtonSwOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos1, HorizontalCornerSize, VerticalCornerSize));
	mButtonSeOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos1, HorizontalCornerSize, VerticalCornerSize));
	mButtonNeOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos4, VerticalPos4, HorizontalCornerSize, VerticalCornerSize));
	mButtonNwOut = mRedTexture.append(mBitmap.getSubRange(HorizontalPos1, VerticalPos4, HorizontalCornerSize, VerticalCornerSize));

	mButtonHorizontalCornerSize = HorizontalCornerSize;
	mButtonVerticalCornerSize = VerticalCornerSize;
}

namespace {

template<typename SourceT, typename DestT, std::size_t Channels = 4>
void resizeNearest(
	SourceT Source, std::size_t SourceWidth, std::size_t SourceHeight,
	DestT Dest, std::size_t DestWidth, std::size_t DestHeight)
{
	for (std::size_t DestY = 0; DestY != DestHeight; ++DestY)
	{
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			std::size_t SourceX = DestX * SourceWidth / DestWidth;
			std::size_t SourceY = DestY * SourceHeight / DestHeight;
			auto DestPtr = Dest + DestY * DestWidth * Channels + DestX * Channels;
			auto SourcePtr = Source + SourceY * SourceWidth * Channels + SourceX * Channels;
			std::copy(SourcePtr, SourcePtr + Channels, DestPtr);
		}
	}
}

double clean(double X)
{
   double const Epsilon = .0000125;
   if (std::abs(X) < Epsilon) return 0.0;
   return X;
}

double sinc(double X)
{
	X *= std::atan(1) * 4;
	if (X < 0.01 && X > -0.01) return 1.0 + X * X * (-1.0 / 6.0 + X * X * 1.0 / 120.0);
	else return std::sin(X) / X;
}

double evalLanczos(double X, std::size_t FilterSize)
{
   if (X < 0.0) X = -X;
   if (X < FilterSize) return clean(sinc(X) * sinc(X / FilterSize));
   else return 0.0;
}

template<typename SourceT, typename DestT>
void resizeLanzos(
	SourceT Source, std::size_t SourceWidth, std::size_t SourceHeight,
	DestT Dest, std::size_t DestWidth, std::size_t DestHeight,
	std::size_t Channels = 4, std::size_t FilterSize = 3)
{
	double RatioX =
		static_cast<double>(SourceWidth) /
		static_cast<double>(DestWidth);

	double RatioY =
		static_cast<double>(SourceHeight) /
		static_cast<double>(DestHeight);

	double SourceMax = std::numeric_limits<typename std::iterator_traits<SourceT>::value_type>::max();
	double DestMax = std::numeric_limits<typename std::iterator_traits<DestT>::value_type>::max();

	auto HorizData = Data::makeUniqueArray<double>(SourceHeight * DestWidth * Channels);

	for (std::size_t DestY = 0; DestY != SourceHeight; ++DestY)
	{
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			for (std::size_t C = 0; C != Channels; ++C)
			{
				double SourceX = RatioX * DestX;
				std::size_t FloorX = SourceX;

				double DestChannel = 0.0;
				double Weight = 0.0;
				for (std::size_t I = FloorX - FilterSize - 1; I != FloorX + FilterSize; ++I)
				{
					if (I < SourceWidth)
					{
						double Term = evalLanczos(SourceX - I, FilterSize);
						DestChannel += Source[DestY * SourceWidth * Channels + I * Channels + C] / SourceMax * Term;
						Weight += Term;
					}
				}

				DestChannel /= Weight;
				if (DestChannel > 1.0) DestChannel = 1.0;
				if (DestChannel < 0.0) DestChannel = 0.0;
				HorizData[DestY * DestWidth * Channels + DestX * Channels + C] = DestChannel;
			}
		}
	}

	for (std::size_t DestY = 0; DestY != DestHeight; ++DestY)
	{
		double SourceY = RatioY * DestY;
		std::size_t FloorY = SourceY;
		for (std::size_t DestX = 0; DestX != DestWidth; ++DestX)
		{
			for (std::size_t C = 0; C != Channels; ++C)
			{
				double DestChannel = 0.0;
				double Weight = 0.0;
				for (std::size_t I = FloorY - FilterSize - 1; I != FloorY + FilterSize; ++I)
				{
					if (I < SourceHeight)
					{
						double Term = evalLanczos(SourceY - I, FilterSize);
						DestChannel += HorizData[I * DestWidth * Channels + DestX * Channels + C] * Term;
						Weight += Term;
					}
				}

				DestChannel /= Weight;
				if (DestChannel > 1.0) DestChannel = 1.0;
				if (DestChannel < 0.0) DestChannel = 0.0;

				Dest[DestY * DestWidth * Channels + DestX * Channels + C] = DestChannel * DestMax + 0.5;
			}
		}
	}
}

}

BitmapEntryT const & ManagerT::loadBitmapEntry(char const * Path)
{
	auto Iter = mBitmapEntries.find(Path);
	if (Iter != mBitmapEntries.end()) return Iter->second;

	Loader::PngT Image{Path};

	std::uint16_t Width = mWindow.scaleX(Image.getWidth());
	std::uint16_t Height = mWindow.scaleY(Image.getHeight());
	auto Allocation = mRgbaTexture.allocate(Width * Height * 4);
	std::uint32_t Offset = Allocation.second / 4;

	resizeLanzos(
		Image.begin(), Image.getWidth(), Image.getHeight(),
		Allocation.first, Width, Height);

	BitmapEntryT Entry{Offset, Width, Height};
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
	std::uint32_t Offset = mRedTexture.append(mBitmap.begin(), mBitmap.end());

	// Return entry
	GlyphEntryT Entry{Bearings, Advance, Index, LsbDelta, RsbDelta, Offset, Width, Height};
	auto Pair = mFontEntries.insert({Codepoint, Entry});
	return Pair.first->second;
}

void ManagerT::markNeedsRedraw()
{
	mNeedsRedraw = true;
}

bool ManagerT::update(Ui::PixelT Width, Ui::PixelT Height)
{
	mNeedsRedraw |= mSolidArray.checkNeedsRedraw();
	mNeedsRedraw |= mOutlineArray.checkNeedsRedraw();
	mNeedsRedraw |= mBitmapArray.checkNeedsRedraw();

	if (!mNeedsRedraw || Width <= 0 || Height <= 0) return false;

	std::uint32_t Result = glClientWaitSync(mFences[mFenceIndex], 0, 10000000); // wait at most 10ms
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
	mOutlineArray.draw(mFenceIndex);
	glUseProgram(0);

	glUseProgram(mFillSolidProgram);
	mFillSolidProgram.setScaling(ScalingX, ScalingY);
	mSolidArray.draw(mFenceIndex);
	glUseProgram(0);

	glBindTexture(GL_TEXTURE_BUFFER, 0);

	glBindTexture(GL_TEXTURE_BUFFER, mRgbaTexture.getTexture());

	glUseProgram(mBitmapProgram);
	mBitmapProgram.setScaling(ScalingX, ScalingY);
	mBitmapArray.draw(mFenceIndex);
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

