#pragma once

#include "outline.hxx"

#include "bitmap.hxx"
#include "library.hxx"
#include "stroker.hxx"

#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H

namespace twil {
namespace ft {

/// \brief A FreeType outline.
///
/// Represents a set of closed paths comprised of lines and bezier curves. Can be rendered into a
/// twil::Ft::Bitmap.
class Outline
{
	friend Bitmap;
	friend Stroker;

	Outline(Outline const &) = delete;
	Outline & operator =(Outline const &) = delete;

private:
	FT_Outline id_;
	FT_Vector a_;
	std::uint16_t point_capacity_;
	std::uint16_t contour_capacity_;

public:
	Outline();
	~Outline() noexcept;

	/// \brief Reserve enough space to hold an amount of points
	void ReservePoints(std::uint16_t size);

	/// \brief Reserve enough space to hold an amount of contours
	void ReserveContours(std::uint16_t size);

	/// \brief Clear all points and contours
	void Clear();

	/// \brief Reverse all points and contours.
	void Reverse();

	/// \brief Add values to each point.
	void Translate(FT_Pos x, FT_Pos y);

	/// \brief Multiply each point by a matrix.
	void Transform(FT_Matrix const & matrix);

	/// \brief Begin a new contour.
	///
	/// Behaviour is undefined if not terminated with endPath.
	/// \param a The starting point.
	void BeginContour(FT_Vector a);

	/// \brief End a contour
	void EndContour();

	/// \brief Move the contour in a line.
	void MoveLine(FT_Vector b);

	/// \brief Move the contour in a quadratic bezier curve.
	void MoveQuadratic(FT_Vector b, FT_Vector c);

	/// \brief Move the contour in a cubic bezier curve.
	void MoveCubic(FT_Vector b, FT_Vector c, FT_Vector d);

	/// \brief Append one side of a stroke.
	///
	/// \param border Selects which side of the stroke to append.
	void Append(Stroker const & stroker, FT_StrokerBorder border);

	/// \brief Append both sides of a stroke.
	void Append(Stroker const & stroker);
};

}
}
