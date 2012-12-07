#include "Ft/Outline.hpp"

#include "Ft/Library.hpp"
#include "Ft/Stroker.hpp"

#include <iostream>

namespace Twil {
namespace Ft {

Outline::Outline(Ft::Library const & Library) :
	mLibrary{Library},
	mId{}, // zero-initialize
	mPointCapacity{0},
	mContourCapacity{0}
{
}

void Outline::clear()
{
	mId.n_points = 0;
	mId.n_contours = 0;
}

void Outline::reverse()
{
	std::reverse(mId.points, mId.points + mId.n_points);
	std::reverse(mId.contours, mId.contours + mId.n_contours);
}

void Outline::translate(FT_Pos x, FT_Pos y)
{
	FT_Outline_Translate(&mId, x, y);
}

void Outline::transform(FT_Matrix const & Matrix)
{
	FT_Outline_Transform(&mId, &Matrix);
}

void Outline::reservePoints(short Num)
{
	if (mPointCapacity >= Num) return;
	if (mPointCapacity == 0) mPointCapacity = 1;
	while (mPointCapacity < Num) mPointCapacity *= 2;

	auto Points = new FT_Vector[mPointCapacity];
	std::copy(mId.points, mId.points + mId.n_points, Points);
	delete[] mId.points;
	mId.points = Points;

	auto Tags = new char[mPointCapacity];
	std::copy(mId.tags, mId.tags + mId.n_points, Tags);
	delete[] mId.tags;
	mId.tags = Tags;
}

void Outline::reserveContours(short Num)
{
	if (mContourCapacity >= Num) return;
	if (mContourCapacity == 0) mContourCapacity = 1;
	while (mContourCapacity < Num) mContourCapacity *= 2;

	auto Contours = new short[mContourCapacity];
	std::copy(mId.contours, mId.contours + mId.n_contours, Contours);
	delete[] mId.contours;
	mId.contours = Contours;
}

void Outline::beginPath(FT_Vector A)
{
	mA = A;
}

void Outline::endPath()
{
	reserveContours(mId.n_contours + 1);
	mId.contours[mId.n_contours] = mId.n_points - 1;
	mId.n_contours = mId.n_contours + 1;
}

void Outline::addLine(FT_Vector B)
{
	reservePoints(mId.n_points + 1);
	mId.points[mId.n_points] = mA;
	mId.tags[mId.n_points] = FT_CURVE_TAG_ON;
	mId.n_points = mId.n_points + 1;
	mA = B;
}

void Outline::addQuadratic(FT_Vector B, FT_Vector C)
{
	reservePoints(mId.n_points + 2);
	mId.points[mId.n_points] = mA;
	mId.tags[mId.n_points] = FT_CURVE_TAG_ON;
	mId.points[mId.n_points + 1] = B;
	mId.tags[mId.n_points + 1] = FT_CURVE_TAG_CONIC;
	mId.n_points = mId.n_points + 2;
	mA = C;
}

void Outline::addCubic(FT_Vector B, FT_Vector C, FT_Vector D)
{
	reservePoints(mId.n_points + 3);
	mId.points[mId.n_points] = mA;
	mId.tags[mId.n_points] = FT_CURVE_TAG_ON;
	mId.points[mId.n_points + 1] = B;
	mId.tags[mId.n_points + 1] = FT_CURVE_TAG_CUBIC;
	mId.points[mId.n_points + 2] = C;
	mId.tags[mId.n_points + 2] = FT_CURVE_TAG_CUBIC;
	mId.n_points = mId.n_points + 3;
	mA = D;
}

void Outline::add(Stroker const & Stroker, FT_StrokerBorder Border)
{

	FT_UInt NumStrokePoints = 0;
	FT_UInt NumStrokeContours = 0;
	FT_Stroker_GetBorderCounts(Stroker.mId, Border, &NumStrokePoints, &NumStrokeContours);
	reservePoints(mId.n_points + NumStrokePoints);
	reserveContours(mId.n_contours + NumStrokeContours);
	FT_Stroker_ExportBorder(Stroker.mId, Border, &mId);
}

void Outline::add(Stroker const & Stroker)
{

	FT_UInt NumStrokePoints = 0;
	FT_UInt NumStrokeContours = 0;
	FT_Stroker_GetCounts(Stroker.mId, &NumStrokePoints, &NumStrokeContours);
	reservePoints(mId.n_points + NumStrokePoints);
	reserveContours(mId.n_contours + NumStrokeContours);
	FT_Stroker_Export(Stroker.mId, &mId);
}

Outline::~Outline()
{
	delete[] mId.points;
	delete[] mId.tags;
	delete[] mId.contours;
}

void Outline::stroke(Ft::Stroker & Stroker)
{
	Stroker.set(*this);
	add(Stroker);
}

}
}
