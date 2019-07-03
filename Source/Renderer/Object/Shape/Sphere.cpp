//
// Created by Valentin on 2019-07-02.
//

#include <Renderer/Object/Shape/Sphere.hpp>

namespace rt
{
    bool Sphere::Intersect(Ray& ray, HitResult& hit)
    {
        float t, t1, t2;
        vec3 co = ray.Position() - Position();
        float b = 2 * glm::dot(ray.Direction(), co);
        float c = glm::dot(co, co) - Pow2(m_radius);

        if (!SolveQuadratic(1, b, c, t1, t2)) return false;

        if      (InRange(t1, ray.Tmin(), ray.Tmax())) t = t1;
        else if (InRange(t2, ray.Tmin(), ray.Tmax())) t = t2;
        else return false; // this sphere is out of range

        ray.Tmax() = t;
        vec3 hitp = ray.At(t);
        vec3 normal = hitp - Position();
        hit = HitResult(hitp, glm::normalize(normal), m_mat);

        return true;
    }
}