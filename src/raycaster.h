#pragma once
#include "camera.h"
#include "materialMesh.h"
#include "pointCloud.h"
#include "BVH.h"
#include <random>

// better with ECS
namespace game {
    class raycaster : public materialMesh {
        std::vector<materialMesh*>* meshes_;
        //detected after raycast points
        std::vector<materialMesh*>* points_;
        camera* camera_;
        std::unique_ptr<pointCloud>  pointCloud_;
        float accumulatedTime_;
        std::mt19937 rng_{std::random_device{}()};
        float maxDist_ = 10;

        int frameCount_ =0 ;

        bool castRay(glm::vec3 &dir, glm::vec3 &pos, glm::vec3 &v0, glm::vec3 &v1, glm::vec3 &v2,
            float &t, float &u, float &v,float eps = 0.001);


        public:
        void setSceneMesh(std::vector<materialMesh*>* mesh);
        void setActiveCamera(camera* camera) { camera_ = camera; }

        explicit raycaster(shader* shader);
        void render() override;
        void update(float dt);



    };

}

