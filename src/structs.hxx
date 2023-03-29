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
struct object {
    glm::mat4 pos = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));
    std::vector<triangle> triags;
    float speed = 0.01f;
    float angle = 1.0f;

    bool load_obj_file(const char *filename) {
        std::vector<glm::vec3> points;
        std::vector<glm::vec2> textures;


        std::ifstream in(filename, std::ios::in);
        if (!in) {
            std::cerr << "Cannot open " << filename << std::endl;
            return false;
        }
        std::string line;
        while (std::getline(in, line)) {
            if (line.substr(0, 2) == "v ") {
                std::cout<< line<<std::endl;
                std::istringstream v(line.substr(2));
                float x, y, z;
                v >> x;
                v >> y;
                v >> z;
                points.push_back({x,y,z});
            }else if (line.substr(0, 3) == "vn ") {
                std::cout<< line<<std::endl;
                std::istringstream v(line.substr(2));
                float x, y, z;
                v >> x;
                v >> y;
                v >> z;
                points.push_back({x,y,z});
            } else if (line.substr(0, 2) == "vt") {
                std::istringstream v(line.substr(3));
                float U, V;
                v >> U;
                v >> V;
                textures.push_back({U,V});

            }
        }
        for (auto i: points) {
            std::cout << i.x << ":" << i.y << ":" << i.z << std::endl;
        }
        /*for (auto i: textures) {
            std::cout << i.x << ":" << i.y << std::endl;
        }*/
        return true;
    }

};

struct camera{
    glm::vec3 CamPos=glm::vec3(0.0f, 0.0f, 0.0f);;
    glm::vec3 CamFront=glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 CamUP=glm::vec3(0.0f, 1.0f, 0.0f);
    float CamSpeed=0.2f;
    glm::mat4 Camera=glm::mat4(1.0f);
    glm::mat4& getCamera(){
        this->Camera=glm::lookAt(this->CamPos, this->CamPos+this->CamFront, this->CamUP);
        return this->Camera;
    }
    void left(){
        this->CamPos-=glm::normalize(glm::cross(this->CamFront,this->CamUP))*CamSpeed;
    }
    void right(){
        this->CamPos+=glm::normalize(glm::cross(this->CamFront,this->CamUP))*CamSpeed;
    }
    void move(float x, float y){

    }
};


