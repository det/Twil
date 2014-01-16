#include "Label.hpp"

#include "Manager.hpp"

#include <iostream>

namespace Twil {
namespace Theme {

void LabelT::init(ManagerT & Manager)
{
	mManager = &Manager;
	mManager->mSolidArray.allocate(*this, 0);
	mHeight = mManager->mLabelSize.getHeight() / 64;
}

void LabelT::setText(std::u32string const & Text)
{
	mGlyphs.clear();
	auto & Face = mManager->mLabelFace;
	Face.setActiveSize(mManager->mLabelSize);

	FT_Vector Pen{0, -mManager->mLabelSize.getDescender()};
	GlyphEntryT PreviousEntry{};

	for (auto Codepoint : Text)
	{
		auto Entry = mManager->loadGlyphEntry(Face, Codepoint);

		// We can hit a divide by 0 in clipping without this check
		if (Entry.Width == 0 || Entry.Height == 0) continue;

		// Apply characacter pair kerning / Hint advance adjustment
		auto Delta = Face.getKerning(PreviousEntry.Index, Entry.Index);
		if (PreviousEntry.RsbDelta - Entry.LsbDelta >= 32) Delta.x -= 64;
		else if (PreviousEntry.RsbDelta - Entry.LsbDelta < -32) Delta.x += 64;
		Pen.x += Delta.x;
		Pen.y += Delta.y;

		std::int16_t Left = (Pen.x + Entry.Bearings.x) / 64;
		std::int16_t Bottom = (Pen.y + Entry.Bearings.y) / 64;
		std::int16_t Right = Left + Entry.Width;
		std::int16_t Top = Bottom + Entry.Height;

		LabelGlyph Glyph;
		Glyph.PositionMin = {Left, Bottom};
		Glyph.PositionMax = {Right, Top};
		Glyph.TextureSize = {Entry.Width, Entry.Height};
		Glyph.Offset = {Entry.Offset};
		mGlyphs.push_back(Glyph);

		Pen.x += Entry.Advance.x;
		Pen.y += Entry.Advance.y;

		PreviousEntry = Entry;
	}

	mWidth = Pen.x / 64;
	mManager->mSolidArray.resize(*this, mGlyphs.size());
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipLeft(float X)
{
	mClipLeft = X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipRight(float X)
{
	mClipRight = X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipBottom(float Y)
{
	mClipBottom = Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipTop(float Y)
{
	mClipTop = Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::draw(Vertex::FillSolidT * Vertices) const
{
	std::int16_t Left = mManager->fitHorizontalGrid(mLeft);
	std::int16_t Bottom = mManager->fitVerticalGrid(mBottom);

	for (std::size_t I = 0, E = mGlyphs.size(); I != E; ++I)
	{
		std::int16_t GlyphLeft = Left + mGlyphs[I].PositionMin.X;
		std::int16_t GlyphRight = Left + mGlyphs[I].PositionMax.X;
		std::int16_t GlyphBottom = Bottom + mGlyphs[I].PositionMin.Y;
		std::int16_t GlyphTop = Bottom + mGlyphs[I].PositionMax.Y;

		std::int16_t ClipLeft = mManager->fitHorizontalGrid(mClipLeft);
		std::int16_t ClipRight = mManager->fitHorizontalGrid(mClipRight);
		std::int16_t ClipBottom = mManager->fitVerticalGrid(mClipBottom);
		std::int16_t ClipTop = mManager->fitVerticalGrid(mClipTop);

		std::int16_t Width = GlyphRight - GlyphLeft;
		std::int16_t Height = GlyphTop - GlyphBottom;

		std::int16_t LeftClipped = GlyphLeft;
		std::int16_t RightClipped = GlyphRight;
		std::int16_t BottomClipped = GlyphBottom;
		std::int16_t TopClipped = GlyphTop;

		LeftClipped = std::max(LeftClipped, ClipLeft);
		RightClipped = std::max(RightClipped, ClipLeft);
		LeftClipped = std::min(LeftClipped, ClipRight);
		RightClipped = std::min(RightClipped, ClipRight);
		BottomClipped = std::max(BottomClipped, ClipBottom);
		TopClipped = std::max(TopClipped, ClipBottom);
		BottomClipped = std::min(BottomClipped, ClipTop);
		TopClipped = std::min(TopClipped, ClipTop);

		Vertices[I].Color = {0, 0, 0, 255};
		Vertices[I].ClipMin.S = (LeftClipped - GlyphLeft) * 65535 / Width;
		Vertices[I].ClipMin.T = (BottomClipped - GlyphBottom) * 65535 / Height;
		Vertices[I].ClipMax.S = (RightClipped - GlyphLeft) * 65535 / Width;
		Vertices[I].ClipMax.T = (TopClipped - GlyphBottom) * 65535 / Height;
		Vertices[I].PositionMin = {LeftClipped, BottomClipped};
		Vertices[I].PositionMax = {RightClipped, TopClipped};
		Vertices[I].TextureSize = mGlyphs[I].TextureSize;
		Vertices[I].Offset = mGlyphs[I].Offset;
	}
}

void LabelT::moveX(float X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::moveY(float Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

float LabelT::getLeft() const
{
	return mLeft;
}

float LabelT::getBottom() const
{
	return mBottom;
}

float LabelT::getRight() const
{
	return mLeft + getBaseWidth();
}

float LabelT::getTop() const
{
	return mBottom + getBaseHeight();
}

float LabelT::getClipLeft() const
{
	return mClipLeft;
}

float LabelT::getClipRight() const
{
	return mClipRight;
}

float LabelT::getClipBottom() const
{
	return mClipBottom;
}

float LabelT::getClipTop() const
{
	return mClipTop;
}

float LabelT::getBaseWidth() const
{
	return mWidth / Settings::Global::HorizontalScale;
}

float LabelT::getBaseHeight() const
{
	return mHeight / Settings::Global::VerticalScale;
}

}
}
