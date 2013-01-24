#include "Label.hpp"

#include "Manager.hpp"

#include <iostream>

namespace Twil {
namespace Theme {

LabelT::LabelT(ManagerT & Manager) :
	mManager(Manager) // Gcc bug prevents brace initialization syntax here
{}

void LabelT::setText(std::u32string const & Text)
{
	mVertices.clear();
	auto & Face = mManager.mLabelFace;
	Face.setActiveSize(mManager.mLabelSize);

	FT_Vector Pen{0, -mManager.mLabelSize.getDescender()};
	GlyphEntryT PreviousEntry{}; // Zero-initialize

	for (auto Codepoint : Text) {
		auto Entry = mManager.loadGlyphEntry(Face, Codepoint);

		// We will hit a divide by 0 in clipping without this check
		if (Entry.Width == 0 || Entry.Height == 0) continue;

		// Apply characacter pair kerning / Hint advance adjustment
		auto Delta = Face.getKerning(PreviousEntry.Index, Entry.Index);
		if (PreviousEntry.RsbDelta - Entry.LsbDelta >= 32) Delta.x -= 64;
		else if (PreviousEntry.RsbDelta - Entry.LsbDelta < -32) Delta.x += 64;
		Pen.x += Delta.x;
		Pen.y += Delta.y;

		GLshort Left = mLeft + (Pen.x + Entry.Bearings.x) / 64;
		GLshort Bottom = mBottom + (Pen.y + Entry.Bearings.y) / 64;
		GLshort Right = Left + Entry.Width;
		GLshort Top = Bottom + Entry.Height;
		Vertex::FillSolidT Vertex;
		Vertex.Color = {0, 0, 0, 255};
		Vertex.PositionMin = {Left, Bottom};
		Vertex.PositionMax = {Right, Top};
		Vertex.TextureSize = {Entry.Width, Entry.Height};
		Vertex.ClipMin = {Left, Bottom};
		Vertex.ClipMax = {Left, Bottom};
		Vertex.Offset = {Entry.Offset};
		mVertices.push_back(Vertex);

		Pen.x += Entry.Advance.x;
		Pen.y += Entry.Advance.y;

		PreviousEntry = Entry;
	}

	mRight = mLeft + Pen.x / 64;
	mTop = mBottom + mManager.mLabelSize.getHeight() / 64;
}

void LabelT::setClipLeft(signed short X)
{
	mClipLeft = X;
	for (auto & Vertex : mVertices) {
		Vertex.ClipMin.X = X;
		Vertex.ClipMin.X = std::max<signed short>(Vertex.ClipMin.X, Vertex.PositionMin.X);
		Vertex.ClipMin.X = std::min<signed short>(Vertex.ClipMin.X, Vertex.PositionMax.X);
	}
}

void LabelT::setClipRight(signed short X)
{
	mClipRight = X;
	for (auto & Vertex : mVertices) {
		Vertex.ClipMax.X = X;
		Vertex.ClipMax.X = std::max<signed short>(Vertex.ClipMax.X, Vertex.PositionMin.X);
		Vertex.ClipMax.X = std::min<signed short>(Vertex.ClipMax.X, Vertex.PositionMax.X);
	}
}

void LabelT::setClipBottom(signed short Y)
{
	mClipBottom = Y;
	for (auto & Vertex : mVertices) {
		Vertex.ClipMin.Y = Y;
		Vertex.ClipMin.Y = std::max<signed short>(Vertex.ClipMin.Y, Vertex.PositionMin.Y);
		Vertex.ClipMin.Y = std::min<signed short>(Vertex.ClipMin.Y, Vertex.PositionMax.Y);
	}
}

void LabelT::setClipTop(signed short Y)
{
	mClipTop = Y;
	for (auto & Vertex : mVertices) {
		Vertex.ClipMax.Y = Y;
		Vertex.ClipMax.Y = std::max<signed short>(Vertex.ClipMax.Y, Vertex.PositionMin.Y);
		Vertex.ClipMax.Y = std::min<signed short>(Vertex.ClipMax.Y, Vertex.PositionMax.Y);
	}
}

void LabelT::draw() const
{
	if (mClipLeft > mClipRight || mClipBottom > mClipTop) return;
	mManager.mSolidArray.queue(mVertices);
}

void LabelT::moveX(signed short X)
{
	mLeft += X;
	mRight += X;
	mClipLeft += X;
	mClipRight += X;

	for (auto & Vertex : mVertices)	{
		Vertex.PositionMin.X += X;
		Vertex.PositionMax.X += X;
		Vertex.ClipMin.X += X;
		Vertex.ClipMax.X += X;
	}
}

void LabelT::moveY(signed short Y)
{
	mBottom += Y;
	mTop += Y;
	mClipBottom += Y;
	mClipTop += Y;

	for (auto & Vertex : mVertices) {
		Vertex.PositionMin.Y += Y;
		Vertex.PositionMax.Y += Y;
		Vertex.ClipMin.Y += Y;
		Vertex.ClipMax.Y += Y;
	}
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
	return mRight;
}

signed short LabelT::getTop() const
{
	return mTop;
}

signed short LabelT::getBaseWidth() const
{
	return mRight - mLeft;
}

signed short LabelT::getBaseHeight() const
{
	return mManager.mLabelSize.getHeight() / 64;
}

}
}
