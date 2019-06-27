//
//  rdm.hpp
//  RayTracer
//
//  Created by Valentin on 15/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef rdm_hpp
#define rdm_hpp

#include "../material.hpp"
#include "../common/types.hpp"

namespace rdm {
    float Chiplus(float c);
    
    float Beckmann(float ndoth, float alpha);
    
    bool Snell(float cosThetaI, float n1, float n2, float & cosThetaT);
    
    float Fresnel(float cosThetaI, float n1, float n2);
    
    float G1(float ddoth, float ddotn, float alpha);
    
    float Smith(float ldoth, float ldotn, float vdoth, float vdotn, float alpha);
    
    color3 BsdfSpecular(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material * m);
    
    color3 BasdfDiffuse(Material * m);
    
    color3 Bsdf(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material * m);
}
#endif /* rdm_hpp */
