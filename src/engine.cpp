#include "engine.hxx"


engine::engine(graphic_draw *draw_engine_in)
{
    this->draw_engine=draw_engine_in;
}

bool engine::event(){
    while(SDL_PollEvent(&event_log)){
        ImGui_ImplSDL2_ProcessEvent(&event_log);
        if(event_log.type==SDL_QUIT){
            return false;
        }else if(event_log.type==SDL_KEYDOWN){
            if(event_log.key.keysym.scancode==SDL_SCANCODE_SPACE){
                buffMat=glm::translate(buffMat,glm::vec3(0.0f,0.01,0.0f));
                return true;
            }
        }
    }

    return true;
}



void engine::renderGame(){
    //render background
    //        activateProgBackground(0);
    //        render_triangle(background1);
    //        render_triangle(background2);

    //rotate background matrix
    rotateMat=glm::rotate(glm::mat4(1.0f),
                          glm::radians(static_cast<float>(-angle_new) ),
                          glm::vec3(0.0f,0.0f,1.0f));

    activateProgBody(0,rotateMat);
    render_triangle(background1);
    render_triangle(background2);

    buffMat=glm::translate(buffMat,glm::vec3(moveX,moveY,0.0f));

    activateProgBody(1,buffMat);
    render_triangle(body1);
    render_triangle(body2);

    //rock
    activateProgBackground(3);
    render_triangle(rock);

    crash=checkCollision(body1,rock);
    crash=checkCollision(body2,rock);


    //imgui part
    imgui_newframe(window);
    imgui_window(angle_new,water_power,crash);
    imgui_render();


    glGetError();

    swapBuffers();

}

void engine::logic(){


    if(angle_new!=angle_old){

        if( 0==angle_new || 360==angle_new){

            moveX=0.0f;
            moveY=water_power;

        }else if(angle_new>0 && angle_new<90){

            moveX=sin(angle_new * 3.14 / 180)*water_power;
            moveY=cos(angle_new * 3.14 / 180)*water_power;

        }else if(angle_new==90){

            moveX=water_power;
            moveY=0.0f;

        }else if(angle_new>90 && angle_new<180){
            moveX=cos( (angle_new-90) * 3.14 / 180)*water_power;
            moveY=sin( (angle_new-90) * 3.14 / 180)*water_power*(-1.0f);

        }else if(angle_new==180){

            moveX=0.0f;
            moveY=-water_power;
        }else if(angle_new>180 && angle_new<270){

            moveX=sin( (angle_new-180) * 3.14 / 180)*water_power*(-1.0f);
            moveY=cos( (angle_new-180) * 3.14 / 180)*water_power*(-1.0f);

        }else if(angle_new==270){

            moveX=-water_power;
            moveY=0.0f;

        }else if(angle_new>270 && angle_new<360){
            moveX=cos( (angle_new-270) * 3.14 / 180)*water_power*(-1.0f);
            moveY=sin( (angle_new-270) * 3.14 / 180)*water_power;

        }

        angle_old=angle_new;
    }

}

void engine::startTimer(){
    timerTime=buffTimerTime*1000;
    if(timerTime>60000){
        minutes_=timerTime/60000;
        seconds_=(timerTime%minutes_)/1000;
    }else {
        minutes_=0;
        seconds_=timerTime/1000;
    }

    //std::cout<<std::to_string(timerTime)<<std::endl;
    //std::cout<<std::to_string(minutes_)<<":"<<std::to_string(seconds_)<<std::endl;

    startTime=SDL_GetTicks();
    //std::cout<<std::to_string(startTime)<<std::endl;

}
