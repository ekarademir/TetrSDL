//
//  utils.c
//  TetrSDL
//
//  Created by Ertugrul Karademir on 26/08/2017.
//  Copyright © 2017 RotatingWave. All rights reserved.
//
#include "utils.h"


/**
 * Cleans up the instances.
 */
void cleanUp()
{
    if (tetrWin != NULL)
    {
        SDL_DestroyWindow(tetrWin);
        logger(LOG_DBG, "Destroyed window instance.");
    }
    
    if (tetrRend != NULL)
    {
        SDL_DestroyRenderer(tetrRend);
        logger(LOG_DBG, "Destroyed renderer instance.");
    }
    
    if (tetrFont != NULL)
    {
        TTF_CloseFont(tetrFont);
        logger(LOG_DBG, "Destroyed font instance.");
    }
    
    TTF_Quit();
    SDL_Quit();
}


/**
 * Wraps SDL Log Handling Subsystem
 *
 * @param lvl Level of the message
 * @param msg Message to log.
 */
void logger(int lvl, char *msg)
{
    if (lvl == LOG_ERR)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
    }
    else if (lvl == LOG_CRT)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
    }
    else if (lvl == LOG_DBG)
    {
//        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
    }
    else if (lvl == LOG_WRN)
    {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, msg, SDL_GetError());
    }
    else if (lvl == LOG_INF)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, "");
    }
    else
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, msg, "");
    }
}
