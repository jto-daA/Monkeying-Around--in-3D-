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

#include <windows.h>
#include <gl/gl.h>

#include "Common.h"
#include "GameDefs.h"
#include "GUI.h"

/*
** determines restraints ( and subsequent rel. coord system ) based on the game level
*/
void GUI_SetRestraints( int level , pGUIParams_t guiParams )
{
	guiParams->gameLevel = level;

	switch( level )
	{
	case LVL_BASIC:
		{
			guiParams->xRestraint = guiParams->yRestraint = 1000;
			guiParams->zRestraint = GUI_PLANE_DEPTH;
			break;
		}

	case LVL_NORMAL:
		{
			guiParams->xRestraint = guiParams->yRestraint = 1000;
			guiParams->zRestraint = GUI_PLANE_DEPTH;
			break;
		}

	case LVL_ADVANCED:
		{
			guiParams->xRestraint = guiParams->yRestraint = 1000;
			guiParams->zRestraint = GUI_PLANE_DEPTH;
			break;
		}
	}
}
/*
** draws GUI 
*/
void GUI_Draw( pGUIParams_t guiParams )
{	
	glPushMatrix();
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		glBindTexture( GL_TEXTURE_2D , guiParams->glTextRef );

		glBegin( GL_TEXTURE_2D );
		glBegin( GL_QUADS );

			glTranslated( 0 , 0 , GUI_PLANE_DEPTH ); // is the really needed? answered 6/29/06 NO!!!

			glTexCoord2d( 0 , 0 ); glVertex3d( -guiParams->xRestraint , guiParams->yRestraint , guiParams->zRestraint );
			glTexCoord2d( 1 , 0 ); glVertex3d( guiParams->xRestraint , guiParams->yRestraint , guiParams->zRestraint );
			glTexCoord2d( 1 , 1 ); glVertex3d( guiParams->xRestraint , -guiParams->yRestraint , guiParams->zRestraint );
			glTexCoord2d( 0 , 1 ); glVertex3d( -guiParams->xRestraint , -guiParams->yRestraint , guiParams->zRestraint );

		glEnd();
	glPopMatrix();	
}