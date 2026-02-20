#pragma once

#include "cube.h"
#include "texture.h"


namespace game{
    namespace model{

        class texturedCube : public cube {
            game::texture texture_;
            public:

            texturedCube(shader* shader, const char* path) :texture_(path), cube(shader) {
                setPosition({0,0,0});
                // setScale({100,100,100});
                texture_.type = "texture_diffuse";

                 addTexture(texture_);

            };

            ~texturedCube() {

            }


        };

    }
}




