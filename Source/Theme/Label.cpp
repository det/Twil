#include "Label.hpp"

#include "Manager.hpp"

namespace Twil {
namespace Theme {

LabelT::LabelT(ManagerT & Manager) :
	mManager(Manager) // Gcc bug prevents brace initialization syntax here
{
	mManager.mSolidArray.allocate(*this, 0);
	mHeight = mManager.mLabelSize.getHeight() / 64;
}

void LabelT::setText(std::u32string const & Text)
{
	mGlyphs.clear();
	auto & Face = mManager.mLabelFace;
	Face.setActiveSize(mManager.mLabelSize);

	FT_Vector Pen{0, -mManager.mLabelSize.getDescender()};
	GlyphEntryT PreviousEntry{}; // Zero-initialize

	for (auto Codepoint : Text) {
		auto Entry = mManager.loadGlyphEntry(Face, Codepoint);

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
	mManager.mSolidArray.resize(*this, mGlyphs.size());
	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipLeft(signed short X)
{
	mClipLeft = X;
	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipRight(signed short X)
{
	mClipRight = X;
	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipTop(signed short Y)
{
	mClipTop = Y;
	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::draw(Vertex::FillSolidT * Vertices) const
{
	for (std::size_t I = 0, E = mGlyphs.size(); I != E; ++I) {
		signed short PositionLeft = mLeft + mGlyphs[I].PositionMin.X;
		signed short PositionRight = mLeft + mGlyphs[I].PositionMax.X;
		signed short PositionBottom = mBottom + mGlyphs[I].PositionMin.Y;
		signed short PositionTop = mBottom + mGlyphs[I].PositionMax.Y;

		signed short Width = PositionRight - PositionLeft;
		signed short Height = PositionTop - PositionBottom;

		signed short ClipLeft = PositionLeft;
		signed short ClipRight = PositionRight;
		signed short ClipBottom = PositionBottom;
		signed short ClipTop = PositionTop;

		ClipLeft = std::max<signed short>(ClipLeft, mClipLeft);
		ClipRight = std::max<signed short>(ClipRight, mClipLeft);
		ClipLeft = std::min<signed short>(ClipLeft, mClipRight);
		ClipRight = std::min<signed short>(ClipRight, mClipRight);
		ClipBottom = std::max<signed short>(ClipBottom, mClipBottom);
		ClipTop = std::max<signed short>(ClipTop, mClipBottom);
		ClipBottom = std::min<signed short>(ClipBottom, mClipTop);
		ClipTop = std::min<signed short>(ClipTop, mClipTop);

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

void LabelT::moveX(signed short X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;

	mManager.mSolidArray.markNeedsRedraw(*this);
}

void LabelT::moveY(signed short Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;

	mManager.mSolidArray.markNeedsRedraw(*this);
}

signed short LabelT::getLeft() const
{
	return mLeft;
}

signed short LabelT::getBottom() const
{
	return mBottom;
}

signed short LabelT::getRight() const
{
	return mLeft + mWidth;
}

signed short LabelT::getTop() const
{
	return mBottom + mHeight;
}

signed short LabelT::getBaseWidth() const
{
	return mWidth;
}

signed short LabelT::getBaseHeight() const
{
	return mHeight;
}

}
}
