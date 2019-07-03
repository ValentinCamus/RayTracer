//
// Created by Valentin on 2019-07-02.
//

#include <Renderer/Object/Shape/Plane.hpp>

namespace rt
{
    bool Plane::Intersect(Ray & ray, HitResult & hit)
    {
        float t;
        const float denom = glm::dot(ray.Direction(), m_normal);
        if (denom == 0.0f) return false;

        t  = glm::dot(ray.Position(), m_normal) + m_distance;
        t /= denom;
        t *= -1;

        if (!InRange(t, ray.Tmin(), ray.Tmax())) return false;

        ray.Tmax() = t;
        hit = HitResult(ray.At(t), m_normal, m_material);

        return true;
    }
}
