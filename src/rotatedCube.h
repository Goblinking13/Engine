#pragma once
#include "cube.h"



namespace game {
    namespace model {
        class rotatedCube : public cube{

            double period =0;
            public:
            rotatedCube(shader* shader) : cube(shader) {
                setPosition({0,2,0});
            };

            void updateMovable(float dt) override{

                rotate({1,1,1}, dt);
                // period += dt;

                // setPosition( glm::vec3(0,sin(period)/10,0));

            }


        };


    }
}


