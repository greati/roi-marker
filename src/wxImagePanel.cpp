#include "wxImagePanel.h"

wxBEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
	EVT_PAINT(wxImagePanel::paintEvent)
wxEND_EVENT_TABLE()

wxImagePanel::wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format) : wxPanel {parent} {
	// Load the image
	if (!image.LoadFile(file, format)) {
		std::cout << "Image not loaded" << std::endl;	
	} else {
		image.Rescale(800, 600);	
	}
}

wxImagePanel::wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, int _resize_width, int _resize_height) 
	: wxPanel {parent}, resize_width {_resize_width}, resize_height {_resize_height} {
	// Load the image
	if (!image.LoadFile(file, format)) {
		std::cout << "Image not loaded" << std::endl;	
	} else {
		image.Rescale(resize_width, resize_height);	
	}
}

void wxImagePanel::paintEvent(wxPaintEvent& evt){
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

void wxImagePanel::render(wxDC& dc) {
	dc.DrawBitmap(image, 0, 0, false);
}

void wxImagePanel::paintROIs(const std::vector<roi::Rectangle> rois) {
	wxPaintDC dc(this);
	dc.Clear();
	dc.DrawBitmap(image, 0, 0, false);
	wxColour* transp = new wxColour(0, 0, 200, 0);
	dc.SetBrush(*transp); // blue filling
	dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 10-pixels-thick pink outline
	for (unsigned int i = 0; i < rois.size(); ++i) {
		dc.DrawRectangle( rois[i].ulc.x, rois[i].ulc.y, rois[i].drc.x - rois[i].ulc.x, rois[i].drc.y - rois[i].ulc.y);
		dc.SetTextForeground(wxColour(255,0,0));
		dc.DrawText(wxString::Format(wxT("%d"),i), rois[i].ulc.x, rois[i].ulc.y);
	}
}

void wxImagePanel::setImage(const wxImage & _image) {
	image = _image;
	image.Rescale(resize_width, resize_height);
	paintNow();
}

wxImage & wxImagePanel::getImage() {
	return image;
}

