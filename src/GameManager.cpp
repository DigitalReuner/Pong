#include "GameManager.hpp"
#include <iostream>

void myKeyfunc(GLFWwindow *, int key, int scancode, int action, int mods){
    std::cout << "keypress: " << key  << "\n"
        << "scancode:" << scancode << "\n"
        << "action:" << action<< "\n"
        << "mods:" << mods << std::endl;
}

GameManager::GameManager()
{
app.Init();     
app.keyfunc.push_back(keyCallback<myKeyfunc,GLFW_KEY_W>);
}

void GameManager::run(){
while (!app.shouldWindowClose()) {
    app.mainLoopStep();
}
   
}

GameManager::~GameManager()
{
    app.cleanup();
}
