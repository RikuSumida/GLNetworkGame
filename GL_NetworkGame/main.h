#pragma once
//------------------------------------------------------------------------------
// Title:			Main
// File Name:		main.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/15
// Updated:			2016/11/05
//------------------------------------------------------------------------------
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//------------------------------------------------------------------------------
// LIBRARY LINKS
//------------------------------------------------------------------------------
#pragma comment( lib, "winmm.lib" )			// Used for FPS

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include <Windows.h>		// Windows Functions
#include <math.h>			// Math Functions
#include "gameApp.h"		// OpenGL Game App Class

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
// Client Size Defines
#define SCREEN_WIDTH		( 1280 )
#define SCREEN_HEIGHT		( 720 )

// Update Defines
// çXêVèàóùÇÃíËã`
#define UPDATES_PER_SEC		( 60 )								// Updates Per Second
#define MS_PER_SEC			( 1000 )							// Milliseconds Per Second
#define MS_PER_UPDATE		( MS_PER_SEC / UPDATES_PER_SEC )	// Milliseconds Per Update

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
GameApp* GetGameApp( void );
HWND GetHWND( void );

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif