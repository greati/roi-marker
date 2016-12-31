#ifndef _WXIMAGEPANE_
#define _WXIMAGEPANE_

#include <wx/wx.h>
#include <wx/sizer.h>
#include <vector>
#include "Rectangle.h"

class wxImagePanel : public wxPanel {
	
	wxImage image;
	wxBitmap resized;
	bool resizable;
	int w, h;

	public:
		wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, bool RESIZABLE = false, int _w = -1, int _h = -1);

		wxImage & getImage();
		wxBitmap & getResized();

		void setImage(const wxImage & _image);
		void setImage(const std::string & path, wxBitmapType _format);

		void paintEvent(wxPaintEvent& evt);
		void OnSize(wxSizeEvent& event);
		void paintNow();

		void render(wxDC& dc);
		void paintROIs(const std::vector<roi::Rectangle> rois);

		DECLARE_EVENT_TABLE();
};

#endif
