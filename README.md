in mingw64 shell:\
pacman -S mingw64/mingw-w64-x86_64-gcc mingw64/mingw-w64-x86_64-cmake mingw64/mingw-w64-x86_64-gdb mingw64/mingw-w64-x86_64-make
pacman -S mingw64/mingw-w64-x86_64-toolchain\
pacman -S mingw-w64-x86_64-SDL2\
pacman -S mingw-w64-x86_64-SDL2_image\
pacman -S mingw-w64-x86_64-SDL2_ttf\
pacman -S mingw64/mingw-w64-x86_64-ninja

For release just use dlls from sdl's github

// Удалить все проиндексированные файлы\
git rm -r -f --cached .

send event_log to imgui right after sdl_poll_event:\
while( SDL_PollEvent( &event_log ) != 0 )
{\
    ImGui_ImplSDL2_ProcessEvent(&event_log);\
.....






