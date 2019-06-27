//
//  ray.cpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#include "../ray.hpp"

void Ray::Redirect(vec3 o, vec3 d, float tmin, float tmax, uint32 depth){
    m_origin = o;
    m_dir   = d;
    m_tmin  = tmin;
    m_tmax  = tmax;
    m_depth = depth;
    
    /* pre computed value - use to avoid calcul */
    m_sign[0] = m_dir.x > 0;
    m_sign[1] = m_dir.y > 0;
    m_sign[2] = m_dir.z > 0;
    m_invdir = 1.f / d;
}

#include <stdio.h>
