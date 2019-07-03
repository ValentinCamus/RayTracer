//
//  Created by Valentin on 21/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Renderer/Ray/Ray.hpp>

namespace rt
{
    class Intersectable
    {
    public:
        /// Destructor.
        virtual ~Intersectable() = default;

        /// Intersect this object with a ray.
        /// @hit: The data of the intersection.
        /// @return: true if the ray has intersected with an this object, else false.
        virtual bool Intersect(Ray& r, HitResult& hit) = 0;
    };
}


