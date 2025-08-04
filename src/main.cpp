#include "vulkanapp.hpp"

void myKeyfunc(GLFWwindow *, int key, int scancode, int action, int mods){
    std::cout << "keypress: " << key  << "\n"
        << "scancode:" << scancode << "\n"
        << "action:" << action<< "\n"
        << "mods:" << mods << std::endl;
}

int main() {
    VulkanApp app;
    try {
        app.Init();
        app.keyfunc.push_back(keyCallback<myKeyfunc,67>);
        while (!app.shouldWindowClose()) {
            app.mainLoopStep();
        }
        app.cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
