#pragma once
#include "materialMesh.h"

// need ECS
namespace game {
    class raycaster : public materialMesh{

        materialMesh *mesh_;
        shader *rayShader_;
        shader *basicShader_;

        public:
        explicit raycaster(materialMesh *mesh, shader *shader);
        void render() override;
        void update(float dt);



    };

}

