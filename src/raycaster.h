#pragma once
#include "camera.h"
#include "materialMesh.h"
#include "pointCloud.h"

// better with ECS
namespace game {
    class raycaster : public materialMesh{

        std::vector<materialMesh*>* meshes_;
        //detected after raycast points
        std::vector<materialMesh*>* points_;
        camera* camera_;
        std::unique_ptr<pointCloud>  pointCloud_;
        float accumulatedTime;


        public:
        void setSceneMesh(std::vector<materialMesh*>* mesh) { meshes_ = mesh; }
        void setActiveCamera(camera* camera) { camera_ = camera; }

        explicit raycaster(shader* shader);
        void render() override;
        void update(float dt);



    };

}

