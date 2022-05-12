cmake_minimum_required(VERSION 3.22)
project(OsterhasenEngine C)

set(CMAKE_C_STANDARD 99)

find_package(Vulkan REQUIRED)

include_directories(${Vulkan_INCLUDE_DIRS})

add_executable(OsterhasenEngine main.c Osterhase_Fenster.h Osterhase_Fenster.c Osterhase_Fehlermeldung.h Osterhase_Fehlermeldung.c Osterhase_Renderer.h Osterhase_Renderer.c Osterhase_VulkanHilfsmittel.h Osterhase_VulkanHilfsmittel.c Osterhase_Werkzeuge.h Osterhase_Protokollierung.h Osterhase_Protokollierung.c)
target_link_libraries(OsterhasenEngine ${Vulkan_LIBRARIES})