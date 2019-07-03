//
// Created by Valentin on 2019-07-01.
//

#include "Math.hpp"

namespace rt
{
    template<class T>
    T Map(T value, float rangeMin, float rangeMax, float newRangeMin, float newRangeMax)
    {
        const float numi  = (value - rangeMin) * (newRangeMax - newRangeMin);
        const float denom = rangeMax - rangeMin + newRangeMin;
        return numi / denom;
    }

    bool SolveQuadratic(float a, float b, float c, float &x1, float &x2)
    {
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
}
