#include "Theme/Label.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Theme {

Label::Label(Theme::Manager & Manager) :
	mManager{Manager}
{}

void Label::setText(std::u32string const & Text)
{
	mVertices.clear();
	auto & Face = mManager.mLabelFace;
	Face.setActiveSize(mManager.mLabelSize);

	FT_Vector Pen{0, -mManager.mLabelSize.getDescender()};
	Theme::GlyphEntry PreviousEntry{}; // Zero-initialize

	for (auto Codepoint : Text) {
		auto Entry = mManager.loadGlyphEntry(Face, Codepoint);

		// Apply characacter pair kerning / Hint advance adjustment
		auto Delta = Face.getKerning(PreviousEntry.Index, Entry.Index);
		if (PreviousEntry.RsbDelta - Entry.LsbDelta >= 32) Delta.x -= 64;
		else if (PreviousEntry.RsbDelta - Entry.LsbDelta < -32) Delta.x += 64;
		Pen.x += Delta.x;
		Pen.y += Delta.y;

		GLshort X = mX + (Pen.x + Entry.Bearings.x) / 64;
		GLshort Y = mY + (Pen.y + Entry.Bearings.y) / 64;
		Vertex::FillSolid Vertex;
		Vertex.Color = {0, 0, 0, 255};
		Vertex.Offset = {Entry.Offset};
		Vertex.Position = {X, Y};
		Vertex.Size = {Entry.Width, Entry.Height};
		mVertices.push_back(Vertex);

		Pen.x += Entry.Advance.x;
		Pen.y += Entry.Advance.y;

		PreviousEntry = Entry;
	}

	mWidth = Pen.x / 64;
	mHeight = mManager.mLabelSize.getHeight() / 64;
}

void Label::move(signed short X, signed short Y)
{
	auto DeltaX = X - mX;
	auto DeltaY = Y - mY;

	for (auto & Vertex : mVertices) {
		Vertex.Position.X += DeltaX;
		Vertex.Position.Y += DeltaY;
	}

	mX = X;
	mY = Y;
}

void Label::render()
{
	mManager.mSolidArray.add(mVertices);
}

unsigned short Label::getWidth()
{
	return mWidth;
}

unsigned short Label::getHeight()
{
	return mHeight;
}

}
}
