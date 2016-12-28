#ifndef _MAINFRAME_
#define _MAINFRAME_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "ImageROIManager.h"
#include "Point.h"
#include "Rectangle.h"
#include "wx/listctrl.h"
#include <vector>

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
			ID_Hello = 1,
			ID_Reset_1 = 2,
			ID_Reset_2 = 3,
			ID_AddROI = 4,
			ID_RemoveROI = 5
		};

	private:

		roi::ImageROIManager imageROIManager;

		wxStaticText* ulc_text;
		wxStaticText* drc_text;
		wxListCtrl* roi_list_box;

		roi::Point ulc {-1, -1};
		roi::Point drc {-1, -1};

		//--- Helpers ---//
		void populateROIListBox(const std::vector<roi::Rectangle> rois);

		//--- Event handlers ---//
		// Button handlers
		void OnReset1Pressed(wxCommandEvent& event);
		void OnReset2Pressed(wxCommandEvent& event);
		void OnAddROIPressed(wxCommandEvent& event);
		void OnRemoveROIPressed(wxCommandEvent& event);

		// Mouse handlers
		void OnMouseMoved(wxMouseEvent& event);
		void OnImageClick(wxMouseEvent& event);

		// Menu button handlers
		void OnHello(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();

};

#endif
