#include "wxROIsImagePanel.h"

wxBEGIN_EVENT_TABLE(wxROIsImagePanel, wxPanel)
	EVT_PAINT(wxROIsImagePanel::paintEvent)
	EVT_SIZE(wxROIsImagePanel::OnSize)
wxEND_EVENT_TABLE()

wxROIsImagePanel::wxROIsImagePanel(wxWindow* parent, wxString file, wxBitmapType format, roi::ImageROIManager & _imageROIManager)
: wxPanel{parent}, imageROIManager {_imageROIManager} {
	if (!image.LoadFile(file, format)) {
		std::cout << "Image not loaded" << std::endl;	
	}
}

void wxROIsImagePanel::paintEvent(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	render(dc);
}

void wxROIsImagePanel::paintNow() {
	wxPaintDC dc(this);
	render(dc);
}

void wxROIsImagePanel::render(wxDC& dc) {
	// Paint the image, resizing
	int newh, neww;
	dc.GetSize(&neww, &newh);

	if (neww != w || newh != h) {
		resized = wxBitmap(image.Scale(neww, newh, wxIMAGE_QUALITY_HIGH));	
		w = neww;
		h = newh;
	}
	dc.DrawBitmap(resized, 0, 0, false);

	// Paint the ROIs
	std::vector<roi::Rectangle> rois = imageROIManager.getROIs();
	wxColour* transp = new wxColour(0, 0, 200, 0);
	dc.SetBrush(*transp); // blue filling
	dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 10-pixels-thick pink outline
	for (unsigned int i = 0; i < rois.size(); ++i) {
		dc.DrawRectangle( rois[i].ulc.x, rois[i].ulc.y, rois[i].drc.x - rois[i].ulc.x, rois[i].drc.y - rois[i].ulc.y);
		dc.SetTextForeground(wxColour(255,0,0));
		dc.DrawText(wxString::Format(wxT("%d"),i), rois[i].ulc.x, rois[i].ulc.y);
	}

}

void wxROIsImagePanel::OnSize(wxSizeEvent& event) {
	Refresh();
	event.Skip();
}

void wxROIsImagePanel::setImage(const std::string & newPath, wxBitmapType newFormat) {
	wxImage newImage;
	if (!newImage.LoadFile(newPath, newFormat)) {
		std::cout << "Image not loaded" << std::endl;	
	} else {
		image = newImage;
		resized = wxBitmap(image.Scale(w, h, wxIMAGE_QUALITY_HIGH));	
		paintNow();
	}
}
