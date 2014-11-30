#pragma once

#include "stroker.hxx"

#include "face.hxx"
#include "library.hxx"
#include "outline.hxx"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace twil {
namespace ft {

/// \brief A FreeType Stroker.
///
/// Represents a stroke of a set of open or closed paths comprised of lines and bezier curves. Can
/// be rendered into a twil::Ft::Bitmap.
class Stroker
{
	friend Outline;

	Stroker(Stroker const &) = delete;
	Stroker & operator =(Stroker const &) = delete;

private:
	FT_Stroker id_;

public:
	Stroker(Library &);
	~Stroker() noexcept;

	/// \returns Clear all contours.
	void Clear();

	/// \brief Set rendering options
	///
	/// \param radius The distance to each side of the stroke in 26.6 fix point.
	/// \param line_cap The style to use when capping open paths.
	/// \param line_join The style the use when joining lines.
	/// \param miter_limit TODO: document this
	void SetOptions(
		FT_Fixed radius, FT_Stroker_LineCap line_cap,
		FT_Stroker_LineJoin line_join, FT_Fixed miter_limit);

	/// \brief Begin a new contour.
	///
	/// Behaviour is undefined if not terminated with endPath.
	/// \param a The starting point.
	/// \param is_open Sets if the contour is open or closed.
	void BeginContour(FT_Vector a, FT_Bool is_open = false);

	/// \brief End a contour.
	void EndContour();

	/// \brief Move the contour in a line.
	void MoveLine(FT_Vector);

	/// \brief Move the contour in a quadratic bezier curve.
	void MoveQuadratic(FT_Vector, FT_Vector);

	/// \brief Move the contour in a cubic bezier curve.
	void MoveCubic(FT_Vector, FT_Vector, FT_Vector);

	/// \brief Clear all contours and add the contours of an outline.
	void Set(Outline &);

	/// \brief Clear all contours and add the contours of a face.
	void Set(Face &);
};

}
}
