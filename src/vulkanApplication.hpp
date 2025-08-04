// VulkanApplication.hpp

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <limits>
#include <array>
#include <chrono>
#include <optional>

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan_raii.hpp>

#include <vulkan/vk_platform.h>

#include <vulkan/vulkan_profiles.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

#include <ktx.h>

typedef void AssetManagerType;

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define LOGI(...) printf(__VA_ARGS__); printf("\n")
#define LOGW(...) printf(__VA_ARGS__); printf("\n")
#define LOGE(...) fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_CXX11
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
constexpr uint64_t FenceTimeout = 100000000;
const std::string MODEL_PATH = "../models/viking_room.glb";
const std::string TEXTURE_PATH = "../textures/viking_room.ktx2";
constexpr int MAX_FRAMES_IN_FLIGHT = 2;
constexpr int MAX_OBJECTS = 3;

#ifndef VP_KHR_ROADMAP_2022_NAME
#define VP_KHR_ROADMAP_2022_NAME "VP_KHR_roadmap_2022"
#endif

#ifndef VP_KHR_ROADMAP_2022_SPEC_VERSION
#define VP_KHR_ROADMAP_2022_SPEC_VERSION 1
#endif

struct AppInfo {
    bool profileSupported = false;
    VpProfileProperties profile;
};

#ifdef NDEBUG
constexpr bool enableValidationLayers = false;
#else
constexpr bool enableValidationLayers = true;
#endif

#include "vertex.hpp"
#include "gameObject.hpp"

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

class VulkanApplication {
public:
    void run();

private:

    GLFWwindow* window = nullptr;

    AppInfo appInfo = {};
    vk::raii::Context                context;
    vk::raii::Instance               instance       = nullptr;
    vk::raii::DebugUtilsMessengerEXT debugMessenger = nullptr;
    vk::raii::SurfaceKHR             surface        = nullptr;
    vk::raii::PhysicalDevice         physicalDevice = nullptr;
    vk::raii::Device                 device         = nullptr;
    uint32_t                         queueIndex     = ~0;
    vk::raii::Queue                  queue          = nullptr;

    vk::raii::SwapchainKHR swapChain = nullptr;
    std::vector<vk::Image> swapChainImages;
    vk::Format swapChainImageFormat = vk::Format::eUndefined;
    vk::Extent2D swapChainExtent;
    std::vector<vk::raii::ImageView> swapChainImageViews;

    vk::raii::DescriptorSetLayout descriptorSetLayout = nullptr;
    vk::raii::PipelineLayout pipelineLayout = nullptr;
    vk::raii::Pipeline graphicsPipeline = nullptr;

    vk::raii::Image depthImage = nullptr;
    vk::raii::DeviceMemory depthImageMemory = nullptr;
    vk::raii::ImageView depthImageView = nullptr;

    vk::raii::Image textureImage = nullptr;
    vk::raii::DeviceMemory textureImageMemory = nullptr;
    vk::raii::ImageView textureImageView = nullptr;
    vk::raii::Sampler textureSampler = nullptr;
    vk::Format textureImageFormat = vk::Format::eUndefined;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    vk::raii::Buffer vertexBuffer = nullptr;
    vk::raii::DeviceMemory vertexBufferMemory = nullptr;
    vk::raii::Buffer indexBuffer = nullptr;
    vk::raii::DeviceMemory indexBufferMemory = nullptr;

    std::array<GameObject, MAX_OBJECTS> gameObjects;

    vk::raii::DescriptorPool descriptorPool = nullptr;

    vk::raii::CommandPool commandPool = nullptr;
    std::vector<vk::raii::CommandBuffer> commandBuffers;

    std::vector<vk::raii::Semaphore> presentCompleteSemaphore;
    std::vector<vk::raii::Semaphore> renderFinishedSemaphore;
    std::vector<vk::raii::Fence> inFlightFences;
    uint32_t currentFrame = 0;

    bool framebufferResized = false;

    std::vector<const char*> requiredDeviceExtension;

    void initWindow();
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

public:
    void initVulkan();

private:
    void mainLoop();

    void cleanupSwapChain();

    void cleanup();

    void recreateSwapChain();

    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createDescriptorSetLayout();
    void createGraphicsPipeline();
    void createCommandPool();
    void createDepthResources();
    vk::Format findSupportedFormat(const std::vector<vk::Format>& candidates, vk::ImageTiling tiling, vk::FormatFeatureFlags features) const;
    [[nodiscard]] vk::Format findDepthFormat() const;
    static bool hasStencilComponent(vk::Format format);
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    vk::raii::ImageView createImageView(vk::raii::Image& image, vk::Format format, vk::ImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::raii::Image& image, vk::raii::DeviceMemory& imageMemory);
    void transitionImageLayout(const vk::raii::Image& image, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
    void copyBufferToImage(const vk::raii::Buffer& buffer, vk::raii::Image& image, uint32_t width, uint32_t height);
    void loadModel();
    void createVertexBuffer();
    void createIndexBuffer();
    void setupGameObjects();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::raii::Buffer& buffer, vk::raii::DeviceMemory& bufferMemory);
    std::unique_ptr<vk::raii::CommandBuffer> beginSingleTimeCommands();
    void endSingleTimeCommands(const vk::raii::CommandBuffer& commandBuffer) const;
    void copyBuffer(vk::raii::Buffer & srcBuffer, vk::raii::Buffer & dstBuffer, vk::DeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
    void createCommandBuffers();
    void recordCommandBuffer(uint32_t imageIndex);
    void transition_image_layout(
        uint32_t imageIndex,
        vk::ImageLayout old_layout,
        vk::ImageLayout new_layout,
        vk::AccessFlags2 src_access_mask,
        vk::AccessFlags2 dst_access_mask,
        vk::PipelineStageFlags2 src_stage_mask,
        vk::PipelineStageFlags2 dst_stage_mask
        );
    void createSyncObjects();
    void updateUniformBuffers();
    void drawFrame();
    [[nodiscard]] vk::raii::ShaderModule createShaderModule(const std::vector<char>& code) const;
    static vk::Format chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
    static vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities);
    [[nodiscard]] std::vector<const char*> getRequiredExtensions() const;
    [[nodiscard]] bool checkValidationLayerSupport() const;
    static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(vk::DebugUtilsMessageSeverityFlagBitsEXT severity, vk::DebugUtilsMessageTypeFlagsEXT type, const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData, void*);
    std::vector<char> readFile(const std::string& filename);
};
