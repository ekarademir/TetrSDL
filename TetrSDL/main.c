//
//  main.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 23/08/2017.
//  Copyright © 2017 Ertugrul Karademir. See LICENCE for licence info.
//

#include "tetr.h"

int main(int argc, const char *argv[])
{
    // Initialise video and audio subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        logger(LOG_ERR, "SDL Init Error: %s");
    }
    
    createWindow();
    createRenderer();
    
    int quit = 0;
    while (quit == 0)
    {
        int cmd = GAME_NOOP;
        clearScene();
        
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                // Getting the scancode
                int sc = e.key.keysym.scancode;
                
                if (sc == SDL_SCANCODE_Q)
                {
                    logger(LOG_DBG, "Key Press Q - Quit");
                    cmd = GAME_QUIT;
                    quit = 1;
                }
                else if (sc == SDL_SCANCODE_D || sc == SDL_SCANCODE_RIGHT)
                {
                    logger(LOG_DBG, "Key Press D or RIGHT - Move right");
                    cmd = GAME_MOVERIGHT;
                }
                else if (sc == SDL_SCANCODE_A || sc == SDL_SCANCODE_LEFT)
                {
                    logger(LOG_DBG, "Key Press A or LEFT - Move left");
                    cmd = GAME_MOVELEFT;
                }
                else if (sc == SDL_SCANCODE_W || sc == SDL_SCANCODE_UP)
                {
                    logger(LOG_DBG, "Key Press W or UP - Rotate");
                    cmd = GAME_ROTATE;
                }
                else if (sc == SDL_SCANCODE_S || sc == SDL_SCANCODE_DOWN)
                {
                    logger(LOG_DBG, "Key Press S or DOWN - Move down");
                    cmd = GAME_MOVEDOWN;
                }
            }
        }
        
        loop(cmd, SDL_GetTicks());
    }
    
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
        // Set blend mode to alpha blending.
        SDL_SetRenderDrawBlendMode(tetrRend, SDL_BLENDMODE_BLEND);
        logger(LOG_DBG, "Created renderer instance.");
    }
}
