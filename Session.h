/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Session.h
 * $auth : Josiah T. Avery
 * $date : i6/10/06
 *  
 * -------------------------------------------------------------------------------------
 * Representations active game session
 *
 * 'GAME' level
 *
 ****************************************************************************************/	

#ifndef __SESSION_H__
#define __SESSION_H__

#include "Common.h"
#include "Elements.h"
#include "GUI.h"

typedef enum
{
	URG_NORMAL,
    URG_DIRE,
	URG_IMMIMENT_DEATH
}SessionUrgency_t;

typedef enum
{
	GM_BASIC, 
    GM_NORMAL, 
	GM_ADVANCE
}GameMode_t;

typedef struct Session_t
{
	// overall
	GameMode_t gameMode;
	int difficultyLevel,
	    activeCubes,
	    totalCubes,
	    currentLevel;

	// time
	int secondsToNextLevel,
		currentTime,
		totalPlayingTime;	 

	// elements
	Cube_t nextCube;
	pCube_t activeCube;
	Avatar_t activeAvatar;

	// GUI 
	GUIParams_t gui;

	// scoring
	long currentScore,
		   highScore;	 

	// game area
	//m_boolean** gameGrid;
	//Color_t** gridFront,**gridBack;
	m_boolean gameGrid[50][50];
	Color_t frontGrid[50][50], 
		     backGrid[50][50];

	int xArea,yArea;
	
	// etc
	SessionUrgency_t howUrgent;
	m_boolean paused;
	m_boolean inProgress;	
}*pSession_t;

#endif