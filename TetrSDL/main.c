//
//  main.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 23/08/2017.
//  Copyright © 2017 See LICENCE for licence info.
//

#include "tetr.h"

int main(int argc, const char *argv[])
{
    // Initialise video and audio subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        logger(LOG_ERR, "SDL Init Error: %s");
    }
    
    // Initialise TTF
    if (TTF_Init() == -1)
    {
        logger(LOG_ERR, "TTF_Init Error %s");
    }
    
    createWindow();
    createRenderer();
    loadFont();
    
    setup();
    
    int feedback = GAME_NOOP;
    int cmd = GAME_NOOP;
    
    SDL_Event e;
    
    while (feedback != GAME_QUIT)
    {
        clearScene();
        
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
                else if (sc == SDL_SCANCODE_N)
                {
                    logger(LOG_DBG, "Key Press N - New game");
                    cmd = GAME_NEWGAME;
                }
                else if (sc == SDL_SCANCODE_P || sc == SDL_SCANCODE_ESCAPE)
                {
                    logger(LOG_DBG, "Key Press P - Pause");
                    cmd = GAME_PAUSE;
                }
            }
        }
        
        feedback = loop(cmd, SDL_GetTicks());
        SDL_RenderPresent(tetrRend);
        cmd = GAME_NOOP;
    }
    
    cleanUp();
    exit(EXIT_SUCCESS);
}


/**
 * Wraps SDL_CreateWindow
 */
int createWindow()
{
    tetrWin = SDL_CreateWindow("TETR",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   TETR_SCREEN_WIDTH, TETR_SCREEN_HEIGHT,
                                   SDL_WINDOW_OPENGL);
  
    if (tetrWin == NULL)
    {
        logger(LOG_ERR, "Error creating window: %s");
        cleanUp();
        exit(EXIT_FAILURE);
    }
    else
    {
        logger(LOG_DBG, "Created window instance.");
        return 0;
    }

}


/**
 * Wraps SDL_CreateRenderer
 */
int createRenderer()
{
    tetrRend = SDL_CreateRenderer(tetrWin, -1, SDL_RENDERER_PRESENTVSYNC|SDL_RENDERER_ACCELERATED);
  
    if (tetrRend == NULL)
    {
        logger(LOG_ERR, "Error creating renderer: %s");
        cleanUp();
        exit(EXIT_FAILURE);
    }
    else
    {
        // Set blend mode to alpha blending.
        SDL_SetRenderDrawBlendMode(tetrRend, SDL_BLENDMODE_BLEND);
        logger(LOG_DBG, "Created renderer instance.");
        return 0;
    }
}


int loadFont()
{
    // http://www.1001fonts.com/ethnocentric-font.html
    // Made by Raymond Larabie
    // http://typodermicfonts.com/
    
    tetrFont = TTF_OpenFont("/assets/ethocentric.ttf", 25);
    if (!tetrFont)
    {
        logger(LOG_ERR, "Unable to load the font %s");
        cleanUp();
        exit(EXIT_FAILURE);
    } else {
        logger(LOG_DBG, "Loaded game font.");
        return 0;
    }
}
