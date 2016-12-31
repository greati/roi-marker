#ifndef _ROIIMAGEPANEL_
#define _ROIIMAGEPANEL_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <vector>
#include "Rectangle.h"
#include "ImageROIManager.h"

class wxROIsImagePanel : public wxPanel {

	wxImage image;
	wxBitmap resized;
	int w, h;

	roi::ImageROIManager& imageROIManager;

	public:

		wxROIsImagePanel(wxWindow* parent, wxString file, wxBitmapType format, roi::ImageROIManager & _imageROIManager);

		void paintEvent(wxPaintEvent& evt);
		void OnSize(wxSizeEvent& event);
		void paintNow();
		void render(wxDC& dc);
		void setImage(const std::string & newPath, wxBitmapType newFormat);

		wxBitmap getResized() const { return resized; }
		
		DECLARE_EVENT_TABLE();
};

#endif
