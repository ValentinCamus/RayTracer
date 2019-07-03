//
//  light.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Component/SceneComponent.hpp>

namespace rt
{
    class Light : public SceneComponent
    {
    public:
        /// Constructor.
        explicit inline Light(vec3 pos, color3 color) :
            SceneComponent(pos),
            m_color(color) {}

        /// @return: The color of the light.
        inline color3& Color() { return m_color; }

    private:
        /// The color of the light.
        color3 m_color;
    };
}



