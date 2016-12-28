#ifndef _MAINFRAME_
#define _MAINFRAME_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "Point.h"

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

		wxStaticText* ulc_text;
		wxStaticText* drc_text;

		roi::Point ulc {-1, -1};
		roi::Point drc {-1, -1};

		void OnHello(wxCommandEvent& event);
		
		void OnMouseMoved(wxMouseEvent& event);

		void OnImageClick(wxMouseEvent& event);

		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();

};

#endif
