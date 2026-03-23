#pragma once
#include "object.h"
#include "shader.h"

struct point {
    glm::vec3 position;
    glm::vec3 color;

};

namespace game {


    class pointCloud : public object {
        unsigned int VAO_ = 0;
        unsigned int VBO_ = 0;
        shader* shader_ = nullptr;

        std::vector<point> points_;
        size_t maxPoints_ = 20000;
        size_t head_ = 0;
        bool filed_ = false;

    public:
        pointCloud(shader* sh, size_t maxPoints=20000);

        void addPoint(const point& p);
        void addPoints(const std::vector<point>&);
        void clear();

        void render() override;
        void update(float dt) override {}
    };


}