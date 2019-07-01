//
//  light.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include "Renderer/Component/SceneComponent.hpp"

#include <Core/Core.hpp>

class Light : public SceneComponent {
public:
    Light(vec3 pos, color3 color) : SceneComponent(pos), m_color(color) {}
    inline color3& Color() { return m_color; }
private:
    color3 m_color;
};

#endif /* light_hpp */
