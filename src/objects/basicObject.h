#include "structs.hxx"

#ifndef ENGINE_PROJECT_BASICOBJECT_H
#define ENGINE_PROJECT_BASICOBJECT_H

#include "structs.hxx"

class basicObject {
public:
    unsigned int tex_number;
    std::vector<triangle3d> triags;
    float speed = 0.01f;
    float angle = 1.0f;
    std::vector<unsigned int> pointsAll;
    std::vector<vertex3d> vertexAll;
    std::vector<vertex3dspec> vertexAllspec;

    // vao containe vbo, vbo - vector of points,ebo - list of points
    unsigned int VBO, EBO, VAO;


    bool load_obj_file(const char *filename);

};



#endif
