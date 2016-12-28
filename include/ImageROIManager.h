#ifndef _IMGROIWRAPPER_
#define _IMGROIWRAPPER_

#include "Rectangle.h"
#include "Point.h"

namespace roi {

class ImageROIManager {

	private:
		std::string imagePath;			// The image being analysed
		std::vector<roi::Rectangle> rois;	// Vector of ROIs

	public:
		/**
		 * Constructor.
		 *
		 * */
		ImageROIManager();

		/**
		 * Takes an image path and try to load it's 
		 * metadata. Returns false if the operation
		 * didn't succeed.
		 *
		 * Executed every time one wants to take
		 * the ROIs.
		 *
		 * */
		bool loadImage(std::string imagePath);

		/**
		 * Commit changes to the image's metatada
		 * related to the ROIs. Effectively, update
		 * the metadata to agree with the new ROIs.
		 *
		 * Executed when one has ended the ROI analysis
		 * and wants to save the changes.
		 *
		 * */
		bool commit();

		/**
		 * Creates a new ROI. Effectively, adds a new roi::Rectangle
		 * in the vector of ROIs from two roi::Point.
		 *
		 * */
		bool addROI(const roi::Point ulc, const roi::Point drc);

		/**
		 * Remove an existing ROI from the vector of ROIs
		 * by the index.
		 *
		 * */
		bool removeROI(const int & pos);

};

}
#endif

