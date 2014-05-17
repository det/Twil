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

		Ui::PixelT Left = (Pen.x + Entry.Bearings.x) / 64;
		Ui::PixelT Bottom = (Pen.y + Entry.Bearings.y) / 64;
		Ui::PixelT Right = Left + Entry.Width;
		Ui::PixelT Top = Bottom + Entry.Height;

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

void LabelT::setClipLeft(Ui::DipT X)
{
	mClipLeft = X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipRight(Ui::DipT X)
{
	mClipRight = X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipBottom(Ui::DipT Y)
{
	mClipBottom = Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::setClipTop(Ui::DipT Y)
{
	mClipTop = Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::draw(Vertex::FillSolidT * Vertices) const
{
	auto & Manager = mWindow->getThemeManager();

	Ui::PixelT Left = mWindow->convertDipToPixelX(mLeft);
	Ui::PixelT Bottom = mWindow->convertDipToPixelY(mBottom);

	for (std::size_t I = 0, E = mGlyphs.size(); I != E; ++I)
	{
		Ui::PixelT GlyphLeft = Left + mGlyphs[I].PositionMin.X;
		Ui::PixelT GlyphRight = Left + mGlyphs[I].PositionMax.X;
		Ui::PixelT GlyphBottom = Bottom + mGlyphs[I].PositionMin.Y;
		Ui::PixelT GlyphTop = Bottom + mGlyphs[I].PositionMax.Y;

		Ui::PixelT ClipLeft = mWindow->convertDipToPixelX(mClipLeft);
		Ui::PixelT ClipRight = mWindow->convertDipToPixelX(mClipRight);
		Ui::PixelT ClipBottom = mWindow->convertDipToPixelY(mClipBottom);
		Ui::PixelT ClipTop = mWindow->convertDipToPixelY(mClipTop);

		Ui::PixelT Width = GlyphRight - GlyphLeft;
		Ui::PixelT Height = GlyphTop - GlyphBottom;

		Ui::PixelT LeftClipped = GlyphLeft;
		Ui::PixelT RightClipped = GlyphRight;
		Ui::PixelT BottomClipped = GlyphBottom;
		Ui::PixelT TopClipped = GlyphTop;

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

void LabelT::moveX(Ui::DipT X)
{
	mLeft += X;
	mClipLeft += X;
	mClipRight += X;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

void LabelT::moveY(Ui::DipT Y)
{
	mBottom += Y;
	mClipBottom += Y;
	mClipTop += Y;
	mWindow->getThemeManager().mSolidArray.markNeedsRedraw(*this);
}

Ui::DipT LabelT::getLeft() const
{
	return mLeft;
}

Ui::DipT LabelT::getBottom() const
{
	return mBottom;
}

Ui::DipT LabelT::getRight() const
{
	return mLeft + getBaseWidth();
}

Ui::DipT LabelT::getTop() const
{
	return mBottom + getBaseHeight();
}

Ui::DipT LabelT::getClipLeft() const
{
	return mClipLeft;
}

Ui::DipT LabelT::getClipRight() const
{
	return mClipRight;
}

Ui::DipT LabelT::getClipBottom() const
{
	return mClipBottom;
}

Ui::DipT LabelT::getClipTop() const
{
	return mClipTop;
}

Ui::DipT LabelT::getBaseWidth() const
{
	return mWindow->convertPixelToDipX(mWidth);
}

Ui::DipT LabelT::getBaseHeight() const
{
	return mWindow->convertPixelToDipY(mHeight);
}

}
}
