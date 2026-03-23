#include "BVH.h"
#include <cmath>
#include "mesh.h"

inline TriRef getTri(const game::mesh& mesh, int index){
    int base = index * 3;
    return {
        mesh.indices_[base + 0],
        mesh.indices_[base + 1],
        mesh.indices_[base + 2]
    };

}

BVH::BVH(game::mesh& mesh, unsigned int maxDepth) : mesh_(mesh) {



    int trigCount = mesh_.indices_.size() / 3;

    maxDepth_ = fmin(maxDepth, std::ceil(std::log2(trigCount)));

    for(int i = 0; i < trigCount; i++){
        triangles_.push_back(getTri(mesh_, i));
    }


   nodes_.clear();
   // maybe maxDepthˆ2
   nodes_.reserve(trigCount*2);

    root_ = (int)nodes_.size();
    nodes_.push_back(BVHNode{});

   buildTree(root_,0,trigCount, 0);

}


void BVH::buildTree(int root, int start, int count, int level){

    const auto& vertices = mesh_.vertices_;


    AABB box;
    const auto& tri = triangles_;
    for(int i = start; i < start + count; i++){

        glm::vec3 v0 = vertices[tri[i].i0].position;
        glm::vec3 v1 = vertices[tri[i].i1].position;
        glm::vec3 v2 = vertices[tri[i].i2].position;

        box.expand(v0);
        box.expand(v1);
        box.expand(v2);
    }

    nodes_[root].aabb = box;
    nodes_[root].indexTrig = start;
    nodes_[root].countTrig = count;


    if (level >= (int)maxDepth_ || count <= leafSize_) {
        nodes_[root].left = nodes_[root].right = -1;
        nodes_[root].isLeaf = true;
        return;
    }


    int axis = nodes_[root].aabb.longestAxis();

    int midCount = count / 2;
    int midIndex = start + midCount;

    std::nth_element(
    triangles_.begin() + start,
    triangles_.begin() + midIndex,
    triangles_.begin() + start + count,
    [&](const TriRef& a, const TriRef& b){
        return computeCentroid(mesh_, a)[axis] < computeCentroid(mesh_, b)[axis];
    }

    );

    int left = nodes_.size();
    nodes_.push_back(BVHNode{});
    int right = nodes_.size();
    nodes_.push_back(BVHNode{});

    nodes_[root].left = left;
    nodes_[root].right = right;



    buildTree(left,  start,    midCount,         level+1);
    buildTree(right, midIndex, count - midCount, level+1);
}


glm::vec3 BVH::computeCentroid(const game::mesh& mesh,const TriRef& tri) const{
    glm::vec3 v0 = mesh.vertices_[tri.i0].position;
    glm::vec3 v1 = mesh.vertices_[tri.i1].position;
    glm::vec3 v2 = mesh.vertices_[tri.i2].position;


   return {(v0.x + v1.x + v2.x)/3.0f,(v0.y + v1.y + v2.y)/3.0f,(v0.z + v1.z + v2.z)/3.0f};

}



