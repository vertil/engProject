#include "graphic/graphicinit.hxx"
#include "myimgui.h"
#include "iostream"

int main(int argc, char *argv[]){


    graphicInit gr;
    gr.load_texture("../materials/beer.png",0);
    gr.initProgramBackground();

    std::cout<< gr.initProgramBody()<<std::endl;

    imgui_init(gr.window,&gr.gl_context,gr.rend);

    SDL_Event event_log;

    glm::mat4 testMath=glm::mat4( 1.0 );
    while (true){

        SDL_PollEvent(&event_log);
        ImGui_ImplSDL2_ProcessEvent(&event_log);
        if(event_log.type==SDL_KEYDOWN){
            if(event_log.key.keysym.scancode==SDL_SCANCODE_SPACE){
                break;
            }else if(event_log.key.keysym.scancode==SDL_SCANCODE_Q){
                testMath*=glm::rotate(glm::mat4(1.0f),
                                      glm::radians(45.0f),
                                      glm::vec3(0.0f,0.0f,1.0f));

            }else if(event_log.key.keysym.scancode==SDL_SCANCODE_E){
                testMath*=glm::rotate(glm::mat4(1.0f),
                                      glm::radians(-45.0f),
                                      glm::vec3(0.0f,0.0f,1.0f));
            }
        }


        gr.renderOneColGL();
        std::cout<< gr.activateProgBody(0, testMath)<<std::endl;
        gr.render_triangle(gr.background1, testMath);

        //imgui part
        imgui_newframe();
        imgui_window();
        imgui_render();

        gr.swapBuffers();

    }

    imgui_shutdown();
return 0;
}
