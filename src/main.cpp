#include "graphic/graphicinit.hxx"
#include "myimgui.h"
#include "iostream"
#include "objects/basicCamera.h"

#include "objects/basicPerson.h"





int main(int argc, char *argv[]){


    graphicInit gr;
    basicObject myObj;
    basicPerson myPers=basicPerson(&myObj);
    myObj.load_obj_file("../materials/cat_triag.obj");
    gr.load_texture("../materials/beerold.png",0);
    gr.load_texture("../materials/Cat_diffuse.jpg",1);
    gr.load_texture("../materials/black.png",2);

    gr.initProgramBackground();

    std::cout<< gr.initProgramBody()<<std::endl;

    GLboolean last_enable_depth_test1 = glIsEnabled(GL_DEPTH_TEST);


    imgui_init(gr.window,&gr.gl_context,gr.rend);

    GLboolean last_enable_depth_test2 = glIsEnabled(GL_DEPTH_TEST);

    GLboolean def = GL_TRUE;

    SDL_Event event_log;



    basicCamera myCam;

    int triags=0;

    bool run=true;
    bool change=false;



    std::string info= myObj.triags[0].getInfo();
    while (run){

        while( SDL_PollEvent( &event_log ) != 0 )
        {
            ImGui_ImplSDL2_ProcessEvent(&event_log);

            if( event_log.type == SDL_QUIT )
            {
                run = false;
            }
        }


        const uint8_t* state=SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_SPACE]){
            std::cout<<"dfa";
            run=false;
        }
//        if (state[SDL_SCANCODE_W]){
//            myObj.pos *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, myObj.speed, 0.0f));
//        }
        if (state[SDL_SCANCODE_A]){
            myPers.pos *= glm::rotate(glm::mat4(1.0f), glm::radians(myObj.angle),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
        }
        if (state[SDL_SCANCODE_D]){
            myPers.pos *= glm::rotate(glm::mat4(1.0f), glm::radians(-myObj.angle),
                                     glm::vec3(0.0f, 0.0f, 1.0f));
        }
//        if (state[SDL_SCANCODE_F]){
//            change= !change;
//            for (int i=0;i<100000;){
//                i++;
//            }
//        }
        if (state[SDL_SCANCODE_E]){
            myCam.forward();
        }
        if (state[SDL_SCANCODE_Q]){
            myCam.backward();

        }

//        if (state[SDL_SCANCODE_UP]){
//            glm::mat4 buff=glm::mat4(1.0f);
//            myObj.pos *= glm::rotate(buff, glm::radians(-2.0f), glm::vec3(1.0, 0.0, 0.0));
//        }
//        if (state[SDL_SCANCODE_DOWN]){
//            glm::mat4 buff=glm::mat4(1.0f);
//            myObj.pos *= glm::rotate(buff, glm::radians(2.0f), glm::vec3(1.0, 0.0, 0.0));
//
//        }
        if (state[SDL_SCANCODE_LEFT]){
            glm::mat4 buff=glm::mat4(1.0f);
            myPers.pos *= glm::rotate(buff, glm::radians(-2.0f), glm::vec3(0.0, 1.0, 0.0));
        }
        if (state[SDL_SCANCODE_RIGHT]){
            glm::mat4 buff=glm::mat4(1.0f);
            myPers.pos *= glm::rotate(buff, glm::radians(2.0f), glm::vec3(0.0, 1.0, 0.0));

        }



        int x, y;
        SDL_GetMouseState( &x, &y );



        gr.renderOneColGL();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        gr.activateProgBody(1 ,myCam.getCamera());

        gr.changeRotMat(myPers.pos);

        glm::mat4 projection;
        projection = glm::perspective(45.0f,1.0f, 0.1f, 10000.0f);
        gr.changeProj(projection);


        gr.render_triangle3dVAO(myObj);




        //imgui part
        imgui_newframe();
        std::string text1=glm::to_string(myPers.pos);
        std::string text2=glm::to_string(myCam.getCamera());
        imgui_window(x,y, triags,text1,text2);
        imgui_render();

        gr.swapBuffers();

    }

    imgui_shutdown();
    return 0;
}
