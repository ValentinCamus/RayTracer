//
//  ray_tracer.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef ray_tracer_hpp
#define ray_tracer_hpp

#include <omp.h>
#include <memory>
#include <iostream>

#include <Core/Core.hpp>

#include <Renderer/Rdm/Rdm.hpp>

#include <Renderer/Scene/Scene.hpp>
#include <Renderer/Image/Image.hpp>
#include <Renderer/Object/Object.hpp>
#include <Renderer/Camera/Camera.hpp>
#include <Renderer/KdTree/KdTree.hpp>

#include <Vendor/cpptqdm/tqdm.hpp>

#define MAX_DEPTH 10      // Max number of reflection
#define MAX_RADIANCE 0.01 // Minimal intensity

class RayTracer {
public:
    RayTracer(Image * img, Scene * scene, Camera * cam) {
        m_img = img ;
        m_scene = scene;
        m_cam = cam;
        m_kdtree = new KdTree(scene->Objects());

    };

    bool CastRay(Ray & ray, HitResult& hit) const;

    bool IsLighted(vec3 ldir, vec3 lpos, vec3 hitpos) const;

    color3 Shade(vec3 n, vec3 v, vec3 l, color3 lc, Material * mat) const;

    color3 Trace(Ray & ray) const;
    inline color3 Trace(vec3 & rdir) const;

    color3 Reflect(Ray & ray, HitResult & hit) const;

    Image * Render();
private:
    Image  * m_img;
    Scene  * m_scene;
    Camera * m_cam;

    KdTree * m_kdtree;
};

color3 RayTracer::Shade(vec3 n, vec3 v, vec3 l, color3 lc, Material * mat) const {
    if ((v + l) == vec3(0.f)) return color3(0.f);
    vec3 h = glm::normalize(v + l);
    const float ldoth = glm::dot(l, h);
    const float ndoth = glm::dot(n, h);
    const float vdoth = glm::dot(v, h);
    const float ldotn = glm::dot(l, n);
    const float vdotn = glm::dot(v, n);
    const color3 bsdf = rdm::Bsdf(ldoth, ndoth, vdoth, ldotn, vdotn, mat);
    return bsdf * ldotn * lc;
}

bool RayTracer::CastRay(Ray & ray, HitResult & hit) const {

    hit = HitResult(false);

    /* if KdTree */
    // m_kdtree->Intersect(ray, hit);

    /* else */
   for (Object * obj : m_scene->Objects())
       obj->Intersect(ray, hit);

    return hit.bSuccess;
}

bool RayTracer::IsLighted(vec3 ldir, vec3 lpos, vec3 hitpos) const {
    const float tmax = glm::length(lpos - hitpos);
    Ray ray = Ray(hitpos + ldir * float(BIAS), ldir, 0, tmax);
    HitResult hit = HitResult(false);
    return !CastRay(ray, hit);
}

color3 RayTracer::Reflect(Ray & ray, HitResult & hit) const {
    const vec3 refldir = glm::reflect(ray.Direction(), hit.normal);
    ray = Ray(hit.location + refldir * float(BIAS), refldir, 0, MAX_RANGE, ray.Depth() + 1);
    const float ldotn = glm::dot(ray.Direction(), hit.normal);
    const float fresnel = rdm::Fresnel(ldotn, 1.f, hit.material->IOR());
    return fresnel * Trace(ray) * hit.material->Specular();
}

color3 RayTracer::Trace(Ray & ray) const {
    color3 out = color3(0.0f);
    if (ray.Depth() >  MAX_DEPTH) return out;

    HitResult hit = HitResult(false);

    if (!CastRay(ray, hit)) return m_scene->SkyColor();

    for (Light * light : m_scene->Lights()) {
        const vec3 ldir = glm::normalize(light->Position() - hit.location);
        const bool bIsLighted = IsLighted(ldir, light->Position(), hit.location);
        const bool bIsWhiteColor = out.x >= 1.f && out.y >= 1.f && out.z < 1.f;

        if (bIsLighted && !bIsWhiteColor) {
            const vec3 n = hit.normal;
            const vec3 v = -ray.Direction();
            const color3 lc = light->Color();
            Material * m = hit.material;
            out += Shade(n, v, ldir, lc, m);
        }
    }
    const bool bCanBeReflect = glm::min(out, vec3(1)) == out;
    if (bCanBeReflect) out += Reflect(ray, hit);
    return glm::clamp(out, vec3(0), vec3(1));
}

inline color3 RayTracer::Trace(vec3 & rdir) const {
    Ray ray = Ray(m_cam->Position(), rdir);
    const color3 output = Trace(ray);
    return output;
}

Image * RayTracer::Render() {
    const uint32 w = m_img->Width();
    const uint32 h = m_img->Height();
    const float aspect = 1.f/m_cam->Aspect();

    const float deltaY = 1.f / (h * 0.5f); // one pixel size
    const vec3 dy = deltaY * aspect * m_cam->Ydir(); // one pixel step
    const vec3 rdy = (0.5f - h * 0.5f) / (h * 0.5f) * aspect * m_cam->Ydir();

    const float deltaX = 1.f / (w * 0.5f);
    const vec3 dx = deltaX * m_cam->Xdir();
    const vec3 rdx = (0.5f - w * 0.5f) / (w * 0.5f) * m_cam->Xdir();
    const vec3 rconst = m_cam->Center() + rdx + rdy;

    std::cout << "Rendering : " << std::endl;
    tqdm bar;

#pragma omp parallel for schedule(dynamic)
    for(uint32 j = 0; j < m_img->Height(); ++j) {
        for(uint32 i = 0; i < m_img->Width(); ++i) {
            vec3 rdir = float(i) * dx + float(j) * dy + rconst;
            rdir = glm::normalize(rdir);
            m_img->Pixel(i, j) = Trace(rdir);
        }
        bar.progress(j, m_img->Height()); // Update the progress bar
    }
    std::cout << std::endl << std::endl;

    return m_img;
}

#endif /* ray_tracer_hpp */
