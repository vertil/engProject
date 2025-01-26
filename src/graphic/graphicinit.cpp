#include "graphicinit.hxx"

graphicInit::graphicInit()
{

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        SDL_Quit();;
    }
    
    std::stringstream serr;
    using namespace std;

    const int init_result = SDL_Init(SDL_INIT_TIMER
                                     |SDL_INIT_VIDEO
                                     |SDL_INIT_EVENTS );
    if (init_result != 0)
    {
        const char* err_message = SDL_GetError();
        serr << "error: failed call SDL_Init: " << err_message << std::endl;

        cout << "fail sdl"<<endl;
    }


    int resulteee = SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);



    window=SDL_CreateWindow("engProj",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            900,
                            900,
                            SDL_WINDOW_OPENGL
                            );

    if(window==NULL){
        std::cout<<"Couldn't create window"<<SDL_GetError()<<std::endl;
        SDL_DestroyWindow(window);
    }

    rend=SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE
                            | SDL_RENDERER_PRESENTVSYNC
                            | SDL_RENDERER_TARGETTEXTURE);
    if(rend==NULL){
        const char* err_message = SDL_GetError();
        serr << "error: failed call createRenderer: " << err_message << std::endl;
        cout<<"failed call create rendered "<<err_message<<endl;
    }

    int gl_major_ver       = 3;//3
    int gl_minor_ver       = 0;//2
    int gl_context_profile = SDL_GL_CONTEXT_PROFILE_ES;

    const char* platform_from_sdl = SDL_GetPlatform();
    std::string_view platform{platform_from_sdl};
    using namespace std::string_view_literals;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, gl_context_profile);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_ver);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_ver);



    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == nullptr)
    {
        const char* err_message = SDL_GetError();
        serr << "error: failed call createcontext: " << err_message << std::endl;
        cout<<"failed call create context "<<err_message<<endl;


        gl_major_ver       = 3;//3
        gl_minor_ver       = 0;//2
        gl_context_profile = SDL_GL_CONTEXT_PROFILE_ES;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, gl_context_profile);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl_major_ver);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl_minor_ver);
        gl_context = SDL_GL_CreateContext(window);
    }
    assert(gl_context != nullptr);

    int result =
            SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &gl_major_ver);
    assert(result == 0);
    result =
            SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &gl_minor_ver);
    assert(result == 0);

    if (gl_major_ver < 3)
    {
        std::clog << "current context opengl version: " << gl_major_ver
                  << '.' << gl_minor_ver << '\n'
                  << "need openg ES version at least: 3.2\n"
                  << std::flush;
        throw std::runtime_error("opengl version too low");
    }

    std::clog << "OpenGl "<< gl_major_ver << '.'<< gl_minor_ver<<'\n';

    if (gladLoadGLES2Loader(SDL_GL_GetProcAddress) == 0)
    {
        std::clog << "error: failed to ialize glad" << std::endl;
    }



    glGenTextures(20, tex_handl); //texture descriptor
    OM_GL_CHECK()
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,32);
    //SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL );

    glDepthMask(GL_TRUE);

    //show and hide sided of vertex to viewer
    glEnable(GL_CULL_FACE);
    //glDepthRangef(0.0,0.001);
    //glFrontFace(GL_CCW); //that is default
    //glCullFace(GL_FRONT);


    SDL_ShowCursor(SDL_ENABLE);

    //1
    background1.v[0].x=-1;
    background1.v[0].y=-1;
    background1.v[0].tex_x=0.0;
    background1.v[0].tex_y=0.0;

    //2
    background1.v[1].x=-1;
    background1.v[1].y=1;
    background1.v[1].tex_x=0.0;
    background1.v[1].tex_y=1.0;

    //3
    background1.v[2].x=1;
    background1.v[2].y=-1;
    background1.v[2].tex_x=1.0;
    background1.v[2].tex_y=0.0;

    //
    background2.v[0].x=-1;
    background2.v[0].y=1;
    background2.v[0].tex_x=0.0;
    background2.v[0].tex_y=1.0;

    //2
    background2.v[1].x=1;
    background2.v[1].y=1;

    background2.v[1].tex_x=1;
    background2.v[1].tex_y=1;
    //3
    background2.v[2].x=1;
    background2.v[2].y=-1;
    background2.v[2].tex_x=1.0;
    background2.v[2].tex_y=0.0;


}

graphicInit::~graphicInit()
{
    //delete numbers_;
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    window=NULL;
    rend=NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool graphicInit::load_texture(std::string path, int number)
{
    SDL_Surface* surf;
    GLenum textureFormat;
    GLint bpp;

    surf = IMG_Load(path.c_str());
    if (surf == nullptr) {
        std::string msg("IMG error: ");
        msg += IMG_GetError();
        throw std::runtime_error(msg.c_str());
    }
    switch (surf->format->BytesPerPixel)
    {
        case 4:
            if (surf->format->Rmask == 0x000000ff)
                bpp = GL_RGBA;
            else
                bpp = GL_RGBA;
            break;
        case 3:
            if (surf->format->Rmask == 0x000000ff)
                bpp = GL_RGB;
            else
                bpp = GL_RGB;
            break;
        default:
            std::cout << "Error, image is not truecolor." << std::endl;

    }

    //mirror
    SDL_LockSurface(surf);
    int pitch = surf->pitch; // row size
    char* temp = new char[pitch]; // intermediate buffer
    char* pixels = (char*) surf->pixels;

    for(int i = 0; i < surf->h / 2; ++i) {
        // get pointers to the two rows to swap
        char* row1 = pixels + i * pitch;
        char* row2 = pixels + (surf->h - i - 1) * pitch;

        // swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }

    delete[] temp;

    SDL_UnlockSurface(surf);
    //end mirror

    glActiveTexture(GL_TEXTURE0+number);
    glBindTexture(GL_TEXTURE_2D,tex_handl[number]);


    if(surf == NULL || surf == nullptr )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );

    }else{
        GLint mipmap_level = 0;
        GLint border       = 0;

        glTexImage2D(GL_TEXTURE_2D, // type of texture
                     mipmap_level,  //
                     bpp,       //color format in
                     surf->w,//texture weight
                     surf->h,//texture height
                     border,
                     bpp,       // color format out(color what we want to get in opengl)
                     GL_UNSIGNED_BYTE, // Specifies the data type of the texel data
                     surf->pixels);

        OM_GL_CHECK()

    }
    SDL_FreeSurface(surf );


    //making correct color of zoomed texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    OM_GL_CHECK()
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    OM_GL_CHECK()



    //SDL_FreeSurface( surf );

    return true;
}

void graphicInit::swapBuffers()
{
    SDL_GL_SwapWindow(window);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

std::string graphicInit::initProgramBackground()
{
    std::stringstream serr;
    //vertex
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    OM_GL_CHECK()
    std::string_view vertex_shader_src = R"(
                                             #version 300 es

                                             layout(location=0)in vec4 vPosition;
                                             in vec2 a_tex_coord;

                                             out vec2 v_tex_coord;

                                             void main()
                                             {
                                                 v_tex_coord=a_tex_coord;
                                                 gl_Position=vPosition;//vertex pos
                                             }
                                        )";
    const char* source            = vertex_shader_src.data();
    glShaderSource(vert_shader, 1, &source, nullptr);
    OM_GL_CHECK()

    glCompileShader(vert_shader);
    OM_GL_CHECK()

    GLint compiled_status = 0;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &compiled_status);
    OM_GL_CHECK()

    if (compiled_status == 0)
    {
        GLint info_len = 0;
        glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &info_len);
        OM_GL_CHECK()

        std::vector<char> info_chars(static_cast<size_t>(info_len));
        glGetShaderInfoLog(vert_shader, info_len, nullptr, info_chars.data());
        OM_GL_CHECK()

        glDeleteShader(vert_shader);
        OM_GL_CHECK()

        std::string shader_type_name = "vertex";
        serr << "Error compiling shader(vertex)\n"
             << vertex_shader_src << "\n"
             << info_chars.data();

        return serr.str();
    }

    //fragment
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    OM_GL_CHECK()
            std::string_view fragment_shader_src = R"(
                                               #version 300 es
                                               precision mediump float;

                                               in vec2 v_tex_coord;

                                               uniform sampler2D s_texture;

                                               out vec4 frag_color;
                                               void main()
                                               {
                                                 frag_color = texture(s_texture, v_tex_coord);
                                               }
                          )";

    source = fragment_shader_src.data();
    glShaderSource(fragment_shader, 1, &source, nullptr);
    OM_GL_CHECK()

    glCompileShader(fragment_shader);
    OM_GL_CHECK()

    compiled_status = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_status);
    OM_GL_CHECK()

    if (compiled_status == 0)
    {
        GLint info_len = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_len);
        OM_GL_CHECK()

        std::vector<char> info_chars(static_cast<size_t>(info_len));

        glGetShaderInfoLog(fragment_shader, info_len, nullptr, info_chars.data());
        OM_GL_CHECK()

        glDeleteShader(fragment_shader);
        OM_GL_CHECK()

        serr << "Error compiling shader(fragment)\n"
             << vertex_shader_src << "\n"
             << info_chars.data();

        return serr.str();
    }

    //union shaders in one program
    program_id_background = glCreateProgram();
    OM_GL_CHECK()

    if (0 == program_id_background)
    {
        serr << "failed to create gl program";
        return serr.str();
    }

    glAttachShader(program_id_background, vert_shader);
    OM_GL_CHECK()

    glAttachShader(program_id_background, fragment_shader);
    OM_GL_CHECK()

    // bind attribute location
    glBindAttribLocation(program_id_background, 0, "a_position");
    OM_GL_CHECK()

    // link program after binding attribute locations
    glLinkProgram(program_id_background);
    OM_GL_CHECK()

        // Check the link status
    GLint linked_status = 0;
    glGetProgramiv(program_id_background, GL_LINK_STATUS, &linked_status);
    OM_GL_CHECK()

    if (linked_status == 0)
    {
        GLint infoLen = 0;
        glGetProgramiv(program_id_background, GL_INFO_LOG_LENGTH, &infoLen);
        OM_GL_CHECK()

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetProgramInfoLog(program_id_background, infoLen, nullptr, infoLog.data());
        OM_GL_CHECK()

        serr << "Error linking program:\n" << infoLog.data();
        glDeleteProgram(program_id_background);
        OM_GL_CHECK()

        return serr.str();
    }
    return "";
}

std::string graphicInit::initProgramBody()
{
    std::stringstream serr;

    //vertex
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    OM_GL_CHECK()

    std::string_view vertex_shader_src = R"(
                                             #version 300 es

                                             uniform mat4 view;
                                             uniform mat4 worldPos;
                                             uniform mat4 Proj;



                                             layout (location = 0) in vec3 vPosition;
                                             layout (location = 1) in vec2 a_tex_coord;
                                             //layout (location = 2) in mat4 rot_matrix;


                                             out vec2 v_tex_coord;

                                             void main()
                                             {
                                                 v_tex_coord=a_tex_coord;
                                                 gl_Position=Proj*view*worldPos*vec4(vPosition,1.0f);//vertex pos

                                             }
                                        )";
    const char* source            = vertex_shader_src.data();
    glShaderSource(vert_shader, 1, &source, nullptr);
    OM_GL_CHECK()

    glCompileShader(vert_shader);
    OM_GL_CHECK()

    GLint compiled_status = 0;
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &compiled_status);
    OM_GL_CHECK()

    if (compiled_status == 0)
    {
        GLint info_len = 0;
        glGetShaderiv(vert_shader, GL_INFO_LOG_LENGTH, &info_len);
        OM_GL_CHECK()

        std::vector<char> info_chars(static_cast<size_t>(info_len));
        glGetShaderInfoLog(vert_shader, info_len, nullptr, info_chars.data());
        OM_GL_CHECK()

        glDeleteShader(vert_shader);
        OM_GL_CHECK()

        std::string shader_type_name = "vertex";

        serr << "Error compiling shader(vertex)\n"
             << vertex_shader_src << "\n"
             << info_chars.data();
        return serr.str();
    }

    //fragment
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    OM_GL_CHECK()

    std::string_view fragment_shader_src = R"(
                                               #version 300 es
                                               precision mediump float;

                                               in vec2 v_tex_coord;

                                               uniform sampler2D s_texture;

                                               out vec4 frag_color;
                                               void main()
                                               {
                                                 frag_color = texture(s_texture, v_tex_coord);
                                               }
    )";

    source = fragment_shader_src.data();
    glShaderSource(fragment_shader, 1, &source, nullptr);
    OM_GL_CHECK()

    glCompileShader(fragment_shader);
    OM_GL_CHECK()

    compiled_status = 0;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compiled_status);
    OM_GL_CHECK()

    if (compiled_status == 0)
    {
        GLint info_len = 0;
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &info_len);
        OM_GL_CHECK()

        std::vector<char> info_chars(static_cast<size_t>(info_len));
        glGetShaderInfoLog(fragment_shader, info_len, nullptr, info_chars.data());
        OM_GL_CHECK()

        glDeleteShader(fragment_shader);
        OM_GL_CHECK()

        serr << "Error compiling shader(fragment)\n"
             << vertex_shader_src << "\n"
             << info_chars.data();
        return serr.str();
    }

    //union shaders in one program
    program_id_body = glCreateProgram();
    OM_GL_CHECK()

    if (0 == program_id_body)
    {
        serr << "failed to create gl program";
        return serr.str();
    }

    glAttachShader(program_id_body, vert_shader);
    OM_GL_CHECK()

    glAttachShader(program_id_body, fragment_shader);
    OM_GL_CHECK()

    // bind attribute location
    glBindAttribLocation(program_id_body, 0, "a_position");
    OM_GL_CHECK()

    // link program after binding attribute locations
    glLinkProgram(program_id_body);
    OM_GL_CHECK()

    // Check the link status
    GLint linked_status = 0;
    glGetProgramiv(program_id_body, GL_LINK_STATUS, &linked_status);
    OM_GL_CHECK()

    if (linked_status == 0)
    {
        GLint infoLen = 0;
        glGetProgramiv(program_id_body, GL_INFO_LOG_LENGTH, &infoLen);
        OM_GL_CHECK()

        std::vector<char> infoLog(static_cast<size_t>(infoLen));
        glGetProgramInfoLog(program_id_body, infoLen, nullptr, infoLog.data());
        OM_GL_CHECK()

        serr << "Error linking program:\n" << infoLog.data();
        glDeleteProgram(program_id_body);
        OM_GL_CHECK()

        return serr.str();
    }



    return "";
}

std::string graphicInit::activateProgBackground(uint8_t text_num)
{

    glUseProgram(program_id_background);
    OM_GL_CHECK()

    int location = glGetUniformLocation(program_id_background, "s_texture");
    OM_GL_CHECK()

    assert(-1 != location);
    int texture_unit = text_num;//number of texture
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    OM_GL_CHECK()


    glUniform1i(location, 0 + texture_unit);
    OM_GL_CHECK()

    glEnable(GL_BLEND);
    OM_GL_CHECK()

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    OM_GL_CHECK()

    return "";
}

std::string graphicInit::activateProgBody(uint8_t text_num, glm::mat4 mat_in)
{

    // turn on rendering with just created shader program
    glUseProgram(program_id_body);
    OM_GL_CHECK()

    //---------ADDING UNIFORM MATRIX
    GLuint mem=glGetUniformLocation(program_id_body,"view");
    OM_GL_CHECK()

    glUniformMatrix4fv(mem,1,GL_FALSE,glm::value_ptr(mat_in));
    OM_GL_CHECK()
    //------------------------


    int location = glGetUniformLocation(program_id_body, "s_texture");
    OM_GL_CHECK()

    assert(-1 != location);
    int texture_unit = text_num;//number of texture
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    OM_GL_CHECK()

    glUniform1i(location, 0 + texture_unit);
    OM_GL_CHECK()

    glEnable(GL_BLEND);
    OM_GL_CHECK()

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    OM_GL_CHECK()



     return "";
}

std::string graphicInit::changeRotMat(glm::mat4 mat_in) {

    GLuint mem=glGetUniformLocation(program_id_body,"worldPos");
    OM_GL_CHECK()

    glUniformMatrix4fv(mem,1,GL_FALSE,glm::value_ptr(mat_in));
    OM_GL_CHECK()

    return "";
}

std::string graphicInit::changeProj(glm::mat4 mat_in){

    GLuint mem=glGetUniformLocation(program_id_body,"Proj");
    OM_GL_CHECK()

    glUniformMatrix4fv(mem,1,GL_FALSE,glm::value_ptr(mat_in));
    OM_GL_CHECK()

    return "";
}

void graphicInit::render_triangle(const triangle &t, glm::mat4& mat_in)
{
    //vertexs
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          &t.v[0].x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(0);
    OM_GL_CHECK()

    //textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          &t.v[0].tex_x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(1);
    OM_GL_CHECK()

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[0]);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[1]);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[2]);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[3]);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    OM_GL_CHECK()
}
void graphicInit::render_triangle3d(const triangle3d &t, glm::mat4& mat_in)
{


    //vertexs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3d),
                          &t.v[0].x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(0);
    OM_GL_CHECK()

    //textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3d),
                          &t.v[0].tex_x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(1);
    OM_GL_CHECK()


    glDrawArrays(GL_TRIANGLES, 0, 3);
    OM_GL_CHECK()
}

void graphicInit::render_triangle3dVAO(const basicObject &t)
{

    glBindVertexArray(t.VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(t.pointsAll.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void graphicInit::render_line_triangle(const triangle& t, glm::mat4& mat_in){
    //vertexs
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          &t.v[0].x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(0);
    OM_GL_CHECK()

    //textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
                          &t.v[0].tex_x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(1);
    OM_GL_CHECK()

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[0]);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[1]);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[2]);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[3]);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glDrawArrays(GL_LINE_LOOP, 0, 3);
    OM_GL_CHECK()
}

void graphicInit::render_line_triangle3d(const triangle3d& t, glm::mat4& mat_in){
    //vertexs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex3d),
                          &t.v[0].x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(0);
    OM_GL_CHECK()

    //textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex3d),
                          &t.v[0].tex_x);
    OM_GL_CHECK()

    glEnableVertexAttribArray(1);
    OM_GL_CHECK()

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[0]);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[1]);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[2]);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)&mat_in[3]);

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glDrawArrays(GL_LINE_LOOP, 0, 3);
    OM_GL_CHECK()
}

void graphicInit::renderOneColGL()
{
    glClearColor(0.357,0.950,0.665,0.0f);
    OM_GL_CHECK()

    glClear(GL_COLOR_BUFFER_BIT);
    OM_GL_CHECK()
}

void graphicInit::render_background(int pos, glm::mat4& mat_in )
{
    //background
    activateProgBackground(pos);
    glm::mat4 buff = glm::mat4( 1.0 );
    render_triangle(background1, mat_in);
    render_triangle(background2, mat_in);
}









