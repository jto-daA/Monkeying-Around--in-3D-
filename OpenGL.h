/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\OpenGL.h
 * $auth : Josiah T. Avery
 * $date : i5/8/06
 *  
 * -------------------------------------------------------------------------------------
 * Low level support for OpenGL ( platform interfacing , 'wiggle' stuff )
 *
 * 'SYSTEM' level
 *
 ****************************************************************************************/

#ifndef __OPENGL_H__
#define __OPENGL_H__

#include "Common.h"

#include <gl/glaux.h>
#include <gl/glu.h>
#include <gl/gl.h>

#define OGL_DEBUG_TEXTURES             100
#define OGL_MAX_TEXTURES          
#define OGL_NEAR_PLANE                 0.0f
#define OGL_FAR_PLANE               5000.0f 

typedef struct Texture_t
{
	char* fileName;
	int uDimen,vDimen;
	unsigned int glTexIndex;
}*pTexture_t;

m_int OGL_SetPixelFormat( m_int );
void OGL_CreateGLRenderContext( void );
void OGL_DestroyGLRenderContext( void );
void OGL_ResizeGLWindow( m_int , m_int );
void OGL_SetInitialStates( void );

m_boolean OGL_LoadTexture( char* );

#endif