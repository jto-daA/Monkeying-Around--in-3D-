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

#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include "Common.h"
#include "Elements.h"

#define GL_RAND_COLOR_TABLE_SIZE                         500

#define GL_DIRECTION_LEFT                                  0
#define GL_DIRECTION_RIGHT                                 1
#define GL_DIRECTION_DOWN                                  2 

#define GL_POINTS_PRI_COLOR                              500
#define GL_POINTS_SEC_COLOR                              750

static void* GL_Allocate2DArray( int , int , int );
int GL_AllocateGameGrid( int );
void GL_GenerateRandomColors( void );
void GL_GenerateCube( pCube_t );
pCube_t GL_AddCube( pCube_t );
pCube_t GL_DeleteCube( pCube_t );
void GL_CheckFreeDirections( pCube_t , m_boolean[50][50] );
void GL_SendCubeToGameGrid( pCube_t );
void GL_PopulateGameGrid( pCube_t);
void GL_ProcessGameGrid( m_boolean[50][50] );
int GL_CheckForLinks( int , int , m_boolean[50][50] );

void GL_UserMoveCube( pCube_t );


#endif
