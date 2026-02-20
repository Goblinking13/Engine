#pragma once

#include<GLFW/glfw3.h>


namespace game{

    class window {
        private:
          int width_, height_;
          GLFWwindow* window_;
        public:

          window(int width, int height);
          ~window();
          GLFWwindow* getWindow();
          int getWidth();
          int getHeight();

    };

}




