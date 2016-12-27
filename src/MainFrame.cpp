#include "MainFrame.h"

class MainFrame;

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(MainFrame::ID_Hello, MainFrame::OnHello)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size) {
	// Building the menu
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

	// Status bar
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

