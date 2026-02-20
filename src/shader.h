#pragma once
#include<GLFW/glfw3.h>
#include<string>
#include <glm/fwd.hpp>

namespace game{

    class shader {
      unsigned int shaderProgram_;
      unsigned int vertexShader_;
      unsigned int fragmentShader_;

      std::string loadFromFile(const char* path) const;
      unsigned int compileShader(const std::string& source, GLenum shaderType) const;
      void createProgram();

      public:
        shader(const char* vertexPath, const char* fragmentPath);
        ~shader();
        void use() const;
        void loadUniformMat4(const glm::mat4& matrix, const std::string& uniformName);
        void loadUniformVec3(const glm::vec3& vector, const std::string& uniformName);
        void setPerspective(float fov, float aspect, float zNear, float zFar);
        void setOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
        unsigned int getShaderProgram() const;
    };

};



