#ifndef ENGINE_PROJECT_BASICPERSON_H
#define ENGINE_PROJECT_BASICPERSON_H

#include "structs.hxx"
#include "basicObject.h"

class basicPerson {
public:
    basicObject* model= nullptr;
    glm::mat4 pos = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.0f, 0.0f));
    basicPerson(basicObject* model_in);
    basicPerson(float x_in, float y_in, float z_in, basicObject* model_in);
};


#endif //ENGINE_PROJECT_BASICPERSON_H
