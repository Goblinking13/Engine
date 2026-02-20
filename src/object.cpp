#include "object.h"
#include<iostream>
#include <glm/ext/matrix_transform.hpp>


// game::object::object(const std::vector<float>& data) {
//
//     id_ = game::object_id++;
//     data_ = data;
//
//     glGenVertexArrays(1, &VAO_);
//     glBindVertexArray(VAO_);
//     glGenBuffers(1, &VBO_);
//
//     glBindBuffer(GL_ARRAY_BUFFER, VBO_);
//     glBufferData(GL_ARRAY_BUFFER, data_.size()*sizeof(data_[0]), data_.data(), GL_STATIC_DRAW);
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(data_[0]), nullptr);
//     glEnableVertexAttribArray(0);
//
//     std::cout << "Create object: " << id_ << std::endl;
//
//     vertexCount_ = data_.size()/3;
//
//
//
// }


game::object::object() : id_(game::object_id++) {
    std::cout << "object, ID: " <<  id_ << std::endl;
    updateModelMatrix();
}

game::object::object(const glm::vec3& position) : id_(game::object_id++) ,position_(position) {
    std::cout << "object with position, ID: " <<  id_ << std::endl;
    updateModelMatrix();
}

game::object::~object() {

    // glDeleteVertexArrays(1, &VAO_);
    // glDeleteBuffers(1, &VBO_);

    std::cout << "Delete object: " << id_ << std::endl;
}


// void game::object::draw() const {
//     glBindVertexArray(VAO_);
//     glDrawArrays(GL_TRIANGLES, 0, vertexCount_);
//
// }



void game::object::setScale(const glm::vec3& scale) {
    scale_ = scale;
    dirty_ = true;
}


glm::vec3 game::object::getScale() const {
    return scale_;
}

void game::object::setPosition(const glm::vec3& position) {
     position_ = position;
     dirty_ = true;
}



glm::vec3 game::object::getPosition() const{
    return position_;
}


glm::quat game::object::getRotation() const {
    return rotation_;
}

void game::object::setRotation(const glm::vec3& rotation) {
    rotation_ = glm::normalize(rotation);
    dirty_ = true;
}

void game::object::rotate(const glm::vec3& axis, float angle) {
    const glm::quat q = glm::angleAxis(angle, axis);
    rotation_ = glm::normalize(q * rotation_);
    dirty_ = true;
}


void game::object::updateModelMatrix() {
    model_ = glm::translate(glm::mat4(1.0f), position_);
    model_ = model_ * glm::toMat4(rotation_);
    model_ = glm::scale(model_, scale_);
    dirty_ = false;
}


glm::mat4 game::object::getModelMatrix(){

    if (dirty_) {
        updateModelMatrix();
    }

    return model_;

}


void game::object::setRotation(const glm::quat &rotation) {
    rotation_ = rotation;
}
