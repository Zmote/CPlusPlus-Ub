#include <wx/wx.h>
#include "zChatterUI.h"
#include <iostream>

class my_first_app : public wxApp
{
public :
	bool OnInit()
	{
		zChatterUI * mywindow = new zChatterUI(NULL);
		mywindow->Show();
		return true;
	}
private:
};

IMPLEMENT_APP(my_first_app);
