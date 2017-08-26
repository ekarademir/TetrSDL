//
//  main.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 23/08/2017.
//  Copyright © 2017 Ertugrul Karademir. See LICENCE for licence info.
//

#include "tetr.h"
#include "utils.h"
#include "scene.h"

int main(int argc, const char *argv[])
{
    // Initialise video and audio subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        logger(LOG_ERR, "SDL Init Error: %s");
    }
    
    createWindow();
    createRenderer();
    
    SDL_Color clr = {.r=255, .g=0, .b=0, .a=255};
    
    fillRect(0, 0, 100, 100, &clr);
    
    SDL_RenderPresent(tetrRend);
    
    SDL_Delay(3000);
    
    cleanUp();
    exit(EXIT_SUCCESS);
}


/**
 * Wraps SDL_CreateWindow
 */
void createWindow()
{
    tetrWin = SDL_CreateWindow("TETR",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   TETR_SCREEN_WIDTH, TETR_SCREEN_HEIGHT,
                                   SDL_WINDOW_OPENGL);
  
    if (tetrWin == NULL)
    {
        logger(LOG_ERR, "Error creating window: %s");
        cleanUp();
    }
    else
    {
        logger(LOG_DBG, "Created window instance.");
    }

}


/**
 * Wraps SDL_CreateRenderer
 */
void createRenderer()
{
    tetrRend = SDL_CreateRenderer(tetrWin, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
  
    if (tetrRend == NULL)
    {
        logger(LOG_ERR, "Error creating renderer: %s");
        cleanUp();
    }
    else
    {
        logger(LOG_DBG, "Created renderer instance.");
    }
}
