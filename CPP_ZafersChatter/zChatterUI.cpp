#include "zChatterUI.h"
#include <iostream>
#include <string>

zChatterUI::zChatterUI( wxWindow* parent )
:
globalFrame( parent )
{}

//EVENT HANDLER BUTTONS
void zChatterUI::handle_connect( wxCommandEvent& event )
{

}
void zChatterUI::handle_disconnect( wxCommandEvent& event )
{

}
void zChatterUI::handle_save_settings( wxCommandEvent& event )
{

}

void zChatterUI::handle_send(wxCommandEvent & event)
{
	wxString prepend{"[" + zChatterUI::get_session_name() + "]: "};
	zChatterUI::chat_text_output->SetValue(prepend + zChatterUI::chat_text_output->GetValue() + zChatterUI::chat_text_input->GetValue());
	//TODO: newline
}

//EVENT HANDLER FIELDS
void zChatterUI::handle_session_name_input( wxCommandEvent& event )
{
	zChatterUI::set_session_name(event.GetString());
}
void zChatterUI::handle_host_input( wxCommandEvent& event )
{
	zChatterUI::set_session_host(event.GetString());
}
void zChatterUI::handle_host_port_input( wxCommandEvent& event )
{
	zChatterUI::set_session_host_port(event.GetString());
}
void zChatterUI::handle_other_host_input( wxCommandEvent& event )
{
	zChatterUI::set_session_other_host(event.GetString());
}
void zChatterUI::handle_other_host_port( wxCommandEvent& event )
{
	zChatterUI::set_session_other_host_port(event.GetString());
}
void zChatterUI::handle_chat_text_input( wxCommandEvent& event )
{
	wxString prepend{"[" + zChatterUI::get_session_name() + "]: "};
	zChatterUI::chat_text_output->GetValue().insert(zChatterUI::chat_text_output->GetValue().length(),event.GetString());
	//TODO: newline
}

//DATA MANIPULATORS
void zChatterUI::set_session_name(wxString name)
{
	zChatterUI::user_session_name = name;
}
wxString zChatterUI::get_session_name()
{
	return zChatterUI::user_session_name;
}

void zChatterUI::set_session_host(wxString name)
{
	zChatterUI::user_session_host = name;
}
wxString zChatterUI::get_session_host()
{
	return zChatterUI::user_session_host;
}

void zChatterUI::set_session_host_port(wxString name)
{
	zChatterUI::user_session_host_port = name;
}
wxString zChatterUI::get_session_host_port()
{
	return zChatterUI::user_session_host_port;
}

void zChatterUI::set_session_other_host(wxString name)
{
	zChatterUI::user_session_other_host = name;
}
wxString zChatterUI::get_session_other_host()
{
	return zChatterUI::user_session_other_host;
}

void zChatterUI::set_session_other_host_port(wxString name)
{
	zChatterUI::user_session_other_host_post = name;
}
wxString zChatterUI::get_session_other_host_port()
{
	return zChatterUI::user_session_other_host_post;
}
