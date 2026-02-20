#pragma once
#include "object.h"
#include "movable.h"
#include "controllable.h"
#include <glm/glm.hpp>
#include <vector>

#include "shader.h"


namespace game{

    class camera : public object, public movable, public controllable {
      protected:

        glm::vec3 cameraFront_, cameraUp_;
        glm::mat4 view_;

        GLFWwindow* activeWindow_;

        double mouseSensitivity_ = 0.1;
        double lastMousePosX_ = 0, lastMousePosY_ = 0;
        bool firstMouse_ = true;
        double yaw_ = 0, pitch_ = 0;
        float deltaTime_=0;
        float speed = 3.0f;
        float speedUp = 100.0f;

        // pointers to shaders in which the new lookAt matrix is loaded after the update
        std::vector<shader*> activeShaders;

      public:

        camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up);

        ~camera() override;
        //can't render camera
        void render() override {};
        void update(float dt) override;
        void updateMovable(float dt) override;
        void getKeyBoardInput() override;
        void getMouseInput() override;
        void setActiveWindow(GLFWwindow* window);
        void addActiveShader(shader* shader);

    };

};