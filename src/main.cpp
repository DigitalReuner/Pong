#include "vulkanapp.hpp"


#if PLATFORM_ANDROID
void android_main(android_app* app) {
    app_dummy();

    VulkanApplication vulkanApp;
    vulkanApp.run(app);
}
#else
int main() {
    try {
        VulkanApplication app;
        app.run();
    } catch (const std::exception& e) {
        LOGE("%s", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif
