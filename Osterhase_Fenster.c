#include "Osterhase_Fenster.h"
#include "Osterhase_Renderer.h"
#include "Osterhase_Fehlermeldung.h"

#include <Windows.h>

static unsigned schleife_an = 1;

LRESULT CALLBACK FensterProzedur(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE:
            break;
        case WM_SIZE:
            break;
        case WM_DESTROY:
            schleife_an = 0;
            break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Osterhase_Fenster Osterhase_Fenster_Erstellen(const char* titel, unsigned laenge, unsigned hoehe) {
    HINSTANCE h_instance = GetModuleHandle(NULL);

    WNDCLASSEX wnd_class;
    ZeroMemory(&wnd_class, sizeof(WNDCLASSEX));
    wnd_class.cbSize = sizeof(WNDCLASSEX);
    wnd_class.lpszClassName = "DER_EIERMANN_HAT_DICKE_EIER";
    wnd_class.lpfnWndProc = FensterProzedur;
    wnd_class.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE + 1;
    wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd_class.hInstance = h_instance;

    if(!RegisterClassEx(&wnd_class)) {
        Osterhase_FehlermeldungZeigen(NULL, "RegisterClassEx ist fehlgeschlagen");
    }

    HWND h_wnd = CreateWindowEx(0, "DER_EIERMANN_HAT_DICKE_EIER",
                   titel,
                   WS_OVERLAPPEDWINDOW,
                   CW_USEDEFAULT,
                   CW_USEDEFAULT,
                   (int)laenge,
                   (int)hoehe,
                   NULL,
                   NULL,
                   h_instance,
                   NULL);

    if(h_wnd == NULL) {
        Osterhase_FehlermeldungZeigen(NULL, "CreateWindowEx ist fehlgeschlagen");
    }

    return (Osterhase_Fenster)h_wnd;
}

void Osterhase_Fenster_Leeren(Osterhase_Fenster fenster) {
    DestroyWindow((HWND)fenster);
    UnregisterClass("DER_EIERMANN_HAT_DICKE_EIER", GetModuleHandle(NULL));
}

void Osterhase_Fenster_Schleife(Osterhase_Fenster fenster, Osterhase_Renderer renderer, OsterhaseFensterSchleifeFunktion* funktion, void* benutzerdaten) {
    HWND h_wnd = (HWND)fenster;

    ShowWindow(h_wnd, SW_SHOW);
    UpdateWindow(h_wnd);

    schleife_an = 1;

    MSG botschaft;
    while(schleife_an == 1) {
        if(PeekMessage(&botschaft, h_wnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&botschaft);
            DispatchMessage(&botschaft);
        } else {
            funktion(renderer, benutzerdaten);
        }
    }
}

unsigned Osterhase_Fenster_BekommeLaenge(Osterhase_Fenster fenster) {
    RECT rect;
    if(!GetWindowRect((HWND)fenster, &rect)) {
        Osterhase_FehlermeldungZeigen(fenster, "GetWindowRect");
    }

    return rect.right;
}

unsigned Osterhase_Fenster_BekommeHoehe(Osterhase_Fenster fenster) {
    RECT rect;
    if(!GetWindowRect((HWND)fenster, &rect)) {
        Osterhase_FehlermeldungZeigen(fenster, "GetWindowRect");
    }

    return rect.bottom;
}