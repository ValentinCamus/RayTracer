//
//  component.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef component_hpp
#define component_hpp

#include "common/types.hpp"

class Component {
public:
    inline Component() { /* empty */ }
    inline Component(vec3& pos) : m_pos(pos) {}
    virtual ~Component() {};
    
    inline vec3& Position() { return m_pos; }
private:
    vec3 m_pos;
};

#endif /* component_hpp */
