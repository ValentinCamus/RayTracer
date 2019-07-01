//
//  intersectable.hpp
//  Ray
//
//  Created by Valentin on 21/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef intersectable_hpp
#define intersectable_hpp

#include <Renderer/Ray/Ray.hpp>

class Intersectable
{
public:
    virtual ~Intersectable() = default;

    virtual bool Intersect(Ray& r, HitResult& hit) = 0;
};

#endif /* intersectable_hpp */
