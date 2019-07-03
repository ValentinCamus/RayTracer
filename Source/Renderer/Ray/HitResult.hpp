//
// Created by Valentin on 2019-07-02.
//

#pragma once

#include <Core/Core.hpp>

#include <Renderer/Component/SceneComponent.hpp>
#include <Renderer/Material/Material.hpp>

namespace rt
{
    struct HitResult
    {
        /// Contains if the hit result is valid.
        bool bSuccess;

        /// The hit location.
        vec3 location;

        /// The hit normal.
        vec3 normal;

        /// The hit material.
        Material * material;

        /// Constructor.
        explicit inline HitResult(vec3 inLocation,
                                  vec3 inNormal,
                                  Material * inMaterial) :
                bSuccess(true),
                location(inLocation),
                normal(inNormal),
                material(inMaterial)
        {}

        /// Default Constructor.
        explicit inline HitResult(bool inbSuccess = false) : bSuccess(inbSuccess) {};
    };
}
