#pragma once
#include "object.h"
#include "shader.h"

namespace game {


    class pointCloud : public object {
        unsigned int VAO_ = 0;
        unsigned int VBO_ = 0;
        shader* shader_ = nullptr;

        std::vector<glm::vec3> points_;
        size_t maxPoints_ = 20000;   // лимит, иначе память будет расти
        size_t head_ = 0;             // для ring buffer
        bool filed_ = false;

    public:
        pointCloud(shader* sh, size_t maxPoints=20000);

        void addPoint(const glm::vec3& p);              // 1 точка
        void addPoints(const std::vector<glm::vec3>&);  // пачка
        void clear();

        void render() override;
        void update(float dt) override {}
    };


}