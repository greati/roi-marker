#ifndef _WXIMAGEPANE_
#define _WXIMAGEPANE_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <vector>
#include "Rectangle.h"

class wxImagePanel : public wxPanel {
	
	wxImage image;
	int resize_width;
	int resize_height;

	public:
		wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format);
		wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, int resize_width, int resize_height);

		wxImage & getImage();

		void setImage(const wxImage & _image);

		void paintEvent(wxPaintEvent& evt);
		void paintNow();

		void render(wxDC& dc);
		void paintROIs(const std::vector<roi::Rectangle> rois);

		DECLARE_EVENT_TABLE();
};

#endif
