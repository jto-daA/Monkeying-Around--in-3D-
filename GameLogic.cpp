/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\FileSpec.h
 * $auth : Josiah T. Avery
 * $date : i6/17/06 rewritten on 6/21/06
 *  
 * -------------------------------------------------------------------------------------
 * Game Logic. Movement checking, scoring etc.
 *
 * 'GAME' level
 *
 ****************************************************************************************/

#include <stdlib.h>

#include "Common.h"
#include "DirectInput.h"
#include "Elements.h"
#include "GameDefs.h"
#include "GameLogic.h"

static Color_t colorArray[ GL_RAND_COLOR_TABLE_SIZE ];

Game_t currentGame; 

/*
** Util routine. Allocates an arbitrarily sized 2D array.
*/
static void* GL_Allocate2DArray( int elementSize , int xRow , int yCol )
{
	 return malloc( elementSize*xRow*yCol );
}
/*
** allocates game grid depending on which level setting is passed.
*/
int GL_AllocateGameGrid( int level )
{
	currentGame.currentSession.currentLevel = level;

	switch( level )
	{
	case LVL_BASIC:
		{ 
			currentGame.currentSession.xArea = LVL_BASIC_HOR_AREA;
			currentGame.currentSession.yArea = LVL_BASIC_VER_AREA;
			GL_Allocate2DArray(  sizeof( m_boolean ) ,  LVL_BASIC_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_BASIC_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_BASIC_HOR_AREA , LVL_BASIC_VER_AREA );
			break;
		}

	case LVL_NORMAL:
		{ 
			currentGame.currentSession.xArea = LVL_NORM_HOR_AREA;
			currentGame.currentSession.yArea = LVL_NORM_VER_AREA;
			GL_Allocate2DArray(  sizeof( m_boolean ) ,  LVL_NORM_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_NORM_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_NORM_HOR_AREA , LVL_BASIC_VER_AREA );
			break;
		}

	case LVL_ADVANCED:
		{
			currentGame.currentSession.xArea = LVL_ADVD_HOR_AREA;
			currentGame.currentSession.yArea = LVL_ADVD_HOR_AREA;
			GL_Allocate2DArray(  sizeof( m_boolean ) ,  LVL_ADVD_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_ADVD_HOR_AREA , LVL_BASIC_VER_AREA );
			GL_Allocate2DArray(  sizeof( Color_t )   ,  LVL_ADVD_HOR_AREA , LVL_BASIC_VER_AREA );
			break;
		}
	}
	
	return currentGame.currentSession.xArea*currentGame.currentSession.yArea*sizeof(m_boolean);
}
/*
** Pre-calc routine; Calculates random color lookup table.
*/
void GL_GenerateRandomColors( void )
{
	for(int c=0; c < GL_RAND_COLOR_TABLE_SIZE;c++ )
	{
		switch( rand()%3 )
		{
		case 0:
			{
				colorArray[ c ] = PRI_RED;
				break;
			}

		case 1: 		{
				colorArray[ c ] = PRI_BLUE;
				break;
			}

		case 2:
			{
				colorArray[ c ] = PRI_YELLOW;
			}
		}
	}
}
/*
** Generates a random cube. Prepares for entry into game grid.
*/
void GL_GenerateCube( pCube_t pCube )
{
	pCube->frontFace = colorArray[ rand()%GL_RAND_COLOR_TABLE_SIZE ];
	pCube->backFace  = colorArray[ rand()%GL_RAND_COLOR_TABLE_SIZE ];

	if( pCube->frontFace == pCube->backFace )
	{
		pCube->doubleSided = m_true;
	}

	else
	{
		pCube->doubleSided = m_false;
	}

	pCube->active = m_true;
	pCube->processed = m_false;

	pCube->gridPosition.x = 25;//currentGame.currentSession.xArea/2; // default position is in middle of play space
	pCube->gridPosition.y = 0;
	pCube->gridPosition.z = 0;

	pCube->direction[0] = pCube->direction[1] = pCube->direction[2] = m_true;

	pCube->Draw = NULL; 
	pCube->nextCube = NULL;
}
/*
** Adds a cube to the current list of cubes.
*/
pCube_t GL_AddCube( pCube_t pCube )
{
	pCube->nextCube = (Cube_t*)malloc(sizeof(Cube_t));

	pCube_t nextCube = pCube->nextCube;

	nextCube->nextCube = NULL;

	return nextCube;
}
/*
** Deletes cube. ( frees memory/removes from game grid )
*/
pCube_t GL_DeleteCube( pCube_t pCube )
{
	free( pCube );

	return pCube;
}
/* 
** Checks which directions are valid for movement ( if any ) Also preforms initial processing. ( prior to scoring )
*/
void GL_CheckFreeDirections( pCube_t pCube , m_boolean gameGrid[50][50] )
{
	int x = (int)pCube->gridPosition.x , 
		y = (int)pCube->gridPosition.y,
		left  = x-1,
		right = x+1,
		down  = y+1,
		maxX  = currentGame.currentSession.xArea,
		maxY  = currentGame.currentSession.yArea;

	// empty spaces all around cube.
	if( !gameGrid[ left ][ y ] && !gameGrid[ right ][ y ] && !gameGrid[ x ][ down ] )
	{
		pCube->direction[ GL_DIRECTION_LEFT ] = 
		pCube->direction[ GL_DIRECTION_RIGHT ] =
		pCube->direction[ GL_DIRECTION_DOWN ] = m_true;

		pCube->processed = m_true;
		return;
	}

	// stuck inbetween a rock... 
	else if( gameGrid[ left ][ y ] && gameGrid[ right ][ y ] && gameGrid[ x ][ down ] )
	{
		pCube->direction[ GL_DIRECTION_LEFT ] = 
		pCube->direction[ GL_DIRECTION_RIGHT ] =
		pCube->direction[ GL_DIRECTION_DOWN ] = m_false;

		pCube->active = m_false;
		pCube->processed = m_true;
		return;
	}

	// cell to the left occupied
	else if( gameGrid[ left ][ y ] )
	{
		pCube->direction[ GL_DIRECTION_LEFT ] = m_false;

		( gameGrid[ right ][ y ] ) ? ( pCube->direction[GL_DIRECTION_RIGHT] = m_false ) : ( pCube->direction[GL_DIRECTION_RIGHT] = m_false );
		( gameGrid[ x ][ down ] ) ? ( pCube->direction[GL_DIRECTION_DOWN] = m_false ) : ( pCube->direction[GL_DIRECTION_DOWN] = m_false );

		if( !pCube->direction[ GL_DIRECTION_RIGHT ] && !pCube->direction[ GL_DIRECTION_DOWN ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		return;
	}

	// cell to the right occupied
	else if( gameGrid[ right ][ y ] )
	{
		pCube->direction[ GL_DIRECTION_RIGHT ] = m_false;

		( gameGrid[ left ][ y ] ) ? ( pCube->direction[GL_DIRECTION_LEFT] = m_false ) : ( pCube->direction[GL_DIRECTION_LEFT] = m_false );
		( gameGrid[ x ][ down ] ) ? ( pCube->direction[GL_DIRECTION_DOWN] = m_false ) : ( pCube->direction[GL_DIRECTION_DOWN] = m_false );

		if( !pCube->direction[ GL_DIRECTION_LEFT ] && !pCube->direction[ GL_DIRECTION_DOWN ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		return;
	}

	// cell below occupied
	else if( gameGrid[ x ][ down ] )
	{
		pCube->direction[ GL_DIRECTION_DOWN ] = m_false;

		( gameGrid[ left ][ y ] ) ? ( pCube->direction[GL_DIRECTION_LEFT] = m_false ) : ( pCube->direction[GL_DIRECTION_LEFT] = m_false );
		( gameGrid[ right ][ y ] ) ? ( pCube->direction[GL_DIRECTION_RIGHT] = m_false ) : ( pCube->direction[GL_DIRECTION_RIGHT] = m_false );

		if( !pCube->direction[ GL_DIRECTION_LEFT ] && !pCube->direction[ GL_DIRECTION_RIGHT ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		return;
	}

	// cube in first column ( left-most edge )
	else if( !x )
	{
		pCube->direction[ GL_DIRECTION_LEFT ] = m_false;

		( gameGrid[ right ][ y ] ) ? ( pCube->direction[GL_DIRECTION_RIGHT] = m_false ) : ( pCube->direction[GL_DIRECTION_RIGHT] = m_false );
		( gameGrid[ x ][ down ] ) ? ( pCube->direction[GL_DIRECTION_DOWN] = m_false ) : ( pCube->direction[GL_DIRECTION_DOWN] = m_false );

		if( !pCube->direction[ GL_DIRECTION_RIGHT ] && !pCube->direction[ GL_DIRECTION_DOWN ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		return;
	}

	// cube in last column ( right-most edge )
	else if( x == maxX )
	{
	pCube->direction[ GL_DIRECTION_RIGHT ] = m_false;

		( gameGrid[ left ][ y ] ) ? ( pCube->direction[GL_DIRECTION_LEFT] = m_false ) : ( pCube->direction[GL_DIRECTION_LEFT] = m_false );
		( gameGrid[ x ][ down ] ) ? ( pCube->direction[GL_DIRECTION_DOWN] = m_false ) : ( pCube->direction[GL_DIRECTION_DOWN] = m_false );

		if( !pCube->direction[ GL_DIRECTION_LEFT ] && !pCube->direction[ GL_DIRECTION_DOWN ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		return;
	}

	// cube in bottom row
	else if( y == maxY )
	{
		pCube->direction[ GL_DIRECTION_DOWN ] = m_false;

		( gameGrid[ left ][ y ] ) ? ( pCube->direction[GL_DIRECTION_LEFT] = m_false ) : ( pCube->direction[GL_DIRECTION_LEFT] = m_false );
		( gameGrid[ right ][ y ] ) ? ( pCube->direction[GL_DIRECTION_RIGHT] = m_false ) : ( pCube->direction[GL_DIRECTION_RIGHT] = m_false );

		if( !pCube->direction[ GL_DIRECTION_LEFT ] && !pCube->direction[ GL_DIRECTION_RIGHT ] )
		{
			pCube->active = m_false;
		}

		pCube->processed = m_true;
		pCube->active = m_false;
		return;
	}

	else
	{
		// Hmmm... very interesting.
	}
}
/*
** Sends cube data to game grid.
*/
void GL_SendCubeToGameGrid( pCube_t pCube )
{
	m_boolean gameGrid[50][50];
	int x = (int)pCube->gridPosition.x, 
		y = (int)pCube->gridPosition.y;

	currentGame.currentSession.gameGrid[ y ][ x ] = m_true;

	currentGame.currentSession.frontGrid[ x ][ y ] = pCube->frontFace;
	currentGame.currentSession.backGrid[ x ][ y ] = pCube->backFace;
}
/* 
** Takes all cubes and sends to game grid for further processing.
*/
void GL_PopulateGameGrid( pCube_t cubeList )
{
	while( cubeList )
	{
		GL_SendCubeToGameGrid( cubeList );
		cubeList = cubeList->nextCube;
	}
}
/**************************************************************************************
** [ EASY MODE ]
** Checks cube at passed coordinate for possible links ( 3+ similiar, adjacent colors )
*/
int GL_CheckForLinks( int xCoord , int yCoord , m_boolean gameGrid[50][50] )
{
	
	return 1;

}
/*************************************************************************************
** [ EASY MODE ]
** Processes game grid to determine which ( if any ) cubes are to be eliminated. Tallys points.
*/
void GL_ProcessGameGrid( m_boolean gameGrid[50][50] )
{
	int points=0,
		maxX=currentGame.currentSession.xArea,
		maxY=currentGame.currentSession.yArea;

	for( int col=0;col<maxY;col++ )
	{
		for( int row=0;row<maxX;row++ )
		{
			points += GL_CheckForLinks( row , col , currentGame.currentSession.gameGrid );
		}
	}

	currentGame.currentSession.currentScore += points;
}
/*
** Checks/Reads keyboard movement; translate into game movement.
** CALLED ONCE PER FRAME.
*/
void GL_UserMoveCube( pCube_t pCube )
{
	if( FAILED ( lpDI_Keyboard->GetDeviceState( sizeof(keyBoard) , (LPVOID)keyBoard) )  )
	{
		MessageBox( NULL , "Unable to poll keyboard." , "DirectInput8::GetDeviceState failed!!!" , MB_ICONERROR );
	}
	
	if( DI_KEYDOWN( DIK_LEFT ) )
	{
		if( pCube->direction[ GL_DIRECTION_LEFT ] )
		{
			pCube->gridPosition.x--;
		}

		else
		{
			// ignore
		}
	}

	else if( DI_KEYDOWN( DIK_RIGHT ) )
	{
		if( pCube->direction[ GL_DIRECTION_RIGHT ] )
		{
			pCube->gridPosition.x++;
		}
		
		else
		{

		}

	}

	else if( DI_KEYDOWN( DIK_DOWN ) )
	{
		if( pCube->direction[ GL_DIRECTION_DOWN ] )
		{
			pCube->gridPosition.y++;     
			// consider changing speed ( z-coord ) here 
		}
			
	}

	else if( DI_KEYDOWN( DIK_SPACE ) ) 
	{
	
	}

	else
	{
		pCube->gridPosition.y += 0.25f;		// ignore superflous input for now, and advance downward.
		
	}
}


	






	


