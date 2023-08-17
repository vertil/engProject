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

    std::string getInfo(){
        return std::to_string(x)+":"+ std::to_string(y)+
        "|"+ std::to_string(tex_x)+":"+std::to_string(tex_y);
    }

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
                std::cout << line << std::endl;
                std::istringstream v(line.substr(2));
                float x, y, z;
                v >> x;
                v >> y;
                v >> z;
                points.push_back({x, y, z});
            }else if (line.substr(0, 2) == "vt") {
                std::cout << line << std::endl;
                std::istringstream v(line.substr(3));
                float U, V;
                v >> U;
                v >> V;
                textures.push_back({U,V});

            }else if (line.substr(0, 2) == "f ") {
                std::cout << line << std::endl;

                std::istringstream v(line.substr(2));
                int v1,v2,v3;
                int t1,t2,t3;

                const char* chh=line.c_str();
                sscanf (chh, "f %i/%i %i/%i %i/%i",&v1,&t1,&v2,&t2,&v3,&t3);

                v1--;
                v2--;
                v3--;
                t1--;
                t2--;
                t3--;

                triangle buff;
                buff.v[0].x=points[v1].x;
                buff.v[0].y=points[v1].y;
                buff.v[0].tex_x=textures[t1].x;
                buff.v[0].tex_y=textures[t1].y;

                buff.v[1].x=points[v2].x;
                buff.v[1].y=points[v2].y;
                buff.v[1].tex_x=textures[t2].x;
                buff.v[1].tex_y=textures[t2].y;

                buff.v[2].x=points[v3].x;
                buff.v[2].y=points[v3].y;
                buff.v[2].tex_x=textures[t3].x;
                buff.v[2].tex_y=textures[t3].y;

                this->triags.push_back(buff);
            }
        }

        return true;
    }

};

struct camera{
    glm::vec3 CamPos=glm::vec3(0.0f, 0.0f, 0.0f);;
    glm::vec3 CamFront=glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 CamUP=glm::vec3(0.0f, 1.0f, 0.0f);
    float CamSpeed=0.001f;
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
    void up(){
        //this->CamPos+=glm::normalize(glm::cross(glm::vec3(0.0f,0.),this->CamUP))*CamSpeed;
    }
    void down(){
        //this->CamPos-=CamSpeed*this->CamFront;
    }

};


