// TEST BED.CPP

#include <windows.h>

#include "common.h"
#include "OpenGL.h"
#include "Win32.h"
#include "DirectInput.h"
#include "DirectSound.h"
#include "FileSpecs.h"
#include "GameLogic.h"
#include "Elements.h"
#include "Game.h"

extern HDC hDisplayContext;
extern Game_t currentGame;

int WINAPI WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpstrCmdArgs , int nShowWin )
{
	MSG msg;

	G_Init( &currentGame );

	int x=0,y=0,z=0,i=0;

	m_boolean complete = m_false;

	Cube_t testCube;
	
	Sys_CreateClass( hInstance );
	Sys_CreateWindow( nShowWin , 500 , 500 );

	OGL_LoadTexture( "content/graphics/GUI/placeholder512.bmp" );			
	OGL_LoadTexture( "content/graphics/GUI/placeholder512.bmp" );
	OGL_LoadTexture( "content/graphics/NeHe.bmp" );
	OGL_LoadTexture( "content/graphics/me.bmp" );

	GL_GenerateCube( &testCube );

	glEnable( GL_TEXTURE_2D );

	DI_InitDirectInput();
	DI_InitKeyboard();
	DI_InitMouse();

//	DS_InitDirectSound();
//	DS_LoadSegment( "content/audio/music/MoonShiner.wav" );

	while( complete == m_false )
	{
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )
		{
			if( msg.message == WM_QUIT )
			{
				complete = m_true;
				break;
			}

			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		else
		{
			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glLoadIdentity();

			glTranslated( 0 , 0 , -2800 );

			glColor3d(1,1,1);
			
			glBindTexture( GL_TEXTURE_2D , 2 );

			
	
			glBegin( GL_QUADS );
			glBegin( GL_TEXTURE_2D );
			glTexCoord2d( 0 , 0 ); glVertex3f( -1000.0f , -1000.0f , 0.0f );
			glTexCoord2d( 1 , 0 ); glVertex3f( 1000.0f , -1000.0f , 0.0f );
			glTexCoord2d( 1 , 1 ); glVertex3f( 1000.0f , 1000.0f , 0.0f );
			glTexCoord2d( 0 , 1 ); glVertex3f( -1000.0f , 1000.0f , 0.0f );
			glEnd();

			G_RunCycle( &currentGame );

			SwapBuffers( hDisplayContext );

		}
	}

	DI_ShutdownDirectInput();
//	DS_ShutdownDirectSound();
	
	return msg.message;
}