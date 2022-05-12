#ifndef ALLESWUNDABAAH_VULKAN_PROTOKOLLIERUNG_H
#define ALLESWUNDABAAH_VULKAN_PROTOKOLLIERUNG_H

#include <stdio.h>
#include <stdarg.h>

void Osterhase_Protokollierung_Erstellen();
void Osterhase_Protokollierung_SchreibeInformation(const char* nachricht, ...);
void Osterhase_Protokollierung_SchreibeWarnung(const char* nachricht, ...);
void Osterhase_Protokollierung_SchreibeFehler(const char* nachricht, ...);

#endif //ALLESWUNDABAAH_VULKAN_PROTOKOLLIERUNG_H