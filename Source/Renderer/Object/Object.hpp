//
//  object.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Interface/Intersectable.hpp>
#include <Renderer/Component/SceneComponent.hpp>
#include <Renderer/Bound/AxisAlignedBoundingBox.hpp>
#include <Renderer/Ray/Ray.hpp>

#define NULL_AABB AxisAlignedBoundingBox(vec3(0.f), vec3(0.f))

namespace rt
{
    class Object :
            public SceneComponent,
            public Intersectable
    {
    public:
        /// Constructor.
        explicit inline Object(vec3 pos, bool bUseAABB = true) :
            SceneComponent(pos),
            m_bIsBoundByAABB(bUseAABB) {}

        /// Destructor.
        ~Object() override = default;

        /// @return: true if this object is bound by an AABB.
        inline bool IsBoundByAABB() const { return m_bIsBoundByAABB; }

        /// @return: The object AABB (NULL_AABB by default).
        virtual inline AxisAlignedBoundingBox AABB() { return NULL_AABB; }

    private:
        /// If this object is bound by an AABB.
        bool m_bIsBoundByAABB;
    };
}

