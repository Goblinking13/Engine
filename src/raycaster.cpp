#include "raycaster.h"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


namespace game {

    raycaster::raycaster(shader* shader) : pointCloud_(std::make_unique<pointCloud>(shader, 500000))
    {


    }

    void raycaster::render() {

        // glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LEQUAL);
        //
        // // и перед рисованием точек:
        // glDepthMask(GL_FALSE); // не пишем в depth
        // draw points
        // glDisable(GL_DEPTH_TEST);
        pointCloud_->render();
        // glEnable(GL_DEPTH_TEST);
        // glDepthMask(GL_TRUE);


        //
        // std::cout << "viewPos = " << camera_->getPosition().x << ";"<< camera_->getPosition().y << ";"<< camera_->getPosition().z  << std::endl;
        // std::cout << "viewDir = " << camera_->getCameraDirection().x << ";"<< camera_->getCameraDirection().y << ";"<< camera_->getCameraDirection().z  << std::endl;
    }

    void raycaster::update(float dt) {
        accumulatedTime_ += dt;
        // int step = 10;

        if(accumulatedTime_ >= 0.1) {
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


                // float angleRad = glm::radians(-step * pointCount/2 + step * i );
                //
                // glm::mat4 rot = glm::rotate(glm::mat4(1.0f), angleRad, up);
                // glm::vec3 nRayDir = glm::vec3(rot * glm::vec4(forward, 0.0f));
                //
                // rot = glm::rotate(glm::mat4(1.0f), angleRad, right);
                // nRayDir = glm::vec3(rot * glm::vec4(forward, 0.0f));

                // float yaw = angleDist(rng_);
                // float pitch = angleDist(rng_);


                float yaw   = glm::radians(yawDist(rng_));
                float pitch = glm::radians(pitchDist(rng_));

                // float yaw   = glm::radians(1.0f);
                // float pitch = glm::radians(1.0f);

                // 1) yaw вокруг up
                glm::mat4 R_yaw = glm::rotate(glm::mat4(1.0f), yaw, up);
                glm::vec3 d1 = glm::vec3(R_yaw * glm::vec4(forward, 0.0f));

                // 2) после yaw пересчитай right (чтобы pitch был “перпендикулярен” новому forward)
                glm::vec3 right2 = glm::normalize(glm::cross(d1, up));

                // 3) pitch вокруг right2
                glm::mat4 R_pitch = glm::rotate(glm::mat4(1.0f), pitch, right2);
                glm::vec3 nRayDir = glm::normalize(glm::vec3(R_pitch * glm::vec4(d1, 0.0f)));

                float bestT = maxDist_;
                bool isHit = false;
                glm::vec3 bestN;


                for (auto& obj : *meshes_) {

                    glm::mat4 model;
                    // model = obj->getModelMatrix();
                    if(obj->getOwner() != nullptr) {
                        auto* tmp = obj->getOwner();
                        model = tmp->getModelMatrix();
                    }else {
                        model = obj->getModelMatrix();
                    }



                    for (int k = 0; k + 2 < (int)obj->indices_.size(); k += 3) {
                        int i0 = obj->indices_[k];
                        int i1 = obj->indices_[k+1];
                        int i2 = obj->indices_[k+2];

                        glm::vec3 aL = obj->vertices_[i0].position;
                        glm::vec3 bL = obj->vertices_[i1].position;
                        glm::vec3 cL = obj->vertices_[i2].position;

                        glm::vec3 aW = glm::vec3(model * glm::vec4(aL, 1.0f));
                        glm::vec3 bW = glm::vec3(model * glm::vec4(bL, 1.0f));
                        glm::vec3 cW = glm::vec3(model * glm::vec4(cL, 1.0f));

                        float t, u, v;

                        if (castRay(nRayDir, rayOrig, aW, bW, cW, t, u, v, 1e-6f) && t < bestT && t > 0.0f) {

                            glm::vec3 n = glm::normalize(glm::cross(bW - aW, cW - aW));
                            if (glm::dot(n, nRayDir) > 0.0f) n = -n;

                            isHit = true;
                            bestT = t;
                            bestN = n;

                            // const float bias = 0.015f;
                            // glm::vec3 hit = rayOrig + nRayDir * t;
                            // hit += n * bias;
                            // pointCloud_->addPoint(hit);

                            // if(glm::length(rayOrig - hit) <= maxDist_)
                            // points.push_back(hit);

                        }
                    }

                    if(bestT < maxDist_) {
                        glm::vec3 hit = rayOrig + nRayDir * bestT;
                        const float bias = 0.015f;
                        hit += bestN * bias;
                        points.push_back(hit);
                    }


                }

            }


            pointCloud_->addPoints(points);


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


}