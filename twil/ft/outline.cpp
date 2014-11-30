#include "outline.hpp"

#include "library.hpp"
#include "stroker.hpp"

#include <algorithm>
#include <memory>

namespace twil {
namespace ft {

Outline::Outline()
:
	id_{},
	point_capacity_{0},
	contour_capacity_{0}
{}

void Outline::Clear()
{
	id_.n_points = 0;
	id_.n_contours = 0;
}

void Outline::Reverse()
{
	std::reverse(id_.points, id_.points + id_.n_points);
	std::reverse(id_.contours, id_.contours + id_.n_contours);
}

void Outline::Translate(FT_Pos x, FT_Pos y)
{
	FT_Outline_Translate(&id_, x, y);
}

void Outline::Transform(FT_Matrix const & matrix)
{
	FT_Outline_Transform(&id_, &matrix);
}

void Outline::ReservePoints(std::uint16_t num)
{
	if (point_capacity_ >= num) return;
	auto point_capacity = point_capacity_;
	if (point_capacity == 0) point_capacity = 1;
	while (point_capacity < num) point_capacity *= 2;

	std::unique_ptr<FT_Vector[]> points{new FT_Vector[point_capacity]};
	std::unique_ptr<char> tags{new char[point_capacity]};
	std::copy(id_.points, id_.points + id_.n_points, points.get());
	std::copy(id_.tags, id_.tags + id_.n_points, tags.get());

	delete[] id_.points;
	delete[] id_.tags;
	id_.points = points.release();
	id_.tags = tags.release();
	point_capacity_ = point_capacity;
}

void Outline::ReserveContours(std::uint16_t num)
{
	if (contour_capacity_ >= num) return;
	auto contour_capacity = contour_capacity_;
	if (contour_capacity == 0) contour_capacity = 1;
	while (contour_capacity < num) contour_capacity *= 2;

	std::unique_ptr<FT_Short[]> contours{new FT_Short[contour_capacity]};
	std::copy(id_.contours, id_.contours + id_.n_contours, contours.get());

	delete[] id_.contours;
	id_.contours = contours.release();
	contour_capacity_ = contour_capacity;
}

void Outline::BeginContour(FT_Vector a)
{
	a_ = a;
}

void Outline::EndContour()
{
	ReserveContours(id_.n_contours + 1);
	id_.contours[id_.n_contours] = id_.n_points - 1;
	id_.n_contours = id_.n_contours + 1;
}

void Outline::MoveLine(FT_Vector b)
{
	ReservePoints(id_.n_points + 1);
	id_.points[id_.n_points] = a_;
	id_.tags[id_.n_points] = FT_CURVE_TAG_ON;
	id_.n_points = id_.n_points + 1;
	a_ = b;
}

void Outline::MoveQuadratic(FT_Vector b, FT_Vector c)
{
	ReservePoints(id_.n_points + 2);
	id_.points[id_.n_points] = a_;
	id_.tags[id_.n_points] = FT_CURVE_TAG_ON;
	id_.points[id_.n_points + 1] = b;
	id_.tags[id_.n_points + 1] = FT_CURVE_TAG_CONIC;
	id_.n_points = id_.n_points + 2;
	a_ = c;
}

void Outline::MoveCubic(FT_Vector b, FT_Vector c, FT_Vector d)
{
	ReservePoints(id_.n_points + 3);
	id_.points[id_.n_points] = a_;
	id_.tags[id_.n_points] = FT_CURVE_TAG_ON;
	id_.points[id_.n_points + 1] = b;
	id_.tags[id_.n_points + 1] = FT_CURVE_TAG_CUBIC;
	id_.points[id_.n_points + 2] = c;
	id_.tags[id_.n_points + 2] = FT_CURVE_TAG_CUBIC;
	id_.n_points = id_.n_points + 3;
	a_ = d;
}

void Outline::Append(Stroker const & stroker, FT_StrokerBorder border)
{
	FT_UInt num_stroke_points = 0;
	FT_UInt num_stroke_contours = 0;
	FT_Stroker_GetBorderCounts(stroker.id_, border, &num_stroke_points, &num_stroke_contours);
	ReservePoints(id_.n_points + num_stroke_points);
	ReserveContours(id_.n_contours + num_stroke_contours);
	FT_Stroker_ExportBorder(stroker.id_, border, &id_);
}

void Outline::Append(Stroker const & stroker)
{
	FT_UInt num_stroke_points = 0;
	FT_UInt num_stroke_contours = 0;
	FT_Stroker_GetCounts(stroker.id_, &num_stroke_points, &num_stroke_contours);
	ReservePoints(id_.n_points + num_stroke_points);
	ReserveContours(id_.n_contours + num_stroke_contours);
	FT_Stroker_Export(stroker.id_, &id_);
}

Outline::~Outline() noexcept
{
	delete[] id_.points;
	delete[] id_.tags;
	delete[] id_.contours;
}

}
}
