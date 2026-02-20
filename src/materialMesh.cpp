#include "materialMesh.h"

#include <iostream>
#include <ostream>


game::materialMesh::materialMesh()
: shader_(nullptr)
{}

game::materialMesh::materialMesh(const std::vector<Vertex>& vertices,
                                 const std::vector<unsigned int>& indices,
                                 shader* shader)
: mesh(vertices, indices), shader_(shader)
{}




void game::materialMesh::render() {


    shader_->use();
    glm::mat4 inverseMatrix = glm::inverse(getModelMatrix());
    shader_->loadUniformMat4(inverseMatrix, "inverseModel");
    shader_->loadUniformMat4(getModelMatrix(), "model");
    shader_->loadUniformVec3(color_, "vColor");


    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures_[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        glUniform1i(glGetUniformLocation(shader_->getShaderProgram(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].getTexture());


    }
    // VVV??
    // if (texture_ != nullptr) {
    //     texture_->bind();
    //     // std::cout << "Texture was binded" << std::endl;
    // }
    // if (textures_.size() == 0)
    //     return;

    mesh::draw();
    glActiveTexture(GL_TEXTURE0);
}

// void game::materialMesh::loadMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices){
//     mesh::loadMesh(vertices, indices);
//     // model_ = glm::mat4(1.0f);
// }


void game::materialMesh::setShader(shader* shader) {
    shader_ = shader;
}


void game::materialMesh::addTexture(texture texture) {
    // texture_ = texture;
    textures_.push_back(texture);
}


void game::materialMesh::setColor(glm::vec3 color) {
    color_ = color;

}

game::materialMesh::materialMesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : mesh(vertices, indices){

}

void game::materialMesh::addTexture(std::vector<texture> texture) {
    textures_.insert(textures_.end(), texture.begin(), texture.end());
}


game::materialMesh::materialMesh(const materialMesh &other) {
    std::cout << "copy constructor" << std::endl;
    shader_ = other.shader_;
    color_ = other.color_;
    textures_ = other.textures_;

}


game::materialMesh& game::materialMesh::operator=(const materialMesh& other) {
    std::cout << "copy assignment ASS" << std::endl;
    if (this != &other) {
        shader_ = other.shader_;
        color_ = other.color_;
        textures_ = other.textures_;
    }
    return *this;
}



glm::vec3 game::materialMesh::getColor() const {
    return color_;
}

void game::materialMesh::renderWithoutUniform() {


    shader_->loadUniformVec3(color_, "vColor");

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    for (int i = 0; i < textures_.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        std::string name = textures_[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        glUniform1i(glGetUniformLocation(shader_->getShaderProgram(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].getTexture());


    }
    mesh::draw();
    glActiveTexture(GL_TEXTURE0);

}