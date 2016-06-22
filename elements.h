/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Elements.h
 * $auth : Josiah T. Avery
 * $date : i6/11/06 rewritten on 6/21/06 
 *  
 * -------------------------------------------------------------------------------------
 * structs for in game elements ( visual )
 *
 * 'GAME' level
 *
 ****************************************************************************************/

#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#include "Common.h"
#include "Vector.h"

typedef enum
{ 
	PRI_RED,
    PRI_BLUE,
	PRI_YELLOW, 
	SEC_PURPLE, 
	SEC_GREEN,
	SEC_ORANGE
}Color_t;

typedef struct Cube_t
{
	Color_t frontFace,backFace;
	Vect3_t gridPosition;                // normalized grid coordinates ( z==speed )
	float sizeFactor;	                 // used in drawing ( maintains uniform apperance )

	m_boolean doubleSided,
		           active,
		        processed;

	m_boolean direction[3];

	Cube_t* nextCube;

	void (*Draw)(void);
}*pCube_t;

typedef enum 
{
	AVTR_PLACEHOLDER_01,
	AVTR_MONKEYMAN
}AvatarName_t;

typedef struct Avatar_t
{
	AvatarName_t avatarName;

	Vect3_t avatarPosition;             // normalized avatar space coordinate

	void (*Idle)(void);
	void (*Fetch)(void);
	void (*Throw)(void);
	void (*Draw)(void);

}*pAvatar_t;

void ELM_DrawCubePoly( pCube_t );
void ELM_DrawCubeSprite( pCube_t );

#endif
