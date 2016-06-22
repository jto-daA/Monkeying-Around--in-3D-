/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Globals.cpp
 * $auth : Josiah T. Avery
 * $date : i5/4/06
 *  
 * -------------------------------------------------------------------------------------
 * Globally used variables.
 *
 * 'GLOBAL' level
 *
 ****************************************************************************************/

#include "Common.h"

#include <windows.h>

#include <gl/gl.h>
#include <dx/dinput.h>
#include <dx/dsound.h>
#include <dx/dmusicc.h>
#include <dx/dmusici.h>

#define __MONKEY_DEBUG__
/* VERSION INFO *************************************************************************/
const char* currentVersion = "Monkeying Around ( in 3D ) version : DEBUG";

/* SYSTEM ********************************************************************************/
WNDCLASSEX mainWndClassEx; 
HINSTANCE mainAppInstance;
HWND mainAppWindow;
PIXELFORMATDESCRIPTOR openGLPFD;
HDC hDisplayContext;

/* SYSTEM-OPENGL *************************************************************************/
HGLRC hGLRenderContext;

/*  SYTEM-DIRECTX ************************************************************************/
/* [ DIRECT INPUT ]                                                                      */
LPDIRECTINPUT lpDI;
LPDIRECTINPUTDEVICE lpDI_Keyboard, lpDI_Mouse;
DIMOUSESTATE diMouseState;
m_byte keyBoard[ 256 ];

/* [ DIRECT-SOUND ]                                                                      */
IDirectMusicPerformance8* dmPerformance = NULL;
IDirectMusicLoader8* dmLoader = NULL;
IDirectMusicSegment8* dmSegment = NULL;

/* CONTENT PATHS *************************************************************************/
char* audioPath = "/Content/Audio/";
char* sfxPath = "/Content/Audio/SFX/";
char* musicPath = "/Content/Audio/MUSIC/";
