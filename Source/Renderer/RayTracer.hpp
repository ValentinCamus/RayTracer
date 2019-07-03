//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

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

namespace rt
{
    class RayTracer
    {
    public:
        /// Constructor.
        explicit inline RayTracer(Image * image,
                                  Scene * scene,
                                  Camera * camera) :
            m_image(image),
            m_scene(scene),
            m_camera(camera)
        {
            m_kdTree = new KdTree(scene->Objects());
        };

        /// Detect the hit information between a ray and the scene.
        /// @hit: The hit result.
        bool CastRay(Ray & ray, HitResult& hit) const;

        /// Check if a position is lighted by any source of light.
        bool IsLighted(vec3 ldir, vec3 lpos, vec3 hitpos) const;

        /// Shader an object with its hit result information.
        color3 Shade(vec3 n, vec3 v, vec3 l, color3 lc, Material * mat) const;

        /// Trace a ray.
        color3 Trace(Ray & ray) const;

        /// Trace a ray from a direction.
        color3 Trace(vec3 & rdir) const;

        /// Reflect a ray.
        color3 Reflect(Ray & ray, HitResult & hit) const;

        /// Render a scene in a image (@see Image).
        Image * Render();

    private:
        /// The rendered image.
        Image * m_image;

        /// The scene to render.
        Scene * m_scene;

        /// The camera.
        Camera * m_camera;

        KdTree * m_kdTree;
    };
}

