#include "wxImagePanel.h"

wxBEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
	EVT_PAINT(wxImagePanel::paintEvent)
	EVT_SIZE(wxImagePanel::OnSize)
wxEND_EVENT_TABLE()

wxImagePanel::wxImagePanel(wxWindow* parent, wxString file, wxBitmapType format, bool RESIZABLE, int _w, int _h) 
	: wxPanel {parent}, resizable {RESIZABLE}, w {_w}, h {_h} {
	// Load the image
	if (!image.LoadFile(file, format)) {
		std::cout << "Image not loaded" << std::endl;	
	} else {
		if (!resizable)
			image.Rescale(w, h);	
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
	if (resizable) {
		int newh, neww;
		dc.GetSize(&neww, &newh);

		if (neww != w || newh != h) {
			resized = wxBitmap(image.Scale(neww, newh, wxIMAGE_QUALITY_HIGH));	
			w = neww;
			h = newh;
		}
		dc.DrawBitmap(resized, 0, 0, false);
	} else {
		dc.DrawBitmap(image, 0, 0, false);
	}
}

void wxImagePanel::OnSize(wxSizeEvent& event) {
	if (resizable) {
		Refresh();
		event.Skip();	
	}
}

void wxImagePanel::paintROIs(const std::vector<roi::Rectangle> rois) {
	wxClientDC dc(this);
	//dc.Clear();
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
	resized = wxBitmap(image.Scale(w, h, wxIMAGE_QUALITY_HIGH));	
	if (!resizable) 
		image.Rescale(w, h);
	paintNow();
}

void wxImagePanel::setImage(const std::string & path, wxBitmapType _format) {
	wxImage newImage;
	if (!newImage.LoadFile(path, _format)) {
		std::cout << "Image not loaded" << std::endl;	
	} else {
		//newImage.Rescale(resize_width, resize_height);	
		//setImage(newImage);
		image = newImage;
		resized = wxBitmap(image.Scale(w, h, wxIMAGE_QUALITY_HIGH));	
		paintNow();
	}
}

wxImage & wxImagePanel::getImage() {
	return image;
}

wxBitmap & wxImagePanel::getResized() {
	return resized;
}
