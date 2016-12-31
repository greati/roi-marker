#ifndef _POINT_
#define _POINT_

namespace roi {

class Point {

	public:
		// Point coordinates
		double x, y;		

		/**
		 * Default constructor.
		 * */
		Point() {};

		/**
		 * Constructor based on coordinates.
		 * */
		Point (const double x_, const double y_) : x {x_}, y {y_} {}

};

}
#endif
