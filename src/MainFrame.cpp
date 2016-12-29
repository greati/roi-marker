#include "MainFrame.h"
#include "wxImagePanel.h"

class MainFrame;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(MainFrame::ID_Hello, MainFrame::OnHello)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_MOTION(MainFrame::OnMouseMoved)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size) {

	//--- Arranging the layout ---//
	
	/**
	 * 1 - Put a BoxSizer (hbox_all) into the entire frame
	 * 2 - Put a Panel (global_panel) inside hbox_all
	 *
	 *
	 * */
	
	wxPanel* global_panel = new wxPanel(this, -1);
	//global_panel->SetBackgroundColour(wxColour(* wxBLACK));

	//-- Sizers --//
	wxBoxSizer* hbox_all = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vbox_image = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vbox_controls = new wxBoxSizer(wxVERTICAL);

	//-- Image --//
	image_panel = new wxImagePanel(global_panel, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG);	
	//image_panel->SetBackgroundColour(wxColour(* wxGREEN));
	vbox_image->Add(image_panel, 1, wxEXPAND);
	hbox_all->Add(vbox_image, 1, wxEXPAND);		// Image stage expands horizontally and vertically

	//-- Controls --//
	//wxPanel* control_panel = new wxPanel(global_panel, -1);
	//control_panel->SetBackgroundColour(wxColour(* wxWHITE));

	// Add control buttons
	wxButton* done_button = new wxButton(global_panel, -1, wxT("Done"));
	wxButton* next_button = new wxButton(global_panel, -1, wxT("Next"));
	vbox_controls->Add(done_button);
	vbox_controls->Add(next_button);

	// Add information texts + reset buttons
	wxButton* reset_ulc_button = new wxButton(global_panel, MainFrame::ID_Reset_1, wxT("Reset"));
	wxButton* reset_drc_button = new wxButton(global_panel, MainFrame::ID_Reset_2, wxT("Reset"));
	wxStaticText* first_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("Upper left corner:"));
	wxStaticText* second_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("Lower right corner:"));
	roi_preview = new wxImagePanel(global_panel, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG, 150, 50);	

	ulc_text = new wxStaticText(global_panel, wxID_ANY, wxT("(-1,-1)"));
	drc_text = new wxStaticText(global_panel, wxID_ANY, wxT("(-1,-1)"));
	vbox_controls->Add(first_point_txt);
	vbox_controls->Add(ulc_text);
	vbox_controls->Add(reset_ulc_button);
	vbox_controls->Add(second_point_txt);
	vbox_controls->Add(drc_text);
	vbox_controls->Add(reset_drc_button);
	vbox_controls->Add(roi_preview, 1, wxEXPAND);

	// Add listbox for multiple ROIs
	roi_list_box = new wxListCtrl(global_panel, wxID_ANY,
		                       wxDefaultPosition, wxSize(200,100),
				       wxLC_REPORT | wxBORDER_THEME);	
	//roi_list_box->InsertItem(0, wxT("Teste"));
	//roi_list_box->InsertItem(1, wxT("Teste"));
	roi_list_box->InsertColumn(1, wxT("#"));
	roi_list_box->InsertColumn(2, wxT("ULC"));
	roi_list_box->InsertColumn(3, wxT("DRC"));
	vbox_controls->Add(roi_list_box);

	// Add buttons for editing the listbox
	wxButton* add_roi_button = new wxButton(global_panel, MainFrame::ID_AddROI, wxT("+"));
	wxButton* remove_roi_button = new wxButton(global_panel, MainFrame::ID_RemoveROI, wxT("-"));
	vbox_controls->Add(add_roi_button);
	vbox_controls->Add(remove_roi_button);

	//vbox_controls->Add(control_panel, 1);
	hbox_all->Add(vbox_controls, 0, wxEXPAND);	// Controls expands only vertically

	global_panel->SetSizer(hbox_all);

	//--- Events ---//
	image_panel->Connect( wxID_ANY, wxEVT_MOTION , wxMouseEventHandler(MainFrame::OnMouseMoved),NULL,this);
	image_panel->Connect( wxID_ANY, wxEVT_LEFT_DOWN , wxMouseEventHandler(MainFrame::OnImageClick),NULL,this);
	Connect(MainFrame::ID_Reset_1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnReset1Pressed));
	Connect(MainFrame::ID_Reset_2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnReset2Pressed));
	Connect(MainFrame::ID_AddROI, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnAddROIPressed));
	Connect(MainFrame::ID_RemoveROI, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnRemoveROIPressed));

	//---n Building the menu ---//
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string.");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);	

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	//--- Status bar ---//
	CreateStatusBar();
	SetStatusText("Welcome to ROI-Marker!");

	//-- Center window --//
	Centre();

	//-- Setting the icon --//
	//SetIcon(wxIcon(wxT("/path/to/icon")); 
}

void MainFrame::OnImageClick(wxMouseEvent& event) {
	// Reset if two points were already filled
	if (ulc.x != -1 && drc.x != -1) {
		drc.x = -1;
		drc.y = -1;
		drc_text->SetLabel("(-1,-1)");
		ulc.x = -1;
		ulc.y = -1;
		ulc_text->SetLabel("(-1,-1)");
	}

	// Selecting the first point
	if (ulc.x == -1) {
		ulc.x = event.GetX();
		ulc.y = event.GetY();
		ulc_text->SetLabel("("+wxString::FromDouble(event.GetX())+","+wxString::FromDouble(event.GetY())+ ")");
	// Selecting the second point
	} else if (drc.x == -1) {
		drc.x = event.GetX();
		drc.y = event.GetY();
		drc_text->SetLabel("("+wxString::FromDouble(event.GetX())+","+wxString::FromDouble(event.GetY())+ ")");

		// Update the preview
		wxRect clipRect {ulc.x, ulc.y, drc.x - ulc.x, drc.y - ulc.y};
		wxImage prev = image_panel->getImage().GetSubImage(clipRect);
		roi_preview->setImage(prev);

	}
}

void MainFrame::OnReset1Pressed(wxCommandEvent& event) {
	ulc.x = -1;
	ulc.y = -1;
	ulc_text->SetLabel("(-1,-1)");
}

void MainFrame::OnReset2Pressed(wxCommandEvent& event) {
	drc.x = -1;
	drc.y = -1;
	drc_text->SetLabel("(-1,-1)");
}

void MainFrame::OnAddROIPressed(wxCommandEvent& event) {
	// TODO Here I'll probably have to fix the rectangle points

	// For now, consider the user will give the right rectangle
	imageROIManager.addROI(ulc, drc);		
	populateROIListBox(imageROIManager.getROIs());
	image_panel->paintROIs(imageROIManager.getROIs());

	ulc.x = -1;
	ulc.y = -1;
	ulc_text->SetLabel("(-1,-1)");
	drc.x = -1;
	drc.y = -1;
	drc_text->SetLabel("(-1,-1)");

}

void MainFrame::OnRemoveROIPressed(wxCommandEvent& event) {
	long itemIndex = -1;

	while ((itemIndex = roi_list_box->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
		long roiIndex;
		(roi_list_box->GetItemText(itemIndex)).ToLong(&roiIndex);
		imageROIManager.removeROI(roiIndex);		
	}	

	populateROIListBox(imageROIManager.getROIs());
	image_panel->paintROIs(imageROIManager.getROIs());
}

void MainFrame::OnMouseMoved(wxMouseEvent& event) {
	SetStatusText("("+wxString::FromDouble(event.GetX())+","+wxString::FromDouble(event.GetY())+ ")");
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox("This is ROI-Marker.", "About", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnHello(wxCommandEvent& event) {
	wxLogMessage("Hello!");
}

void MainFrame::populateROIListBox(const std::vector<roi::Rectangle> rois) {
	roi_list_box->DeleteAllItems();
	for (unsigned int i = 0; i < rois.size(); ++i) {
		long item_index = roi_list_box->InsertItem(0, wxString::Format("%d",i));		
		roi_list_box->SetItem(item_index, 1, "(" + wxString::Format("%d",rois[i].ulc.x) + "," + wxString::Format("%d", rois[i].ulc.y) + ")");
		roi_list_box->SetItem(item_index, 2, "(" + wxString::Format("%d",rois[i].drc.x) + "," + wxString::Format("%d", rois[i].drc.y) + ")");
	}
}


