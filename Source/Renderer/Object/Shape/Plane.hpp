//
//  Created by Valentin on 14/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Ray/Ray.hpp>
#include <Renderer/Object/Object.hpp>

#define PLANE_WORLD_POSITION vec3(0.f)  /* A plane doesn't have a world position,      */
                                        /* so by default it's the center of the world  */

namespace rt
{
    class Plane : public Object
    {
    public:
        /// Default Constructor.
        explicit inline Plane() : Object(PLANE_WORLD_POSITION, false) {};

        /// Constructor.
        explicit inline Plane(vec3 normal,
                              float dist,
                              Material * mat) :
            Object(PLANE_WORLD_POSITION, false),
            m_normal(glm::normalize(normal)),
            m_distance(dist),
            m_material(mat) {}

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        bool Intersect(Ray & ray, HitResult & hit) override;

    private:
        /// The plane normal.
        vec3  m_normal;

        /// The plane distance.
        float m_distance;

        /// The plane material.
        Material * m_material;
    };
}

