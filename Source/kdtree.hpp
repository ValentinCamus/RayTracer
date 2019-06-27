//
//  kdtree.hpp
//  RayTracer
//
//  Created by Valentin on 21/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef kdtree_hpp
#define kdtree_hpp

#include <vector>
#include <stack>

#include "aabb.hpp"
#include "object.hpp"
#include "math/math.hpp"
#include "interface/intersectable.hpp"

struct KDNode {
    bool  bIsLeaf;              // is this node a leaf ?
    int32 axis;                 // axis index of the split, if not leaf
    int32 depth;                // depth in the tree
    float split;                // position of the split

    std::vector<int> indexes;   // index of objects, if leaf

    KDNode * left;                // left child
    KDNode * right;               // right child

    vec3 min;                   // min pos of node bounding box
    vec3 max;                   // max pos of node bounding box

    KDNode(bool _bIsLeaf, int32 _axis, int32 _depth) {
        bIsLeaf = _bIsLeaf;
        axis    = _axis;
        depth   = _depth;
        left    = nullptr;
        right   = nullptr;
    }
};

#define KD_MAX_DEPTH  30
#define KD_OBJ_LIMIT  5

class KdTree : public Intersectable {
public:
    KdTree() {};
    KdTree(std::vector<Object*>& objects);

    ~KdTree() { /* TODO */ };

    bool Intersect(Ray & ray, HitResult & hit) override;

private:
    KDNode * m_root; // the root of the tree

    std::vector<Object*> m_objects;

    std::vector<int> m_out; // all object's index out of the KdTree
    std::vector<int> m_in;  // all object's index in the KdTree

    void Subdivide(KDNode * node);
    void UpdateKDNode(KDNode * node, uint32 index);

    bool IntersectLeaf(KDNode * leaf, Ray & ray, HitResult & hit);

    // REMOVE ME
    void Browse(KDNode * node) {

        if (node->left) Browse(node->left);

        std::cout << ((node->bIsLeaf) ? "LEAF" : (node->depth == 0) ? "ROOT" : "NODE") << std::endl;
        std::cout << "Depth : " << node->depth << std::endl;
        std::cout << "N_OBJ : " << node->indexes.size() << std::endl;
        std::cout << std::endl;

        if (node->right) Browse(node->right);
    }
};




KdTree::KdTree(std::vector<Object*>& objects) : m_objects(objects) {

    for (uint32 index = 0; index < objects.size(); ++index) {
        Object * obj = objects.at(index);
        (obj->UseAABB()? m_in : m_out).push_back(index);
    }
    m_root = new KDNode(true, 1, 0);

    if (m_in.empty()) {
        m_root->min = vec3(0.f);
        m_root->max = vec3(0.f);

    } else {

        /* the default aabb is the first object's aabb */
        m_root->min = m_objects[m_in[0]]->GetAABB().Min();
        m_root->max = m_objects[m_in[0]]->GetAABB().Max();

        for (uint32 idx = 1; idx < m_in.size(); ++idx) UpdateKDNode(m_root, idx);
        m_root->split /= 2 * m_in.size(); // average of the center of each aabb

        Subdivide(m_root);

        // Browse(m_root); // REMOVE ME
    }
}

void KdTree::UpdateKDNode(KDNode * node, uint32 index) {
    Object * current = m_objects[m_in.at(index)];
    node->indexes.push_back(index); // the current object belongs to the node's aabb
    /* for each axis of a vector (aka x, y and z), */
    /* seek if the root's aabb must be expend      */
    for (uint32 axis = 0; axis < 3; ++axis) {
        /* if the aabb's min pos should be expend */
        if (current->GetAABB().Min()[axis] < node->min[axis])
            node->min[axis] = current->GetAABB().Min()[axis];
        /* if the aabb's max pos should be expend */
        if (current->GetAABB().Max()[axis] > node->max[axis])
            node->min[axis] = current->GetAABB().Max()[axis];
    }
    /* update the split */
    node->split += current->GetAABB().Min()[node->axis];
    node->split += current->GetAABB().Max()[node->axis];
}

void KdTree::Subdivide(KDNode * node) {
    node->bIsLeaf = false; // because we subdivide this node, it cannot be a leaf

    /* create the left and right son */
    KDNode * left =  node->left  = new KDNode(true, (node->axis + 1) % 3, node->depth + 1);
    KDNode * right = node->right = new KDNode(true, (node->axis + 1) % 3, node->depth + 1);

    /* create the default aabb -- here the default is set to its max value */
    left->min  = node->max;
    left->max  = node->min;
    right->min = node->max;
    right->max = node->min;

    left->split  = 0.f;
    right->split = 0.f;

    for (uint32 index : node->indexes) {
        const bool bIsLeft = m_objects[index]->GetAABB().Center()[node->axis] < node->split;
        if (bIsLeft) UpdateKDNode(left, index); // @index belongs to the left child
        else UpdateKDNode(right, index); // @index belongs to the right child
    }
    left->split  /= 2.f * node->left->indexes.size();
    right->split /= 2.f * node->right->indexes.size();

    const bool bIsLeftSubdividable  = InRange((int32) left->indexes.size(), 2, KD_OBJ_LIMIT);
    const bool bIsRightSubdividable = InRange((int32) right->indexes.size(), 2, KD_OBJ_LIMIT);

    if (bIsLeftSubdividable && left->depth < KD_MAX_DEPTH) Subdivide(left);
    if (bIsRightSubdividable && right->depth < KD_MAX_DEPTH) Subdivide(right);
}

bool KdTree::IntersectLeaf(KDNode * leaf, Ray & ray, HitResult & hit) {
    hit = HitResult(false);
    for (auto index : leaf->indexes)
        m_objects[index]->Intersect(ray, hit);
    return hit.bSuccess;
}

bool KdTree::Intersect(Ray & ray, HitResult & hit) {
    hit = HitResult(false);

    std::stack<KDNode*> stack;
    KDNode * node;

    stack.push(m_root); // start with the root

    while (!stack.empty()) {

        /* get and pop the top of the stack */
        node = stack.top();
        stack.pop();

        if (node->bIsLeaf) IntersectLeaf(node, ray, hit);
        else {

            AABB leftAABB  = AABB(node->left->min, node->left->max);
            AABB rightAABB = AABB(node->right->min, node->right->max);
            HitResult nodeHitResult;

            const bool bRightFirst = ray.Direction()[node->axis] > 0;

            if (bRightFirst) {
                if (rightAABB.Intersect(ray, nodeHitResult)) stack.push(node->right);
                if (leftAABB.Intersect(ray, nodeHitResult))  stack.push(node->left);

            } else {
                if (leftAABB.Intersect(ray, nodeHitResult))  stack.push(node->left);
                if (rightAABB.Intersect(ray, nodeHitResult)) stack.push(node->right);
            }
        }
    }
    // intersect all the object that cannot be contains in the KdTree
    for (uint32 index : m_out) m_objects[index]->Intersect(ray, hit);

    return hit.bSuccess;
}









#endif /* kdtree_hpp */
