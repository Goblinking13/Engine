#include "raycaster.h"
#include <iostream>


namespace game {

    raycaster::raycaster(shader* shader)
    {
        setShader(shader);

    }

    void raycaster::render() {
        //
        // std::cout << "viewPos = " << camera_->getPosition().x << ";"<< camera_->getPosition().y << ";"<< camera_->getPosition().z  << std::endl;
        // std::cout << "viewDir = " << camera_->getCameraDirection().x << ";"<< camera_->getCameraDirection().y << ";"<< camera_->getCameraDirection().z  << std::endl;
    }

    void raycaster::update(float dt) {

    };

}