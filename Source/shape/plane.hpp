//
//  plane.hpp
//  RayTracer
//
//  Created by Valentin on 14/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

#include "../ray.hpp"
#include "../object.hpp"

#include "../common/types.hpp"

#define PLANE_WORLD_POSITION vec3(0.f)  /* A plane doesn't have a world position,      */
                                        /* so by default it's the center of the world  */

class Plane : public Object {
public:
    Plane() : Object(PLANE_WORLD_POSITION, false) {};
    Plane(vec3 normal, float dist, Material * mat) : Object(PLANE_WORLD_POSITION, false) {
        m_normal = glm::normalize(normal);
        m_dist = dist;
        m_mat = mat;
    }
    bool Intersect(Ray & ray, HitResult & hit) override;
private:
    vec3  m_normal;
    float m_dist;
    Material * m_mat;
};

bool Plane::Intersect(Ray & ray, HitResult & hit) {
    float t;
    const float denom = glm::dot(ray.Direction(), m_normal);
    if (denom == 0.0f) return false;
    t  = glm::dot(ray.Position(), m_normal) + m_dist;
    t /= denom;
    t *= -1;
    if (!InRange(t, ray.Tmin(), ray.Tmax())) return false;
    ray.Tmax() = t;
    hit = HitResult(ray.At(t), m_normal, m_mat);
    return true;
}

#endif /* plane_hpp */
