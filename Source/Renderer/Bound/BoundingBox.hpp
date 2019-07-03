//
//  Created by Valentin on 21/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Ray/Ray.hpp>
#include <Renderer/Component/SceneComponent.hpp>
#include <Renderer/Interface/Intersectable.hpp>

namespace rt
{
    class BoundingBox : public Intersectable
    {
    public:
        /// Default Constructor.
        explicit inline BoundingBox(vec3 min = vec3(0), vec3 max = vec3(0)) : m_bounds {min, max} {}

        /// Constructor.
        explicit inline BoundingBox(vec3 bounds[2]) : m_bounds {bounds[0], bounds[1]} {}

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        bool Intersect(Ray & ray, HitResult & hit) override;

        /// @return: The center of the AABB.
        inline vec3 Center() const { return (m_bounds[0] + m_bounds[1]) / 2.0f; }

        /// @return: The bottom left corner of the AABB.
        inline vec3& Min() { return m_bounds[0]; }

        /// @return: The top right corner of the AABB.
        inline vec3& Max() { return m_bounds[1]; }

        /// Expand this bounding box in order to bound this bbox and the one in argument.
        inline void Expand(BoundingBox bbox)
        {
            if (bbox.Min().x < Min().x) Min().x = bbox.Min().x;
            if (bbox.Min().y < Min().y) Min().y = bbox.Min().y;
            if (bbox.Min().z < Min().z) Min().z = bbox.Min().z;

            if (bbox.Max().x > Max().x) Max().x = bbox.Max().x;
            if (bbox.Max().y > Max().y) Max().y = bbox.Max().y;
            if (bbox.Max().z > Max().z) Max().z = bbox.Max().z;
        }

        inline uint32 LongestAxis()
        {
            vec3 minMax = m_bounds[1] - m_bounds[0];

            if (minMax.x > minMax.y) return (minMax.x > minMax.z) ? 0 : 2;
            else return (minMax.y > minMax.z) ? 1 : 2;
        }

    private:
        /// The bounds of the AABB.
        vec3 m_bounds[2];
    };
}


