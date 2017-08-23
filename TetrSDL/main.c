//
//  main.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 23/08/2017.
//  Copyright © 2017 Ertugrul Karademir. See LICENCE for licence info.
//

#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, const char * argv[])
{
    // Initialise subsystems
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL Init Error: %s", SDL_GetError());
    }
    
    // insert code here...
    printf("Initialised SDL!\n");
    
    SDL_Quit();
    return 0;
}
