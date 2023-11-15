#include "basicObject.h"

bool basicObject::load_obj_file(const char *filename) {
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
            //std::cout << line << std::endl;
            std::istringstream v(line.substr(2));
            float x, y, z;
            v >> x;
            v >> y;
            v >> z;
            points.push_back({x, y, z});
        }else if (line.substr(0, 2) == "vt") {
            //std::cout << line << std::endl;
            std::istringstream v(line.substr(3));
            float U, V;
            v >> U;
            v >> V;
            textures.push_back({U,V});

        }else if (line.substr(0, 2) == "f ") {
            //std::cout << line << std::endl;

            std::istringstream v(line.substr(2));
            unsigned int v1,v2,v3;
            unsigned int t1,t2,t3;
            unsigned int vn1,vn2,vn3;

            const char* chh=line.c_str();
            sscanf (chh, "f %i/%i/%i %i/%i/%i %i/%i/%i",&v1,&t1,&vn1,&v2,&t2,&vn2,&v3,&t3,&vn3);

            v1--;
            v2--;
            v3--;
            t1--;
            t2--;
            t3--;


            vertex3dspec vertspec;

            vertspec.pos=points[v1];
            vertspec.TexCoords=textures[t1];

            vertexAllspec.push_back(vertspec);
            /////////////////
            vertspec.pos=points[v2];
            vertspec.TexCoords=textures[t2];

            vertexAllspec.push_back(vertspec);
            ////////////////////
            vertspec.pos=points[v3];
            vertspec.TexCoords=textures[t3];

            vertexAllspec.push_back(vertspec);

            //----------------------------------------

            triangle3d buff;

            buff.v[0].x=points[v1].x;
            buff.v[0].y=points[v1].y;
            buff.v[0].z=points[v1].z;
            buff.v[0].tex_x=textures[t1].x;
            buff.v[0].tex_y=textures[t1].y;


            /////////////////////////

            buff.v[1].x=points[v2].x;
            buff.v[1].y=points[v2].y;
            buff.v[1].z=points[v2].z;
            buff.v[1].tex_x=textures[t2].x;
            buff.v[1].tex_y=textures[t2].y;


            ////////////////////////////////////

            buff.v[2].x=points[v3].x;
            buff.v[2].y=points[v3].y;
            buff.v[2].z=points[v3].z;
            buff.v[2].tex_x=textures[t3].x;
            buff.v[2].tex_y=textures[t3].y;




            //////////////////////////////////

            this->triags.push_back(buff);
        }
    }
    for (int i=0;i<vertexAllspec.size();i++){
        pointsAll.push_back(i);
    }


    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexAllspec.size()*sizeof(vertex3dspec),
                 &vertexAllspec[0],  GL_DYNAMIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pointsAll.size()* sizeof(unsigned int),
                 &pointsAll[0],  GL_DYNAMIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3dspec), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3d), (void*)offsetof( vertex3dspec, TexCoords));
    glBindVertexArray(0);
    return true;
}
