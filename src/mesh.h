#pragma once
#include "object.h"
#include "renderable.h"

namespace game {

    struct Vertex {
        Vertex(glm::vec3 position,glm::vec3 normal, glm::vec2 texCoord = glm::vec2(0,0))
        : position(position),normal(normal), texCoord(texCoord)
        {}
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    class mesh : public object, public renderable {
      protected:
         std::vector<Vertex> vertices_;
        std::vector<unsigned int> indices_;
         unsigned int VAO_;
         unsigned int VBO_;
         unsigned int EBO_;
         GLsizei vertexCount_;
         bool meshLoaded_;

        public:
          mesh();
          mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices);
          virtual void loadMesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices);

          void draw() override;
         // object interface part
          void render() override {draw();}
          void update(float dt) override {};
          ~mesh() override;
          // mesh(const mesh&) = delete;
          mesh& operator=(const mesh&) = delete;
    };

};