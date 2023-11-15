#include "basicCamera.h"

glm::mat4 &basicCamera::getCamera() {
    // we just need camera position, target, world up
    //this->Camera=glm::lookAt(this->CamPos, this->CamPos+this->CamFront, this->CamUP);
    glm::vec3 asd = this->CamPos+this->CamFront;
    this->Camera=glm::lookAt(this->CamPos, this->CamPos+this->CamFront, this->CamUP);

    return this->Camera;
}

void basicCamera::left() {
    this->CamPos-=glm::normalize(glm::cross(this->CamFront,this->CamUP))*CamSpeed;
}
void basicCamera::right(){
    this->CamPos+=glm::normalize(glm::cross(this->CamFront,this->CamUP))*CamSpeed;
}
void basicCamera::forward(){
    CamPos+=CamSpeed*this->CamFront;
}
void basicCamera::backward(){
    CamPos-=CamSpeed*this->CamFront;
}