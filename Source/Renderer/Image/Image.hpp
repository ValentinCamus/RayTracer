//
//  image.hpp
//  Ray
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#pragma once

#include <vector>
#include <string>
#include <fstream>

#include <Core/Core.hpp>

namespace rt
{
    class Image
    {
    public:
        /// Constructor.
        explicit inline Image(uint32 width, uint32 height) :
            m_width(width),
            m_height(height),
            m_pixels(std::vector<color3>(m_width * m_height)) {}

        /// @return:
        inline uint32 AsIndex(uint32 x, uint32 y) const { return x + y * m_width; }

        /// @return:
        inline color3& Pixel(uint32 x, uint32 y) { return m_pixels[AsIndex(x, y)]; }

        /// @return: The vector of pixel.
        inline std::vector<color3>& Pixels() { return m_pixels; }

        /// @return: true if the given dimension are valid coordinate in the image, else false.
        inline bool IsValid(uint32 x, uint32 y) const { return x < m_width && y < m_height; }

        /// @return: The width of the image.
        inline uint32& Width() { return m_width; }

        /// @return: The height of the image.
        inline uint32& Height() { return m_height; }

        /// @return:
        inline color3& operator[](uint32 i) { return m_pixels[i]; }

        /// Save the image .
        /// @name: The name of the saved image: <name>.png.
        void SaveAs(const std::string& name) const;

    private:
        /// The width of the image.
        uint32 m_width;

        /// The height of the image.
        uint32 m_height;

        /// The pixels of the image.
        /// @note: 2D array.
        std::vector<color3> m_pixels;
    };
}
