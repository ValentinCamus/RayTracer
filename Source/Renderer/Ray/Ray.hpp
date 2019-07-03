//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Ray/HitResult.hpp>
#include <Renderer/Component/SceneComponent.hpp>
#include <Renderer/Material/Material.hpp>

#define MAX_RANGE 10000
#define BIAS 2e-4

namespace rt
{
    class Ray : public SceneComponent
    {
    public:
        /// Default Constructor.
        explicit inline Ray() : SceneComponent() {}

        /// Constructor.
        explicit inline Ray(vec3 origin,
                            vec3 direction,
                            float tmin = 0,
                            float tmax = MAX_RANGE,
                            uint32 depth = 0) : SceneComponent(origin)
        {
            Redirect(origin, direction, tmin, tmax, depth);
        }

        /// Redirect the ray.
        void Redirect(vec3 o, vec3 d, float tmin= 0, float tmax= MAX_RANGE, uint32 depth= 0);

        /// @return: A location in the ray at a given distance t.
        inline vec3 At(float t) const { return m_origin + m_dir * t; }

        /// @return: t-max.
        inline float& Tmax() { return m_tmax; }

        /// @return: t-min.
        inline float& Tmin() { return m_tmin; }

        /// @return: The number of time that the ray has reflected.
        inline uint32& Depth() { return m_depth; }

        /// @return: The ray origin.
        inline vec3& Orign() { return m_origin; }

        /// @return: The ray direction.
        inline vec3& Direction() { return m_dir; }

        /// @return: The inverse direction of the ray.
        inline const vec3 & Invdir() const { return m_invdir; }

        /// @return: The sign of the ray.
        inline const uint32 * Sign() const { return m_sign; }

        /// @return: true if the X-Axis is positive.
        inline bool IsXPositive() const { return m_dir.x > 0; }

        /// @return: true if the Y-Axis is positive.
        inline bool IsYPositive() const { return m_dir.y > 0; }

        /// @return: true if the Z-Axis is positive.
        inline bool IsZPositive() const { return m_dir.z > 0; }

    private:
        /// The ray origin.
        vec3 m_origin;

        /// The ray direction.
        vec3 m_dir;

        /// The t-min.
        float m_tmin;

        /// The t-max.
        float m_tmax;

        /// The number of time that the ray has reflected.
        uint32 m_depth;

        /// The sign of the ray (in the 3 direction).
        uint32 m_sign[3];

        /// The ray inverse direction.
        vec3 m_invdir;
    };
}

