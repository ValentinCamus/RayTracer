//
//  image.cpp
//  Ray
//
//  Created by Valentin on 15/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#include "Image.hpp"

#include <Vendor/lode_png/lode_png.hpp>
#include <Vendor/cpptqdm/tqdm.hpp>

namespace rt
{
    void Image::SaveAs(const std::string& name) const
    {
        tqdm bar;
        uint32 cpt = 0;
        std::string filename = name + ".png";
        auto * image = new unsigned char[m_width * m_height * 3];

        std::cout << "Saving : " << std::endl;

        for (unsigned j = 0; j < m_height; ++j)
        {
            for (unsigned i = 0; i < m_width; i++)
            {
                color3 c = m_pixels[i + (m_height - j -1) * m_width];
                image[cpt++] = (byte) Clamp(c.x * 255, 0.f, 255.f);
                image[cpt++] = (byte) Clamp(c.y * 255, 0.f, 255.f);
                image[cpt++] = (byte) Clamp(c.z * 255, 0.f, 255.f);
            }
            bar.progress(j, m_height); // Update the progress bar
        }
        std::cout << std::endl << std::endl;

        unsigned error = lodepng_encode24_file(filename.c_str(), image, m_width, m_height);
        if (error) std::cerr << "Error : " << error << ": " << lodepng_error_text(error);

        delete[] image;
    };
}

