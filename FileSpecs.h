/***************************************************************************************
 *                     Monkeying Around ( in 3D )                 
 *                     --------------------------
 * $path : E:\Program Files\Microsoft Visual Studio\MyProjects\Monkeying Around\FileSpec.h
 * $auth : Josiah T. Avery
 * $date : i6/11/06
 *  
 * -------------------------------------------------------------------------------------
 * Routinues to represents/load/and write game file formats.
 *
 * 'GAME' level
 *
 ****************************************************************************************/

#ifndef __FILE_SPEC_H__
#define __FILE_SPEC_H__

#include <stdio.h>

#include "Common.h"

#define FS_MONKEY_CFG_ID                                                       0xAFF0CF01
#define FS_MONKEY_SVE_ID													   0xBEE0C001	
#define FS_MONKEY_DEM_ID                                                       0x00DE003D

typedef struct CfgFile_t
{
	m_boolean fullScreen;
	int xDimension,yDimension;
	int bitDepth;
	int version;
}*pCfgFile_t;

typedef struct SaveFile_t
{
	long hiScore; 

}*pSaveFile_t;

typedef struct DemoFileFrame_t
{

}*pDemoFileFrame_t;

typedef struct DemoFile_t
{
	int frameCount;
	pDemoFileFrame_t frameData;
}*pDemoFile_t;

int FS_WriteCfgFile( pCfgFile_t );
int FS_WriteSaveFile( pSaveFile_t );
int FS_OpenDemoFile( char* , pDemoFile_t );
int FS_WriteToDemoFile( FILE* , pDemoFileFrame_t );
int FS_CloseDemoFile( FILE* , pDemoFile_t );

m_boolean FS_VerifyFileType( FILE* , int );

int FS_ReadCfgFile( char* , pCfgFile_t);
int FS_ReadSaveFile( char* , pSaveFile_t);
int FS_LoadDemoFile( char* , pDemoFile_t);

// Optional 
int FS_MonkeyCompress( FILE* );
int FS_MonkeyDeCompress( FILE* );

#endif