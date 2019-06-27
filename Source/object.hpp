//
//  object.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include "common/types.hpp"

#include "interface/intersectable.hpp"
#include "component.hpp"
#include "aabb.hpp"
#include "ray.hpp"

class Object : public Component, public Intersectable {
public:
    Object(vec3 pos, bool bUseAABB = true) : Component(pos), m_bUseAABB(bUseAABB) {}
    virtual ~Object() {};
    
    inline bool UseAABB() const { return m_bUseAABB; }
    
    // TODO : we can do better ;)
    virtual AABB GetAABB() { return AABB(vec3(0.f), vec3(0.f)); }
    
private:
    bool m_bUseAABB;
};

#endif /* object_hpp */
