#pragma once

#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include FT_STROKER_H

namespace Twil {
namespace Ft {

class BitmapT;
class LibraryT;
class Path;
class StrokerT;

/// \brief A FreeType outline.
///
/// Represents a set of closed paths comprised of lines and bezier curves. Can be rendered into a
/// Twil::Ft::Bitmap.
class OutlineT
{
	friend class BitmapT;
	friend class StrokerT;

	OutlineT(OutlineT const &) = delete;
	OutlineT & operator =(OutlineT const &) = delete;

private:
	FT_Outline mId;
	FT_Vector mA;
	std::uint16_t mPointCapacity;
	std::uint16_t mContourCapacity;

public:
	OutlineT();
	~OutlineT() noexcept;

	/// \brief Reserve enough space to hold an amount of points
	void reservePoints(std::uint16_t Size);

	/// \brief Reserve enough space to hold an amount of contours
	void reserveContours(std::uint16_t Size);

	/// \brief Clear all points and contours
	void clear();

	/// \brief Reverse all points and contours.
	void reverse();

	/// \brief Add values to each point.
	void translate(FT_Pos X, FT_Pos Y);

	/// \brief Multiply each point by a matrix.
	void transform(FT_Matrix const & Matrix);

	/// \brief Begin a new contour.
	///
	/// Behaviour is undefined if not terminated with endPath.
	/// \param A The starting point.
	void beginContour(FT_Vector A);

	/// \brief End a contour
	void endContour();

	/// \brief Move the contour in a line.
	void moveLine(FT_Vector B);

	/// \brief Move the contour in a quadratic bezier curve.
	void moveQuadratic(FT_Vector B, FT_Vector C);

	/// \brief Move the contour in a cubic bezier curve.
	void moveCubic(FT_Vector B, FT_Vector C, FT_Vector D);

	/// \brief Append one side of a stroke.
	///
	/// \param Border Selects which side of the stroke to append.
	void append(StrokerT const & Stroker, FT_StrokerBorder Border);

	/// \brief Append both sides of a stroke.
	void append(StrokerT const & Stroker);
};

}
}
