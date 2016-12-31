#ifndef _ROIMARKERAPPLICATION_
#define _ROIMARKERAPPLICATION_

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "MainFrame.h"
#include "ImageROIManager.h"

/**
 * Main class of the application, responsible
 * for initialization and frame management.
 *
 * Based on <http://docs.wxwidgets.org/stable/overview_helloworld.html>
 * 
 * Author:	Vitor Greati
 * Date: 	2016-12-27
 * */
class RoiMarkerApplication : public wxApp {

	private:
		roi::ImageROIManager imageROIManager;
	public:
		/**
		 * Regarded to the initialization of the
		 * application.
		 * */
		virtual bool OnInit();

};

#endif

