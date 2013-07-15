#include "Label.hpp"

#include "Manager.hpp"

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

		GLshort Left = (Pen.x + Entry.Bearings.x) / 64;
		GLshort Bottom = (Pen.y + Entry.Bearings.y) / 64;
		GLshort Right = Left + Entry.Width;
		GLshort Top = Bottom + Entry.Height;

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

void LabelT::setClipLeft(std::int16_t X)
{
	mClipLeft = X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipRight(std::int16_t X)
{
	mClipRight = X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipBottom(std::int16_t Y)
{
	mClipBottom = Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipTop(std::int16_t Y)
{
	mClipTop = Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::draw(Vertex::FillSolidT * Vertices) const
{
	for (std::size_t I = 0, E = mGlyphs.size(); I != E; ++I)
	{
		std::int16_t PositionLeft = mLeft + mGlyphs[I].PositionMin.X;
		std::int16_t PositionRight = mLeft + mGlyphs[I].PositionMax.X;
		std::int16_t PositionBottom = mBottom + mGlyphs[I].PositionMin.Y;
		std::int16_t PositionTop = mBottom + mGlyphs[I].PositionMax.Y;

		std::int16_t Width = PositionRight - PositionLeft;
		std::int16_t Height = PositionTop - PositionBottom;

		std::int16_t ClipLeft = PositionLeft;
		std::int16_t ClipRight = PositionRight;
		std::int16_t ClipBottom = PositionBottom;
		std::int16_t ClipTop = PositionTop;

		ClipLeft = std::max<std::int16_t>(ClipLeft, mClipLeft);
		ClipRight = std::max<std::int16_t>(ClipRight, mClipLeft);
		ClipLeft = std::min<std::int16_t>(ClipLeft, mClipRight);
		ClipRight = std::min<std::int16_t>(ClipRight, mClipRight);
		ClipBottom = std::max<std::int16_t>(ClipBottom, mClipBottom);
		ClipTop = std::max<std::int16_t>(ClipTop, mClipBottom);
		ClipBottom = std::min<std::int16_t>(ClipBottom, mClipTop);
		ClipTop = std::min<std::int16_t>(ClipTop, mClipTop);

		Vertices[I].Color = {0, 0, 0, 255};
		Vertices[I].ClipMin.S = (ClipLeft - PositionLeft) * 65535 / Width;
		Vertices[I].ClipMin.T = (ClipBottom - PositionBottom) * 65535 / Height;
		Vertices[I].ClipMax.S = (ClipRight - PositionLeft) * 65535 / Width;
		Vertices[I].ClipMax.T = (ClipTop - PositionBottom) * 65535 / Height;
		Vertices[I].PositionMin = {ClipLeft, ClipBottom};
		Vertices[I].PositionMax = {ClipRight, ClipTop};
		Vertices[I].TextureSize = mGlyphs[I].TextureSize;
		Vertices[I].Offset = mGlyphs[I].Offset;
	}	
}

void LabelT::moveX(std::int16_t X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

void LabelT::moveY(std::int16_t Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mManager->mSolidArray.markNeedsRedraw(*this);
}

std::int16_t LabelT::getLeft() const
{
	return mLeft;
}

std::int16_t LabelT::getBottom() const
{
	return mBottom;
}

std::int16_t LabelT::getRight() const
{
	return mLeft + mWidth;
}

std::int16_t LabelT::getTop() const
{
	return mBottom + mHeight;
}

std::int16_t LabelT::getClipLeft() const
{
	return mClipLeft;
}

std::int16_t LabelT::getClipRight() const
{
	return mClipRight;
}

std::int16_t LabelT::getClipBottom() const
{
	return mClipBottom;
}

std::int16_t LabelT::getClipTop() const
{
	return mClipTop;
}

std::int16_t LabelT::getBaseWidth() const
{
	return mWidth;
}

std::int16_t LabelT::getBaseHeight() const
{
	return mHeight;
}

}
}
