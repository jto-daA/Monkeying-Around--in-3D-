/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Game.h
 * $auth : Josiah T. Avery
 * $date : i6/24/06
 *  
 * -------------------------------------------------------------------------------------
 * Wrapper routines for functionality just beneath main loop.
 *
 * 'GAME' level
 ****************************************************************************************/	

#include "Game.h"
#include "GameDefs.h"
#include "GameLogic.h"
#include "FileSpecs.h"
#include "GUI.h"

/*
** Sets up everything required to start a game.
*/
void G_Init( pGame_t pGame )
{
	pSession_t currentSession = &pGame->currentSession;

	currentSession->gameMode = GM_BASIC;
	currentSession->difficultyLevel = LVL_BASIC;
	currentSession->activeCubes = 0;
	currentSession->totalCubes  = 0;
	currentSession->currentLevel = 0;

	currentSession->secondsToNextLevel = 0; // change this later
	currentSession->currentTime = 0;
	currentSession->totalPlayingTime = 0;

	currentSession->activeCube = NULL;
	 
	currentSession->currentScore = 0;
	currentSession->highScore = 0;

	currentSession->howUrgent = URG_NORMAL;
	currentSession->paused = m_false;
	currentSession->inProgress = m_true;

	GUI_SetRestraints( LVL_BASIC , &currentSession->gui );

//	currentSession->gameGrid = (m_boolean**)GL_AllocateGameGrid( LVL_BASIC );
	
	GL_GenerateRandomColors();

	GL_AddCube( currentSession->activeCube );
	GL_GenerateCube( currentSession->activeCube );
	GL_AddCube( &currentSession->nextCube );
	GL_GenerateCube( &currentSession->nextCube );
	
	//currentSession->activeCube = &currentSession->nextCube;
	
	
}
/*
** Changes game difficulty. ( via menu??? )
*/
void G_ChangeDifficulty( pGame_t pGame , int difficulty )
{
	pSession_t currentSession = &pGame->currentSession;

	switch( difficulty )
	{
	case LVL_BASIC:
		{
			currentSession->gameMode = GM_BASIC;
			currentSession->difficultyLevel = LVL_BASIC;
			break;
		}

	case LVL_NORMAL:
		{
			currentSession->gameMode = GM_NORMAL;
			currentSession->difficultyLevel = LVL_NORMAL;
			break;
		}

	case LVL_ADVANCED:
		{
			currentSession->gameMode = GM_ADVANCE;
			currentSession->difficultyLevel = LVL_ADVANCED;
			break;
		}

	}
}
/*
** Performs all the actions required to render a single frame
*/
void G_RunCycle( pGame_t pGame )
{
	pSession_t currentSession = &pGame->currentSession;

	if( currentSession->activeCube->active )
	{
		GL_CheckFreeDirections( currentSession->activeCube , currentSession->gameGrid );
		GL_UserMoveCube( currentSession->activeCube );
		GL_SendCubeToGameGrid( currentSession->activeCube );
		GL_ProcessGameGrid( currentSession->gameGrid );
	}

	else
	{
		GL_AddCube( &currentSession->nextCube );
		GL_GenerateCube( &currentSession->nextCube );
	}

	ELM_DrawCubePoly( currentSession->activeCube );
	GUI_Draw( &currentSession->gui );
}
/*
** Shuts down current game ( prior to exit )
*/
void G_Shutdown( pGame_t pGame )
{
	FS_WriteSaveFile( &pGame->saveFile );
}

