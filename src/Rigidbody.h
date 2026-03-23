#pragma once
#include <glm/glm.hpp>


class Rigidbody {
public:
    float mass;
    glm::vec3 velocity;
    bool isKinematic;

};

