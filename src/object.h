#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<GLFW/glfw3.h>
#include<OpenGL/gl3.h>



namespace game {

    static int object_id=0;

    class object {
        private:

        int id_;
        glm::mat4 model_;


        glm::quat rotation_ = glm::quat(1,0,0,0);
        glm::vec3 position_ = glm::vec3(0, 0, 0);
        glm::vec3 scale_ = glm::vec3(1, 1, 1);
        // glm::vec3 rotation_;
        // glm::vec3 position_ = glm::vec3(0, 0, 0);
        // glm::vec3 scale_ = glm::vec3(1,1,1);
        // glm::vec3 rotation_ = glm::vec3(0, 0, 0);

        void updateModelMatrix();

        protected:
        bool dirty_ = true;

        public:

        object();
        explicit object(const glm::vec3& position);
        virtual void update(float dt) =0;
        virtual void render() = 0;
        virtual ~object();

        void setPosition(const glm::vec3& position);
        void setScale(const glm::vec3& scale);
        void setRotation(const glm::vec3& rotation);
        void setRotation(const glm::quat& rotation);
        void rotate(const glm::vec3& axis, float angle);


        glm::vec3 getPosition() const;
        glm::vec3 getScale() const;
        glm::quat getRotation() const;
        glm::mat4 getModelMatrix();





    };
}


