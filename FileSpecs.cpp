/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\FileSpecs.cpp
 * $auth : Josiah T. Avery
 * $date : i6/11/06
 *  
 * -------------------------------------------------------------------------------------
 * Routinues to represents/load/and write game file formats.
 *
 * 'GAME' level
 *
 ****************************************************************************************/

#include <stdio.h>
#include <windows.h>

#include "FileSpecs.h"
/*
** Writes config file. 
** [ FILE ID ]
**     |-- [ System ]
**     |        |-- fullscreen?
**     |        |-- xResolution/xDimension
**     |        |-- yResolution/yDimension
**     |        |-- bitDepth
**     |        |-- [ more later...]
**     |        
**     |-- [ Game ]
**     |        |--  version       
**     |        |--  [ more later... ]   
**     |        |--        
*/
int FS_WriteCfgFile( pCfgFile_t pConfig )
{
	FILE* pCfgFile = fopen( "debug_config.mcfg" , "w" );

	int header = FS_MONKEY_CFG_ID;

	fwrite( &header , sizeof(int) , sizeof(int) , pCfgFile );
	fwrite( &pConfig->fullScreen , sizeof(m_boolean) , sizeof(m_boolean) , pCfgFile );
	fwrite( &pConfig->xDimension , sizeof(int) , sizeof(int) , pCfgFile );
	fwrite( &pConfig->yDimension , sizeof(int) , sizeof(int) , pCfgFile );
	fwrite( &pConfig->bitDepth , sizeof(int) , sizeof(int) , pCfgFile );

	FS_MonkeyCompress( pCfgFile );
	fclose( pCfgFile );
	
	return 1;
}
/*
** Writes save file. 
** [ FILE ID ]
**     |-- [ Game ]
**     |        |--  hiScore    
*/
int FS_WriteSaveFile( pSaveFile_t pSave )
{
	FILE* pSaveFile = fopen( "debug_save.msav" , "w" );

	int header = FS_MONKEY_SVE_ID;

	fwrite( &header , sizeof(int) , sizeof(int) , pSaveFile );
	fwrite( &pSave->hiScore , sizeof(int) , sizeof(int) , pSaveFile );

	FS_MonkeyCompress( pSaveFile );
	fclose( pSaveFile );

	return 1;
}
/*
** Opens file to begin logging demo data.
** [ FILE ID ]
**     |-- [ Demo ]
**     |        |--  frameCount
**     |        |--  [ more later... ]
**     |-- [ DemoFrames ] 
**
*/
int FS_OpenDemoFile( char* fileName , pDemoFile_t pDemo )
{
	static FILE* pDemoFile = fopen( fileName , "w" );

	int header = FS_MONKEY_DEM_ID;

	fwrite( &header , sizeof(int) , sizeof(int) , pDemoFile );
	
	return 1;
}
/*
** Records a single frame.
*/
int FS_WriteToDemoFile( FILE *pDemoFile , pDemoFileFrame_t demoFrame )
{
	// add code to write all data required to record a frame.
	return 1;
}
/*
** Closes out demo file.
*/
int FS_CloseDemoFile( FILE* pDemoFile , pDemoFile_t pDemo )
{
	// write any remaining stuff...

	FS_MonkeyCompress( pDemoFile );
	fclose( pDemoFile );

	return 1;
}
/*
** Make sure the desired file type is being loaded.
*/
m_boolean  FS_VerifyFileType( FILE* pf , int fileID )
{
	int header=0;
	
	fread( &header , sizeof(int) , sizeof(int) , pf );

	return ( header == fileID ) ? m_true : m_false;
}
/*
** Reads config file.
*/
int FS_ReadCfgFile( char* fileName , pCfgFile_t pConfig )
{
	FILE *pf = fopen(fileName , "r" );

	if( pf == NULL ) 
	{
		MessageBox( NULL , "Unable to load config file!" , "FS_ReadCfgFile fault." , MB_ICONERROR );
		return -1;
	}

	if( !FS_VerifyFileType( pf , FS_MONKEY_CFG_ID ) ) 
	{
		MessageBox( NULL , "Invalid config file loaded!" , "FS_LoadConfigFile fault" , MB_ICONERROR );
		return -1;
	}

	FS_MonkeyDeCompress( pf );

    fread( &pConfig->fullScreen , sizeof(m_boolean) , sizeof(m_boolean) , pf );
	fread( &pConfig->xDimension , sizeof(int) , sizeof(int) , pf );
	fread( &pConfig->yDimension , sizeof(int) , sizeof(int) , pf );
	fread( &pConfig->bitDepth , sizeof(int) , sizeof(int) , pf );

	fclose( pf );

	return 1;
}
/*
** Reads save file.
*/
int FS_ReadSaveFile( char* fileName , pSaveFile_t pSave )
{
	FILE *pf = fopen(fileName , "r" );

	if( pf == NULL ) 
	{
		MessageBox( NULL , "Unable to load save file!" , "FS_ReadSaveFile fault." , MB_ICONERROR );
		return -1;
	}

	if( !FS_VerifyFileType( pf , FS_MONKEY_SVE_ID ) ) 
	{
		MessageBox( NULL , "Invalid save file loaded!" , "FS_LoadSaveFile fault" , MB_ICONERROR );
		return -1;
	}

	FS_MonkeyDeCompress( pf );

    fread( &pSave->hiScore , sizeof(int) , sizeof(int) , pf );
	
	fclose( pf );

	return 1;
}
/*
** Loads a demo file.
*/
int FS_LoadDemoFromFile( char* fileName, pDemoFile_t pDemo )
{
	FILE *pf = fopen(fileName , "r" );

	if( pf == NULL ) 
	{
		MessageBox( NULL , "Unable to load demo file!" , "FS_ReadDemoFromFile fault." , MB_ICONERROR );
		return -1;
	}

	if( !FS_VerifyFileType( pf , FS_MONKEY_DEM_ID ) ) 
	{
		MessageBox( NULL , "Invalid save file loaded!" , "FS_LoadDemoFromFile fault" , MB_ICONERROR );
		return -1;
	}

	FS_MonkeyDeCompress( pf );

	fread( &pDemo->frameCount , sizeof(int) , sizeof(int) , pf );

	for(int index = 0;index < pDemo->frameCount;index++ )
	{
		// load in frame data
		//pDemo->frameData[ index ]
	}

	fclose( pf );

	return 1;
}
/*
** Data Compression for files
*/
int FS_MonkeyCompress( FILE* pf )
{
	return 1;
}
/*
** Data extraction for files
*/
int FS_MonkeyDeCompress( FILE* pf )
{
	return 1;
}