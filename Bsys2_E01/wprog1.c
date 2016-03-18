// WPROG1.CPP
//
// Beispielsprogramm "Hello World!" für die WIN32 API
// ==================================================
//
// 22.06.00/EG
//
// Entwicklungsumgebung:
// MS Visual Studio for C/C++ 6.0 under Windows NT 4.0 SP5
//

#define STRICT
#include <windows.h>
#include <string.h>

// Vorwärtsdeklaration der Fensterprozedur
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// Vorwärtsdeklaration der Hilfsfunktion für Fehlerausgabe
void err_msg ( HWND hwnd, char *p );


//*************************************************************
// WinMain -- Das Hauptprogramm (als Primary Thread gestartet)
//*************************************************************
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, int nCmdShow)
{
    HWND        hwnd;           // Window handle: Identifikation für erzeugtes Fenster
    WNDCLASS    wndclass;       // Class structure: Datenstruktur für neue Fensterklasse
    MSG         msg;            // Msg data structure: Meldungsstruktur für Ereignismeldungen

    if (!hPrevInstance)         // Bedingung immer erfüllt für Windows-95/98/NT/2000
    {
        wndclass.style         = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc   = WndProc;
        wndclass.cbClsExtra    = 0;
        wndclass.cbWndExtra    = 0;
        wndclass.hInstance     = hInstance;
        wndclass.hIcon         = LoadIcon (0, IDI_APPLICATION);
        wndclass.hCursor       = LoadCursor (0, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
        wndclass.lpszMenuName  = NULL;
        wndclass.lpszClassName = "wprog1";

		ATOM ret = RegisterClass (&wndclass); // Neue Fensterklasse beim BS registrieren
		if (ret == 0) 
		{
			err_msg (NULL, "Unable to create class");
            return FALSE;
		}
    }

	hwnd = CreateWindow (        // Ein Fenster der neuen Fensterklasse erzeugen   
        "wprog1",                // Class name; muss wndclass.lpszClassName entsprechen
        "wprog1: Hello Zafer",   // Fenstertitel (window caption)
        WS_OVERLAPPEDWINDOW,     // Fensterstil (style)
        50,                      // Anfängliche Fensterposition in X und y Pixelwerten
        50,                      // (falls BS automatisch wählen soll: CW_USEDEFAULT nehmen)
        250,                     // Anfangsbreite und Höhe in Pixeln
        150,                     // (falls BS automatisch wählen soll: CW_USEDEFAULT nehmen)
        0,                       // Identifikation des Elternfensters (hier: keines)
        0,                       // Identifikation des Menüs (hier: keines vorhanden)
        hInstance,               // Identifikation der laufenden Programminstanz (Thread Id.)
        NULL);                   // Erzeugungsparameter (hier: keine)

	if (hwnd == 0) {
	    err_msg (NULL,"Unable to create window");
		return 0;
		}

	ShowWindow   (hwnd, nCmdShow);// Fenster zur Anzeige bringen
	UpdateWindow (hwnd);          // Fenster veranlassen den Anwendungsbereich neu zu zeichnen

	while (GetMessage (&msg, NULL, 0, 0) != FALSE) // Eine Meldung aus Ereignis-WS entnehmen
		{
		DispatchMessage (&msg);   // Ereignis der richtigen Fensterprozedur weitergeben
		}
    return (int)msg.wParam;       // Fenster wurde geschlossen: beende Programm
}



//*********************************************************
// WndProc -- Die Fensterprozedur (window procedure)
//*********************************************************
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam )
{
    switch (iMsg)                  // Wähle die richtige Bearbeitungssequenz entsprechend
    {                              //  dem Meldungstyp
		case WM_DESTROY:           // Fenster wurde zerstört
			PostQuitMessage(0);    // Schreibe WM_QUIT in Ereignis-WS, setze Programmstatus (hier:0)
			return 0;

        case WM_PAINT:             // Fenster soll Anwendungsbereich neu zeichnen
			{
			PAINTSTRUCT		ps;
			HDC	hdc = BeginPaint ( hwnd, &ps );
			char * psz = "Hello World!";
            TextOut (hdc, 0, 0, psz, (int)strlen(psz));
			EndPaint ( hwnd, &ps );
			}
			return 0;
 
        default:                   // Standardbehandlung für übrige Ereignisse (durch BS)
           return DefWindowProc (hwnd, iMsg, wParam, lParam);
    }
}


//************************************************************
// ERR_MSG -- Ausgabe einer Fehlermeldung (Hilfsfunktion)
//************************************************************
void err_msg (HWND hwnd, char *p)
{
	char	szMsg[1000];		// error message string
	DWORD	dwEcode;			// error code

	dwEcode = GetLastError ();  // ermittle genauen Fehlerkode
	wsprintf (szMsg, "%s, error code = %d", p, dwEcode ); // Setze Fehlertext in szMsg auf
	MessageBox (hwnd, szMsg, "Error", MB_OK); // Gib szMsg in einem Meldungsfenster aus
}



