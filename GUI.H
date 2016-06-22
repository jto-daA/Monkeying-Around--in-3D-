/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\GUI.h
 * $auth : Josiah T. Avery
 * $date : i6/12/06
 *  
 * -------------------------------------------------------------------------------------
 * Draws in-game/menu/etc, GUIs
 *
 * 'GAME' level
 *
 ****************************************************************************************/	

#ifndef __GUI_H__
#define __GUI_H__

#include "Common.h"
#include "GameDefs.h"

typedef struct GUIParams_t
{ 
	char* fileName;
	int gameLevel;
	int xRestraint,yRestraint,zRestraint;
	unsigned int glTextRef;
}*pGUIParams_t;

void GUI_SetRestraints( int , pGUIParams_t );
void GUI_Draw( pGUIParams_t );

#endif