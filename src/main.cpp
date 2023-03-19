#include "engine.hxx"

int main(int argc, char *argv[]){    

    engine eng;

   eng.initfTriagBackground();
//init shaders
    std::string error = eng.initProgramBackground();//init opengl programs
    if (!error.empty())
    {
        std::cerr << error << std::endl;
        return EXIT_FAILURE;
    }
    error = eng.initProgramBody();//init opengl programs
        if (!error.empty())
        {
            std::cerr << error << std::endl;
            return EXIT_FAILURE;
        }


    //loading textures
    if (!eng.load_texture("materials/water.png",0)){
        std::cout<<"failed to load start.png"<<std::endl;
        return EXIT_FAILURE;
    }
    if (!eng.load_texture("materials/ship.png",1)){
        std::cout<<"failed to load start.png"<<std::endl;
        return EXIT_FAILURE;
    }
    if (!eng.load_texture("materials/map.png",2)){
        std::cout<<"failed to load start.png"<<std::endl;
        return EXIT_FAILURE;
    }
    if (!eng.load_texture("materials/stone.png",3)){
        std::cout<<"failed to load start.png"<<std::endl;
        return EXIT_FAILURE;
    }

    bool q=true;

    while(q){
        q=eng.event();
        eng.logic();
        eng.renderGame();

    }




return 0;
}
