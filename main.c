#include "Osterhase_Protokollierung.h"
#include "Osterhase_Fenster.h"
#include "Osterhase_Renderer.h"

void Osterhase_Schleife(Osterhase_Renderer renderer, void* benutzerdaten) {
    unsigned bild_index = Osterhase_Renderer_BeginneZeichnen(renderer);

    Osterhase_Renderer_EndeZeichnen(renderer, bild_index);
}

int main() {
    Osterhase_Protokollierung_Erstellen();
    Osterhase_Fenster fenster = Osterhase_Fenster_Erstellen("OsterhasenEngine by KlingelingelingDerEiermann", 1600, 900);
    Osterhase_Renderer renderer = Osterhase_Renderer_Erstellen(fenster, 1);

    Osterhase_Fenster_Schleife(fenster, renderer, Osterhase_Schleife, 0);

    Osterhase_Renderer_Leeren(renderer);
    Osterhase_Fenster_Leeren(fenster);
}
