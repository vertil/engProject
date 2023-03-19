#pragma once


#include "engine.hxx"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
//#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"

void imgui_init(SDL_Window* window, SDL_GLContext* gl_context,SDL_Renderer* rend){

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& im=ImGui::GetIO();
    (void)im;

    //set dart theme
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window,&gl_context);
    ImGui_ImplOpenGL3_Init("#version 300 es");

//    im.Fonts->AddFontFromFileTTF("multimarkdown_NotoSans-Bold.ttf", 32,
//                       NULL,ImGui::GetIO().Fonts->GetGlyphRangesCyrillic()
//                       );
        //im.ConfigFlags |=ImGuiConfigFlags_None;//ImGuiConfigFlags_NavEnableKeyboard;
    //im.ConfigFlags |=ImGuiConfigFlags_NavEnableKeyboard;


    //ImGui::GetIO().Fonts->GetGlyphRangesCyrillic();
}
void imgui_newframe(SDL_Window* window){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();
}
void imgui_window(int& angle,float& waterPower,bool& crash){
    ImGui::Begin("Window");

    ImGui::SliderInt("angle",&angle,0,360);
    ImGui::SliderFloat("waterPower", &waterPower, 0.0f, 0.01f);
    ImGui::Checkbox("crash",&crash);

    ImGui::End();

}
void imgui_render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


}
void imgui_shutdown(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}
