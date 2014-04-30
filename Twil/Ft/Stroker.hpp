#pragma once

#include "StrokerFwd.hpp"

#include "FaceFwd.hpp"
#include "LibraryFwd.hpp"
#include "OutlineFwd.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

namespace Twil {
namespace Ft {

/// \brief A FreeType Stroker.
///
/// Represents a stroke of a set of open or closed paths comprised of lines and bezier curves. Can
/// be rendered into a Twil::Ft::Bitmap.
class StrokerT
{
	friend class OutlineT;

	StrokerT(StrokerT const &) = delete;
	StrokerT & operator =(StrokerT const &) = delete;

private:
	FT_Stroker mId;

public:
	StrokerT(LibraryT &);
	~StrokerT() noexcept;

	/// \returns Clear all contours.
	void clear();

	/// \brief Set rendering options
	///
	/// \param Radius The distance to each side of the stroke in 26.6 fix point.
	/// \param LineCap The style to use when capping open paths.
	/// \param LineJoin The style the use when joining lines.
	/// \param MiterLimit TODO: document this
	void setOptions(FT_Fixed Radius, FT_Stroker_LineCap LineCap, FT_Stroker_LineJoin LineJoin,
		FT_Fixed MiterLimit);

	/// \brief Begin a new contour.
	///
	/// Behaviour is undefined if not terminated with endPath.
	/// \param A The starting point.
	/// \param IsOpen Sets if the contour is open or closed.
	void beginContour(FT_Vector A, FT_Bool IsOpen = false);

	/// \brief End a contour.
	void endContour();

	/// \brief Move the contour in a line.
	void moveLine(FT_Vector);

	/// \brief Move the contour in a quadratic bezier curve.
	void moveQuadratic(FT_Vector, FT_Vector);

	/// \brief Move the contour in a cubic bezier curve.
	void moveCubic(FT_Vector, FT_Vector, FT_Vector);

	/// \brief Clear all contours and add the contours of an outline.
	void set(OutlineT &);

	/// \brief Clear all contours and add the contours of a face.
	void set(FaceT &);
};

}
}
