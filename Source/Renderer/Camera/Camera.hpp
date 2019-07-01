//
//  camera.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <Core/Core.hpp>

#include "Renderer/Component/SceneComponent.hpp"

class Camera : public SceneComponent {
public:
    Camera(vec3 pos, vec3 at, vec3 up, float fov, float aspect) : SceneComponent(pos) {
        m_fov       = fov;
        m_aspect    = aspect;
        m_zdir      = glm::normalize(at - pos);
        m_xdir      = glm::normalize(glm::cross(up, m_zdir));
        m_ydir      = glm::normalize(glm::cross(m_zdir, m_xdir));
        m_center    = 1.f / tanf((fov * M_PI / 180.f) * 0.5f) * m_zdir;
    }
    
    inline float& FOV()        { return m_fov; }
    inline float& Aspect()     { return m_aspect; }
    
    inline vec3& Xdir()    { return m_xdir; }
    inline vec3& Ydir()    { return m_ydir; }
    inline vec3& Zdir()    { return m_zdir; }
    inline vec3& Center()  { return m_center; }
    
    
private:
    vec3 m_zdir;    // view direction
    vec3 m_xdir;    // right direction
    vec3 m_ydir;    // up direction
    vec3 m_center;  // center of the image plane
    
    float m_fov;        // field of view
    float m_aspect;     // aspect ratio (typically use width/height of the computed image)
};

#endif /* camera_hpp */
