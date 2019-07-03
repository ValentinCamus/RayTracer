//
//  scene.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <vector>
#include <memory>

#include <Core/Core.hpp>

#include <Renderer/Object/Object.hpp>
#include <Renderer/Light/Light.hpp>

namespace rt
{
    class Scene
    {
    public:
        /// Default constructor.
        explicit inline Scene (color3 skyColor = color3(1)) : m_skyColor(skyColor) {}

        /// Destructor.
        virtual ~Scene() = default;

        /// @return: Vector of rt objects.
        inline std::vector<Object*> & Objects() { return m_objects; }

        /// @return: Vector of rt light.
        inline std::vector<Light *> & Lights()  { return m_lights;  }

        /// @return: The sky color.
        inline color3& SkyColor() { return m_skyColor; }

    private:
        /// Vector of rt objects.
        std::vector<Object*> m_objects;

        /// Vector of rt lights.
        std::vector<Light *> m_lights;

        /// The sky color.
        color3 m_skyColor;
    };
}

