/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Elements.cpp
 * $auth : Josiah T. Avery
 * $date : i6/23/06 
 *  
 * -------------------------------------------------------------------------------------
 * Rendering of in game entities
 *
 * 'GAME' level
 *
 ****************************************************************************************/

#include <windows.h>
#include <gl/gl.h>

#include "Elements.h"
#include "GameDefs.h"

GLfloat glRed[3] =      { 100.0f , 0.0f , 0.0f };
GLfloat glBlue[3] =     { 0.0f , 0.0f , 100.0f };
GLfloat glYellow[3] =   { 100.0f , 100.0f , 0.0f };
GLfloat glPurple[3] =   { 1.0f , 0.0f , 1.0f };
GLfloat glGreen[3] =    { 0.0f , 1.0f , 0.0f };
GLfloat glOrange[3] =   { 0.0f , 1.0f , 1.0f };
GLfloat glBlack[3] =    { 0.0f , 0.0f , 0.0f };

extern Game_t currentGame;

/*
** Draws a game cube using OpenGL quad rendering Translate realitive to GUI space
*/
void ELM_DrawCubePoly( pCube_t pCube )
{
	GLfloat* color;
	float x = pCube->gridPosition.x, 
		  y = pCube->gridPosition.y,
		  sizeFactor = 100;

	switch( pCube->frontFace )
	{
	case PRI_RED:
		{
			color = glRed;
			break;
		}

	case PRI_BLUE:
		{
			color = glBlue;
			break;
		}

	case PRI_YELLOW:
		{
			color = glYellow;
			break;
		}

	case SEC_PURPLE:
		{
			color = glPurple;
			break;
		}

	case SEC_GREEN:
		{
			color = glGreen;
			break;
		}

		case SEC_ORANGE:
		{
			color = glOrange;
			break;
		}
	}
	
	glPushMatrix();
		glTranslated( 0 , 0 , GAME_PLANE_DEPTH );
		glBegin( GL_QUADS );
			glColor3fv( color );
				glVertex3f( x - sizeFactor , y + sizeFactor , 0 );
				glVertex3f( x + sizeFactor , y + sizeFactor , 0 );
				glVertex3f( x + sizeFactor , y - sizeFactor , 0 );
				glVertex3f( x - sizeFactor , y - sizeFactor , 0 );
		glEnd();

	glPopMatrix();

	if( pCube->nextCube )
	{
	//	ELM_DrawCubePoly( pCube->nextCube );
	}
		

	
	

}
 