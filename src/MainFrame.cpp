#include "MainFrame.h"
#include "wxImagePanel.h"

class MainFrame;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(MainFrame::ID_Hello, MainFrame::OnHello)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
	EVT_MENU(MainFrame::ID_Open, MainFrame::OnOpen)
	EVT_MENU(MainFrame::ID_OpenDir, MainFrame::OnOpenDir)
	EVT_MOTION(MainFrame::OnMouseMoved)
	EVT_SIZE(MainFrame::OnSize)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size, roi::ImageROIManager & _imageROIManager)
: wxFrame(NULL, wxID_ANY, title, pos, size), imageROIManager {_imageROIManager} {

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
	hbox_all = new wxBoxSizer(wxHORIZONTAL);
	vbox_image = new wxBoxSizer(wxVERTICAL);
	vbox_controls = new wxBoxSizer(wxVERTICAL);

	//-- Image --//
	image_panel = new wxROIsImagePanel(global_panel, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG, imageROIManager);	

	//image_panel->SetBackgroundColour(wxColour(* wxGREEN));
	vbox_image->Add(image_panel, 1, wxEXPAND);
	hbox_all->Add(vbox_image, 1, wxEXPAND);		// Image stage expands horizontally and vertically

	//-- Controls --//
	//wxPanel* control_panel = new wxPanel(global_panel, -1);
	//control_panel->SetBackgroundColour(wxColour(* wxWHITE));

	// Add control buttons
	wxButton* done_button = new wxButton(global_panel, MainFrame::ID_Done, wxT("Done"));
	wxButton* next_button = new wxButton(global_panel, MainFrame::ID_Next, wxT("Next"));
	vbox_controls->Add(done_button);
	vbox_controls->Add(next_button);

	// Add information texts + reset buttons
	wxButton* reset_ulc_button = new wxButton(global_panel, MainFrame::ID_Reset_1, wxT("Reset"));
	wxButton* reset_drc_button = new wxButton(global_panel, MainFrame::ID_Reset_2, wxT("Reset"));
	wxStaticText* first_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("Upper left corner:"));
	wxStaticText* second_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("Lower right corner:"));
	roi_preview = new wxImagePanel(global_panel, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG, false, 150, 50);	

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
	roi_list_box = new wxListCtrl(global_panel, MainFrame::ID_RoisList,
		                       wxDefaultPosition, wxSize(200,100),
				       wxLC_REPORT | wxBORDER_THEME);	
	//roi_list_box->InsertItem(0, wxT("Teste"));
	//roi_list_box->InsertItem(1, wxT("Teste"));
	roi_list_box->InsertColumn(1, wxT("#"));
	roi_list_box->InsertColumn(2, wxT("ULC"));
	roi_list_box->InsertColumn(3, wxT("DRC"));
	vbox_controls->Add(roi_list_box);

	// Add buttons for editing the ROIs listbox
	wxButton* add_roi_button = new wxButton(global_panel, MainFrame::ID_AddROI, wxT("+"));
	wxButton* remove_roi_button = new wxButton(global_panel, MainFrame::ID_RemoveROI, wxT("-"));
	vbox_controls->Add(add_roi_button);
	vbox_controls->Add(remove_roi_button);

	// Add listbox for paths
	paths_list_box = new wxListCtrl(global_panel, MainFrame::ID_PathsList,
		                       wxDefaultPosition, wxSize(200,100),
				       wxLC_REPORT | wxBORDER_THEME);	
	paths_list_box->InsertColumn(1, wxT("#"));
	paths_list_box->InsertColumn(2, wxT("Image name"));
	vbox_controls->Add(paths_list_box);

	//vbox_controls->Add(control_panel, 1);
	hbox_all->Add(vbox_controls, 0, wxEXPAND);	// Controls expands only vertically

	global_panel->SetSizer(hbox_all);
	
	//--- Configure initial size for the manager ---//

	//--- Events ---//
	image_panel->Connect( wxID_ANY, wxEVT_MOTION , wxMouseEventHandler(MainFrame::OnMouseMoved),NULL,this);
	image_panel->Connect( wxID_ANY, wxEVT_LEFT_DOWN , wxMouseEventHandler(MainFrame::OnImageClick),NULL,this);
	Connect(MainFrame::ID_Reset_1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnReset1Pressed));
	Connect(MainFrame::ID_Reset_2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnReset2Pressed));
	Connect(MainFrame::ID_AddROI, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnAddROIPressed));
	Connect(MainFrame::ID_RemoveROI, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnRemoveROIPressed));
	Connect(MainFrame::ID_Done, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnDonePressed));
	Connect(MainFrame::ID_Next, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnNextPressed));
	Connect(MainFrame::ID_RoisList, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(MainFrame::OnRoiListSelected));
	Connect(MainFrame::ID_PathsList, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(MainFrame::OnPathsListSelected));

	//if(imageROIManager.loadImage("img/test.jpeg")) {
	//	populateROIListBox(imageROIManager.getROIs());	
	//}

	//---n Building the menu ---//
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_Open, "&Load from image(s)...\tCtrl-O", "Load image(s).");
	menuFile->Append(ID_OpenDir, "&Load from dir...\tCtrl-D", "Load image(s) from dir.");
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
		//wxImage prev = image_panel->getImage().GetSubImage(clipRect);
		wxBitmap prev = image_panel->getResized().GetSubBitmap(clipRect);
		roi_preview->setImage(prev.ConvertToImage());
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
	// For now, consider the user will give the right rectangle
	imageROIManager.addROI(ulc, drc);		
	populateROIListBox(imageROIManager.getROIs());
	//image_panel->paintROIs(imageROIManager.getROIs());
	image_panel->paintNow();

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
	image_panel->paintNow();
	//image_panel->paintROIs(imageROIManager.getROIs());
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

void MainFrame::OnOpenDir(wxCommandEvent& event) {
	wxDirDialog * dirPicker = new wxDirDialog(NULL, "Choose a directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (dirPicker->ShowModal() == wxID_OK) {
		// TODO
	}
}

void MainFrame::OnOpen(wxCommandEvent& event) {
	wxFileDialog * filePicker = new wxFileDialog(this, _("Choose file(s) to edit."), wxEmptyString, wxEmptyString, 
			_("Image Files (*.jpg, *.jpeg, *.png) |*.jpg;*.jpeg;*.png"), wxFD_OPEN | wxFD_MULTIPLE, wxDefaultPosition);
	if(filePicker->ShowModal() == wxID_OK) {

		wxArrayString selectedPaths;
		wxArrayString selectedFilenames;

		filePicker->GetPaths(selectedPaths);
		filePicker->GetFilenames(selectedFilenames);

		loadedPaths.clear();
		loadedFilenames.clear();

		for (unsigned int i = 0; i < selectedPaths.GetCount(); ++i) {
			loadedPaths.push_back(std::string(selectedPaths[i].mb_str()));
			loadedFilenames.push_back(std::string(selectedFilenames[i].mb_str()));
		}

		if(!selectedPaths.IsEmpty()) {
			currentPathIndex = 0;
			updateScreenOnLoad();
		}
	}
}
 
void MainFrame::OnNextPressed(wxCommandEvent& event) {
	currentPathIndex++;
	if (currentPathIndex == loadedPaths.size())
		currentPathIndex = 0;
	updateScreenOnLoad();
}

void MainFrame::OnDonePressed(wxCommandEvent& event) {
	imageROIManager.commit();	
}

void MainFrame::OnSize(wxSizeEvent& event) {
	std::cout << "RESIZED!" << std::endl;
	wxSize s = vbox_image->GetSize();
	std::cout << "From the sizer:" << s.GetWidth() << " " << s.GetHeight() << std::endl;
	std::cout << "From the event:" << event.GetSize().GetWidth() << " " << event.GetSize().GetHeight() << std::endl;
	// The panel is doing this (but I don't like it)
	imageROIManager.updateAfterResize(s.GetWidth(), s.GetHeight());
	populateROIListBox(imageROIManager.getROIs());	
	//image_panel->paintROIs(imageROIManager.getROIs());
	//image_panel->paintNow();
	event.Skip();
}

void MainFrame::OnRoiListSelected(wxListEvent& event) {
	// TODO
}

void MainFrame::OnPathsListSelected(wxListEvent& event) {
	currentPathIndex = event.GetIndex();
	updateScreenOnLoad();
}

void MainFrame::populateROIListBox(const std::vector<roi::Rectangle> rois) {
	roi_list_box->DeleteAllItems();
	for (unsigned int i = 0; i < rois.size(); ++i) {
		long item_index = roi_list_box->InsertItem(0, wxString::Format("%d",i));		
		roi_list_box->SetItem(item_index, 1, "(" + wxString::Format("%f",rois[i].ulc.x) + "," + wxString::Format("%f", rois[i].ulc.y) + ")");
		roi_list_box->SetItem(item_index, 2, "(" + wxString::Format("%f",rois[i].drc.x) + "," + wxString::Format("%f", rois[i].drc.y) + ")");
	}
}

void MainFrame::populatePathsListBox(const std::vector<std::string> paths) {
	paths_list_box->DeleteAllItems();
	for (unsigned int i = 0; i < paths.size(); ++i) {
		long item_index = paths_list_box->InsertItem(0, wxString::Format("%d",i));		
		paths_list_box->SetItem(item_index, 1, paths[i]);
	}
}

void MainFrame::updateScreenOnLoad() {
	wxSize s = vbox_image->GetSize();
	imageROIManager.updateAfterResize(s.GetWidth(), s.GetHeight());
	// Update manager
	imageROIManager.loadImage(loadedPaths[currentPathIndex]);
	// Update image panel
	// TODO: check type of image
	image_panel->setImage(loadedPaths[currentPathIndex], wxBITMAP_TYPE_JPEG);
	// Populate list boxes
	populatePathsListBox(loadedFilenames);
	populateROIListBox(imageROIManager.getROIs());	
}
