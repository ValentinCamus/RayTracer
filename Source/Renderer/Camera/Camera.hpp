//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Component/SceneComponent.hpp>

namespace rt
{
    class Camera : public SceneComponent
    {
    public:
        /// Constructor
        inline explicit Camera(vec3 position,
                               vec3 at,
                               vec3 up,
                               float fov,
                               float aspect) :
                SceneComponent(position),
                m_zdir(glm::normalize(at - position)),
                m_xdir(glm::normalize(glm::cross(up, m_zdir))),
                m_ydir(glm::normalize(glm::cross(m_zdir, m_xdir))),
                m_center(1.f / tanf(fov * float(M_PI) / 180.f * 0.5f) * m_zdir),
                m_fov(fov),
                m_aspect(aspect) {}

        /// The field of view.
        inline float& Fov() { return m_fov; }

        /// The aspect ratio.
        inline float& Aspect() { return m_aspect; }

        /// The view direction.
        inline vec3& Xdir() { return m_xdir; }

        /// The right direction
        inline vec3& Ydir() { return m_ydir; }

        /// The up direction
        inline vec3& Zdir() { return m_zdir; }

        /// The location of the center of the image plane.
        inline vec3& Center() { return m_center; }

    private:
        /// View direction.
        vec3 m_zdir;

        /// Right direction.
        vec3 m_xdir;

        /// Up direction.
        vec3 m_ydir;

        /// Center of the image plane.
        vec3 m_center;

        /// Field of view.
        float m_fov;

        /// Aspect ratio (typically use width/height of the computed image).
        float m_aspect;
    };
}


