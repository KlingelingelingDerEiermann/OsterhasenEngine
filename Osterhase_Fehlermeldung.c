#include "Osterhase_Fehlermeldung.h"

#include <Windows.h>

static const char frage[] = "// Willst du die Fehlernachricht abspeichern?";

void Osterhase_FehlermeldungZeigen(Osterhase_Fenster fenster, const char* botschaft) {
    size_t frage_laenge = strlen(frage);
    size_t botschaft_laenge = strlen(botschaft);
    size_t laenge = frage_laenge + botschaft_laenge;

    char* totale_botschaft = malloc(laenge + 1);

    memcpy(totale_botschaft, botschaft, botschaft_laenge);
    memcpy(totale_botschaft + botschaft_laenge, frage, frage_laenge);
    totale_botschaft[laenge] = 0;

    if(MessageBoxA(NULL, totale_botschaft, "Majuuhsebeddanah, ein Fehler ist aufgetreten", MB_YESNOCANCEL) == IDYES) {

    }

    free(totale_botschaft);
}