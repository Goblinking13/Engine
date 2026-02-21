#include "raycaster.h"
#include <iostream>


namespace game {

    raycaster::raycaster(materialMesh *mesh,  shader *shader) : mesh_(mesh), rayShader_(shader)
    {
        // dubplicate code from EnginecCore.cpp
        // const float aspect = 1920.0f / 1280.0f;
        // const float fov = glm::radians(45.0f);
        // const float zNear = 0.01f;
        // const float zFar = 1000.0f;

        if(mesh->getShader() == nullptr) {
            std::cout << "RAYCASTER::MESH::SHADER::NOT::FOUND" << std::endl;
            return;
        }


        basicShader_ = mesh->getShader();


    }

void raycaster::render() {

        std::cout << "RAYCASTER::RAYCASTER::RENDER" << std::endl;

        auto tmp = getModelMatrix();

        // mesh_->setPosition(getPosition());
        // mesh_->setRotation(getRotation());
        // mesh_->setScale(getScale());
        //
        // mesh_->updateModelMatrix();


        // glDepthFunc(GL_LEQUAL);
        // mesh_->setShader(rayShader_);
        // mesh_->render();
        // glDepthFunc(GL_LESS); // вернуть обратно
        // mesh_->render();
        // mesh_->setShader(basicShader_);

        // mesh_->setShader(basicShader_);
        // mesh_->render();
        //
        // glDepthFunc(GL_LEQUAL);
        // mesh_->setShader(rayShader_);
        // mesh_->render();
        // glDepthFunc(GL_LESS);
        //
        // mesh_->setShader(basicShader_); // вернуть, чтобы не ломать следующий объект


        // базовый проход
        mesh_->setShader(basicShader_);
        mesh_->render();

        // круг-проход
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(-1.0f, -1.0f);   // подтолкнуть ближе к камере (значения можно подбирать)

        glDepthFunc(GL_LEQUAL);
        glDepthMask(GL_FALSE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mesh_->setShader(rayShader_);
        mesh_->render();

        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

        glDisable(GL_POLYGON_OFFSET_FILL);

}

    void raycaster::update(float dt) {
        mesh_->update(dt);
    };

}