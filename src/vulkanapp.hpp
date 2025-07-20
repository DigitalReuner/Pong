#define GLFW_INCLUDE_VULKAN
#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <GLFW/glfw3.h>

class VulkanApp {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;

    void initWindow();

    void initVulkan();

    void createInstance();

    void createSurface();

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        bool isComplete() { return graphicsFamily.has_value(); }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void pickPhysicalDevice();

    void createLogicalDevice();

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup();
};
