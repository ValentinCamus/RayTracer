//
//  rdm.cpp
//  Ray
//
//  Created by Valentin on 15/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#include "Rdm.hpp"

#include "Core/Math/Math.hpp"

float rdm::Chiplus(float c) { return (c > 0.f) ? 1.f : 0.f; }

float rdm::Beckmann(float ndoth, float alpha) {
    if (Chiplus(ndoth) < 1.0f) return 0.0f;
    float ndoth2 = Pow2(ndoth);
    float alpha2 = Pow2(alpha);
    float tan2   = (1 - ndoth2) / ndoth2;
    float numi  = exp(-1.f * tan2 / alpha2);
    float denom = M_PI * alpha2 * Pow2(ndoth2);
    return (numi / denom);
}

bool rdm::Snell(float ldoth, float n1, float n2, float & cosThetaT){
    const float ldoth2 = Pow2(ldoth);
    const float sin2t  = Pow2(n1 / n2) * (1 - ldoth2);
    if (sin2t <= 1) cosThetaT = Sqrt(1 - sin2t);
    return (sin2t <= 1);
}

float rdm::Fresnel(float cosThetaI, float n1, float n2) {
    float cosThetaT;
    if (!Snell(cosThetaI, n1, n2, cosThetaT)) return 1;
    const float rsnumi  = Pow2(n1 * cosThetaI - n2 * cosThetaT);
    const float rsdenom = Pow2(n1 * cosThetaI + n2 * cosThetaT);
    const float rs = rsnumi / rsdenom;
    const float rpnumi  = Pow2(n1 * cosThetaT - n2 * cosThetaI);
    const float rpdenom = Pow2(n1 * cosThetaT + n2 * cosThetaI);
    const float rp = rpnumi / rpdenom;
    return (rs + rp) / 2;
}

float rdm::G1(float ddoth, float ddotn, float alpha) {
    const float k = ddoth / ddotn;
    if (Chiplus(k) < 1.0f ) return 0.0f;
    const float tanTheta = Sqrt(1 - Pow2(ddotn)) / ddotn;
    const float b = 1 / (alpha * tanTheta);
    if (k <= 0 || b >= 1.6f) return Chiplus(k);
    const float b2 = Pow2(b);
    const float numi  = (3.535f * b + 2.181f * b2);
    const float denom = (1.f + 2.276f * b + 2.577f * b2);
    return numi / denom;
}

float rdm::Smith(float ldoth, float ldotn, float vdoth, float vdotn, float alpha) {
    const float a = G1(ldoth, ldotn, alpha);
    const float b = G1(vdoth, vdotn, alpha);
    return a * b;
}

color3 rdm::BsdfSpecular(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material * m) {
    const float b = Beckmann(ndoth, m->Roughness());
    const float f = Fresnel(ldoth, 1.0f, m->IOR());
    const float s = Smith(ldoth, ldotn, vdoth, vdotn, m->Roughness());
    const float numi = b * f * s;
    const float denom = 4 * ldotn * vdotn;
    return m->Specular() * (numi / denom);
}

color3 rdm::BasdfDiffuse(Material * m) { return (m->Diffuse() / (float) M_PI); }

color3 rdm::Bsdf(float ldoth, float ndoth, float vdoth, float ldotn, float vdotn, Material *m) {
    const color3 bsdfDiffuse  = BasdfDiffuse(m);
    const color3 bsdfSpecular = BsdfSpecular(ldoth, ndoth, vdoth, ldotn, vdotn, m);
    return bsdfDiffuse + bsdfSpecular;
}
