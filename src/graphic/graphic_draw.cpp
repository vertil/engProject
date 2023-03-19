#include "graphic_draw.h"

graphic_draw::graphic_draw()
{
    draw_engine=new graphicInit();


    //init shaders
    draw_engine->initProgramBackground();
    draw_engine->initProgramBody();


}

graphic_draw::~graphic_draw()
{
    draw_engine->~graphicInit();
}

bool graphic_draw::load_texture(std::string_view path, int number)
{
    draw_engine->load_texture(path, number);
}

void graphic_draw::draw_all(std::vector<triangle> &triangles)
{
    this->draw_engine->render_background(0);
    for (auto i:triangles){
        this->draw_engine->render_triangle(i);
    }
}


