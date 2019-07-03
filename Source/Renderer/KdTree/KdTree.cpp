//
// Created by Valentin on 2019-07-03.
//

#include "KdTree.hpp"

namespace rt
{
    bool KdTree::Intersect(Ray & ray, HitResult & hit)
    {
        for (Object* obj : m_out) obj->Intersect(ray, hit);

        m_root->Intersect(ray, hit);

        return hit.bSuccess;
    }
}
