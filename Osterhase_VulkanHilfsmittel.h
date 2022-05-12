#ifndef ALLESWUNDABAAH_VULKAN_HILFSMITTEL_H
#define ALLESWUNDABAAH_VULKAN_HILFSMITTEL_H

#include <vulkan/vulkan.h>

void Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(VkResult result, const char* name);

VkComponentMapping Osterhase_VulkanHilfsmittel_FarbkomponentenAbbildungNormal();

VkFence Osterhase_VulkanHilfsmittel_ErstelleGartenzaun(VkDevice geraet, VkFenceCreateFlags flags);
VkSemaphore Osterhase_VulkanHilfsmittel_ErstelleSemaphore(VkDevice geraet, VkSemaphoreCreateFlags flags);
VkImageView Osterhase_VulkanHilfsmittel_ErstelleEinfacheImageView(VkDevice geraet, VkImage bild, VkFormat format, int depth);
VkImageView Osterhase_VulkanHilfsmittel_ErstelleEinfacheFarbImageView(VkDevice geraet, VkImage bild, VkFormat format);
VkCommandPool Osterhase_VulkanHilfsmittel_ErstelleKommandoBecken(VkDevice geraet, VkCommandPoolCreateFlags flags, unsigned warteschlangen_familien_index);
VkCommandBuffer Osterhase_VulkanHilfsmittel_ErstelleKommandoPuffer(VkDevice geraet, VkCommandPool kommando_becken);

unsigned Osterhase_VulkanHilfsmittel_FindeDenRichtigenSpeichertyp(const VkPhysicalDeviceMemoryProperties* speicher_eigenschaften, unsigned speicher_typ_bits, VkMemoryPropertyFlags speicher_eigenschaft_flaggen);

#endif //ALLESWUNDABAAH_VULKAN_HILFSMITTEL_H