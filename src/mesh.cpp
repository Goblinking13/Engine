#include "mesh.h"

#include <iostream>
#include <ostream>

game::mesh::mesh()  : VAO_(0), VBO_(0), EBO_(0), vertexCount_(0), meshLoaded_(false) {  }

game::mesh::mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices) : mesh() {

    meshLoaded_ = false;
    loadMesh(vertices, indices);


}

game::mesh::~mesh() {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}

void game::mesh::draw() {
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, vertexCount_, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}


void game::mesh::loadMesh(const std::vector<Vertex>& vertices,const  std::vector<unsigned int>& indices) {

    if (vertices.empty() || indices.empty()) {
        std::cerr << "Mesh: empty vertex/index data!\n";
        return;
    }

    if (meshLoaded_) {
        glDeleteVertexArrays(1, &VAO_);
        glDeleteBuffers(1, &VBO_);
        glDeleteBuffers(1, &EBO_);


        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        VAO_ =0, VBO_ =0, EBO_ = 0;
        meshLoaded_ = false;
    }

    vertices_ = vertices;
    indices_ = indices;

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size()*sizeof(vertices_[0]), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size()*sizeof(indices_[0]), indices_.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));



    glBindVertexArray(0);

    vertexCount_ = indices_.size();
    meshLoaded_ = true;

}

