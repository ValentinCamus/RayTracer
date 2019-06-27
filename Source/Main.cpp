//
//  main.cpp
//  RayTracer
//
//  Created by Valentin on 11/11/2018.
//  Copyright © 2018 Valentin. All rights reserved.
//

#define WIDTH   800
#define HEIGHT  600

#include <memory>
#include <chrono>
#include <iostream>

#include "image.hpp"
#include "object.hpp"
#include "ray_tracer.hpp"
#include "common/types.hpp"

#include "shape/sphere.hpp"
#include "shape/plane.hpp"

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

void Scene1() {
    const float fov     = 60;
    const vec3 pos  = vec3(3, 1,0);
    const vec3 at   = vec3(0,0.3,0);
    const vec3 up   = vec3(0,  1,0);
    const float aspect  = (float) WIDTH / (float) HEIGHT;
    
    color3 skyColor = color3(0.196078, 0.7, 0.85);
    
    Image img   = Image(WIDTH, HEIGHT);
    Scene scene = Scene(skyColor);
    Camera cam  = Camera(pos, at, up, fov, aspect);
    
    Material m1 = Material(1.3, 0.1, color3(.5f, .5f, .5f), color3(0.6f));
    Material m2 = Material(1.3, 0.1, color3(0.5f, 0.f, 0.f), color3(0.6f));
    Material m3 = Material(1.3, 0.1, color3(0.f, 0.5f, 0.5f), color3(0.6f));
    Material m4 = Material(1.3, 0.1, color3(0.f, 0.f, 0.5f), color3(0.6f));
    
    Sphere s1 = Sphere(vec3(0,0,0), 0.25, &m1);
    Sphere s2 = Sphere(vec3(1,0,0), 0.25, &m2);
    Sphere s3 = Sphere(vec3(0,1,0), 0.25, &m3);
    Sphere s4 = Sphere(vec3(0,0,1), 0.25, &m4);
    
    Material m5 = Material(1.12, 0.2, color3(0.6f), color3(0.6f));
    Plane p1 = Plane(vec3(0,1,0), 0, &m5);
    
    Light l1 = Light(vec3(10,10,10),  color3(1,1,1));
    Light l2 = Light(vec3(4,10,-2), color3(1,1,1));
    
    scene.Objects().push_back(&s1);
    scene.Objects().push_back(&s2);
    scene.Objects().push_back(&s3);
    scene.Objects().push_back(&s4);
    
    scene.Objects().push_back(&p1);
    
    scene.Lights().push_back(&l1);
    scene.Lights().push_back(&l2);
    
    Clock::time_point t1 = Clock::now();
    RayTracer rt = RayTracer(&img, &scene, &cam);
    rt.Render()->SaveAs("image");
    Clock::time_point t2 = Clock::now();
    Duration time = std::chrono::duration_cast<Duration>(t2 - t1);
    std::cout << "All Step Duration : " << time.count() << std::endl;
}


void Scene2() {
    const float fov = 60;
    const vec3 pos  = vec3(3,0,0);
    const vec3 at   = vec3(0,0.3,0);
    const vec3 up   = vec3(0, 1,0);
    const float aspect  = (float) WIDTH / (float) HEIGHT;
    
    color3 skyColor = color3(0.196078, 0.7, 0.85);
    
    Image img   = Image(WIDTH, HEIGHT);
    Scene scene = Scene(skyColor);
    Camera cam  = Camera(pos, at, up, fov, aspect);
    
    for(int i=0; i<10; ++i) {
        Material mat = Material(1.1382, ((float) 10 - i) / (10 * 9.f), color3(0.301, 0.034, 0.039), color3(1.0, 0.992, 0.98));
        Sphere * s = new Sphere(vec3(0, 0, -1.5 + i / 9.f * 3.f), .15f, &mat);
        scene.Objects().push_back(s);
    }
    
    for(int i=0; i<10; ++i) {
        Material mat = Material(1.1153, ((float)i+1) / 10.f, color3(0.012,0.036,0.106), color3(1.0, 0.965, 1.07));
        Sphere * s = new Sphere(vec3(0, 1, -1.5 + i / 9.f * 3.f), .15f, &mat);
        scene.Objects().push_back(s);
    }
    
    Material m1 = Material(2.4449, 0.0681, color3(0.014, 0.012, 0.012), color3(1.0, 0.882, 0.786));
    Sphere s = Sphere(vec3(-3.f, 1.f, 0.f), 2.f, &m1);
    scene.Objects().push_back(&s);
    
    Material m2 = Material(1.1481, 0.0625, color3(0.016, 0.073, 0.04), color3(1.0, 1.056, 1.146));
    Plane p = Plane(vec3(0,1,0), 1, &m2);
    scene.Objects().push_back(&p);
    
    Light l1 = Light(vec3(10,10,10), color3(10,10,10));
    Light l2 = Light(vec3(4,10,-2), color3(5,3,10));
    
    scene.Lights().push_back(&l1);
    scene.Lights().push_back(&l2);
    
    Clock::time_point t1 = Clock::now();
    RayTracer rt = RayTracer(&img, &scene, &cam);
    rt.Render()->SaveAs("image");
    Clock::time_point t2 = Clock::now();
    Duration time = std::chrono::duration_cast<Duration>(t2 - t1);
    std::cout << "All Step Duration : " << time.count() << std::endl;
}

void Scene3() {
    const float fov = 60;
    const vec3 pos  = vec3(4.5,.8,4.5);
    const vec3 at   = vec3(0,0.3,0);
    const vec3 up   = vec3(0,1,0);
    const float aspect  = (float) WIDTH / (float) HEIGHT;
    
    color3 skyColor = color3(0.196078, 0.7, 0.85);
    
    Image  img   = Image(WIDTH, HEIGHT);
    Scene  scene = Scene(skyColor);
    Camera cam  = Camera(pos, at, up, fov, aspect);

    Light l1 = Light(vec3(0,1.7,1), 0.5f * color3(3,3,3));
    Light l2 = Light(vec3(3,2,3),   0.5f * color3(4,4,4));
    Light l3 = Light(vec3(4,3,-1),  0.5f * color3(5,5,5));
    
    scene.Lights().push_back(&l1);
    scene.Lights().push_back(&l2);
    scene.Lights().push_back(&l3);
    
    Material m1 = Material(6, 0.0181, color3(0.014, 0.012, 0.012), color3(0.7, 0.882, 0.786));
    Material m2 = Material(1.3771, 0.01589, color3(0.26, 0.036, 0.014), color3(1.0, 0.852, 1.172));
    Material m3 = Material(3, 0.00181, color3(0.014, 0.012, 0.012), color3(0.7, 0.882, 0.786));
    Material m4 = Material(1.5771, 0.01589, color3(0.46, 0.136, 0.114), color3(0.8, 0.852, 0.8172));
    Material m5 = Material(1.3051, 0.567, color3(0.06, 0.26, 0.22), color3(0.70, 0.739, 0.721));
    Material m6 = Material(1.1153, 0.18, color3(0.012,0.036,0.406), color3(1.0, 0.965, 1.07));
    
    Material m7 = Material(1.382, 0.05886, color3(.2,.4,.3), color3(.2,.2,.2));
    Material m8 = Material(1.8382, 0.886, color3(.5,.09,.07), color3(.2,.2,.1));
    Material m9 = Material(1.9382, 0.0886, color3(.1,.3,.05), color3(.5,.5,.5));
    
    Sphere s1 = Sphere(vec3(0,0.1,0), 0.3, &m1);
    Sphere s2 = Sphere(vec3(1,-.05,0), 0.15, &m2);
    Sphere s3 = Sphere(vec3(3,0.05,2), 0.25, &m3);
    Sphere s4 = Sphere(vec3(1.3,0.,2.6), 0.215, &m4);
    Sphere s5 = Sphere(vec3(1.9,0.05,2.2), 0.25, &m5);
    Sphere s6 = Sphere(vec3(0,0,1), 0.2, &m6);
    
    Plane p1 = Plane(vec3(0,1,0), 0.2, &m7);
    Plane p2 = Plane(vec3(1, 0.0, -1.0), 2.0, &m8);
    Plane p3 = Plane(vec3(0.3,-0.2,1), 4, &m9);
    
    scene.Objects().push_back(&s1);
    scene.Objects().push_back(&s2);
    scene.Objects().push_back(&s3);
    scene.Objects().push_back(&s4);
    scene.Objects().push_back(&s5);
    scene.Objects().push_back(&s6);
    
    scene.Objects().push_back(&p1);
    scene.Objects().push_back(&p2);
    scene.Objects().push_back(&p3);
    
    Clock::time_point t1 = Clock::now();
    RayTracer rt = RayTracer(&img, &scene, &cam);
    rt.Render()->SaveAs("image");
    Clock::time_point t2 = Clock::now();
    Duration time = std::chrono::duration_cast<Duration>(t2 - t1);
    std::cout << "All Stage Duration : " << time.count() << std::endl << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage : " << argv[0] << " <SceneID>\n";
        std::cerr << "\t SceneID : [opt] scene number";
        std::cerr << std::endl;
    } else {
        uint32 sceneID = std::stoi(argv[1]);
        switch (sceneID) {
            case 1  :
                Scene1();
                break;
            case 2  :
                Scene2();
                break;
            case 3  :
                Scene3();
                break;
            default :
                Scene1();
                break;
        }
    }
    return EXIT_SUCCESS;
}
