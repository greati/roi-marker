#include "ImageROIManager.h"

using namespace roi;

ImageROIManager::ImageROIManager() {}

const std::vector<roi::Rectangle> & ImageROIManager::getROIs() const { 
	return rois;
}

bool ImageROIManager::loadImage(std::string imagePath) {
	// TODO
	return false;
}

bool ImageROIManager::commit() {
	//TODO
	return false;
}

bool ImageROIManager::addROI(const roi::Point ulc, const roi::Point drc) {
	roi::Rectangle r {ulc, drc};
	rois.push_back(r);
	return true;
}

bool ImageROIManager::removeROI(const int & pos) {
	if ((unsigned int) pos < rois.size()) {
		rois.erase(rois.begin() + pos);		
		return true;
	}

	return false;
}

void ImageROIManager::clearROIs() {
	rois.clear();
}
