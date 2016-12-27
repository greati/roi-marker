#include "MainFrame.h"
#include "wxImagePanel.h"

class MainFrame;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(MainFrame::ID_Hello, MainFrame::OnHello)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size) {

	//--- Arranging the layout ---//
	
	// Vertical box (the entire frame)
	wxBoxSizer* vbox_all = new wxBoxSizer(wxVERTICAL);
	
	// Horizontal box (for the image)
	wxBoxSizer* hbox_image = new wxBoxSizer(wxHORIZONTAL);

	// Horizontal box (for the informations and buttons)
	wxBoxSizer* hbox_controls = new wxBoxSizer(wxHORIZONTAL);

	// Vertical box (for marker informations)
	wxBoxSizer* vbox_controls_informations = new wxBoxSizer(wxVERTICAL);

	// Vertical box (for marker buttons)
	wxBoxSizer* vbox_controls_buttons = new wxBoxSizer(wxVERTICAL);

	// Add image stage drawing component
	wxImagePanel* imagePanel = new wxImagePanel(this, wxT("img/test.jpeg"), wxBITMAP_TYPE_JPEG);	
	hbox_image->Add(imagePanel, 1, wxEXPAND);

	// Add control buttons
	wxButton* done_button = new wxButton(this, -1, wxT("Done"));
	wxButton* next_button = new wxButton(this, -1, wxT("Next"));
	vbox_controls_buttons->Add(done_button);
	vbox_controls_buttons->Add(next_button);

	// Add information texts
	wxStaticText* first_point_txt = new wxStaticText(this, wxID_ANY, wxT("First point:"));
	wxStaticText* second_point_txt = new wxStaticText(this, wxID_ANY, wxT("Second point:"));
	vbox_controls_informations->Add(first_point_txt);
	vbox_controls_informations->Add(second_point_txt);

	// Making the panel hierarchy
	vbox_all->Add(hbox_image, 1, wxEXPAND);
	vbox_all->Add(hbox_controls, 0, wxEXPAND | wxALL | wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
	hbox_controls->Add(vbox_controls_informations, 1, wxEXPAND);
	hbox_controls->Add(vbox_controls_buttons, 0, wxEXPAND);

	SetSizerAndFit(vbox_all);

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

