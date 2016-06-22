/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\Win32.h
 * $auth : Josiah T. Avery
 * $date : i5/3/06
 *  
 * -------------------------------------------------------------------------------------
 * Support for all everything Win32 related.
 *
 * 'SYSTEM' level
 *
 ****************************************************************************************/	

#ifndef __WIN32_H__
#define __WIN32_H__

#include "Common.h"

#include <windows.h>

#define WIN32_LEAN_AND_MEAN

#define SYS_DBG_MSG_HANDLER 0
#define SYS_STD_MSG_HANDLER 1

m_int Sys_CreateClass( HINSTANCE );
m_int Sys_CreateWindow( m_int , m_int , m_int );
LRESULT CALLBACK Sys_MsgHandler( HWND , UINT , WPARAM , LPARAM );


#endif
