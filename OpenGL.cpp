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

#include "Common.h"
#include "OpenGL.h"

#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glaux.h>

extern HDC hDisplayContext;

extern PIXELFORMATDESCRIPTOR openGLPFD;
extern HGLRC hGLRenderContext;

Texture_t gameTextures[ OGL_DEBUG_TEXTURES ];

/*
** Determines , sets , and returns PFD
*/
m_int OGL_SetPixelFormat( m_int bitDepth )
{
	m_int pixelFormat;

	PIXELFORMATDESCRIPTOR GLPFD = 
				{ sizeof(PIXELFORMATDESCRIPTOR) , 
				  1,
				  PFD_DRAW_TO_WINDOW |
				  PFD_SUPPORT_OPENGL |
				  PFD_DOUBLEBUFFER   ,
				  PFD_TYPE_RGBA,
				  bitDepth, 
				  0 , 0 , 0 , 0 , 0 , 0 ,
				  0 , 
				  0 , 
				  0 ,
				  0 , 0 , 0 , 0 , 
				  16, 
				  0 , 
				  0 , 
				  PFD_MAIN_PLANE , 
				  0 , 
				  0 , 0 , 0 };

	pixelFormat = ChoosePixelFormat( hDisplayContext , &GLPFD );
	SetPixelFormat( hDisplayContext , pixelFormat , &openGLPFD );

	openGLPFD = GLPFD;

	return pixelFormat;
}
/*
** Adds support for GL through Win32
*/
void OGL_CreateGLRenderContext( void )
{
	hGLRenderContext = wglCreateContext( hDisplayContext );
	wglMakeCurrent( hDisplayContext , hGLRenderContext );
}
/*
** Kill GL Rendering Context
*/
void OGL_DestroyGLRenderContext( void )
{
	wglMakeCurrent( hDisplayContext , NULL );
	wglDeleteContext( hGLRenderContext );
}
/*
** Resizes Window; maintains current aspect ratio
*/
void OGL_ResizeGLWindow( m_int xDimension , m_int yDimension )
{
	if( !yDimension )
	{
		yDimension = 1;
	}

	float aspectRatio = (float)xDimension/(float)yDimension;

	glViewport( 0 , 0 , xDimension , yDimension );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	gluPerspective( 45.0f , aspectRatio , OGL_NEAR_PLANE , OGL_FAR_PLANE );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
}
/*
** Setup vital state varibles. 
*/
void OGL_SetInitialStates( void )
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f , 0.0f , 0.0f , 0.5f );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}
/*
** Loads a specified texture into OpenGL
*/
m_boolean OGL_LoadTexture( char* fileName )
{
	static textureCount=0;
	FILE* pf = fopen( fileName , "r" );
	AUX_RGBImageRec* auxImage = NULL;

	if( pf == NULL ) 
	{
		MessageBox( NULL , "Unable to load required texture file." , "OGL_LoadTexture Critical Fault." , MB_ICONERROR );
		return m_false;
	}

	else
	{
		auxImage = auxDIBImageLoad( fileName );
	}

	pTexture_t texture = &gameTextures[ textureCount ];

	texture->fileName = fileName;
	texture->uDimen = auxImage->sizeX;
	texture->vDimen = auxImage->sizeY;
	texture->glTexIndex = textureCount;

	glGenTextures( 1 , &texture->glTexIndex );
	glBindTexture( GL_TEXTURE_2D , textureCount );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );

/*    gluBuild2DMipmaps( GL_TEXTURE_2D,
	                   3,
				       auxImage->sizeX,
				       auxImage->sizeY,	
				       GL_RGB,	
				       GL_UNSIGNED_BYTE,
				       auxImage->data );*/
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, auxImage->sizeX, auxImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, auxImage->data);

	fclose( pf );

	textureCount++;

	return m_true;
}


				  
			
