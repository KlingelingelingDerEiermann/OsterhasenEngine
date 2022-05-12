#include "Osterhase_Renderer.h"
#include "Osterhase_VulkanHilfsmittel.h"
#include "Osterhase_Werkzeuge.h"
#include "Osterhase_Protokollierung.h"
#include <Windows.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

typedef struct Osterhase_RendererImpl {
    VkInstance instanz;
    VkSurfaceKHR oberflaeche;
    VkPhysicalDevice physisches_geraet;
    VkDevice geraet;
    VkQueue warteschlange;
    VkSwapchainKHR wechselkette;
    unsigned bilder_laenge;
    VkImage* bilder;
    VkImageView* bild_betrachtungen;
    VkFence gartenzaun;
    VkSemaphore bild_anfrage_semaphore;
    VkSemaphore render_semaphore;
    VkCommandPool befehls_becken;
    VkCommandBuffer befehls_puffer;
    unsigned laenge, hoehe;
} Osterhase_RendererImpl;

static VkPhysicalDevice GetPhysicalDevice(VkInstance instance) {
    unsigned laenge;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkEnumeratePhysicalDevices(instance, &laenge, NULL), "Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich");

    VkPhysicalDevice* physical_devices = malloc(sizeof(VkPhysicalDevice) * laenge);
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkEnumeratePhysicalDevices(instance, &laenge, physical_devices), "Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich");

    VkPhysicalDevice physical_device = physical_devices[0];
    free(physical_devices);

    return physical_device;
}

Osterhase_Renderer Osterhase_Renderer_Erstellen(Osterhase_Fenster fenster, unsigned test_modus) {
    Osterhase_RendererImpl* impl = malloc(sizeof(Osterhase_RendererImpl));

    VkApplicationInfo application_info;
    ZeroMemory(&application_info, sizeof(VkApplicationInfo));
    application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.pApplicationName = "Osterhase_App";
    application_info.applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
    application_info.pEngineName = "Osterhase_Renderer";
    application_info.engineVersion = VK_MAKE_API_VERSION(0, 0, 1, 0);
    application_info.apiVersion = VK_API_VERSION_1_3;

    const char* layers[] = {"VK_LAYER_KHRONOS_validation"};
    const char* extensions[] = {"VK_KHR_surface", "VK_KHR_win32_surface"};

    VkInstanceCreateInfo instanz_kreierungs_struktur;
    ZeroMemory(&instanz_kreierungs_struktur, sizeof(VkInstanceCreateInfo));
    instanz_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanz_kreierungs_struktur.pApplicationInfo = &application_info;
    instanz_kreierungs_struktur.enabledLayerCount = test_modus ? OSTERHASE_SEQUENZLAENGE(layers) : 0;
    instanz_kreierungs_struktur.ppEnabledLayerNames = test_modus ? layers : 0;
    instanz_kreierungs_struktur.enabledExtensionCount = OSTERHASE_SEQUENZLAENGE(extensions);
    instanz_kreierungs_struktur.ppEnabledExtensionNames = extensions;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateInstance(&instanz_kreierungs_struktur, NULL, &impl->instanz), "vkCreateInstance");

    Osterhase_Protokollierung_SchreibeInformation("[Renderer] Die Instanz wurde erstellt");

    VkWin32SurfaceCreateInfoKHR zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur;
    ZeroMemory(&zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur, sizeof(VkWin32SurfaceCreateInfoKHR));
    zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur.hinstance = GetModuleHandle(NULL);
    zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur.hwnd = (HWND)fenster;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateWin32SurfaceKHR(impl->instanz, &zweiunddreissiges_fenster_oberflaechen_kreierungs_struktur, NULL, &impl->oberflaeche), "Die Oberfläche is bies wuhr");

    Osterhase_Protokollierung_SchreibeInformation("[Renderer] Die Oberfläche wurde erstellt");

    const float DEFAULT_PRIO = 1.0f;

    VkDeviceQueueCreateInfo geraet_warteschlangen_kreierungs_struktur;
    ZeroMemory(&geraet_warteschlangen_kreierungs_struktur, sizeof(VkDeviceQueueCreateInfo));
    geraet_warteschlangen_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    geraet_warteschlangen_kreierungs_struktur.queueCount = 1;
    geraet_warteschlangen_kreierungs_struktur.pQueuePriorities = &DEFAULT_PRIO;

    const char* device_extensions[] = {"VK_KHR_swapchain"};

    VkPhysicalDeviceDynamicRenderingFeatures physisches_geraet_dynamisches_rendering_features;
    ZeroMemory(&physisches_geraet_dynamisches_rendering_features, sizeof(VkPhysicalDeviceDynamicRenderingFeatures));
    physisches_geraet_dynamisches_rendering_features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES;

    VkPhysicalDeviceFeatures2 physisches_geraet_features_2;
    ZeroMemory(&physisches_geraet_features_2, sizeof(VkPhysicalDeviceFeatures2));
    physisches_geraet_features_2.pNext = &physisches_geraet_dynamisches_rendering_features;

    VkDeviceCreateInfo geraet_kreierungs_struktur;
    ZeroMemory(&geraet_kreierungs_struktur, sizeof(VkDeviceCreateInfo));
    geraet_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    geraet_kreierungs_struktur.pNext = &physisches_geraet_features_2;
    geraet_kreierungs_struktur.queueCreateInfoCount = 1;
    geraet_kreierungs_struktur.pQueueCreateInfos = &geraet_warteschlangen_kreierungs_struktur;
    geraet_kreierungs_struktur.enabledExtensionCount = OSTERHASE_SEQUENZLAENGE(device_extensions);
    geraet_kreierungs_struktur.ppEnabledExtensionNames = device_extensions;

    impl->physisches_geraet = GetPhysicalDevice(impl->instanz);
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateDevice(impl->physisches_geraet, &geraet_kreierungs_struktur, NULL, &impl->geraet), "Dat Gerät is bies wuhr");

    Osterhase_Protokollierung_SchreibeInformation("[Renderer] Das Gerät wurde erstellt");

    vkGetDeviceQueue(impl->geraet, 0, 0, &impl->warteschlange);
    Osterhase_Protokollierung_SchreibeInformation("[Renderer] Das Warteschlange wurde vom Gerät abgefragt");

    VkSurfaceCapabilitiesKHR oberflaechen_faehigkeiten;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(impl->physisches_geraet, impl->oberflaeche, &oberflaechen_faehigkeiten), "Die Oberflächen Faehigkeiten sind bies wuhr");
    impl->laenge = oberflaechen_faehigkeiten.currentExtent.width;
    impl->hoehe = oberflaechen_faehigkeiten.currentExtent.height;

    VkSwapchainCreateInfoKHR wechselketten_kreierungs_struktur;
    ZeroMemory(&wechselketten_kreierungs_struktur, sizeof(VkSwapchainCreateInfoKHR));
    wechselketten_kreierungs_struktur.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    wechselketten_kreierungs_struktur.surface = impl->oberflaeche;
    wechselketten_kreierungs_struktur.minImageCount = 2;
    wechselketten_kreierungs_struktur.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
    wechselketten_kreierungs_struktur.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wechselketten_kreierungs_struktur.imageExtent.width = oberflaechen_faehigkeiten.currentExtent.width;
    wechselketten_kreierungs_struktur.imageExtent.height = oberflaechen_faehigkeiten.currentExtent.height;
    wechselketten_kreierungs_struktur.imageArrayLayers = 1;
    wechselketten_kreierungs_struktur.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    wechselketten_kreierungs_struktur.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    wechselketten_kreierungs_struktur.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    wechselketten_kreierungs_struktur.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    wechselketten_kreierungs_struktur.presentMode = VK_PRESENT_MODE_FIFO_KHR;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkCreateSwapchainKHR(impl->geraet, &wechselketten_kreierungs_struktur, NULL, &impl->wechselkette), "Die Wechselkette is bies wuhr");

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkGetSwapchainImagesKHR(impl->geraet, impl->wechselkette, &impl->bilder_laenge, NULL), "Die Bilder sein bies wuhr");
    impl->bilder = malloc(impl->bilder_laenge * sizeof(VkImage));
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkGetSwapchainImagesKHR(impl->geraet, impl->wechselkette, &impl->bilder_laenge, impl->bilder), "Die Bilder sein bies wuhr");
    impl->bild_betrachtungen = malloc(impl->bilder_laenge * sizeof(VkImageView));

    for(unsigned i = 0; i < impl->bilder_laenge; i++) {
        impl->bild_betrachtungen[i] = Osterhase_VulkanHilfsmittel_ErstelleEinfacheFarbImageView(impl->geraet, impl->bilder[i], VK_FORMAT_B8G8R8A8_UNORM);
    }

    impl->bild_anfrage_semaphore = Osterhase_VulkanHilfsmittel_ErstelleSemaphore(impl->geraet, 0);
    impl->render_semaphore = Osterhase_VulkanHilfsmittel_ErstelleSemaphore(impl->geraet, 0);
    impl->gartenzaun = Osterhase_VulkanHilfsmittel_ErstelleGartenzaun(impl->geraet, 0);

    impl->befehls_becken = Osterhase_VulkanHilfsmittel_ErstelleKommandoBecken(impl->geraet, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT, 0);
    impl->befehls_puffer = Osterhase_VulkanHilfsmittel_ErstelleKommandoPuffer(impl->geraet, impl->befehls_becken);

    return (Osterhase_Renderer)impl;
}

void Osterhase_Renderer_Leeren(Osterhase_Renderer renderer) {
    Osterhase_RendererImpl* impl = (Osterhase_RendererImpl*)renderer;

    vkDeviceWaitIdle(impl->geraet);

    vkFreeCommandBuffers(impl->geraet, impl->befehls_becken, 1, &impl->befehls_puffer);
    vkDestroyCommandPool(impl->geraet, impl->befehls_becken, NULL);

    vkDestroyFence(impl->geraet, impl->gartenzaun, NULL);
    vkDestroySemaphore(impl->geraet, impl->render_semaphore, NULL);
    vkDestroySemaphore(impl->geraet, impl->bild_anfrage_semaphore, NULL);

    for(unsigned i = 0; i < impl->bilder_laenge; i++) {
        vkDestroyImageView(impl->geraet, impl->bild_betrachtungen[i], NULL);
    }
    free(impl->bild_betrachtungen);
    free(impl->bilder);
    vkDestroySwapchainKHR(impl->geraet, impl->wechselkette, NULL);
    vkDestroyDevice(impl->geraet, NULL);
    vkDestroySurfaceKHR(impl->instanz, impl->oberflaeche, NULL);
    vkDestroyInstance(impl->instanz, NULL);

    free(impl);
}

unsigned Osterhase_Renderer_BeginneZeichnen(Osterhase_Renderer renderer) {
    Osterhase_RendererImpl* impl = (Osterhase_RendererImpl*)renderer;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkResetCommandBuffer(impl->befehls_puffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT), "Der Befehlspuffer is bies wuhr");
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkResetCommandPool(impl->geraet, impl->befehls_becken, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT), "Das Befehlsbecken is bies wuhr");

    unsigned bild_index;
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkAcquireNextImageKHR(impl->geraet, impl->wechselkette, UINT64_MAX, impl->bild_anfrage_semaphore, VK_NULL_HANDLE, &bild_index), "Die Wechselkette hat sich geweigert, das Bild zur Verfügung zu stellen");

    VkCommandBufferBeginInfo befehls_puffer_begin_information;
    ZeroMemory(&befehls_puffer_begin_information, sizeof(VkCommandBufferBeginInfo));
    befehls_puffer_begin_information.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    befehls_puffer_begin_information.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkBeginCommandBuffer(impl->befehls_puffer, &befehls_puffer_begin_information), "Der Befehlspuffer is bies wuhr");

    VkImageMemoryBarrier bild_speicher_barriere;
    ZeroMemory(&bild_speicher_barriere, sizeof(VkImageMemoryBarrier));
    bild_speicher_barriere.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    bild_speicher_barriere.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    bild_speicher_barriere.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    bild_speicher_barriere.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    bild_speicher_barriere.image = impl->bilder[bild_index];
    bild_speicher_barriere.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    bild_speicher_barriere.subresourceRange.levelCount = 1;
    bild_speicher_barriere.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(impl->befehls_puffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, 0, NULL, 0, NULL,
                         1, &bild_speicher_barriere);

    VkRenderingAttachmentInfo rendering_anhang_information;
    ZeroMemory(&rendering_anhang_information, sizeof(VkRenderingAttachmentInfo));
    rendering_anhang_information.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
    rendering_anhang_information.imageView = impl->bild_betrachtungen[bild_index];
    rendering_anhang_information.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    rendering_anhang_information.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    rendering_anhang_information.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    rendering_anhang_information.clearValue.color.float32[0] = 0.0f;
    rendering_anhang_information.clearValue.color.float32[1] = 5.0f;
    rendering_anhang_information.clearValue.color.float32[2] = 8.0f;
    rendering_anhang_information.clearValue.color.float32[3] = 1.0f;

    VkRenderingInfo rendering_information;
    ZeroMemory(&rendering_information, sizeof(VkRenderingInfo));
    rendering_information.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
    rendering_information.renderArea.extent.width = impl->laenge;
    rendering_information.renderArea.extent.height = impl->hoehe;
    rendering_information.layerCount = 1;
    rendering_information.colorAttachmentCount = 1;
    rendering_information.pColorAttachments = &rendering_anhang_information;

    vkCmdBeginRendering(impl->befehls_puffer, &rendering_information);

    return bild_index;
}

void Osterhase_Renderer_EndeZeichnen(Osterhase_Renderer renderer, unsigned bild_index) {
    Osterhase_RendererImpl* impl = (Osterhase_RendererImpl*)renderer;

    vkCmdEndRendering(impl->befehls_puffer);

    VkImageMemoryBarrier bild_speicher_barriere;
    ZeroMemory(&bild_speicher_barriere, sizeof(VkImageMemoryBarrier));
    bild_speicher_barriere.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    bild_speicher_barriere.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    bild_speicher_barriere.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    bild_speicher_barriere.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    bild_speicher_barriere.image = impl->bilder[bild_index];
    bild_speicher_barriere.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    bild_speicher_barriere.subresourceRange.levelCount = 1;
    bild_speicher_barriere.subresourceRange.layerCount = 1;

    vkCmdPipelineBarrier(impl->befehls_puffer, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, NULL, 0, NULL,
                         1, &bild_speicher_barriere);

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkEndCommandBuffer(impl->befehls_puffer), "Der Befehlspuffer is bies wuhr");

    VkPipelineStageFlags wait_dst_stage_mask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo einreich_information;
    ZeroMemory(&einreich_information, sizeof(VkSubmitInfo));
    einreich_information.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    einreich_information.waitSemaphoreCount = 1;
    einreich_information.pWaitSemaphores = &impl->bild_anfrage_semaphore;
    einreich_information.pWaitDstStageMask = &wait_dst_stage_mask;
    einreich_information.commandBufferCount = 1;
    einreich_information.pCommandBuffers = &impl->befehls_puffer;
    einreich_information.signalSemaphoreCount = 1;
    einreich_information.pSignalSemaphores = &impl->render_semaphore;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkQueueSubmit(impl->warteschlange, 1, &einreich_information, impl->gartenzaun), "Die Einreich Info konnte nicht an die Warteschlange hinzugefügt werden");

    VkPresentInfoKHR presentierungs_information;
    ZeroMemory(&presentierungs_information, sizeof(VkPresentInfoKHR));
    presentierungs_information.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentierungs_information.waitSemaphoreCount = 1;
    presentierungs_information.pWaitSemaphores = &impl->render_semaphore;
    presentierungs_information.swapchainCount = 1;
    presentierungs_information.pSwapchains = &impl->wechselkette;
    presentierungs_information.pImageIndices = &bild_index;

    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkQueuePresentKHR(impl->warteschlange, &presentierungs_information), "Die Warteschlange hat sich geweigert, an der Wechselkette zu präsentieren");
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkWaitForFences(impl->geraet, 1, &impl->gartenzaun, VK_TRUE, UINT64_MAX), "vkWaitForFences");
    Osterhase_VulkanHilfsmittel_FehlermeldungWennNichtErfolgreich(vkResetFences(impl->geraet, 1, &impl->gartenzaun), "vkResetFences");
}