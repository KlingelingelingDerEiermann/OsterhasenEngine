#include "Osterhase_Protokollierung.h"
#include <Windows.h>

void Osterhase_Protokollierung_Erstellen() {
    SetConsoleOutputCP(CP_UTF8);
}

void Osterhase_Protokollierung_SchreibeInformation(const char* nachricht, ...) {
    printf("[OsterhasenEngine] [Protokoll/INFORMATION]");

    va_list list;
    va_start(list, nachricht);
    vprintf(nachricht, list);
    va_end(list);

    putchar('\n');
}

void Osterhase_Protokollierung_SchreibeWarnung(const char* nachricht, ...) {
    printf("[OsterhasenEngine] [Protokoll/WARNUNG]");

    va_list list;
    va_start(list, nachricht);
    vprintf(nachricht, list);
    va_end(list);

    putchar('\n');
}

void Osterhase_Protokollierung_SchreibeFehler(const char* nachricht, ...) {
    printf("[OsterhasenEngine] [Protokoll/FEHLER]");

    va_list list;
    va_start(list, nachricht);
    vprintf(nachricht, list);
    va_end(list);

    putchar('\n');
}