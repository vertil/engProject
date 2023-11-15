#pragma once
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <cstddef>
#include "../foundation/glad/glad.h"
#include <cstddef>
#include <string>
//glm
#include "../foundation/glm/glm.hpp"
#include "../foundation/glm/gtc/matrix_transform.hpp"
#include "../foundation/glm/gtc/type_ptr.hpp"
#include "../foundation/glm/gtx/string_cast.hpp"


#define OM_GL_CHECK()                                                      \
{                                                                          \
    const int err = static_cast<int>(glGetError());                        \
    if (err != GL_NO_ERROR)                                                \
    {                                                                      \
        switch (err)                                                       \
        {                                                                  \
            case GL_INVALID_ENUM:                                          \
                std::cerr << "GL_INVALID_ENUM" << std::endl;               \
                break;                                                     \
            case GL_INVALID_VALUE:                                         \
                std::cerr << "GL_INVALID_VALUE" << std::endl;              \
                break;                                                     \
            case GL_INVALID_OPERATION:                                     \
                std::cerr << "GL_INVALID_OPERATION" << std::endl;          \
                break;                                                     \
            case GL_INVALID_FRAMEBUFFER_OPERATION:                         \
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION"            \
                          << std::endl;                                    \
                break;                                                     \
            case GL_OUT_OF_MEMORY:                                         \
                std::cerr << "GL_OUT_OF_MEMORY" << std::endl;              \
                break;                                                     \
        }                                                                  \
        assert(false);                                                     \
    }                                                                      \
}


struct  vertex{
    float x=0.f;
    float y=0.f;
    float tex_x=0.f;
    float tex_y=0.f;

    std::string getInfo(){
        return std::to_string(x)+":"+ std::to_string(y)+
        "-"+ std::to_string(tex_x)+":"+std::to_string(tex_y);
    }

};
struct  vertex3d{
    float x=0.f;
    float y=0.f;
    float z=0.f;
    float tex_x=0.f;
    float tex_y=0.f;

    std::string getInfo(){
        return std::to_string(x)+":"+ std::to_string(y)+":"+ std::to_string(z)+
               "-"+ std::to_string(tex_x)+":"+std::to_string(tex_y);
    }

};
struct  vertex3dspec{
    glm::vec3 pos;
    glm::vec2 TexCoords;


};

struct  triangle
{
    triangle()
    {
        v[0] = vertex();
        v[1] = vertex();
        v[2] = vertex();
    }
    vertex v[3];
    std::string getInfo(){
        return v[0].getInfo()+"\n"+v[1].getInfo()+"\n"+v[2].getInfo();
    }
};
struct  triangle3d
{
    triangle3d()
    {
        v[0] = vertex3d();
        v[1] = vertex3d();
        v[2] = vertex3d();
    }
    vertex3d v[3];
    std::string getInfo(){
        return v[0].getInfo()+"\n"+v[1].getInfo()+"\n"+v[2].getInfo();
    }
};

struct sprite{
  triangle triag_1;
  triangle triag_2;
};
//---------------
struct simple_vertex{
    float x=0.f;
    float y=0.f;
};
struct simple_triangle{
    simple_triangle()
    {
        v[0] = simple_vertex();
        v[1] = simple_vertex();
        v[2] = simple_vertex();
    }
    simple_vertex v[3];
};




