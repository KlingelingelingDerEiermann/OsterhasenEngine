#ifndef ALLESWUNDABAAH_RENDERER_H
#define ALLESWUNDABAAH_RENDERER_H

#include "Osterhase_Fenster.h"

typedef void* Osterhase_Renderer;

Osterhase_Renderer Osterhase_Renderer_Erstellen(Osterhase_Fenster fenster, unsigned test_modus);
void Osterhase_Renderer_Leeren(Osterhase_Renderer renderer);
unsigned Osterhase_Renderer_BeginneZeichnen(Osterhase_Renderer renderer);
void Osterhase_Renderer_EndeZeichnen(Osterhase_Renderer renderer, unsigned bild_index);

#endif //ALLESWUNDABAAH_RENDERER_H