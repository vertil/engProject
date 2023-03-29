#include "graphic/graphicinit.hxx"
#include "myimgui.h"
#include "iostream"

int main(int argc, char *argv[]){

    object myObj;
    myObj.load_obj_file("../materials/untitled.obj");
    /*graphicInit gr;
    gr.load_texture("../materials/beer.png",0);
    gr.initProgramBackground();

    std::cout<< gr.initProgramBody()<<std::endl;

    imgui_init(gr.window,&gr.gl_context,gr.rend);

    SDL_Event event_log;

    glm::mat4 testMath=glm::translate(glm::mat4(1), glm::vec3(0.0f,0.0f,0.0f));

    camera myCam;
    object myObj;
    myObj.triags.push_back(gr.background1);
    myObj.triags.push_back(gr.background2);


    bool run=true;
    while (run){

        bool change=false;

        while( SDL_PollEvent( &event_log ) != 0 )
        {
            if( event_log.type == SDL_QUIT )
            {
                run = false;
            }
        }

        const uint8_t* state=SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_SPACE]){
            run=false;
        }
        if (state[SDL_SCANCODE_W]){
            myObj.pos *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, myObj.speed, 0.0f));
        }
        if (state[SDL_SCANCODE_A]){
            myObj.pos *= glm::rotate(glm::mat4(1.0f), glm::radians(myObj.angle),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (state[SDL_SCANCODE_D]){
            myObj.pos *= glm::rotate(glm::mat4(1.0f), glm::radians(-myObj.angle),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (state[SDL_SCANCODE_F]){
            change=true;
        }




        int x, y;
        SDL_GetMouseState( &x, &y );




        gr.renderOneColGL();

        gr.activateProgBody(0, myCam.getCamera());
        gr.changeRotMat(myObj.pos);
        if(change){
            gr.changeRotMat(testMath);
        }
        gr.render_triangle(myObj.triags[0], myObj.pos);
        gr.render_triangle(myObj.triags[1], myObj.pos);


        //imgui part
        imgui_newframe();
        imgui_window();
        imgui_render();

        gr.swapBuffers();

    }

    imgui_shutdown();*/
    return 0;
}
