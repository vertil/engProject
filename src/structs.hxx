#pragma once



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

bool checkCollision(triangle &a,triangle& b){


}


