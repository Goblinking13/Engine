#include "EngineCore.h"

#include <iostream>
#include<cmath>
#include "object.h"
#include "shader.h"
#include "mesh.h"
#include<glm/gtc/type_ptr.hpp>

#include "cube.h"
#include "grid.h"
#include "rotatedCube.h"
#include "texturedCube.h"
#include "model.h"
#include "raycaster.h"
#include "pointCloud.h"


EngineCore::EngineCore() {

  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
  }

  gameWindow_ = new game::window(1920,1280);
  // gameWindow_ = new game::window(600,600);



}

EngineCore::~EngineCore() {

  delete gameWindow_;
}


void EngineCore::gameLoop() {

  const float aspect = float(gameWindow_->getWidth()) / float(gameWindow_->getHeight());
  const float fov = glm::radians(45.0f);
  const float zNear = 0.01f;
  const float zFar = 1000.0f;


  // shader loading
  game::shader basicPhongShader("../shader/basicPhongVertex.vert","../shader/basicPhongFragment.frag" );
  basicPhongShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader textureShader("../shader/textureVertex.vert","../shader/textureFragment.frag");
  textureShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader textureBasicShader("../shader/textureBasicVertex.vert","../shader/textureBasicFragment.frag");
  textureBasicShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader basicShader("../shader/basicVertex.vert", "../shader/basicFragment.frag");
  basicShader.setPerspective(fov, aspect, zNear, zFar);

  // game::shader rayCasterShader("../shader/raycasterVertex.vert","../shader/raycasterGeometry.geom", "../shader/raycasterFragment.frag");
  game::shader rayCasterShader("../shader/raycasterVertex.vert", "../shader/raycasterFragment.frag");
  rayCasterShader.setPerspective(fov, aspect, zNear, zFar);

  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);


  game::camera cameraObject(cameraPos, cameraFront, cameraUp);
  cameraObject.addActiveShader(&basicPhongShader);
  cameraObject.addActiveShader(&textureShader);
  cameraObject.addActiveShader(&textureBasicShader);
  cameraObject.addActiveShader(&basicShader);
  cameraObject.addActiveShader(&rayCasterShader);

  addCamera(&cameraObject);

  cameraObject.setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));





  while (!glfwWindowShouldClose(gameWindow_->getWindow())) {
    processInput();
    calculateFPS();

    currentTime_ = glfwGetTime();
    deltaTime_ = currentTime_ - lastTime_;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glClearColor( 8/255.0f, 158/255.0f, 204/255.0f, 1.0f);

    updateObjects();

    glfwSwapBuffers(gameWindow_->getWindow());
    glfwPollEvents();
    lastTime_ = currentTime_;

  }

}



void EngineCore::run() {
  gameLoop();
}


void EngineCore::processInput() {
  GLFWwindow* window = gameWindow_->getWindow();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}



void EngineCore::addCamera(game::camera *camera) {

  gameObjects.push_back(camera);
  camera->setActiveWindow(gameWindow_->getWindow());
  camera_ = camera;

}

void EngineCore::updateObjects() {

  for (auto movableActor : gameObjects) {
    movableActor->update(deltaTime_);
  }

  for (auto movableActor : gameObjects) {
    movableActor->render();
  }


}


void EngineCore::calculateFPS() {
  float currentTime = glfwGetTime();
  frames++;

  if (currentTime - lastTime >= 1.0f) {
    lastTime = currentTime;
    std::string msg = "render FPS:" + std::to_string(frames);
    glfwSetWindowTitle(gameWindow_->getWindow(), msg.c_str());

    frames = 0;

  }
}

void EngineCore::addObject(game::object *object) {
  gameObjects.push_back(object);

  if(auto* m = dynamic_cast<game::raycaster*>(object)) {
    m->setSceneMesh(&materialMeshes);
    m->setActiveCamera(camera_);
  }

  if(auto* m = dynamic_cast<game::materialMesh*>(object)) {
    materialMeshes.push_back(m);
  }

  if(auto* m = dynamic_cast<game::model::Model*>(object)) {

    for(auto& ms : m->meshes_) {
      ms->setOwner(m);
      materialMeshes.push_back(ms);

    }

  }

}
