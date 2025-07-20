#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include "GL/gl.h"
#include <GLFW/glfw3.h>


int main(){
    std::cout << "Hello World" << std::endl;
    
    glfwSetErrorCallback([](int code, const char* desc){
    std::cerr << "GLFW Error " << code << ": " << desc << "\n";
    });

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(800, 600, "My GLFW Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
        
    }
    glfwMakeContextCurrent(window);
    // (Load OpenGL functions here, e.g. with GLAD)

    VkInstance instance;
    VkApplicationInfo appInfo = {
        VK_STRUCTURE_TYPE_APPLICATION_INFO,  // sType
        nullptr,                             // pNext
        "VulkanGLFW",                        // pApplicationName
        VK_MAKE_VERSION(1,0,0),              // applicationVersion
        "No Engine",                         // pEngineName
        VK_MAKE_VERSION(1,0,0),              // engineVersion
        VK_API_VERSION_1_0                   // apiVersion
    };
    appInfo.pApplicationName = "VulkanGLFW";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Get required extensions from GLFW
    uint32_t extCount = 0;
    const char** extensions = glfwGetRequiredInstanceExtensions(&extCount);

    VkInstanceCreateInfo createInfo = {
    VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,  // sType
    nullptr,                                 // pNext
    0,                                       // flags
    &appInfo,                                // pApplicationInfo
    extCount,                                // enabledExtensionCount
    extensions,                              // ppEnabledExtensionNames
    0,                                       // enabledLayerCount
    nullptr                                  // ppEnabledLayerNames
    };
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance\n";
        return -1;
    }




    while (!glfwWindowShouldClose(window)) {
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;



}