#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

game::shader::shader(const char* vertexPath, const char* fragmentPath){
  std::string vertexSource = loadFromFile(vertexPath);
  std::string fragmentSource = loadFromFile(fragmentPath);

  vertexShader_ = compileShader(vertexSource, GL_VERTEX_SHADER);
  fragmentShader_ = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

  createProgram();

  }

std::string game::shader::loadFromFile(const char* path) const{

   std::string line;
   std::stringstream buffer;
   std::ifstream file(path);

   if(!file.is_open()){
     std::cout << "Could not open file \"" << path << "\"" << std::endl;
     return "";
   }

   while(getline(file, line)){
    buffer << line << "\n";
   }

    return buffer.str();
}

unsigned int game::shader::compileShader(const std::string& source, GLenum shaderType) const {

  unsigned int shader = glCreateShader(shaderType);
  const char* sourcePointer = source.c_str();
  glShaderSource(shader, 1, &sourcePointer, nullptr);
  glCompileShader(shader);

  GLint success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  std::string shaderTypeString;

  if(shaderType == GL_VERTEX_SHADER){
    shaderTypeString = "VERTEX";
  }else if(shaderType == GL_FRAGMENT_SHADER){
    shaderTypeString = "FRAGMENT";
  }

  if(!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::" + shaderTypeString +"::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  return shader;
}

void game::shader::createProgram(){

  shaderProgram_ = glCreateProgram();

  glAttachShader(shaderProgram_, vertexShader_);
  glAttachShader(shaderProgram_, fragmentShader_);
  glLinkProgram(shaderProgram_);

  GLint success;
  char infoLog[512];
  glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shaderProgram_, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader_);
  glDeleteShader(fragmentShader_);

}


game::shader::~shader() {

  if(shaderProgram_ != 0) {
    glDeleteProgram(shaderProgram_);
  }
}

void game::shader::use() const {

  glUseProgram(shaderProgram_);

}


void game::shader::loadUniformMat4(const glm::mat4& matrix, const std::string& uniformName) {
  glUseProgram(shaderProgram_);
  GLint location = glGetUniformLocation(shaderProgram_, uniformName.c_str());
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram_, GL_ACTIVE_UNIFORMS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram_, 512, nullptr, infoLog);
    std::cout <<"SHADER::PROGRAM::UNIFORM::MATRIX4::ERROR "<< infoLog << std::endl;
  }

}


void game::shader::setPerspective(float fov, float aspect, float zNear, float zFar ) {
  glm::mat4 projection = glm::perspective(fov, aspect, zNear, zFar);
  loadUniformMat4(projection, "projection");
}


void game::shader::loadUniformVec3(const glm::vec3& vector, const std::string& uniformName) {
  glUseProgram(shaderProgram_);
  GLint location = glGetUniformLocation(shaderProgram_, uniformName.c_str());
  glUniform3f(location, vector.x, vector.y, vector.z);

  int success;
  char infoLog[512];
  glGetProgramiv(shaderProgram_, GL_ACTIVE_UNIFORMS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram_, 512, nullptr, infoLog);
    std::cout <<"SHADER::PROGRAM::UNIFORM::VECTOR3::ERROR "<< infoLog << std::endl;
  }
}

unsigned int game::shader::getShaderProgram() const {
  return shaderProgram_;
}

void game::shader::setOrtho(float left, float right, float bottom, float top, float zNear, float zFar) {
  glm::mat4 projection = glm::ortho(left, right, bottom, top, zNear, zFar);
  loadUniformMat4(projection, "projection");
}