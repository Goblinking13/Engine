#pragma once
#include "camera.h"
#include "materialMesh.h"

// better with ECS
namespace game {
    class raycaster : public materialMesh{

        std::vector<materialMesh*>* meshes_;
        //detected after raycast points
        std::vector<materialMesh*>* points_;
        camera* camera_;


        public:
        void setSceneMesh(std::vector<materialMesh*>* mesh) { meshes_ = mesh; }
        void setActiveCamera(camera* camera) { camera_ = camera; }

        explicit raycaster(shader* shader);
        void render() override;
        void update(float dt);



    };

}

