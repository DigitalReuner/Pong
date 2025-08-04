
#include "GameManager.hpp"
#include "vulkanapp.hpp"



int main() {
    GameManager game{};
    try {
        game.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
