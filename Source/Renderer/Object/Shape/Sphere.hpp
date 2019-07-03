//
//  Created by Valentin on 12/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <iostream>

#include <Core/Core.hpp>

#include <Renderer/Object/Object.hpp>

namespace rt
{
    class Sphere : public Object
    {
    public:
        explicit inline Sphere(vec3 origin,
                               float radius,
                               Material * mat) :
                Object(origin, true),
                m_radius(radius),
                m_mat(mat) {};

        ~Sphere() override = default;

        /// @return: The object AABB.
        inline AxisAlignedBoundingBox AABB() override
        {
            vec3 min = Position() - m_radius;
            vec3 max = Position() + m_radius;
            return AxisAlignedBoundingBox(min, max);
        }

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        bool Intersect(Ray& ray, HitResult& hit) override;

    private:
        /// The sphere radius.
        float m_radius;

        /// The object material.
        Material * m_mat;
    };
}

