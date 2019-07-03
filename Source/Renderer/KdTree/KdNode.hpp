#pragma once

#include <vector>

#include <Core/Core.hpp>

#include <Renderer/Interface/Intersectable.hpp>
#include <Renderer/Object/Object.hpp>

namespace rt
{
    class KdNode : public Intersectable
    {
    public:
        void Build(std::vector<Object*> objs, uint32 depth);

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        bool Intersect(Ray & ray, HitResult & hit) override;

    private:
        BoundingBox m_bbox;

        KdNode* m_left;
        KdNode* m_right;

        std::vector<Object*> m_objs;
    };
}

