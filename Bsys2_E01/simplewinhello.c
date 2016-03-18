//
//	Falls Sie ein möglichst einfaches "Hello World"-Programm unter
//	Windows suchen: hier ist es!


#include <windows.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     MessageBox (NULL, TEXT ("Hello World!"), TEXT ("HelloMsg"), 0) ;

     return 0 ;
}
