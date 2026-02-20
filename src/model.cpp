#include "model.h"
#include <iostream>
#include <filesystem>


game::model::Model::Model(const char *path) {
    loadModel(path);
}


void game::model::Model::loadModel(std::string path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    directory_ = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void game::model::Model::processNode(aiNode* node, const aiScene* scene) {

    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.push_back(processMesh(mesh,scene));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        aiNode* child = node->mChildren[i];
        processNode(child, scene);
    }

}

game::materialMesh* game::model::Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<texture> textures;

    for (int i = 0; i < mesh->mNumVertices; i++) {

        glm::vec3 vertex;
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;

        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;

        glm::vec2 texCoord;
        if (mesh->mTextureCoords[0]) {
            texCoord.x = mesh->mTextureCoords[0][i].x;
            texCoord.y = mesh->mTextureCoords[0][i].y;
        }else {
            texCoord = glm::vec2(0, 0);
        }


        vertices.push_back({vertex, normal, texCoord });
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<texture> diffuseMaps = loadMaterialTextures(material,
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<texture> specularMaps = loadMaterialTextures(material,
                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    auto materialMesh = new game::materialMesh(vertices, indices);
    materialMesh->addTexture(textures);

    return materialMesh;
}

std::vector<game::texture> game::model::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {

    std::vector<texture> textures;

    for (int i =  0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        std::filesystem::path basePath = directory_;
        std::filesystem::path relPath  = str.C_Str();

        relPath = relPath.lexically_normal();

        std::filesystem::path fullPath = (basePath / relPath).lexically_normal();

        std::string texPath = fullPath.string();

        texture curTexture(texPath.c_str());
        curTexture.path = texPath;
        curTexture.type = typeName;
        textures.push_back(curTexture);
    }

    return textures;
}


void game::model::Model::update(float dt) {

}

void game::model::Model::render() {

    shader_->use();
    shader_->loadUniformMat4(getModelMatrix(), "model");
    glm::mat4 inverseMatrix = glm::inverse(getModelMatrix());
    shader_->loadUniformMat4(inverseMatrix, "inverseModel");

    for (int i = 0; i < meshes_.size(); i++) {

        meshes_[i]->setShader(shader_);
        meshes_[i]->renderWithoutUniform();

        }

}


void game::model::Model::setShader(shader *shader) {
    shader_ = shader;
}


game::model::Model::~Model() {
    for (int i = 0; i < meshes_.size(); i++) {
        delete meshes_[i];
    }
}


void game::model::Model::setColor(glm::vec3 color) {
    for(int i = 0; i < meshes_.size(); i++) {
        meshes_[i]->setColor(color);
    }
}