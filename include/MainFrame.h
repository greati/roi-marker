#ifndef _MAINFRAME_
#define _MAINFRAME_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

/**
 * The main frame of the application.
 *
 * Author:	Vitor Greati
 * Date:	2016-12-27
 * */
class MainFrame : public wxFrame {

	public:
		MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

		/**
		 * Holds ID's for events.
		 * */
		enum {
			ID_Hello = 1

		};

	private:
		void OnHello(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();

};

#endif
