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
            pointCloud_->addPoint(camera_->getPosition());
        }

    };

}