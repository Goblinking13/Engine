#pragma once
#include "materialMesh.h"

namespace game{
    namespace model {
        class grid : public materialMesh {
            int width_, height_;


        public:
            grid(int width, int height , shader* shader) {
                setShader(shader);
                width_ = width;
                height_ = height;

                setColor(glm::vec3(0.5f, 0.5f, 0.5f));

                float lineWidth = 0.1f;

                materialMesh::loadMesh(
                    {
                        Vertex{glm::vec3(-height/2, 0.0f, -width/2), glm::vec3(0.0f,1.0f,0.0f)},
                        Vertex{glm::vec3(-height/2, 0.0f, width/2), glm::vec3(0.0f,1.0f,0.0f)},
                        Vertex{glm::vec3(height/2, 0.0f, -width/2), glm::vec3(0.0f,1.0f,0.0f)},
                        Vertex{glm::vec3(height/2, 0.0f, width/2), glm::vec3(0.0f,1.0f,0.0f)},
                    },
                    {0,1,2, 1,2,3}
                    );


            }
        };
    }
}