//
//  scene.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef scene_hpp
#define scene_hpp

#include <vector>
#include <memory>

#include <Core/Core.hpp>

#include "Renderer/Object/Object.hpp"
#include "Renderer/Light/Light.hpp"

class Scene {
public:
    Scene () {}
    Scene (color3 skyColor) : m_skyColor(skyColor) {}
    ~Scene() {}
    
    inline std::vector<Object*> & Objects() { return m_objects; }
    inline std::vector<Light *> & Lights()  { return m_lights;  }
    
    inline color3& SkyColor() { return m_skyColor; }
private:
    std::vector<Object*> m_objects;
    std::vector<Light *> m_lights;
    color3 m_skyColor;
};

#endif /* scene_hpp */
