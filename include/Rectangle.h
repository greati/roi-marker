#ifndef _RECTANGLE_
#define _RECTANGLE_

#include "Point.h"

namespace roi {

class Rectangle {
	public:
		// Upper left corner
		roi::Point ulc;
		// Down right corner
		roi::Point drc;

		/**
		 * Constructor which creates the Rectangle
		 * from two roi::Point.
		 *
		 * */
		Rectangle(const roi::Point & ulc_, const roi::Point & drc_) : ulc {ulc_}, drc{drc_} {}
}

}
#endif
