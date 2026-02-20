#include "camera.h"
#include<iostream>
#include <glm/ext/matrix_transform.hpp>


game::camera::camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
: object(pos), cameraFront_(front), cameraUp_(up)
{
    glm::vec3 position = getPosition();
    view_ = glm::lookAt(position, position + cameraFront_, cameraUp_);
}

void game::camera::updateMovable(float dt) {

    deltaTime_ = dt;

    getKeyBoardInput();
    getMouseInput();

    // std::cout << "Camera position: " << "X:" << position_.x << " Y:" << position_.y << " Z:" <<position_.z <<   std::endl;
    // std::cout << "Camera direction: " << "X:" << cameraFront_.x << " Y:" << cameraFront_.y << " Z:" <<cameraFront_.z <<   std::endl;

    glm::vec3 position = getPosition();
    view_ = glm::lookAt(position, position + cameraFront_, cameraUp_);

    for (const auto& shader : activeShaders) {
        shader->loadUniformMat4(view_, "view");
        shader->loadUniformVec3(position, "viewPos");
    }

}

void game::camera::getKeyBoardInput() {

    glm::vec3 position = getPosition();
    const float dist = speed * deltaTime_;
    if (glfwGetKey(activeWindow_, GLFW_KEY_W) == GLFW_PRESS)
       position += cameraFront_ * dist;
    if (glfwGetKey(activeWindow_, GLFW_KEY_S) == GLFW_PRESS)
        position  -= cameraFront_ * dist;
    if (glfwGetKey(activeWindow_, GLFW_KEY_A) == GLFW_PRESS)
        position += glm::normalize(glm::cross(cameraFront_,cameraUp_)) * dist;
    if (glfwGetKey(activeWindow_, GLFW_KEY_D) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(cameraFront_,cameraUp_)) * dist;
    if (glfwGetKey(activeWindow_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        speed = speedUp;
    else
        speed = 3;

    setPosition(position);

}

void game::camera::getMouseInput() {


    double xpos, ypos;
    glfwGetCursorPos(activeWindow_, &xpos, &ypos);

    if (firstMouse_) {
        lastMousePosX_ = xpos;
        lastMousePosY_ = ypos;
        firstMouse_ = false;
    }

    // std::cout << xpos << " " << ypos << std::endl;

    double xoffset = xpos - lastMousePosX_;
    double yoffset = lastMousePosY_ - ypos;
    lastMousePosX_ = xpos;
    lastMousePosY_ = ypos;

    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

    cameraFront_ = glm::normalize(direction);


}


void game::camera::setActiveWindow(GLFWwindow* window) {

    if (window == nullptr)
        throw std::invalid_argument("window is null!");

    activeWindow_ = window;

}


void game::camera::update(const float dt) {
    updateMovable(dt);
}


void game::camera::addActiveShader(shader *shader) {
    activeShaders.push_back(shader);
}

game::camera::~camera() {

}

