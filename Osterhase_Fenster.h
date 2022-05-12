#ifndef ALLES_WUNDABAAH_FENSTER_H
#define ALLES_WUNDABAAH_FENSTER_H

typedef void* Osterhase_Fenster;
typedef void(OsterhaseFensterSchleifeFunktion)(void* renderer, void* benutzerdaten);

Osterhase_Fenster Osterhase_Fenster_Erstellen(const char* titel, unsigned laenge, unsigned hoehe);
void Osterhase_Fenster_Leeren(Osterhase_Fenster fenster);
void Osterhase_Fenster_Schleife(Osterhase_Fenster fenster, void* renderer, OsterhaseFensterSchleifeFunktion* funktion, void* benutzerdaten);

unsigned Osterhase_Fenster_BekommeLaenge(Osterhase_Fenster fenster);
unsigned Osterhase_Fenster_BekommeHoehe(Osterhase_Fenster fenster);

#endif //ALLES_WUNDABAAH_FENSTER_H