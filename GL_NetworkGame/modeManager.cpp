///------------------------------------------------------------------------------
// Title:			Mode Manager
// File Name:		modeManager.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/07/11
// Updated:			2016/10/01
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "modeManager.h"

namespace
{
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
	Mode* g_mode = nullptr;
}

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		ModeManager::SetMode
// Arguments:
//		Mode* mode
// Return Value:
//		void
// Description:
//		Sets New Mode
// 説明:
//		モードの設定
//------------------------------------------------------------------------------
void ModeManager::SetMode( Mode* mode )
{
	// Start Loading Screen
	// ロード画面の始まり
	//LoadScreen::Begin();

	// Uninitialize Previous Mode
	// 前のモード終了処理
	if( g_mode )
	{
		g_mode->Uninit();
		delete g_mode;
		g_mode = nullptr;
	}

	// Initialize New Mode
	// 新しいモードを初期化
	if( mode )
	{
		g_mode = mode;
		g_mode->Init();	
	}

	// End Loading Screen
	// ロード画面の終わり
	//LoadScreen::End();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		ModeManager::GetMode
// Arguments:
//		void
// Return Value:
//		Mode* mode
// Description:
//		Gets New Mode
// 説明:
//		モードを取得
//------------------------------------------------------------------------------
Mode* ModeManager::GetMode( void )
{
	return g_mode;
}