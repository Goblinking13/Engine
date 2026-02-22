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


  game::model::Model teapot("/Users/artem/Desktop/utah_teapot.obj");
  teapot.setShader(&basicPhongShader);
  addObject(&teapot);
  teapot.setColor({173.0f/255.0f, 10.0f/255.0f, 10.0f/255.0f});
  teapot.setPosition(glm::vec3(0, 3, -7));
  teapot.rotate({1,0,0},-90.0f);


// problem with loaded models




  // float x = 1920.0f/1280.0f;
  // std::cout << x << std::endl;
  //  basicShader.setOrtho(-x/2,x/2,-0.5,0.5,zNear,zFar);


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


  std::unique_ptr<game::object> simpleCube = std::make_unique<game::model::rotatedCube>(&basicPhongShader);
  // std::unique_ptr<game::object> simpleGrid = std::make_unique<game::model::grid>(20,20,&basicPhongShader);
  std::unique_ptr<game::object> simpleGrid = std::make_unique<game::model::grid>(15,15,&basicPhongShader);
  // std::unique_ptr<game::object> boxCube = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");
  // std::unique_ptr<game::object> boxCube1 = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");
  // std::unique_ptr<game::object> boxCube2 = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");


  game::model::texturedCube boxCube(&textureShader,"../resources/textures/box.jpg");
  game::model::texturedCube boxCube1(&textureShader,"../resources/textures/box.jpg");
  game::model::texturedCube boxCube2(&textureShader,"../resources/textures/box.jpg");

  // IF OBJECT IS ADD BEFORE CAMERA THER CAN BE PROBLEMS WITH VIEW MATRIX
  // game::model::Model loadedCube("/Users/artem/Desktop/cube.obj");
  // loadedCube.setShader(&textureBasicShader);
  // addObject(&loadedCube);
  // teapot.setPosition(glm::vec3(-5, 5, 0));
  // teapot.setRotation(glm::vec3(90, 00, 0));

  addObject(&boxCube);
  // careful at most vexing parse VVV
  game::raycaster sceneRaycaster{&rayCasterShader};
  addObject(&sceneRaycaster);
  boxCube.setPosition({-5,5,-2});
  boxCube.setScale(glm::vec3(3,3,3));



  addObject(simpleGrid.get());
  (static_cast<game::materialMesh*>(simpleCube.get()))->setColor({1.0f, 0.0f, 0.0f});
  simpleCube->setScale(glm::vec3(2,2,2));



  simpleCube->setPosition(glm::vec3(0.0f, 2.0f, 4.0f));



  addObject(simpleCube.get());
  // addObject(&boxCube);


  // addObject(&sphere2);

  // addObject(&sphere3);
  // addObject(&dragon);

  std::cout << "ALL OBJECT ADDED\n";

  boxCube1.setPosition({-3.75,0.5,-2});
  boxCube2.setPosition({-4.25,1.5,-2});
  // boxCube.setPosition({-5,5,-2});
  // boxCube.setScale(glm::vec3(3,3,3));


  glEnable(GL_DEPTH_TEST);


  // game::pointCloud pc(&rayCasterShader, 10000);
  // addObject(&pc);
  //
  // pc.addPoint({0,1,0});



  while (!glfwWindowShouldClose(gameWindow_->getWindow())) {
    processInput();
    calculateFPS();

    currentTime_ = glfwGetTime();
    deltaTime_ = currentTime_ - lastTime_;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glClearColor( 8/255.0f, 158/255.0f, 204/255.0f, 1.0f);
    //glClearColor(0.3f, 0.3f, 0.3f, 1.0f);



    updateObjects();
    // count += deltaTime_;
    // cube.rotate(glm::vec3{1,1,0,}, deltaTime_);

    glfwSwapBuffers(gameWindow_->getWindow());
    glfwPollEvents();
    lastTime_ = currentTime_;

  }

  // for(int i = 0; i < objects.size(); i++){
  // delete objects[i];}

  // for(int i = 0; i < objects1.size(); i++) {
  //   delete objects1[i];
  // }
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

  if(auto* m = dynamic_cast<game::materialMesh*>(object)) {
    materialMeshes.push_back(m);
  }

  if(auto* m = dynamic_cast<game::model::Model*>(object)) {

    for(auto& ms : m->meshes_) {
      ms->setOwner(m);
      materialMeshes.push_back(ms);

    }

  }

  if(auto* m = dynamic_cast<game::raycaster*>(object)) {
    m->setSceneMesh(&materialMeshes);
    m->setActiveCamera(camera_);
  }




}
