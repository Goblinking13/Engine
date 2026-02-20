#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "window.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "camera.h"
#include <vector>
#include "movable.h"


enum class controlMode {
     CAMERA, PLAYER
};

class EngineCore {
     private:
     game::window* gameWindow_;
     float lastTime_ = 0 , currentTime_ = 0, deltaTime_ = 0;

     // std::vector<game::movable*> gameMovables;
     std::vector<game::object*> gameObjects;

     float frames = 0.0f;
     float lastTime = 0.0f;


     void processInput();


     void addCamera(game::camera* camera);
     void addObject(game::object *object);


     public:
     EngineCore();
     void run();
     void gameLoop();
     ~EngineCore();
     void updateObjects();
     // void renderObjects();

     void calculateFPS();

};




