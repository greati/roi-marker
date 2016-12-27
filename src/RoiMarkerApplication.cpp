#include "RoiMarkerApplication.h"

wxIMPLEMENT_APP(RoiMarkerApplication);

bool RoiMarkerApplication::OnInit() {

	wxInitAllImageHandlers();

	MainFrame* frame = new MainFrame("ROI-Marker", wxPoint(50,50), wxSize(800,800)); 
	frame->Show(true);
	return true;
}

