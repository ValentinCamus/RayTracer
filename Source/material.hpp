//
//  material.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include "common/types.hpp"

class Material {
public:
    
    Material(float IOR, float roughness, color3 diffuse, color3 specular, bool bIsTransparent=false) {
        m_IOR = IOR;
        m_roughness = roughness;
        m_diffuse = diffuse;
        m_specular = specular;
        m_bIsTransparent = bIsTransparent;
    }

    inline float& IOR()          {return m_IOR;}
    inline color3& Diffuse()    {return m_diffuse;}
    inline float& Roughness()    {return m_roughness;}
    inline color3& Specular()   {return m_specular;}
    inline bool& IsTransparant() {return m_bIsTransparent;}

private:
    float m_IOR;
    float m_roughness;
    color3 m_diffuse;
    color3 m_specular;
    bool m_bIsTransparent;
};

#endif /* material_hpp */
