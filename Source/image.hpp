//
//  image.hpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include <vector>
#include <string>
#include <fstream>

#include "math/math.hpp"
#include "common/types.hpp"
#include "misc/progress_bar.hpp"

class Image {
public:
    inline Image(uint32 w, uint32 h) : m_width(w), m_height(h) {
        m_pixels = std::vector<color3>(w * h);
    };
    
    inline uint32 AsIndex(uint32 x, uint32 y) const { return x + y * m_width; }
    inline color3& Pixel(uint32 x, uint32 y) { return m_pixels[AsIndex(x, y)]; }
    inline std::vector<color3>& Pixels() { return m_pixels; }
    inline bool IsValid(uint32 x, uint32 y) const { return x < m_width && y < m_height; }
    
    inline uint32& Width()  { return m_width;  }
    inline uint32& Height() { return m_height; }
    
    inline color3& operator[](uint32 i) { return m_pixels[i]; }
    
    void SaveAs(std::string& name) const;
    inline void SaveAs(std::string&& name) const { std::string s(name); SaveAs(s); };
private:
    uint32 m_width;
    uint32 m_height;
    
    std::vector<color3> m_pixels;
};

#endif /* image_hpp */
