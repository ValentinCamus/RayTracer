//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Core.hpp>

namespace rt
{
    class Material
    {
    public:
        /// Constructor.
        explicit inline Material(float indexOfRefraction,
                                 float roughness,
                                 color3 diffuse,
                                 color3 specular,
                                 bool bIsTransparent = false) :
                m_indexOfRefraction(indexOfRefraction),
                m_roughness(roughness),
                m_diffuse(diffuse),
                m_specular(specular),
                m_bIsTransparent(bIsTransparent) {}

        /// @return: The index of refraction.
        inline float& IndexOfRefraction() { return m_indexOfRefraction; }

        /// @return: The diffuse/albedo color of the material.
        inline color3& Diffuse() { return m_diffuse; }

        /// @return: The roughness of the material.
        inline float& Roughness() { return m_roughness; }

        /// @return: The specular color of the material.
        inline color3& Specular() { return m_specular; }

        /// @return: If the material is transparent.
        inline bool& IsTransparant() { return m_bIsTransparent; }

    private:
        /// The index of refraction.
        float m_indexOfRefraction;

        /// The diffuse/albedo color of the material.
        float m_roughness;

        /// The roughness of the material.
        color3 m_diffuse;

        /// The specular color of the material.
        color3 m_specular;

        /// If the material is transparent.
        bool m_bIsTransparent;
    };
}


