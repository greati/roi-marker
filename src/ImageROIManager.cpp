#include "ImageROIManager.h"
#include <exiv2/exiv2.hpp>
#include <string>

using namespace roi;

ImageROIManager::ImageROIManager(const long & _width, const long & _height) : imageWidth {_width}, imageHeight {_height} {}

std::vector<roi::Rectangle> & ImageROIManager::getROIs() { 
	return rois;
}

bool ImageROIManager::loadImage(const std::string & imagePath) {
	this->imagePath = imagePath;
	// Opening the image for metadata manipulation
	image = Exiv2::ImageFactory::open(imagePath);
	if (image.get() == 0) return false;

	rois.clear();
	loadedRois.clear();	

	// Read metadata
	image->readMetadata();
	
	Exiv2::XmpData &xmpData = image->xmpData();
	
	if (!xmpData.empty()) {
		try {
			const Exiv2::Value & widthTag = xmpData["Xmp.ROIs.ImageWidth"].value();
			const Exiv2::Value & heightTag = xmpData["Xmp.ROIs.ImageHeight"].value();
			const Exiv2::Value & roisTag = xmpData["Xmp.ROIs.ROIString"].value();

            // Extract data, that can exist or not
            std::string roiData;
            try {
                const Exiv2::Value & dataTag = xmpData["Xmp.ROIs.ROIData"].value();
                roiData = dataTag.toString();
            } catch (Exiv2::Error & e) {
                roiData = "";
            }

			loadedImageWidth = widthTag.toLong();
			loadedImageHeight = heightTag.toLong();

            std::string roiString = roisTag.toString();

			size_t c = std::count(roiString.begin(), roiString.end(), ' '); 
			
			std::stringstream ssroi (roiString);
            std::stringstream ssdata (roiData);

			for (unsigned int i = 0; i < c / 4; ++i) {
				// Loaded ROI
				roi::Rectangle r;
				ssroi >> r.ulc.x >> r.ulc.y >> r.drc.x >> r.drc.y;
                ssdata >> r.data;
				loadedRois.push_back(r);
				
				// ROIs adjusted for current width and height
				roi::Rectangle adjustedRoi;
				adjustedRoi.ulc.x = r.ulc.x * imageWidth / loadedImageWidth;
				adjustedRoi.ulc.y = r.ulc.y * imageHeight / loadedImageHeight;
				adjustedRoi.drc.x = r.drc.x * imageWidth / loadedImageWidth;
				adjustedRoi.drc.y = r.drc.y * imageHeight / loadedImageHeight;
                adjustedRoi.data = r.data;
				rois.push_back(adjustedRoi);
			}
		} catch (Exiv2::Error & e) {
			std::cout << "Error: " << e.what() << std::endl;
		}

		return true;

	} else std::cout << "No XMP data!" << std::endl;

	return false;
}

bool ImageROIManager::commit() {
	Exiv2::XmpData xmpData = image->xmpData();

	Exiv2::XmpProperties::registerNs("myNamespace/", "ROIs");

	xmpData["Xmp.ROIs.ImageWidth"] = int32_t(imageWidth);
	xmpData["Xmp.ROIs.ImageHeight"] = int32_t(imageHeight);
	
	std::string roiString = "";
        std::string roiData = "";
	for (unsigned int i = 0; i < rois.size(); ++i) {
		roiString += std::to_string(rois[i].ulc.x) + " " + std::to_string(rois[i].ulc.y) + " " + 
			std::to_string(rois[i].drc.x) + " " + std::to_string(rois[i].drc.y) + " ";		
                roiData += rois[i].data + " ";
	}

	xmpData["Xmp.ROIs.ROIString"] = roiString;
	xmpData["Xmp.ROIs.ROIData"] = roiData;

	// Write the metadata in the image
	image->setXmpData(xmpData);
	image->writeMetadata();

	return true;
}

bool ImageROIManager::addROI(const roi::Point ulc, const roi::Point drc, const std::string & data) {
	roi::Rectangle r {ulc, drc, data};
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

void ImageROIManager::updateAfterResize(const int & w, const int & h) {
	for (unsigned int i = 0; i < rois.size(); ++i) {
		rois[i].ulc.x = rois[i].ulc.x * w / imageWidth;
		rois[i].ulc.y = rois[i].ulc.y * h / imageHeight;
		rois[i].drc.x = rois[i].drc.x * w / imageWidth;
		rois[i].drc.y = rois[i].drc.y * h / imageHeight;
	}
	imageWidth = w;
	imageHeight = h;
}
