//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

namespace rt
{
    class SceneComponent
    {
    public:
        /// Default constructor.
        explicit inline SceneComponent() : m_pos({0, 0, 0}) {}

        /// Constructor.
        explicit inline SceneComponent(const vec3& pos) : m_pos(pos) {}

        /// Destructor.
        virtual ~SceneComponent() = default;

        /// The position of the object.
        inline vec3& Position() { return m_pos; }

    private:
        /// The position of the object.
        vec3 m_pos;
    };
}


