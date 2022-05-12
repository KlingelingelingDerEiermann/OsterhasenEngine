#include "Osterhase_VulkanHilfsmittel.h"
#include "Osterhase_Fehlermeldung.h"
#include <Windows.h>

static const char nachricht[] = "Ein Vulkan Funktionsaufruf ist fehlgeschlagen: ";

VkComponentMapping Osterhase_VulkanHilfsmittel_FarbkomponentenAbbildungNormal() {
    VkComponentMapping farbkomponententen_abbildung;
    farbkomponententen_abbildung.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    farbkomponententen_abbildung.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    farbkomponententen_abbildung.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    farbkomponententen_abbildung.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    return farbkomponententen_abbildung;
}

void Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(VkResult result, const char* name) {
    if(result != VK_SUCCESS) {
        size_t nachricht_laenge = strlen(nachricht);
        size_t name_laenge = strlen(name);
        size_t laenge = nachricht_laenge + name_laenge;

        char* totale_botschaft = malloc(laenge + 1);
        memcpy(totale_botschaft, nachricht, nachricht_laenge);
        memcpy(totale_botschaft + nachricht_laenge, name, name_laenge);
        totale_botschaft[laenge] = 0;

        Osterhase_FehlermeldungZeigen(NULL, totale_botschaft);

        free(totale_botschaft);
    }
}

VkFence Osterhase_VulkanHilfsmittel_ErstelleGartenzaun(VkDevice geraet, VkFenceCreateFlags flags) {
    VkFenceCreateInfo gartenzaun_kreierungs_struktur;
    ZeroMemory(&gartenzaun_kreierungs_struktur, sizeof(VkFenceCreateInfo));
    gartenzaun_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    gartenzaun_kreierungs_struktur.flags = flags;

    VkFence gartenzaun;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateFence(geraet, &gartenzaun_kreierungs_struktur, NULL, &gartenzaun),
                                                                  "Majusebeddanah, dä Ustahoos hot dae zoun kaputtgemaaach");
    return gartenzaun;
}

VkSemaphore Osterhase_VulkanHilfsmittel_ErstelleSemaphore(VkDevice geraet, VkSemaphoreCreateFlags flags) {
    VkSemaphoreCreateInfo semaphoren_kreierungs_struktur;
    ZeroMemory(&semaphoren_kreierungs_struktur, sizeof(VkSemaphoreCreateInfo));
    semaphoren_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoren_kreierungs_struktur.flags = flags;

    VkSemaphore semaphore;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateSemaphore(geraet, &semaphoren_kreierungs_struktur, NULL, &semaphore),
                                                                  "Als die mudda un eich des morjens ous da kärch kohme, honn mir gesehen, dass dä äffgen ohs die semaphore demoliert hott");
    return semaphore;
}

VkImageView Osterhase_VulkanHilfsmittel_ErstelleEinfacheImageView(VkDevice geraet, VkImage bild, VkFormat format, int depth) {
    VkImageSubresourceRange bild_unterresourcen_spanne;
    ZeroMemory(&bild_unterresourcen_spanne, sizeof(VkImageSubresourceRange));
    bild_unterresourcen_spanne.aspectMask = depth == 0 ? VK_IMAGE_ASPECT_COLOR_BIT : VK_IMAGE_ASPECT_DEPTH_BIT;
    bild_unterresourcen_spanne.levelCount = 1;
    bild_unterresourcen_spanne.layerCount = 1;

    VkImageViewCreateInfo bild_betrachtungs_kreierungs_struktur;
    ZeroMemory(&bild_betrachtungs_kreierungs_struktur, sizeof(VkImageViewCreateInfo));
    bild_betrachtungs_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    bild_betrachtungs_kreierungs_struktur.image = bild;
    bild_betrachtungs_kreierungs_struktur.viewType = VK_IMAGE_VIEW_TYPE_2D;
    bild_betrachtungs_kreierungs_struktur.format = format;
    bild_betrachtungs_kreierungs_struktur.components = Osterhase_VulkanHilfsmittel_FarbkomponentenAbbildungNormal();
    bild_betrachtungs_kreierungs_struktur.subresourceRange = bild_unterresourcen_spanne;

    VkImageView bild_betrachtung;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateImageView(geraet, &bild_betrachtungs_kreierungs_struktur, NULL, &bild_betrachtung),
                                                                  "Als die mudda un eich im gochte woohre, homma gesehn, dass dat image nit mehr good angezeicht gewäst wohr");
    return bild_betrachtung;
}

VkImageView Osterhase_VulkanHilfsmittel_ErstelleEinfacheFarbImageView(VkDevice geraet, VkImage bild, VkFormat format) {
    return Osterhase_VulkanHilfsmittel_ErstelleEinfacheImageView(geraet, bild, format, 0);
}

VkCommandPool Osterhase_VulkanHilfsmittel_ErstelleKommandoBecken(VkDevice geraet, VkCommandPoolCreateFlags flags, unsigned warteschlangen_familien_index) {
    VkCommandPoolCreateInfo kommando_becken_kreierungs_struktur;
    ZeroMemory(&kommando_becken_kreierungs_struktur, sizeof(VkCommandPoolCreateInfo));
    kommando_becken_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    kommando_becken_kreierungs_struktur.flags = flags;
    kommando_becken_kreierungs_struktur.queueFamilyIndex = warteschlangen_familien_index;

    VkCommandPool kommando_becken;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateCommandPool(geraet, &kommando_becken_kreierungs_struktur, NULL, &kommando_becken),
                                                                  "Als dä bollzist kohm, hat die mudda et so an de nerwe bekomme, dass se fast ins befehlsbecken gefallen gewäst wohr");
    return kommando_becken;
}

VkCommandBuffer Osterhase_VulkanHilfsmittel_ErstelleKommandoPuffer(VkDevice geraet, VkCommandPool kommando_becken) {
    VkCommandBufferAllocateInfo kommando_puffer_allozierungs_struktur;
    ZeroMemory(&kommando_puffer_allozierungs_struktur, sizeof(VkCommandBufferAllocateInfo));
    kommando_puffer_allozierungs_struktur.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    kommando_puffer_allozierungs_struktur.commandPool = kommando_becken;
    kommando_puffer_allozierungs_struktur.commandBufferCount = 1;
    kommando_puffer_allozierungs_struktur.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    VkCommandBuffer kommando_puffer;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkAllocateCommandBuffers(geraet, &kommando_puffer_allozierungs_struktur, &kommando_puffer),
                                                                  "weile is schluss, wenn dä rullef mir noch einmal soht, dat eich die kwällmänner nit good gemach hon, kann dä seine kommands selber ausführe");
    return kommando_puffer;
}

unsigned Osterhase_VulkanHilfsmittel_FindeDenRichtigenSpeichertyp(const VkPhysicalDeviceMemoryProperties* speicher_eigenschaften, unsigned speicher_typ_bits, VkMemoryPropertyFlags speicher_eigenschaft_flaggen) {
    for (unsigned i = 0; i < speicher_eigenschaften->memoryTypeCount; ++i) {
        if ((speicher_typ_bits & (1 << i)) != 0 && (speicher_eigenschaften->memoryTypes[i].propertyFlags & speicher_eigenschaft_flaggen) == speicher_eigenschaft_flaggen) return i;
    }
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(VK_ERROR_DEVICE_LOST, "ihh haps nit hinpkomme, e valide typ für de spaischa se finne");
    return 0;
}

void Osterhase_VulkanHilfsmittel_ErstellePufferInRAM(VkPhysicalDevice physikalisches_geraet, VkDevice geraet, VkBufferUsageFlags puffer_benutzungsgrund, void* daten, size_t laenge_der_puffer_daten, VkMemoryPropertyFlags speicher_eigenschaft_flaggen,
    VkBuffer* puffer_herausschreiben, VkDeviceMemory* geraetschaftspeicher_herausschreiben) {
    VkBufferCreateInfo puffer_kreierungs_struktur;
    ZeroMemory(&puffer_kreierungs_struktur, sizeof(VkBufferCreateInfo));
    puffer_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    puffer_kreierungs_struktur.size = laenge_der_puffer_daten;
    puffer_kreierungs_struktur.usage = puffer_benutzungsgrund;

    VkBuffer puffer;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateBuffer(geraet, &puffer_kreierungs_struktur, NULL, &puffer), "Puffer konnte nicht erstellt werden");

    VkMemoryRequirements speicher_vorraussetzungen;
    vkGetBufferMemoryRequirements(geraet, puffer, &speicher_vorraussetzungen);

    VkPhysicalDeviceMemoryProperties physikalische_geraetschaft_speicher_eigenschaften;
    vkGetPhysicalDeviceMemoryProperties(physikalisches_geraet, &physikalische_geraetschaft_speicher_eigenschaften);

    unsigned speicher_typ_index = Osterhase_VulkanHilfsmittel_FindeDenRichtigenSpeichertyp(&physikalische_geraetschaft_speicher_eigenschaften,
                                                                                           speicher_vorraussetzungen.memoryTypeBits, speicher_eigenschaft_flaggen);

    VkMemoryAllocateInfo speicher_allozierungs_struktur;
    ZeroMemory(&speicher_allozierungs_struktur, sizeof(VkMemoryAllocateInfo));
    speicher_allozierungs_struktur.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    speicher_allozierungs_struktur.allocationSize = speicher_vorraussetzungen.size;
    speicher_allozierungs_struktur.memoryTypeIndex = speicher_typ_index;

    VkDeviceMemory auf_der_geraetschaft_liegender_speicher;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkAllocateMemory(geraet, &speicher_allozierungs_struktur, NULL, &auf_der_geraetschaft_liegender_speicher),
                                                                  "Der Speicher konnte auf der geraetschaft nicht bereit gestellt werden");
    vkBindBufferMemory(geraet, puffer, auf_der_geraetschaft_liegender_speicher, 0);

    void* puffer_speicher_addresse;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkMapMemory(geraet, auf_der_geraetschaft_liegender_speicher, 0, laenge_der_puffer_daten, 0, &puffer_kreierungs_struktur), "Der Speicher konnte nicht auf der Landkarte eingezeichnet werden");

    memcpy(puffer_speicher_addresse, daten, laenge_der_puffer_daten);
    vkUnmapMemory(geraet, auf_der_geraetschaft_liegender_speicher);

    *puffer_herausschreiben = puffer;
    *geraetschaftspeicher_herausschreiben = auf_der_geraetschaft_liegender_speicher;
}