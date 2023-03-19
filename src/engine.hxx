#pragma once
#include "graphic/graphic_draw.h"


class engine{

    SDL_Event event_log;

    //--MAP


    triangle body1;
    triangle body2;
    //runners

    glm::mat4 buffMat=glm::mat4(1.0f);

    graphic_draw * draw_engine=nullptr;


public:
    engine(graphic_draw * draw_engine_in);


    bool event();

    void renderGame();
    void logic();
    void startTimer();
};
