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

