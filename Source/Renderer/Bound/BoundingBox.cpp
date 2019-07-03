//
// Created by Valentin on 2019-07-02.
//

#include <Renderer/Bound/BoundingBox.hpp>

namespace rt
{
    // TODO: Improve me. See: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
    bool BoundingBox::Intersect(Ray & r, HitResult & hit)
    {
        float tmin = (Min().x - r.Position().x) / r.Direction().x;
        float tmax = (Max().x - r.Position().x) / r.Direction().x;

        if (tmin > tmax) std::swap(tmin, tmax);

        float tymin = (Min().y - r.Position().y) / r.Direction().y;
        float tymax = (Max().y - r.Position().y) / r.Direction().y;

        if (tymin > tymax) std::swap(tymin, tymax);

        if ((tmin > tymax) || (tymin > tmax)) return false;

        if (tymin > tmin) tmin = tymin;
        if (tymax < tmax) tmax = tymax;

        float tzmin = (Min().z - r.Position().z) / r.Direction().z;
        float tzmax = (Max().z - r.Position().z) / r.Direction().z;

        if (tzmin > tzmax) std::swap(tzmin, tzmax);

        if ((tmin > tzmax) || (tzmin > tmax)) return false;

        if (tzmin > tmin) tmin = tzmin;
        if (tzmax < tmax) tmax = tzmax;

        hit.bSuccess = true;

        return true;
    }
}
