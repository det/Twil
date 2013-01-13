#include "Theme/Label.hpp"

#include "Theme/Manager.hpp"

namespace Twil {
namespace Theme {

Label::Label(Theme::Manager & Manager) :
	mManager(Manager) // Gcc bug prevents brace initialization syntax here
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
		Vertex.ClipMin = {0, 0};
		Vertex.ClipMax = {0, 0};
		mVertices.push_back(Vertex);

		Pen.x += Entry.Advance.x;
		Pen.y += Entry.Advance.y;

		PreviousEntry = Entry;
	}

	mWidth = Pen.x / 64;
	mHeight = mManager.mLabelSize.getHeight() / 64;
}

void Label::setClipX(signed short Min, signed short Max)
{
	for (auto & Vertex : mVertices) {
		signed short Left = Vertex.Position.X - mX;
		signed short Right = Left + Vertex.Size.Width;

		if (Right > Max) {
			if (Left > Max) Vertex.ClipMax.Width = Vertex.Size.Width;
			else Vertex.ClipMax.Width = Right - Max;
		}
		else Vertex.ClipMax.Width = 0;

		if (Left < Min) {
			if (Right < Min) Vertex.ClipMin.Width = Vertex.Size.Width;
			else Vertex.ClipMin.Width = Min - Left;
		}
		else Vertex.ClipMin.Width = 0;
	}
}
void Label::setClipY(signed short Min, signed short Max)
{
	for (auto & Vertex : mVertices) {
		signed short Bottom = Vertex.Position.Y - mY;
		signed short Top = Bottom + Vertex.Size.Height;

		if (Top > Max) {
			if (Bottom > Max) Vertex.ClipMax.Height = Vertex.Size.Height;
			else Vertex.ClipMax.Height = Top - Max;
		}
		else Vertex.ClipMax.Height = 0;

		if (Bottom < Min) {
			if (Top < Min) Vertex.ClipMin.Height = Vertex.Size.Height;
			else Vertex.ClipMin.Height = Min - Bottom;
		}
		else Vertex.ClipMin.Height = 0;
	}
}

void Label::setX(signed short X)
{
	auto DeltaX = X - mX;
	mX = X;
	for (auto & Vertex : mVertices) Vertex.Position.X += DeltaX;
}

void Label::setY(signed short Y)
{
	auto DeltaY = Y - mY;
	mY = Y;
	for (auto & Vertex : mVertices) Vertex.Position.Y += DeltaY;
}

void Label::render()
{
	mManager.mSolidArray.add(mVertices);
}

signed short Label::getX()
{
	return mX;
}

signed short Label::getY()
{
	return mY;
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
