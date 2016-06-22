/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\DirectSound.h
 * $auth : Josiah T. Avery
 * $date : i5/29/06
 *  
 * -------------------------------------------------------------------------------------
 * COM level DirectSound initilization support.
 *
 * 'SYSTEM' level
 *
 ****************************************************************************************/

#ifndef __DIRECT_SOUND_H__
#define __DIRECT_SOUND_H__

#include "Common.h"

m_boolean DS_InitDirectSound( void );
m_boolean DS_SetAudioContentPath( char* , m_boolean );
m_boolean DS_LoadSegment( char* );
void DS_ShutdownDirectSound( void );

#endif
