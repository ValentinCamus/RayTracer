//
//  Math.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <cmath>
#include <algorithm>

#include <Core/Type/Type.hpp>

namespace rt
{
    template<class T> T inline Pow2(T value) { return value * value; }
    template<class T> T inline Pow3(T value) { return value * value * value; }
    template<class T> T inline Pow(T value, uint32 expo) { return pow(value, expo); }

    template<class T> T inline Sqrt(T value) { return sqrt(value); }

    template<class T> T inline Abs(T value) { return abs(value); }

    template<class T> T inline Min(T a, T b) { return std::min(a, b); }
    template<class T> T inline Max(T a, T b) { return std::max(a, b); }


    template<class T> T inline Clamp(T value, T min, T max) { return std::max(std::min(value, max), min); }
    template<class T> bool inline InRange(T value, T min, T max){ return (value >= min && value <= max); }

    template<class T> void inline Swap(T& a, T& b) { std::swap(a, b); }

    template<class T> T inline Fact(T value) {return (value > 0) ? value * Fact(value - 1) : 1; }

    template<class T> T Map(T value, float rangeMin, float rangeMax, float newRangeMin, float newRangeMax);

    bool SolveQuadratic(float a, float b, float c, float & x1, float & x2);
}

