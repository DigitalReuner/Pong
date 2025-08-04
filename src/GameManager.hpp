#include "vulkanapp.hpp"

class GameManager{
public:
    GameManager();
    ~GameManager();

    void run();

    VulkanApp app;
};