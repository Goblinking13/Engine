#include "window.h"

game::window::window(int width, int height) : width_(width), height_(height) {

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // glfwWindowHint(GLFW_DEPTH_BITS, 32);

  glfwWindowHint(GLFW_SAMPLES, 16);

  window_ = glfwCreateWindow(width, height, "Waves", nullptr, nullptr);
  glfwMakeContextCurrent(window_);
  glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // glfwSwapInterval(0);

  }


game::window::~window(){
    if(window_){
      glfwDestroyWindow(window_);
    }
  }

GLFWwindow* game::window::getWindow(){
  return window_;
}

int game::window::getWidth() {
  return width_;
}

int game::window::getHeight() {
  return height_;
}
