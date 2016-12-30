#ifndef _POINT_
#define _POINT_

namespace roi {

class Point {

	public:
		// Point coordinates
		int x, y;		

		/**
		 * Default constructor.
		 * */
		Point() {};

		/**
		 * Constructor based on coordinates.
		 * */
		Point (const int x_, const int y_) : x {x_}, y {y_} {}

};

}
#endif
