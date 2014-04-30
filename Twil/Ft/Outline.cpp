#include "Outline.hpp"

#include "Library.hpp"
#include "Stroker.hpp"
#include "Data/Memory.hpp"

#include <algorithm>

namespace Twil {
namespace Ft {

OutlineT::OutlineT()
:
	mId{},
	mPointCapacity{0},
	mContourCapacity{0}
{}

void OutlineT::clear()
{
	mId.n_points = 0;
	mId.n_contours = 0;
}

void OutlineT::reverse()
{
	std::reverse(mId.points, mId.points + mId.n_points);
	std::reverse(mId.contours, mId.contours + mId.n_contours);
}

void OutlineT::translate(FT_Pos x, FT_Pos y)
{
	FT_Outline_Translate(&mId, x, y);
}

void OutlineT::transform(FT_Matrix const & Matrix)
{
	FT_Outline_Transform(&mId, &Matrix);
}

void OutlineT::reservePoints(std::uint16_t Num)
{
	if (mPointCapacity >= Num) return;
	auto PointCapacity = mPointCapacity;
	if (PointCapacity == 0) PointCapacity = 1;
	while (PointCapacity < Num) PointCapacity *= 2;

	auto Points = Data::makeUniqueArray<FT_Vector>(PointCapacity);
	auto Tags = Data::makeUniqueArray<char>(PointCapacity);
	std::copy(mId.points, mId.points + mId.n_points, Points.get());
	std::copy(mId.tags, mId.tags + mId.n_points, Tags.get());

	delete[] mId.points;
	delete[] mId.tags;
	mId.points = Points.release();
	mId.tags = Tags.release();
	mPointCapacity = PointCapacity;
}

void OutlineT::reserveContours(std::uint16_t Num)
{
	if (mContourCapacity >= Num) return;
	auto ContourCapacity = mContourCapacity;
	if (ContourCapacity == 0) ContourCapacity = 1;
	while (ContourCapacity < Num) ContourCapacity *= 2;

	auto Contours = Data::makeUniqueArray<FT_Short>(ContourCapacity);
	std::copy(mId.contours, mId.contours + mId.n_contours, Contours.get());

	delete[] mId.contours;
	mId.contours = Contours.release();
	mContourCapacity = ContourCapacity;
}

void OutlineT::beginContour(FT_Vector A)
{
	mA = A;
}

void OutlineT::endContour()
{
	reserveContours(mId.n_contours + 1);
	mId.contours[mId.n_contours] = mId.n_points - 1;
	mId.n_contours = mId.n_contours + 1;
}

void OutlineT::moveLine(FT_Vector B)
{
	reservePoints(mId.n_points + 1);
	mId.points[mId.n_points] = mA;
	mId.tags[mId.n_points] = FT_CURVE_TAG_ON;
	mId.n_points = mId.n_points + 1;
	mA = B;
}

void OutlineT::moveQuadratic(FT_Vector B, FT_Vector C)
{
	reservePoints(mId.n_points + 2);
	mId.points[mId.n_points] = mA;
	mId.tags[mId.n_points] = FT_CURVE_TAG_ON;
	mId.points[mId.n_points + 1] = B;
	mId.tags[mId.n_points + 1] = FT_CURVE_TAG_CONIC;
	mId.n_points = mId.n_points + 2;
	mA = C;
}

void OutlineT::moveCubic(FT_Vector B, FT_Vector C, FT_Vector D)
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

void OutlineT::append(StrokerT const & Stroker, FT_StrokerBorder Border)
{
	FT_UInt NumStrokePoints = 0;
	FT_UInt NumStrokeContours = 0;
	FT_Stroker_GetBorderCounts(Stroker.mId, Border, &NumStrokePoints, &NumStrokeContours);
	reservePoints(mId.n_points + NumStrokePoints);
	reserveContours(mId.n_contours + NumStrokeContours);
	FT_Stroker_ExportBorder(Stroker.mId, Border, &mId);
}

void OutlineT::append(StrokerT const & Stroker)
{
	FT_UInt NumStrokePoints = 0;
	FT_UInt NumStrokeContours = 0;
	FT_Stroker_GetCounts(Stroker.mId, &NumStrokePoints, &NumStrokeContours);
	reservePoints(mId.n_points + NumStrokePoints);
	reserveContours(mId.n_contours + NumStrokeContours);
	FT_Stroker_Export(Stroker.mId, &mId);
}

OutlineT::~OutlineT() noexcept
{
	delete[] mId.points;
	delete[] mId.tags;
	delete[] mId.contours;
}

}
}
