#ifndef ENGINE_PROJECT_BASICCAMERA_H
#define ENGINE_PROJECT_BASICCAMERA_H

#include "structs.hxx"


class basicCamera {
    glm::vec3 CamPos=glm::vec3(0.0f, 0.0f, 3.0f);;
    glm::vec3 CamFront=glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 CamUP=glm::vec3(0.0f, 1.0f, 0.0f);
    float CamSpeed=0.5f;
    glm::mat4 Camera=glm::mat4(1.0f);
public:
    glm::mat4& getCamera();
    void left();
    void right();
    void forward();
    void backward();
    // not ready
    void up();
    void down();
};


#endif //ENGINE_PROJECT_BASICCAMERA_H
