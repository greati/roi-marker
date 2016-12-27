#include "RoiMarkerApplication.h"

wxIMPLEMENT_APP(RoiMarkerApplication);

bool RoiMarkerApplication::OnInit() {
	MainFrame* frame = new MainFrame("ROI-Marker", wxPoint(50,50), wxSize(800,600)); 
	frame->Show(true);
	return true;
}

