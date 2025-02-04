#pragma once

//#include "graphic/graphicinit.hxx"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"

void imgui_init(SDL_Window* window, SDL_GLContext* gl_context,SDL_Renderer* rend){

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& im=ImGui::GetIO();
    (void)im;

    //set dart theme
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window,&gl_context);
    ImGui_ImplOpenGL3_Init("#version 300 es");

}
void imgui_newframe(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}
void imgui_window(int&x,int&y, int& triags, std::string& text1, std::string& text2){
    ImGui::Begin("Window");
    ImGui::SliderInt("x",&x,0,900);
    ImGui::SliderInt("y",&y,0,900);
    ImGui::InputInt("triags",&triags);
    ImGui::Text(text1.c_str());
    ImGui::Text(text2.c_str());
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
