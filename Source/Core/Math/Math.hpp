//
//  Math.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef math_hpp
#define math_hpp

#include <cmath>

#include <Core/Type/Type.hpp>


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

template<class T> T inline Map(T value, float rangeMin, float rangeMax, float newRangeMin, float newRangeMax) {
    const float numi  = (value - rangeMin) * (newRangeMax - newRangeMin);
    const float denom = rangeMax - rangeMin + newRangeMin;
    return numi / denom;
}

bool inline  SolveQuadratic(float a, float b, float c, float & x1, float & x2) {
    float delta = Pow2(b) - 4 * a * c;
    if (delta < 0) return false;
    
    if (!delta) x1 = x2 = (-0.5f * b) / a ;
    else {
        x1 = (-b - Sqrt(delta)) / (2 * a);
        x2 = (-b + Sqrt(delta)) / (2 * a);
    }
    if (x1 > x2) Swap(x1, x2);
    return true;
}

#endif /* math_hpp */
