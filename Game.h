/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Game.h
 * $auth : Josiah T. Avery
 * $date : i6/14/06
 *  
 * -------------------------------------------------------------------------------------
 * Wrapper routines for functionality just beneath main loop.
 *
 * 'GAME' level
 ****************************************************************************************/	

#ifndef __GAME_H__
#define __GAME_H__

#include "GameDefs.h"
#include "GUI.h"

void G_Init( pGame_t );
void G_ChangeDifficulty( pGame_t , int );
void G_RunCycle( pGame_t );
void G_Shutdown( pGame_t );

#endif