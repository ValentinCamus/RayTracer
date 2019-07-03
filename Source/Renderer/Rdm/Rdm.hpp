//
//  Created by Valentin on 15/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <Core/Type/Type.hpp>

#include <Renderer/Material/Material.hpp>

namespace rt
{
    namespace rdm
    {
        // TODO: Comment me :)
        float Chiplus(float c);

        // TODO: Comment me :)
        float Beckmann(float ndoth, float alpha);

        // TODO: Comment me :)
        bool Snell(float cosThetaI, float n1, float n2, float & cosThetaT);

        // TODO: Comment me :)
        float Fresnel(float cosThetaI, float n1, float n2);

        // TODO: Comment me :)
        float G1(float ddoth, float ddotn, float alpha);

        // TODO: Comment me :)
        float Smith(float ldoth, float ldotn, float vdoth, float vdotn, float alpha);

        // TODO: Comment me :)
        color3 BsdfSpecular(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material * m);

        // TODO: Comment me :)
        color3 BasdfDiffuse(Material * m);

        // TODO: Comment me :)
        color3 Bsdf(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material * m);
    }
}
