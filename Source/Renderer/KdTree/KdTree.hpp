#pragma once

#include <Core/Core.hpp>

#include <Renderer/Interface/Intersectable.hpp>
#include <Renderer/KdTree/KdNode.hpp>

namespace rt
{
    class KdTree : public Intersectable
    {
    public:
        explicit inline KdTree(std::vector<Object*> objs)
        {
            m_root = new KdNode();

            for (Object* obj : objs)
            {
                (obj->IsBoundByBoundingBox() ? m_in : m_out).push_back(obj);
            }

            m_root->Build(m_in, 0);
        }

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        bool Intersect(Ray & ray, HitResult & hit) override;

    public:
        KdNode* m_root;

        std::vector<Object*> m_in;
        std::vector<Object*> m_out;
    };

}

