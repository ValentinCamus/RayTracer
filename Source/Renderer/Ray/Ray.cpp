//
//  ray.cpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#include "Ray.hpp"

namespace rt
{
    void Ray::Redirect(vec3 o, vec3 d, float tmin, float tmax, uint32 depth){
        m_origin = o;
        m_dir   = d;
        m_tmin  = tmin;
        m_tmax  = tmax;
        m_depth = depth;

        /* pre computed value - use to avoid calcul */
        m_sign[0] = static_cast<uint32>(m_dir.x > 0);
        m_sign[1] = static_cast<uint32>(m_dir.y > 0);
        m_sign[2] = static_cast<uint32>(m_dir.z > 0);
        m_invdir = 1.f / d;
    }
}
