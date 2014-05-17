#include "Label.hpp"

#include "Ui/WindowBase.hpp"

namespace Twil {
namespace Theme {

void LabelT::init(Ui::WindowBaseT & Window)
{
	mWindow = &Window;
	auto & Manager = mWindow->getThemeManager();
	Manager.mSolidArray.allocate(*this, 0);
	mHeight = Manager.mLabelSize.getHeight() / 64;
}

void LabelT::setText(std::u32string const & Text)
{
	auto & Manager = mWindow->getThemeManager();

	mGlyphs.clear();
	auto & Face = Manager.mLabelFace;
	Face.setActiveSize(Manager.mLabelSize);

	FT_Vector Pen{0, -Manager.mLabelSize.getDescender()};
	GlyphEntryT PreviousEntry{};

	for (auto Codepoint : Text)
	{
		auto Entry = Manager.loadGlyphEntry(Face, Codepoint);

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
	Manager.mSolidArray.resize(*this, mGlyphs.size());
	Manager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipLeft(std::int32_t X)
{
	mClipLeft = X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipRight(std::int32_t X)
{
	mClipRight = X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipBottom(std::int32_t Y)
{
	mClipBottom = Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipTop(std::int32_t Y)
{
	mClipTop = Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::draw(Vertex::FillSolidT * Vertices) const
{
	auto & Manager = mWindow->getThemeManager();

	std::int16_t Left = mWindow->convertDipToPixelX(mLeft);
	std::int16_t Bottom = mWindow->convertDipToPixelY(mBottom);

	for (std::size_t I = 0, E = mGlyphs.size(); I != E; ++I)
	{
		std::int16_t GlyphLeft = Left + mGlyphs[I].PositionMin.X;
		std::int16_t GlyphRight = Left + mGlyphs[I].PositionMax.X;
		std::int16_t GlyphBottom = Bottom + mGlyphs[I].PositionMin.Y;
		std::int16_t GlyphTop = Bottom + mGlyphs[I].PositionMax.Y;

		std::int16_t ClipLeft = mWindow->convertDipToPixelX(mClipLeft);
		std::int16_t ClipRight = mWindow->convertDipToPixelX(mClipRight);
		std::int16_t ClipBottom = mWindow->convertDipToPixelY(mClipBottom);
		std::int16_t ClipTop = mWindow->convertDipToPixelY(mClipTop);

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

void LabelT::moveX(std::int32_t X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::moveY(std::int32_t Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

std::int32_t LabelT::getLeft() const
{
	return mLeft;
}

std::int32_t LabelT::getBottom() const
{
	return mBottom;
}

std::int32_t LabelT::getRight() const
{
	return mLeft + getBaseWidth();
}

std::int32_t LabelT::getTop() const
{
	return mBottom + getBaseHeight();
}

std::int32_t LabelT::getClipLeft() const
{
	return mClipLeft;
}

std::int32_t LabelT::getClipRight() const
{
	return mClipRight;
}

std::int32_t LabelT::getClipBottom() const
{
	return mClipBottom;
}

std::int32_t LabelT::getClipTop() const
{
	return mClipTop;
}

std::int32_t LabelT::getBaseWidth() const
{
	return mWindow->convertPixelToDipX(mWidth);
}

std::int32_t LabelT::getBaseHeight() const
{
	return mWindow->convertPixelToDipY(mHeight);
}

}
}
