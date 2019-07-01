//
//  aabb.hpp
//  Ray
//
//  Created by Valentin on 21/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef aabb_hpp
#define aabb_hpp

#include <Core/Core.hpp>

#include <Renderer/Ray/Ray.hpp>
#include <Renderer/Component/SceneComponent.hpp>
#include <Renderer/Interface/Intersectable.hpp>

class AxisAlignedBoundingBox : public Intersectable {
public:
    explicit inline AxisAlignedBoundingBox(vec3 min, vec3 max) : m_bounds {min, max} { }
    explicit inline AxisAlignedBoundingBox(vec3 bounds[2]) : m_bounds {bounds[0], bounds[1]} { }
    
    bool Intersect(Ray & ray, HitResult & hit) override;

    inline vec3  Center() const { return (m_bounds[0] + m_bounds[1]) / 2.0f; }
    inline vec3& Min() { return m_bounds[0]; }
    inline vec3& Max() { return m_bounds[1]; }
private:
    vec3 m_bounds[2];
};

bool AxisAlignedBoundingBox::Intersect(Ray & ray, HitResult & hit) {
    
    // TODO : optimize me !!

    const vec3 & rpos = ray.Position();
    const vec3 & rdir = ray.Direction();
    
    float tmin = (Min().x - rpos.x) / rdir.x;
    float tmax = (Max().x - rpos.x) / rdir.x;
    
    if (tmin > tmax) std::swap(tmin, tmax);
    
    float tymin = (Min().x - rpos.y) / rdir.y;
    float tymax = (Max().x - rpos.y) / rdir.y;
    
    if (tymin > tymax) std::swap(tymin, tymax);
    
    if ((tmin > tymax) || (tymin > tmax)) return false;
    
    if (tymin > tmin) tmin = tymin;
    
    if (tymax < tmax) tmax = tymax;
    
    float tzmin = (Min().x - rpos.z) / rdir.z;
    float tzmax = (Max().x - rpos.z) / rdir.z;
    
    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    
    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    
    if (tzmin > tmin) tmin = tzmin;
    
    if (tzmax < tmax) tmax = tzmax;
    
    (void) hit; // TODO : hit result
    
    return true;
}

#endif /* aabb_hpp */
