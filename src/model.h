#pragma once

#include "object.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "materialMesh.h"
#include "texture.h"
#include "shader.h"


namespace game::model {
    class Model :public object {

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        materialMesh* processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

        std::vector<materialMesh*> meshes_;
        std::string directory_;
        shader* shader_;


    public:
        Model(const char* path);
        void update(float dt) override;
        void render() override;
        void setShader(shader* shader);
        void setColor(glm::vec3 color);
        ~Model();




    };
}


