//------------------------------------------------------------------------------
// Title:			Fade
// File Name:		fade.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/07/11
// Updated:			2016/11/07
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "fade.h"
#include "scene2DGL.h"
#include "modeManager.h"

namespace
{
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
	Mode* g_nextMode = nullptr;
	Fade::State g_state = Fade::FadeNone;
	int g_fadeLength = UPDATES_PER_SEC;
	int g_count = 0;

	Scene2DGL* g_fadeScreen = nullptr;
	Vector3 g_fadeColor = Vector3( 1.0f, 1.0f, 1.0f );
}

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::Init
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Initializes Fade
// 説明:
//		Fadeの初期化
//------------------------------------------------------------------------------
void Fade::Init( void )
{
	g_fadeScreen = Scene2DGL::Create(
		Scene2DGL::BASE_WIDTH * 0.5f,
		Scene2DGL::BASE_HEIGHT * 0.5f,
		( float )Scene2DGL::BASE_WIDTH,
		( float )Scene2DGL::BASE_HEIGHT,
		nullptr,
		SceneGL::DrawOutsideList );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Fade
// 説明:
//		Fadeの終了処理
//------------------------------------------------------------------------------
void Fade::Uninit( void )
{
	if( g_fadeScreen )
	{
		g_fadeScreen->Release();
		g_fadeScreen = nullptr;
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::Start
// Arguments:
//		Mode* nextMode
// Return Value:
//		void
// Description:
//		Starts Fade
// 説明:
//		Fade開始
//------------------------------------------------------------------------------
void Fade::Start( Mode* nextMode )
{
	// If Mode doesn't Exists or Currently Fading, Return
	// モードが存在しないまたは現在フェードしている
	if( !nextMode || g_state != FadeNone )
	{
		if( nextMode )
		{
			delete nextMode;
		}

		return;
	}

	// Set Variables
	// 変数の設定
	g_nextMode = nextMode;
	g_state = FadeOut;
	g_count = 0;
	//g_fadeScreen->SetColor( Vector4( g_fadeColor.x, g_fadeColor.y, g_fadeColor.z, 0.0f ) );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Fade
// 説明:
//		Fadeの更新
//------------------------------------------------------------------------------
void Fade::Update( void )
{
	// Update Fade State
	// フェードステートの更新
	switch( g_state )
	{
	case FadeNone:
		return;

	case FadeOut:
		// If Fade Out Length Reached
		// フェードアウトが完成した場合
		if( g_count >= g_fadeLength )
		{
			// Set Next Mode
			// 次のモードに切り替え
			ModeManager::SetMode( g_nextMode );

			// Change to Fade In
			// フェードインに変える
			g_state = FadeIn;
		}

		// Increase Fade Counter
		// フェードのカウンターを増やす
		else
		{
			g_count++;
		}
		
		break;

	case FadeIn:
		// If Fade in Complete
		// フェードインが完成した場合
		if( g_count <= 0 )
		{
			// Return Fade State to None
			// フェードステートをなしに戻って
			g_state = FadeNone;
			return;
		}

		// Decrease Fade Counter
		// フェードのカウンターを減らす
		g_count--;
		break;
	}

	// Set Fade Screen Color
	// フェードの色設定
	//g_fadeScreen->SetColor( Vector4(
	//	g_fadeColor.x, g_fadeColor.y, g_fadeColor.z,
	//	( float )g_count / g_fadeLength ) );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws Fade
// 説明:
//		Fadeの描画処理
//------------------------------------------------------------------------------
void Fade::Draw( void )
{
	if( g_state == FadeNone )
	{
		return;
	}

	// Draw
	g_fadeScreen->Draw();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::GetState
// Arguments:
//		void
// Return Value:
//		Fade::State
// Description:
//		Gets Fade State
// 説明:
//		Fadeステートを取得
//------------------------------------------------------------------------------
Fade::State Fade::GetState( void )
{
	return g_state;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Fade::SetColor
// Arguments:
//		float r
//		float g
//		float b
// Return Value:
//		void
// Description:
//		Sets Fade Color
// 説明:
//		Fade色の設定
//------------------------------------------------------------------------------
void Fade::SetColor( float r, float g, float b )
{
	g_fadeColor = Vector3( r, g, b );
}