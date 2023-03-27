#ifndef GRAPHICINIT_H
#define GRAPHICINIT_H

#pragma once
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <cstddef>

//#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
//glm
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
//other
#include "../structs.hxx"
#include "../animation.hxx"
#include "../numbers.hxx"
#include "../lodepng.h"
//
//#include "../myimgui.h"
#include "../glad/glad.h"


static void APIENTRY callback_opengl_debug(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, [[maybe_unused]] const void* userParam);



class graphicInit
{
    //openGL programs
    GLuint        program_id_background = 0;
    GLuint        program_id_body = 0;

    //textures
    GLuint tex_handl [20];

public:
    SDL_Window *window=NULL;
    SDL_Renderer *rend=NULL;
    SDL_GLContext gl_context=NULL;
private:
    //text
    TTF_Font *gFont = NULL;
    std::vector<SDL_Texture*> names;

    //numbers for timer
    numbersText* numbers_=NULL;

    //timer
    bool boolTime=true;
    Uint32 startTime = 0;
    int buffTimerTime=180;
    uint32_t timerTime = 0;
    Uint32 currentTime = 0;
    Uint32 bufferTime = 0;
    Uint32 diffTime = 0;
    Uint32 lastTime=110;
    uint16_t minutes_=0;
    uint16_t seconds_=0;
public:
    //background
    triangle background1;
    triangle background2;

    //test matrix
    glm::mat4 testMath=glm::mat4( 1.0 );
    glm::mat4* modelMatrices=new glm::mat4[1];
    unsigned int testVAO, testVBO, testEBO;

public:
    graphicInit();
    ~graphicInit();
    bool load_texture(std::string_view path,int number);
    void swapBuffers();
    //shaders
    std::string initProgramBackground();
    std::string initProgramBody();
    std::string activateProgBackground(uint8_t text_num);
    std::string activateProgBody(uint8_t text_num, glm::mat4 mat_in);
    //render
    void render_triangle(const triangle& t, glm::mat4& mat_in);
    void renderOneColGL();
    void render_background(int pos);


};

//tests for gl functions
static const char* source_to_strv(GLenum source)
{
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER_COMPILER";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW_SYSTEM";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD_PARTY";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";
        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";
    }
    return "unknown";
}

static const char* type_to_strv(GLenum type)
{
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";
        case GL_DEBUG_TYPE_MARKER:
            return "MARKER";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return "PUSH_GROUP";
        case GL_DEBUG_TYPE_POP_GROUP:
            return "POP_GROUP";
        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";
    }
    return "unknown";
}
static const char* severity_to_strv(GLenum severity)
{
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";
        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";
    }
    return "unknown";
}

static std::array<char, GL_MAX_DEBUG_MESSAGE_LENGTH> local_log_buff;

static void APIENTRY callback_opengl_debug(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, [[maybe_unused]] const void* userParam)
{
    // The memory formessageis owned and managed by the GL, and should onlybe
    // considered valid for the duration of the function call.The behavior of
    // calling any GL or window system function from within thecallback function
    // is undefined and may lead to program termination.Care must also be taken
    // in securing debug callbacks for use with asynchronousdebug output by
    // multi-threaded GL implementations.  Section 18.8 describes thisin further
    // detail.

    auto& buff{ local_log_buff };
    int   num_chars = std::snprintf(
        buff.data(), buff.size(), "%s %s %d %s %.*s\n", source_to_strv(source),
        type_to_strv(type), id, severity_to_strv(severity), length, message);

    if (num_chars > 0)
    {
        // TODO use https://en.cppreference.com/w/cpp/io/basic_osyncstream
        // to fix possible data races
        // now we use GL_DEBUG_OUTPUT_SYNCHRONOUS to garantie call in main
        // thread
        std::cerr.write(buff.data(), num_chars);
    }
}


#endif // GRAPHICINIT_H
