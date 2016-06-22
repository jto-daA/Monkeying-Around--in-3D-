/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Win32.cpp
 * $auth : Josiah T. Avery
 * $date : i5/4/06
 *  
 * -------------------------------------------------------------------------------------
 * Support for all everything Win32 related.
 *
 * 'SYSTEM' level
 *
 ****************************************************************************************/	

#include <windows.h>

#include "resources\resource.h"
#include "Win32.h"
#include "OpenGL.h"

extern WNDCLASSEX mainWndClassEx;
extern HINSTANCE mainAppInstance;
extern HWND mainAppWindow;
extern HDC hDisplayContext;

extern const char* currentVersion;	

/*
** Main Message Handler
*/
LRESULT CALLBACK Sys_MsgHandler( HWND hWnd , UINT msg , WPARAM wParam , LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hDC;
	
	switch( msg )
	{
	case WM_CREATE:
		{
			hDC = GetDC( hWnd );
			hDisplayContext = hDC;

			OGL_SetPixelFormat( 32 );
			OGL_CreateGLRenderContext();
			OGL_SetInitialStates();
			return 1;
		}

	case WM_DESTROY:
		{
			OGL_DestroyGLRenderContext();
			PostQuitMessage( 0 );
			return 1;
		}

	case WM_PAINT:
		{
			hDisplayContext = BeginPaint( hWnd , &ps );
			EndPaint( mainAppWindow , &ps );
			return 0;
		}

	case WM_COMMAND:
		{
			switch( wParam )
			{
			case MAKEINTRESOURCE( ID_FILE_EXIT ):
				{
					PostQuitMessage( 0 );
					break;
				}
			}
		}

	case WM_SIZE:
		{
			OGL_ResizeGLWindow( LOWORD( lParam ) , HIWORD( lParam ) );		    
			break;
		}

	default:
		{
			break;
		}
	}

	return DefWindowProc( hWnd , msg , wParam , lParam );
}

/*
** Create and register main window class.
*/
m_int Sys_CreateClass( HINSTANCE hInstance )
{
	mainAppInstance = hInstance; // pass from WinMain

	mainWndClassEx.cbSize = sizeof( WNDCLASSEX );
	mainWndClassEx.cbClsExtra = 0;
	mainWndClassEx.cbWndExtra = 0;
	mainWndClassEx.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
	mainWndClassEx.hCursor = LoadCursor( NULL , IDC_ARROW );
	mainWndClassEx.hIcon = LoadIcon( NULL , IDI_APPLICATION );
	mainWndClassEx.hIconSm = LoadIcon( NULL , IDI_APPLICATION );
	mainWndClassEx.hInstance = mainAppInstance;
	mainWndClassEx.lpfnWndProc = Sys_MsgHandler;
	mainWndClassEx.lpszClassName = "MonkeyingAroundWindowClass_debug";
	mainWndClassEx.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	mainWndClassEx.lpszMenuName = MAKEINTRESOURCE( IDR_MENU1 );

	return ( RegisterClassEx( &mainWndClassEx ) ) ? ( 1 ) : ( 0 );
}
/*
** Creates Appilication Window
*/
m_int Sys_CreateWindow( m_int showWindow , m_int xSize , m_int ySize )
{

	mainAppWindow = CreateWindowEx( 
								  /*WS_EX_TOPMOST*/ WS_EX_LEFT, 
								  mainWndClassEx.lpszClassName , 
								  currentVersion , 
								  WS_OVERLAPPEDWINDOW | WS_VISIBLE , 
								  CW_USEDEFAULT , CW_USEDEFAULT , 
								  xSize , ySize , 
								  NULL , 
								  NULL , 
								  mainAppInstance , 
								  NULL );

	ShowWindow( mainAppWindow ,  SW_SHOW );
	UpdateWindow( mainAppWindow );
	SetForegroundWindow(  mainAppWindow );
	SetFocus( mainAppWindow );

	return ( mainAppWindow ) ? ( 1 ) : ( 0 );
}



