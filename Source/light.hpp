//
//  light.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include "component.hpp"

#include "common/types.hpp"

class Light : public Component {
public:
    Light(vec3 pos, color3 color) : Component(pos), m_color(color) {}
    inline color3& Color() { return m_color; }
private:
    color3 m_color;
};

#endif /* light_hpp */
