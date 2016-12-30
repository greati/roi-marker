#ifndef _MAINFRAME_
#define _MAINFRAME_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include "ImageROIManager.h"
#include "wxImagePanel.h"
#include "Point.h"
#include "Rectangle.h"
#include "wx/listctrl.h"
#include "wx/filepicker.h"
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
			ID_RemoveROI = 5,
			ID_Done = 6,
			ID_Open = 7,
			ID_FilePickerImages = 8,
			ID_DirPickerImages = 9,
			ID_OpenDir = 10

		};

	private:

		roi::ImageROIManager imageROIManager {800, 600};

		wxStaticText* ulc_text;
		wxStaticText* drc_text;
		wxListCtrl* roi_list_box;
		wxImagePanel* image_panel;
		wxImagePanel* roi_preview;

		// State of the application
		// TODO: Move them to another place, maybe as static attributes
		roi::Point ulc {-1, -1};
		roi::Point drc {-1, -1};
		std::vector<std::string> loadedPaths;
		unsigned int currentPathIndex;

		//--- Helpers ---//
		void populateROIListBox(const std::vector<roi::Rectangle> rois);

		//--- Event handlers ---//
		// Button handlers
		void OnReset1Pressed(wxCommandEvent& event);
		void OnReset2Pressed(wxCommandEvent& event);
		void OnAddROIPressed(wxCommandEvent& event);
		void OnRemoveROIPressed(wxCommandEvent& event);
		void OnDonePressed(wxCommandEvent& event);

		// Mouse handlers
		void OnMouseMoved(wxMouseEvent& event);
		void OnImageClick(wxMouseEvent& event);

		// Menu button handlers
		void OnOpen(wxCommandEvent& event);
		void OnOpenDir(wxCommandEvent& event);
		void OnHello(wxCommandEvent& event);
		void OnExit(wxCommandEvent& event);
		void OnAbout(wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();

};

#endif
