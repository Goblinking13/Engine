#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "mesh.h"
#include "shader.h"
#include "texture.h"

namespace game{

    class materialMesh : public mesh{

        shader *shader_;
        std::vector<texture> textures_;
        glm::vec3 color_ = glm::vec3(1.0f);

        public:

        materialMesh();

        materialMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, shader* shader);
        materialMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

        materialMesh(const materialMesh& other);
        materialMesh& operator=(const materialMesh& other);

        void render() override;

        void setColor(glm::vec3 color);
        glm::vec3 getColor() const;
        // void loadMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) override;

        void setShader(shader* shader);

        void addTexture(texture texture);

        void addTexture(std::vector<texture> texture);

        void renderWithoutUniform();



    };

};



