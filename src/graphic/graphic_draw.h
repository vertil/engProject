#ifndef GRAPHIC_DRAW_H
#define GRAPHIC_DRAW_H

#include "graphicinit.hxx"

class graphic_draw
{
    graphicInit * draw_engine=nullptr;
public:
    graphic_draw();
    ~graphic_draw();
    bool load_texture(std::string_view path,int number);
    void draw_all(std::vector<triangle>& triangles);


};

#endif // GRAPHIC_DRAW_H
