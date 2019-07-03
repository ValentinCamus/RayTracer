//
// Created by Valentin on 2019-07-02.
//

#include "RayTracer.hpp"

#include <omp.h>

#include <Renderer/Object/Shape/Sphere.hpp>

namespace rt
{
    color3 RayTracer::Shade(vec3 n, vec3 v, vec3 l, color3 lc, Material * mat) const
    {
        if ((v + l) == vec3(0.f)) return color3(0.f);

        vec3 h = glm::normalize(v + l);

        float ldoth = glm::dot(l, h);
        float ndoth = glm::dot(n, h);
        float vdoth = glm::dot(v, h);
        float ldotn = glm::dot(l, n);
        float vdotn = glm::dot(v, n);

        color3 bsdf = rdm::Bsdf(ldoth, ndoth, vdoth, ldotn, vdotn, mat);

        return bsdf * ldotn * lc;
    }

    static Material g_m = Material(1.3, 0.1, color3(.5f, .5f, .5f), color3(0.6f));

    bool RayTracer::CastRay(Ray & ray, HitResult & hit) const
    {
        hit = HitResult(false);

        m_kdTree->Intersect(ray, hit);

        // for (Object * obj : m_scene->Objects()) obj->Intersect(ray, hit);

        return hit.bSuccess;
    }

    bool RayTracer::IsLighted(vec3 ldir, vec3 lpos, vec3 hitpos) const
    {
        float tmax = glm::length(lpos - hitpos);

        Ray ray = Ray(hitpos + ldir * float(BIAS), ldir, 0, tmax);
        HitResult hit = HitResult(false);

        return !CastRay(ray, hit);
    }

    color3 RayTracer::Reflect(Ray & ray, HitResult & hit) const
    {
        vec3 refldir = glm::reflect(ray.Direction(), hit.normal);

        ray = Ray(hit.location + refldir * float(BIAS), refldir, 0, MAX_RANGE, ray.Depth() + 1);

        float ldotn = glm::dot(ray.Direction(), hit.normal);
        float fresnel = rdm::Fresnel(ldotn, 1.f, hit.material->IndexOfRefraction());

        return fresnel * Trace(ray) * hit.material->Specular();
    }

    color3 RayTracer::Trace(Ray& ray) const
    {
        color3 out = color3(0.0f);
        if (ray.Depth() >  MAX_DEPTH) return out;

        HitResult hit = HitResult(false);

        if (!CastRay(ray, hit)) return m_scene->SkyColor();

        for (Light * light : m_scene->Lights())
        {
            vec3 lightDirection = glm::normalize(light->Position() - hit.location);
            bool bIsLighted = IsLighted(lightDirection, light->Position(), hit.location);
            bool bIsWhiteColor = out.x >= 1.f && out.y >= 1.f && out.z < 1.f;

            if (bIsLighted && !bIsWhiteColor)
            {
                vec3 n = hit.normal;
                vec3 v = -ray.Direction();
                color3 lc = light->Color();
                Material * m = hit.material;
                out += Shade(n, v, lightDirection, lc, m);
            }
        }

        bool bCanBeReflect = glm::min(out, vec3(1)) == out;
        if (bCanBeReflect) out += Reflect(ray, hit);

        return glm::clamp(out, vec3(0), vec3(1));
    }

    color3 RayTracer::Trace(vec3 & rdir) const
    {
        Ray ray = Ray(m_camera->Position(), rdir);
        color3 output = Trace(ray);
        return output;
    }

    Image * RayTracer::Render()
    {
        tqdm bar;

        uint32 w = m_image->Width();
        uint32 h = m_image->Height();
        float aspect = 1.f / m_camera->Aspect();

        float deltaY = 1.f / (h * 0.5f); // one pixel size
        vec3 dy = deltaY * aspect * m_camera->Ydir(); // one pixel step
        vec3 rdy = (0.5f - h * 0.5f) / (h * 0.5f) * aspect * m_camera->Ydir();

        float deltaX = 1.f / (w * 0.5f);
        vec3 dx = deltaX * m_camera->Xdir();
        vec3 rdx = (0.5f - w * 0.5f) / (w * 0.5f) * m_camera->Xdir();
        vec3 rconst = m_camera->Center() + rdx + rdy;

        std::cout << "Rendering : " << std::endl;

#pragma omp parallel for schedule(dynamic)
        for(uint32 j = 0; j < m_image->Height(); ++j)
        {
            for(uint32 i = 0; i < m_image->Width(); ++i)
            {
                vec3 rdir = float(i) * dx + float(j) * dy + rconst;
                rdir = glm::normalize(rdir);
                m_image->Pixel(i, j) = Trace(rdir);
            }

            bar.progress(j, m_image->Height()); // Update the progress bar
        }

        std::cout << std::endl << std::endl;

        return m_image;
    }
}
