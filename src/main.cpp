#include "graphic/graphicinit.hxx"
#include "myimgui.h"

int main(int argc, char *argv[]){

    graphicInit gr;
    gr.load_texture("../materials/beer.png",0);
    gr.initProgramBackground();

    imgui_init(gr.window,&gr.gl_context,gr.rend);

    SDL_Event event_log;

    while (true){

        SDL_PollEvent(&event_log);
        ImGui_ImplSDL2_ProcessEvent(&event_log);
        if(event_log.type==SDL_KEYDOWN){
            if(event_log.key.keysym.scancode==SDL_SCANCODE_SPACE){
                break;
            }
        }

        gr.renderOneColGL();
        gr.render_background(0);

        imgui_newframe();
        imgui_window();
        imgui_render();

        gr.swapBuffers();

    }

    imgui_shutdown();

return 0;
}
