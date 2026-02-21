#include "raycaster.h"
#include <iostream>


namespace game {

    raycaster::raycaster(shader* shader) : pointCloud_(std::make_unique<pointCloud>(shader, 10000))
    {


    }

    void raycaster::render() {

        pointCloud_->render();
        //
        // std::cout << "viewPos = " << camera_->getPosition().x << ";"<< camera_->getPosition().y << ";"<< camera_->getPosition().z  << std::endl;
        // std::cout << "viewDir = " << camera_->getCameraDirection().x << ";"<< camera_->getCameraDirection().y << ";"<< camera_->getCameraDirection().z  << std::endl;
    }

    void raycaster::update(float dt) {
        accumulatedTime += dt;
        // int step = 10;

        if(accumulatedTime >= 1) {
            glm::vec3 rayOrig = camera_->getPosition();
            glm::vec3 rayDir  = camera_->getCameraDirection();
            rayDir = glm::normalize(rayDir);

            int pointCount= 10;
            float fov = 90;



            std::vector<glm::vec3> points;

            for(int i = 0; i < pointCount; i++) {

                glm::mat4 rot = glm::rotate(glm::mat4(1.0f),
                                            glm::radians(-fov/2 + fov/pointCount * i ),
                                            glm::vec3(1, 0, 0));

                glm::vec3 nRayDir = glm::vec3(rot * glm::vec4(rayDir, 1.0f));

                for (auto& obj : *meshes_) {
                    glm::mat4 model = obj->getModelMatrix();

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
                        if (castRay(nRayDir, rayOrig, aW, bW, cW, t, u, v, 1e-6f)) {

                            glm::vec3 n = glm::normalize(glm::cross(bW - aW, cW - aW));


                            if (glm::dot(n, nRayDir) > 0.0f) n = -n;

                            const float bias = 0.015f;
                            glm::vec3 hit = rayOrig + nRayDir * t;
                            hit += n * bias;
                            // pointCloud_->addPoint(hit);
                            points.push_back(hit);

                        }
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