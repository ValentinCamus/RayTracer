//
//  sphere.hpp
//  RayTracer
//
//  Created by Valentin on 12/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <iostream>

#include "../math/math.hpp"
#include "../object.hpp"

#include "../common/types.hpp"

class Sphere : public Object {
public:
    Sphere(vec3 origin, float radius, Material * mat) : Object(origin, true), m_radius(radius), m_mat(mat) {};
    ~Sphere() override {};
    
    inline AABB GetAABB() override {
        return AABB(Position() - m_radius, Position() + m_radius);
    }
    
    bool Intersect(Ray& ray, HitResult& hit) override;
private:
    float m_radius;
    Material * m_mat;
};

bool Sphere::Intersect(Ray& ray, HitResult& hit) {
    float t, t1, t2;
    vec3 co = ray.Position() - Position();
    const float b = 2 * glm::dot(ray.Direction(), co);
    const float c = glm::dot(co, co) - Pow2(m_radius);
    if (!SolveQuadratic(1, b, c, t1, t2)) return false;
    if      (InRange(t1, ray.Tmin(), ray.Tmax())) t = t1;
    else if (InRange(t2, ray.Tmin(), ray.Tmax())) t = t2;
    else return false; // this sphere is out of range
    ray.Tmax() = t;
    vec3 hitp   = ray.At(t);
    vec3 normal = hitp - Position();
    hit = HitResult(hitp, glm::normalize(normal), m_mat);
    return true;
}

#endif /* sphere_hpp */
