#ifndef _RECTANGLE_
#define _RECTANGLE_

#include <string>
#include "Point.h"

namespace roi {

class Rectangle {
	public:
		// Upper left corner
		roi::Point ulc;
		// Down right corner
		roi::Point drc;
                // Some data associated to the ROI
                std::string data;

		/**
		 * Default constructor.
		 * */
		Rectangle(){}

		/**
		 * Constructor which creates the Rectangle
		 * from two roi::Point.
		 *
		 * */
		Rectangle(const roi::Point & ulc_, const roi::Point & drc_) : ulc {ulc_}, drc{drc_} {}

                /**
                 * Constructor that also sets the data.
                 *
                 * */
		Rectangle(const roi::Point & ulc_, const roi::Point & drc_, const std::string & _data) 
                    : ulc {ulc_}, drc{drc_}, data{_data} {}
};

}
#endif
