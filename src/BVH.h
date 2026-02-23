#pragma once
#include "AABB.h"
#include <vector>
// #include "mesh.h"
namespace game { class mesh; }



struct BVHNode {
//BVHNode* left;
//BVHNode* right;

int left = -1;
int right = -1;

AABB aabb;


int indexTrig;
int countTrig;

BVHNode() {}

};

struct TriRef{
   unsigned int i0, i1, i2;
};


class BVH {
    // local coordinate triangles
    // devide by middle
    std::vector<TriRef> triangles_;
    std::vector<BVHNode> nodes_;
//    BVHNode* root_;
    int root_ = -1;
    game::mesh& mesh_;
    unsigned int maxDepth_;
    const int leafSize_ = 4;

    glm::vec3 computeCentroid(const game::mesh& mesh,const TriRef& tri) const;
    public:

    explicit BVH(game::mesh& mesh, unsigned int maxDepth);

    void buildTree(int root, int start, int count, int level);



};


