#include "raycaster.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


namespace game {

    raycaster::raycaster(shader* shader) : pointCloud_(std::make_unique<pointCloud>(shader, 500000))
    {


    }

    void raycaster::render() {

        pointCloud_->render();
  }

    void raycaster::update(float dt) {
        accumulatedTime_ += dt;


        if(accumulatedTime_ >= 0.001) {
            accumulatedTime_ = 0;
            glm::vec3 rayOrig = camera_->getPosition();
            glm::vec3 rayDir  = camera_->getCameraDirection();
            rayDir = glm::normalize(rayDir);

            int pointCount= 20;
            float step = 2;

            glm::vec3 forward = glm::normalize(camera_->getCameraDirection());
            glm::vec3 worldUp(0,1,0);

            glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
            glm::vec3 up    = glm::normalize(glm::cross(right, forward));

            std::vector<glm::vec3> points;

            float yawAngle = 15;
            float pitchAngle = 10;

            std::uniform_real_distribution<float> yawDist(-yawAngle, yawAngle);
            std::uniform_real_distribution<float> pitchDist(-pitchAngle, pitchAngle);



            for(int i = 0; i < pointCount; i++) {

                float yaw   = glm::radians(yawDist(rng_));
                float pitch = glm::radians(pitchDist(rng_));


                glm::mat4 R_yaw = glm::rotate(glm::mat4(1.0f), yaw, up);
                glm::vec3 d1 = glm::vec3(R_yaw * glm::vec4(forward, 0.0f));


                glm::vec3 right2 = glm::normalize(glm::cross(d1, up));


                glm::mat4 R_pitch = glm::rotate(glm::mat4(1.0f), pitch, right2);
                glm::vec3 nRayDir = glm::normalize(glm::vec3(R_pitch * glm::vec4(d1, 0.0f)));



                int pickedIndex = -1;
                float bestT = maxDist_;
                glm::vec3 bestN;
                bool isHit = false;

                for (auto& obj : *meshes_) {

                    glm::mat4 model;
                    // model = obj->getModelMatrix();
                    if(obj->getOwner() != nullptr) {
                        auto* tmp = obj->getOwner();
                        model = tmp->getModelMatrix();
                    }else {
                        model = obj->getModelMatrix();
                    }

                    glm::mat4 invModel = glm::inverse(model);
                    glm::vec3 locOrigin = glm::vec3(invModel * glm::vec4(rayOrig, 1.0f));

                    glm::vec3 locDir = glm::vec3(invModel * glm::vec4(nRayDir, 0.0f));
                    locDir = glm::normalize(locDir);
                    glm::vec3 invDir = 1.0f/locDir;



                    std::stack<int> ids;
                    ids.push(obj->bvh_->root_);


                    while(!ids.empty()) {
                        int cur = ids.top();
                        ids.pop();

                        const auto& bvh = obj->bvh_;

                        float enterT, exitT;
                        if(!bvh->nodes_[cur].aabb.rayIntersect(locOrigin,invDir, enterT, exitT))
                            continue;

                        if(bestT < enterT)
                            continue;



                        if(bvh->nodes_[cur].isLeaf) {
                            pickedIndex = cur;

                            const auto& triangles = obj->bvh_->triangles_;
                            int start = obj->bvh_->nodes_[pickedIndex].indexTrig;
                            int count = obj->bvh_->nodes_[pickedIndex].countTrig;




                            for (int k = start; k < start + count; k++) {
                                int i0 = triangles[k].i0;
                                int i1 = triangles[k].i1;
                                int i2 = triangles[k].i2;

                                glm::vec3& aL = obj->vertices_[i0].position;
                                glm::vec3& bL = obj->vertices_[i1].position;
                                glm::vec3& cL = obj->vertices_[i2].position;


                                float t, u, v;

                                if (castRay(locDir, locOrigin, aL, bL, cL, t, u, v, 1e-6f) && t <= bestT && t > 0.0f) {

                                    glm::vec3 n = glm::normalize(glm::cross(bL - aL, cL - aL));
                                    if (glm::dot(n, locDir) > 0.0f) n = -n;

                                    isHit = true;
                                    bestT = t;
                                    bestN = n;

                                }
                            }



                            continue;
                        }



                        if(bvh->nodes_[cur].left !=  -1) {
                                ids.push(bvh->nodes_[cur].left);
                        }

                        if(bvh->nodes_[cur].right !=  -1) {
                                ids.push(bvh->nodes_[cur].right);
                        }



                    }

                    if(isHit && bestT < maxDist_) {
                        const float bias = 0.015f;

                        glm::vec3 hitLocal = locOrigin + locDir * bestT;
                        hitLocal += bestN * bias;

                        glm::vec3 hitWorld = glm::vec3(model * glm::vec4(hitLocal, 1.0f));
                        points.push_back(hitWorld);

                    }


                }

            }

                pointCloud_->addPoints(points);
                // frameCount_ = 0;
            // }



        }

    };




    bool raycaster::castRay(glm::vec3 &dir, glm::vec3 &orig, glm::vec3 &v0, glm::vec3 &v1, glm::vec3 &v2,float &t, float &u, float &v,float eps ) {

        glm::vec3 e1 = v1 - v0;
        glm::vec3 e2 = v2 - v0;

        glm::vec3 pvec = glm::cross(dir, e2);
        float det = glm::dot(e1, pvec);

        if (fabs(det) < eps) return false;
        float invDet = 1.0f / det;

        glm::vec3 tvec = orig - v0;
        u = glm::dot(tvec, pvec) * invDet;
        if (u < 0.0f || u > 1.0f) return false;

        glm::vec3 qvec = glm::cross(tvec, e1);
        v = glm::dot(dir, qvec) * invDet;
        if (v < 0.0f || u + v > 1.0f) return false;

        t = glm::dot(e2, qvec) * invDet;
        if (t < eps) return false;


        return true;


    }

    void raycaster::setSceneMesh(std::vector<materialMesh*>* mesh) {
        meshes_ = mesh;
        // bvh_ = std::make_unique<BVH>(meshes_,10);





    }


}