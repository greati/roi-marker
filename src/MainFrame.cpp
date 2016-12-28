#include "MainFrame.h"
#include "wxImagePanel.h"
#include "wx/listctrl.h"

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
	wxImagePanel* image_panel = new wxImagePanel(global_panel, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG);	
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

	// Add information texts
	wxStaticText* first_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("First point:"));
	wxStaticText* second_point_txt = new wxStaticText(global_panel, wxID_ANY, wxT("Second point:"));
	vbox_controls->Add(first_point_txt);
	vbox_controls->Add(second_point_txt);

	// Add listbox for multiple ROIs
	wxListCtrl* roi_list_box = new wxListCtrl(global_panel, wxID_ANY,
		                       wxDefaultPosition, wxSize(200,100),
				       wxLC_LIST | wxBORDER_THEME);	
	roi_list_box->InsertItem(0, wxT("Teste"));
	roi_list_box->InsertItem(1, wxT("Teste"));
	vbox_controls->Add(roi_list_box);

	// Add buttons for editing the listbox
	wxButton* add_roi_button = new wxButton(global_panel, -1, wxT("+"));
	wxButton* remove_roi_button = new wxButton(global_panel, -1, wxT("-"));
	vbox_controls->Add(add_roi_button);
	vbox_controls->Add(remove_roi_button);

	//vbox_controls->Add(control_panel, 1);
	hbox_all->Add(vbox_controls, 0, wxEXPAND);	// Controls expands only vertically

	global_panel->SetSizer(hbox_all);

	image_panel->Connect( wxID_ANY, wxEVT_MOTION , wxMouseEventHandler(MainFrame::OnMouseMoved),NULL,this);

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

