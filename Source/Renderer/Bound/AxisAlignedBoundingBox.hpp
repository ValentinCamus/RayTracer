//
//  aabb.hpp
//  Ray
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
    class AxisAlignedBoundingBox : public Intersectable
    {
    public:
        /// Constructor.
        explicit inline AxisAlignedBoundingBox(vec3 min, vec3 max) : m_bounds {min, max} {}

        /// Constructor.
        explicit inline AxisAlignedBoundingBox(vec3 bounds[2]) : m_bounds {bounds[0], bounds[1]} {}

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

    private:
        /// The bounds of the AABB.
        vec3 m_bounds[2];
    };
}


