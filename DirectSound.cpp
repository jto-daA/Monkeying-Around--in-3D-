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

#include "DirectSound.h"

#include <string.h>
#include <windows.h>

#include <dx/dsound.h>
#include <dx/dmusicc.h>
#include <dx/dmusici.h>

#include <dx/dmerror.h>

extern IDirectMusicPerformance8* dmPerformance;
extern IDirectMusicLoader8 *dmLoader;
extern IDirectMusicSegment8 *dmSegment;

extern HWND mainAppWindow;

extern char* audioPath;

#define INITGUID

/*
** Create DirectSound by using COM level routines.
*/
m_boolean DS_InitDirectSound( void )
{
	if( FAILED( CoInitialize( NULL ) ) )
	{
		MessageBox( mainAppWindow , "DS_InitDirectSound Unable to init COM" , "TERMINAL FAULT" , MB_OK );
		return m_false;
	}

    if( FAILED( CoCreateInstance( CLSID_DirectMusicLoader , NULL , CLSCTX_INPROC , 
		                          IID_IDirectMusicLoader8 , (void**)&dmLoader ) ) ) 
	{
		MessageBox( mainAppWindow , "DS_InitDirectSound DirectMusicLoader failed" , "CRITICAL FAULT" , MB_ICONERROR );
		return m_false; 
	}	
	
	if(FAILED( CoCreateInstance( CLSID_DirectMusicPerformance  , NULL , CLSCTX_INPROC , 
		                         IID_IDirectMusicPerformance8 , (void**)&dmPerformance )  ))
	{    
		MessageBox( mainAppWindow , "DS_InitDirectSound DirectMusicPerformance failed" , "CRITICAL FAULT" , MB_ICONERROR );
		return m_false;
	}

	dmPerformance->InitAudio( NULL , NULL , mainAppWindow , DMUS_APATH_SHARED_STEREOPLUSREVERB , 64 , DMUS_AUDIOF_ALL , NULL );

	DS_SetAudioContentPath( audioPath , m_false );	

	return m_true;
	
}

/*
** Points DirectSound(--MusicSegment ) to the directory where audio clips/samples are held. Dependant of build version. 
*/
m_boolean DS_SetAudioContentPath( char* audioDirectory , m_boolean finalBuild ) 
{
	char path[MAX_PATH];
	WCHAR wpath[MAX_PATH];
	
	if( finalBuild ) 
	{
		audioPath = audioDirectory;
		GetCurrentDirectory( MAX_PATH , path );
       // path = strcat( path , audioDirectory );
	    dmLoader->SetSearchDirectory( GUID_DirectMusicAllTypes , wpath , FALSE );
	}

	else
	{	
		GetCurrentDirectory( MAX_PATH , path );
	
		MultiByteToWideChar( CP_ACP , 0 , path , -1 , wpath , MAX_PATH );			
	    
		if( FAILED ( dmLoader->SetSearchDirectory( GUID_DirectMusicAllTypes , wpath , FALSE ) ) ) 
		{
			MessageBox( NULL , "DS_SetAudioContentPath Unable to read disk path" , "CRITICAL FAULT" , MB_ICONERROR );
			return m_false;
		}
	}

	return m_true;
}

/*
** Loads specified audio file into active Direct Sound segment
*/
m_boolean DS_LoadSegment( char* filename )
{
	WCHAR wAudioFileName[MAX_PATH];

	HRESULT errorMsg=0;
	
	MultiByteToWideChar( CP_ACP , 0 , filename , -1 , wAudioFileName , MAX_PATH );

	if( FAILED( CoCreateInstance( CLSID_DirectMusicSegment, NULL, CLSCTX_INPROC, IID_IDirectMusicSegment8, (void**) &dmSegment ) ) ) 
	{
		MessageBox( mainAppWindow , "DS_LoadSegment : Unable to init COM" , "TERMINAL FAULT" , MB_ICONERROR );
		PostQuitMessage( 0 );
		return m_false;
	}

	if( FAILED( dmLoader->LoadObjectFromFile( CLSID_DirectMusicSegment , IID_IDirectMusicSegment8 , 
								              wAudioFileName , (void**)dmSegment ) ) )
	{
		MessageBox( NULL , "Unable to load audio content file" , "CRITICAL FAULT!!!" , MB_ICONERROR );
		return m_false;
	}

	dmSegment->Download( dmPerformance ); 
	
//	dmPerformance->PlaySegmentEx( dmSegment , NULL , NULL , 0 , 0 , NULL , NULL , NULL );

	return m_true;
}

/*
** Releases allocated interface, closes down COM.
*/ 
void DS_ShutdownDirectSound( void )
{
	dmPerformance->CloseDown();
	dmSegment->Release();
	dmLoader->Release();
	dmPerformance->Release();
	CoUninitialize();
}
