//
//  object.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

#include <Core/Core.hpp>

#include "Renderer/Interface/Intersectable.hpp"
#include "Renderer/Component/SceneComponent.hpp"
#include "AxisAlignedBoundingBox.hpp"
#include "Renderer/Ray/Ray.hpp"

class Object : public SceneComponent, public Intersectable {
public:
    Object(vec3 pos, bool bUseAABB = true) : SceneComponent(pos), m_bUseAABB(bUseAABB) {}
    virtual ~Object() {};
    
    inline bool UseAABB() const { return m_bUseAABB; }
    
    // TODO : we can do better ;)
    virtual AxisAlignedBoundingBox GetAABB() { return AxisAlignedBoundingBox(vec3(0.f), vec3(0.f)); }
    
private:
    bool m_bUseAABB;
};

#endif /* object_hpp */
