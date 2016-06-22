/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\GameDefs.h
 * $auth : Josiah T. Avery
 * $date : i6/12/06
 *  
 * -------------------------------------------------------------------------------------
 * Definitons for in game objects/behavior.
 *
 * 'GAME' level
 ****************************************************************************************/	

#ifndef __GAME_DEFS_H__
#define __GAME_DEFS_H__

#include "Common.h"
#include "GUI.h"
#include "Elements.h"
#include "Session.h"
#include "FileSpecs.h"

// difficulty levels
#define LVL_BASIC           0x00000000
#define LVL_NORMAL          0x00000001
#define LVL_ADVANCED        0x00000002

// playfield macros
// GRIDS
#define LVL_BASIC_HOR_AREA          10
#define LVL_BASIC_VER_AREA			50
#define LVL_NORM_HOR_AREA			50
#define LVL_NORM_VER_AREA		   100
#define LVL_ADVD_HOR_AREA			50
#define LVL_ADVD_VER_AREA		   100

// SCALE/DEPTH FACTORS ( for rendering )
#define LVL_BASIC_GUI_DEPTH		     0 
#define LVL_NORMAL_GUI_DEPTH         0
#define LVL_ADVANCED_GUI_DEPTH       0

#define AVATAR_PLANE_DEPTH           1
#define GUI_PLANE_DEPTH             10
#define GAME_PLANE_DEPTH            20


typedef enum
{
	G_TX_GUI_PLACEHOLDER
}GameTextures_t;

typedef struct Game_t
// MASTER STRUCT
{	 
	CfgFile_t   cfgFile;
	SaveFile_t saveFile;
	DemoFile_t demoFile;

	Session_t currentSession;
}*pGame_t;

#endif