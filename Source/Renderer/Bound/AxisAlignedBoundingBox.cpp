//
// Created by Valentin on 2019-07-02.
//

#include <Renderer/Bound/AxisAlignedBoundingBox.hpp>

namespace rt
{
    bool AxisAlignedBoundingBox::Intersect(Ray & ray, HitResult & hit)
    {
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
}
