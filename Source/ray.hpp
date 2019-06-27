//
//  ray.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef ray_hpp
#define ray_hpp

#include "common/types.hpp"

#include "component.hpp"
#include "material.hpp"

#define MAX_RANGE 10000
#define BIAS 2e-4

struct HitResult {
    bool bSuccess;
    vec3 location;
    vec3 normal;
    Material * material;
    
    HitResult(vec3 _l, vec3 _n, Material * _m ) {
        bSuccess = true;
        location = _l;
        normal   = _n;
        material = _m;
    }
    
    HitResult(bool _bSuccess = false) : bSuccess(_bSuccess) {};
    
};

class Ray : public Component {
public:
    Ray() : Component() {}
    inline Ray(vec3 o, vec3 d, float tmin = 0, float tmax = MAX_RANGE, uint32 depth = 0) : Component(o) {
        Redirect(o, d, tmin, tmax, depth);
    }
    
    void Redirect(vec3 o, vec3 d, float tmin= 0, float tmax= MAX_RANGE, uint32 depth= 0);

    inline vec3 At(float t) const { return m_origin + m_dir * t; }
    
    inline float& Tmax()     { return m_tmax;   }
    inline float& Tmin()     { return m_tmin;   }
    inline uint32& Depth()   { return m_depth;  }
    inline vec3& Orign()     { return m_origin; }
    inline vec3& Direction() { return m_dir;    }
    
    inline const vec3 & Invdir() const { return m_invdir; }
    inline const uint32 * Sign() const { return m_sign;   }
    
    inline bool IsXPositive() const { return m_dir.x > 0; }
    inline bool IsYPositive() const { return m_dir.y > 0; }
    inline bool IsZPositive() const { return m_dir.z > 0; }
    
private:
    vec3 m_origin;
    vec3 m_dir;
    float m_tmin;
    float m_tmax;
    uint32 m_depth;
    
    uint32 m_sign[3];
    vec3 m_invdir;
};

#endif /* ray_hpp */
