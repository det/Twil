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

	auto PenY = (30 * 64 - Face.getHeight() / 4 - 2 * 64 - 6 * 64) / 2;

	FT_Vector Pen{8 * 64, PenY};
	Theme::GlyphEntry PreviousEntry{}; // Zero-initialize

	for (auto Codepoint : Text) {
		auto Entry = mManager.loadGlyphEntry(Face, Codepoint);

		// Apply characacter pair kerning / Hint advance adjustment
		auto Delta = Face.getKerning(PreviousEntry.Index, Entry.Index);
		if (PreviousEntry.RsbDelta - Entry.LsbDelta >= 32) Delta.x -= 64;
		else if (PreviousEntry.RsbDelta - Entry.LsbDelta < -32) Delta.x += 64;
		Pen.x += Delta.x;
		Pen.y += Delta.y;

		GLshort X = (Pen.x + Entry.Bearings.x) / 64;
		GLshort Y = (Pen.y + Entry.Bearings.y) / 64;
		Vertex::FillSolid Vertex;
		Vertex.Color = {0, 0, 0, 255};
		Vertex.Offset = {GLuint(Entry.Offset)};
		Vertex.Position = {X, Y};
		Vertex.Size = {GLushort(Entry.Size.x), GLushort(Entry.Size.y)};
		mVertices.push_back(Vertex);

		Pen.x += Entry.Advance.x;
		Pen.y += Entry.Advance.y;

		PreviousEntry = Entry;
	}

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
