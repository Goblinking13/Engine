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

  game::shader basicPhongShader("../shader/basicPhongVertex.vs","../shader/basicPhongFragment.fs" );
  basicPhongShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader textureShader("../shader/textureVertex.vs","../shader/textureFragment.fs");
  textureShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader textureBasicShader("../shader/textureBasicVertex.vs","../shader/textureBasicFragment.fs");
  textureBasicShader.setPerspective(fov, aspect, zNear, zFar);

  game::shader basicShader("../shader/basicVertex.vs", "../shader/basicFragment.fs");
  basicShader.setPerspective(fov, aspect, zNear, zFar);

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

  addCamera(&cameraObject);

  cameraObject.setPosition(glm::vec3(-2.0f, 0.0f, 0.0f));


  std::unique_ptr<game::object> simpleCube = std::make_unique<game::model::rotatedCube>(&basicPhongShader);
  // std::unique_ptr<game::object> simpleGrid = std::make_unique<game::model::grid>(20,20,&basicPhongShader);
  std::unique_ptr<game::object> simpleGrid = std::make_unique<game::model::grid>(15,15,&basicPhongShader);
  std::unique_ptr<game::object> boxCube = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");
  std::unique_ptr<game::object> boxCube1 = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");
  std::unique_ptr<game::object> boxCube2 = std::make_unique<game::model::texturedCube>(&textureShader,"../resources/textures/box.jpg");

  addObject(boxCube1.get());
  addObject(boxCube2.get());

  addObject(simpleGrid.get());
  (static_cast<game::materialMesh*>(simpleCube.get()))->setColor({1.0f, 0.0f, 0.0f});
  simpleCube->setScale(glm::vec3(2,2,2));



  simpleCube->setPosition(glm::vec3(0.0f, 2.0f, 4.0f));



  addObject(simpleCube.get());
  addObject(boxCube.get());


  // addObject(&sphere2);

  // addObject(&sphere3);
  // addObject(&dragon);

  std::cout << "ALL OBJECT ADDED\n";

  boxCube1.get()->setPosition({-3.75,0.5,-2});
  boxCube2.get()->setPosition({-4.25,1.5,-2});
  boxCube.get()->setPosition({-5,0.5,-2});


  glEnable(GL_DEPTH_TEST);

  std::vector<game::Vertex> vertices = {
    { glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
    { glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
    { glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
    { glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

    { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 0.0f) },
    { glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 0.0f) },
    { glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(1.0f, 1.0f) },
    { glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f,-1.0f), glm::vec2(0.0f, 1.0f) }
  };

  std::vector<unsigned int> indices = {
    0, 1, 2,
    2, 3, 0,

    4, 5, 6,
    6, 7, 4,

    4, 0, 3,
    3, 7, 4,

    1, 5, 6,
    6, 2, 1,

    4, 5, 1,
    1, 0, 4,

    3, 2, 6,
    6, 7, 3
};

  game::materialMesh cube(vertices, indices, &basicShader);
  cube.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
  cube.setPosition(glm::vec3(0.0f, 5.0f, 0.0f));

  game::materialMesh cube1(vertices, indices, &basicShader);
  cube1.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
  cube1.setPosition(glm::vec3(5.0f, 5.0f, 0.0f));

  std::vector<game::object*> objects;


  double count = 0;
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(gameWindow_->getWindow())) {
    processInput();
    calculateFPS();

    currentTime_ = glfwGetTime();
    deltaTime_ = currentTime_ - lastTime_;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glClearColor( 199/255.0f, 96/255.0f, 18/255.0f, 1.0f);
    //glClearColor(0.3f, 0.3f, 0.3f, 1.0f);


    updateObjects();
    count += deltaTime_;
    cube.rotate(glm::vec3{1,1,0,}, deltaTime_);

    glfwSwapBuffers(gameWindow_->getWindow());
    glfwPollEvents();
    lastTime_ = currentTime_;

  }

  for(int i = 0; i < objects.size(); i++){
  delete objects[i];}

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

}

void EngineCore::updateObjects() {

  for (auto movableActor : gameObjects) {
    movableActor->update(deltaTime_);
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
}
