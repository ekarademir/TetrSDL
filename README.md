* TetrSDL
This is a kind of Hello World project for learning SDL2 and C.

** Compiling from source
Code depends on two main non-standard C libraries: [SDL2](https://www.libsdl.org/download-2.0.php) 
and [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/).

After you've installed those two libraries, all you need is to compile with gcc. However, directory
to find `SDL_ttf.h` might change from system to system. For instance on Ubuntu, if you've installed 
SDL2 with `apt`, SDL_ttf.h would be inside the SDL2 folder. So you might want to change the
corresponding line in `imports.h`.

