#include "basicPerson.h"

basicPerson::basicPerson(basicObject *model_in) {
    this->model=model_in;
}


basicPerson::basicPerson(float x_in, float y_in, float z_in, basicObject *model_in) {
    glm::mat4 pos = glm::translate(glm::mat4(1), glm::vec3(x_in, y_in, z_in));
    this->model=model_in;
}

