///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "chat_ui.h"

///////////////////////////////////////////////////////////////////////////

globalFrame::globalFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	mainMenu = new wxMenuBar( 0 );
	menu_file = new wxMenu();
	mainMenu->Append( menu_file, wxT("File") ); 
	
	menu_settings = new wxMenu();
	mainMenu->Append( menu_settings, wxT("Settings") ); 
	
	this->SetMenuBar( mainMenu );
	
	wxBoxSizer* main_content_sizer;
	main_content_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* button_wrapper_sizer;
	button_wrapper_sizer = new wxBoxSizer( wxVERTICAL );
	
	connect_button = new wxButton( this, wxID_ANY, wxT("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	connect_button->SetToolTip( wxT("To Start Chat Session") );
	
	button_wrapper_sizer->Add( connect_button, 0, wxALL|wxEXPAND, 0 );
	
	disconnect_button = new wxButton( this, wxID_ANY, wxT("Disconnect"), wxDefaultPosition, wxDefaultSize, 0 );
	disconnect_button->SetToolTip( wxT("To Disconnect from Session") );
	
	button_wrapper_sizer->Add( disconnect_button, 0, wxALL|wxEXPAND, 0 );
	
	connection_info_input = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	connection_info_input->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* input_form_wrapper_sizer;
	input_form_wrapper_sizer = new wxBoxSizer( wxVERTICAL );
	
	session_name = new wxStaticText( connection_info_input, wxID_ANY, wxT("Session Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	session_name->Wrap( -1 );
	input_form_wrapper_sizer->Add( session_name, 0, wxALL|wxEXPAND, 5 );
	
	session_name_input = new wxTextCtrl( connection_info_input, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_form_wrapper_sizer->Add( session_name_input, 0, wxALL|wxEXPAND, 5 );
	
	session_host = new wxStaticText( connection_info_input, wxID_ANY, wxT("Host (Your IP)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	session_host->Wrap( -1 );
	input_form_wrapper_sizer->Add( session_host, 0, wxALL|wxEXPAND, 5 );
	
	session_host_input = new wxTextCtrl( connection_info_input, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_form_wrapper_sizer->Add( session_host_input, 0, wxALL|wxEXPAND, 5 );
	
	session_host_port = new wxStaticText( connection_info_input, wxID_ANY, wxT("Host Port (Port to Connect from)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	session_host_port->Wrap( -1 );
	input_form_wrapper_sizer->Add( session_host_port, 0, wxALL|wxEXPAND, 5 );
	
	session_host_port_input = new wxTextCtrl( connection_info_input, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_form_wrapper_sizer->Add( session_host_port_input, 0, wxALL|wxEXPAND, 5 );
	
	session_other_host = new wxStaticText( connection_info_input, wxID_ANY, wxT("Other Host (Host IP to connect to)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	session_other_host->Wrap( -1 );
	input_form_wrapper_sizer->Add( session_other_host, 0, wxALL|wxEXPAND, 5 );
	
	session_other_host_input = new wxTextCtrl( connection_info_input, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_form_wrapper_sizer->Add( session_other_host_input, 0, wxALL|wxEXPAND, 5 );
	
	session_other_host_port = new wxStaticText( connection_info_input, wxID_ANY, wxT("Other Host Port (Port to connect to)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	session_other_host_port->Wrap( -1 );
	input_form_wrapper_sizer->Add( session_other_host_port, 0, wxALL|wxEXPAND, 5 );
	
	session_other_host_port_input = new wxTextCtrl( connection_info_input, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_form_wrapper_sizer->Add( session_other_host_port_input, 0, wxALL|wxEXPAND, 5 );
	
	save_session_settings_button = new wxButton( connection_info_input, wxID_ANY, wxT("Save Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	input_form_wrapper_sizer->Add( save_session_settings_button, 0, wxALL|wxEXPAND, 0 );
	
	
	connection_info_input->SetSizer( input_form_wrapper_sizer );
	connection_info_input->Layout();
	input_form_wrapper_sizer->Fit( connection_info_input );
	button_wrapper_sizer->Add( connection_info_input, 0, wxALL|wxEXPAND, 0 );
	
	current_settings_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	current_settings_panel->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* current_settings_wrapper_sizer;
	current_settings_wrapper_sizer = new wxBoxSizer( wxVERTICAL );
	
	current_settings_title = new wxStaticText( current_settings_panel, wxID_ANY, wxT("Current Settings"), wxDefaultPosition, wxDefaultSize, 0 );
	current_settings_title->Wrap( -1 );
	current_settings_wrapper_sizer->Add( current_settings_title, 0, wxALL|wxEXPAND, 5 );
	
	cs_s_name = new wxStaticText( current_settings_panel, wxID_ANY, wxT("Session Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	cs_s_name->Wrap( -1 );
	current_settings_wrapper_sizer->Add( cs_s_name, 0, wxALL|wxEXPAND, 5 );
	
	cs_s_name_info = new wxStaticText( current_settings_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	cs_s_name_info->Wrap( -1 );
	cs_s_name_info->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	current_settings_wrapper_sizer->Add( cs_s_name_info, 0, wxALL|wxEXPAND, 5 );
	
	cs_host_ip_port = new wxStaticText( current_settings_panel, wxID_ANY, wxT("Host : Port"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	cs_host_ip_port->Wrap( -1 );
	cs_host_ip_port->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	
	current_settings_wrapper_sizer->Add( cs_host_ip_port, 0, wxALL|wxEXPAND, 5 );
	
	cs_host_ip_port_info = new wxStaticText( current_settings_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	cs_host_ip_port_info->Wrap( -1 );
	cs_host_ip_port_info->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	current_settings_wrapper_sizer->Add( cs_host_ip_port_info, 0, wxALL|wxEXPAND, 5 );
	
	cs_other_host_ip_port = new wxStaticText( current_settings_panel, wxID_ANY, wxT("Other Host : Port"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	cs_other_host_ip_port->Wrap( -1 );
	current_settings_wrapper_sizer->Add( cs_other_host_ip_port, 0, wxALL|wxEXPAND, 5 );
	
	cs_other_host_ip_port_info = new wxStaticText( current_settings_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	cs_other_host_ip_port_info->Wrap( -1 );
	cs_other_host_ip_port_info->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	current_settings_wrapper_sizer->Add( cs_other_host_ip_port_info, 0, wxALL|wxEXPAND, 5 );
	
	
	current_settings_panel->SetSizer( current_settings_wrapper_sizer );
	current_settings_panel->Layout();
	current_settings_wrapper_sizer->Fit( current_settings_panel );
	button_wrapper_sizer->Add( current_settings_panel, 1, wxALIGN_TOP|wxALL|wxEXPAND, 0 );
	
	
	main_content_sizer->Add( button_wrapper_sizer, 1, wxEXPAND, 5 );
	
	chat_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	chat_panel->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* chat_wrapper_sizer;
	chat_wrapper_sizer = new wxBoxSizer( wxVERTICAL );
	
	chat_text_output = new wxStaticText( chat_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	chat_text_output->Wrap( -1 );
	chat_text_output->SetBackgroundColour( wxColour( 240, 240, 240 ) );
	
	chat_wrapper_sizer->Add( chat_text_output, 7, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* input_wrapper_sizer;
	input_wrapper_sizer = new wxBoxSizer( wxHORIZONTAL );
	
	chat_text_input = new wxTextCtrl( chat_panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	input_wrapper_sizer->Add( chat_text_input, 5, wxALL|wxEXPAND, 5 );
	
	send_button = new wxButton( chat_panel, wxID_ANY, wxT("SEND"), wxDefaultPosition, wxDefaultSize, 0 );
	input_wrapper_sizer->Add( send_button, 1, wxALL|wxEXPAND, 5 );
	
	
	chat_wrapper_sizer->Add( input_wrapper_sizer, 1, wxEXPAND, 5 );
	
	
	chat_panel->SetSizer( chat_wrapper_sizer );
	chat_panel->Layout();
	chat_wrapper_sizer->Fit( chat_panel );
	main_content_sizer->Add( chat_panel, 5, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( main_content_sizer );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	connect_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_connect ), NULL, this );
	disconnect_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_disconnect ), NULL, this );
	session_name_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_session_name_input ), NULL, this );
	session_host_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_host_input ), NULL, this );
	session_host_port_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_host_port_input ), NULL, this );
	session_other_host_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_other_host_input ), NULL, this );
	session_other_host_port_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_other_host_port ), NULL, this );
	save_session_settings_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_save_settings ), NULL, this );
	chat_text_input->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_chat_text_input ), NULL, this );
}

globalFrame::~globalFrame()
{
	// Disconnect Events
	connect_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_connect ), NULL, this );
	disconnect_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_disconnect ), NULL, this );
	session_name_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_session_name_input ), NULL, this );
	session_host_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_host_input ), NULL, this );
	session_host_port_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_host_port_input ), NULL, this );
	session_other_host_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_other_host_input ), NULL, this );
	session_other_host_port_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_other_host_port ), NULL, this );
	save_session_settings_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( globalFrame::handle_save_settings ), NULL, this );
	chat_text_input->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( globalFrame::handle_chat_text_input ), NULL, this );
	
}
