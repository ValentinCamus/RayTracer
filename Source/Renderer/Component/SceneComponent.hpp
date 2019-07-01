//
//  component.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include <Core/Core.hpp>

class SceneComponent {
public:
    inline SceneComponent() { /* empty */ }
    inline SceneComponent(vec3& pos) : m_pos(pos) {}
    virtual ~SceneComponent() {};
    
    inline vec3& Position() { return m_pos; }
private:
    vec3 m_pos;
};

#endif /* component_hpp */
