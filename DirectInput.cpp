/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\DirectInput.h
 * $auth : Josiah T. Avery
 * $date : i5/19/06
 *  
 * -------------------------------------------------------------------------------------
 * COM level DirectInput support for devices.
 *
 * 'SYSTEM' level
 *
 ****************************************************************************************/

#include "DirectInput.h"

#include <dx/dinput.h>

extern HINSTANCE mainAppInstance;

extern LPDIRECTINPUT lpDI;
extern LPDIRECTINPUTDEVICE lpDI_Keyboard;
extern LPDIRECTINPUTDEVICE lpDI_Mouse;	
extern HWND mainAppWindow;

/*
** Initilize DirectInput interface.
*/
m_boolean DI_InitDirectInput( void )
{
	if ( FAILED( DirectInput8Create( mainAppInstance , DIRECTINPUT_VERSION,	IID_IDirectInput8, (void**)&lpDI ,NULL ) )  )
	{
		return m_false;
	}

	else
	{
		return m_true;
	}
}
/*
** Init DirectInput Keyboard ineterface.
*/
m_boolean DI_InitKeyboard( void )
{
	if( FAILED(lpDI->CreateDevice( GUID_SysKeyboard , &lpDI_Keyboard , NULL ) ) )
	{
		return m_false;
	}

	if( FAILED( lpDI_Keyboard->SetDataFormat( &c_dfDIKeyboard ) ) ) 
	{
		return m_false;
	}

	//if( FAILED( lpDI_Keyboard->SetCooperativeLevel( mainAppWindow , DISCL_FOREGROUND | DISCL_EXCLUSIVE ) ) )
	if( FAILED( lpDI_Keyboard->SetCooperativeLevel( mainAppWindow , DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return m_false;
	}

	if( FAILED( lpDI_Keyboard->Acquire() ) ) 
	{
		return m_false;
	}

	return m_true;
}
/*
** Init DiretInput Mouse interface.
*/
m_boolean DI_InitMouse( void )
{
	if( FAILED( lpDI->CreateDevice( GUID_SysMouse , &lpDI_Mouse , NULL ) ) )
	{
		return m_false;
	}

	if( FAILED( lpDI_Mouse->SetDataFormat( &c_dfDIMouse ) ) ) 
	{
		return m_false;
	}

	if( FAILED( lpDI_Mouse->SetCooperativeLevel( mainAppWindow , DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ) )
	{
		return m_false;
	}

	if( FAILED( lpDI_Mouse->Acquire() ) )
	{
		return m_false;
	}

	return m_true;
}
/*
** Kills DirectInput interface, releases devices.
*/
void DI_ShutdownDirectInput( void ) 
{
	lpDI_Keyboard->Unacquire();
	lpDI_Keyboard->Release();
	lpDI_Keyboard = NULL;

	lpDI_Mouse->Unacquire();
	lpDI_Mouse->Release();
	lpDI_Mouse = NULL;

	lpDI->Release();
	lpDI = NULL;
}