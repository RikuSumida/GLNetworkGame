//------------------------------------------------------------------------------
// Title:			Title
// File Name:		title.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/07/11
// Updated:			2016/11/07
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "title.h"
#include "input.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Title
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Constructor
// 説明:
//		Titleのコンストラクタ
//------------------------------------------------------------------------------
Title::Title()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::~Title
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Destructor
// 説明:
//		Titleのデストラクタ
//------------------------------------------------------------------------------
Title::~Title()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Init
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Initialization
// 説明:
//		Titleの初期化
//------------------------------------------------------------------------------
void Title::Init( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Uninitialization
// 説明:
//		Titleの終了処理
//------------------------------------------------------------------------------
void Title::Uninit( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Update
// 説明:
//		Titleの更新処理
//------------------------------------------------------------------------------
void Title::Update( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Draw
// 説明:
//		Titleの描画処理
//------------------------------------------------------------------------------
void Title::Draw( void )
{
	// Begin 3D Draw
	// 3D描画開始
	{
		//m_camera->Set();


	}
	// End 3D Draw
	// 3D描画終了処理

	// Begin 2D Draw
	// 2D描画開始
	GetGameApp()->GetRenderer()->Begin2D();
	{
			
	}
	GetGameApp()->GetRenderer()->End2D();
	// End 2D Draw
	// 2D描画終了処理

}