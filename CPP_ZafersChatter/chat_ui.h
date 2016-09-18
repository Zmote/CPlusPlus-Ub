///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CHAT_UI_H__
#define __CHAT_UI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class globalFrame
///////////////////////////////////////////////////////////////////////////////
class globalFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* mainMenu;
		wxMenu* menu_file;
		wxMenu* menu_settings;
		wxButton* connect_button;
		wxButton* disconnect_button;
		wxPanel* connection_info_input;
		wxStaticText* session_name;
		wxTextCtrl* session_name_input;
		wxStaticText* session_host;
		wxTextCtrl* session_host_input;
		wxStaticText* session_host_port;
		wxTextCtrl* session_host_port_input;
		wxStaticText* session_other_host;
		wxTextCtrl* session_other_host_input;
		wxStaticText* session_other_host_port;
		wxTextCtrl* session_other_host_port_input;
		wxButton* save_session_settings_button;
		wxPanel* current_settings_panel;
		wxStaticText* current_settings_title;
		wxStaticText* cs_s_name;
		wxStaticText* cs_s_name_info;
		wxStaticText* cs_host_ip_port;
		wxStaticText* cs_host_ip_port_info;
		wxStaticText* cs_other_host_ip_port;
		wxStaticText* cs_other_host_ip_port_info;
		wxPanel* chat_panel;
		wxTextCtrl* chat_text_output;
		wxTextCtrl* chat_text_input;
		wxButton* send_button;
		
		// Virtual event handlers, overide them in your derived class
		virtual void handle_connect( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_disconnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_session_name_input( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_host_input( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_host_port_input( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_other_host_input( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_other_host_port( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_save_settings( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_chat_text_input( wxCommandEvent& event ) { event.Skip(); }
		virtual void handle_send( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		globalFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Zafer Dogan Basic Chatter"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1071,683 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~globalFrame();
	
};

#endif //__CHAT_UI_H__
