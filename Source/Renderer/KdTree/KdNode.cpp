//
// Created by Valentin on 2019-07-03.
//

#include "KdNode.hpp"

namespace rt
{
    void KdNode::Build(std::vector<Object*> objs, uint32 depth)
    {
        m_objs = objs;
        m_left = new KdNode();
        m_right = new KdNode();
        m_bbox = BoundingBox();

        if (objs.empty()) return;

        if (objs.size() == 1)
        {
            m_bbox = objs[0]->BBox();
            m_left->m_objs = std::vector<Object*>();
            m_right->m_objs = std::vector<Object*>();
            return;
        }

        // Get a bbox surrounding all the objects.
        m_bbox = objs[0]->BBox();
        for (Object* obj : objs) m_bbox.Expand(obj->BBox());


        vec3 midpt = vec3(0, 0, 0);
        for (Object* obj : objs) midpt += obj->Position() * float(1.0 / objs.size());

        std::vector<Object*> leftObjs;
        std::vector<Object*> rightObjs;
        uint32 axis = m_bbox.LongestAxis();

        for (Object* obj : objs)
        {
            switch (axis)
            {
                case 0:
                    midpt.x >= obj->Position().x ? rightObjs.push_back(obj) : leftObjs.push_back(obj);
                    break;

                case 1:
                    midpt.y >= obj->Position().y ? rightObjs.push_back(obj) : leftObjs.push_back(obj);
                    break;

                default:
                    midpt.z >= obj->Position().z ? rightObjs.push_back(obj) : leftObjs.push_back(obj);
                    break;
            }
        }

        if (leftObjs.empty() && !rightObjs.empty()) leftObjs = rightObjs;
        if (rightObjs.empty() && !leftObjs.empty()) rightObjs = leftObjs;

        uint32 matches = 0;
        for (Object* lobj : leftObjs)
            for (Object* robj : rightObjs)
                if (lobj == robj) ++matches;

        if ( ((float) matches / leftObjs.size()) < 0.1f && ((float) matches / rightObjs.size()) < 0.1f)
        {
            // Recurse down left and right sides.
            m_left->Build(leftObjs, depth + 1);
            m_right->Build(rightObjs, depth + 1);
        }
        else
        {
            m_left->m_objs = std::vector<Object*>();
            m_right->m_objs = std::vector<Object*>();
        }
    }

    bool KdNode::Intersect(Ray & ray, HitResult & hit)
    {
        HitResult lHit;

        // Check if the ray intersects the bbox of the given node.
        if (m_bbox.Intersect(ray, lHit))
        {

            // If either child still has objects, recurse down both sides
            // and check for intersections.
            if (!m_left->m_objs.empty() || !m_right->m_objs.empty())
            {
                bool hitLeft = m_left->Intersect(ray, hit);
                bool hitRight = m_right->Intersect(ray, hit);

                return hitLeft || hitRight;
            }

            for (Object* obj : m_objs) obj->Intersect(ray, hit);

            return hit.bSuccess;
        }
        return false;
    }
}
