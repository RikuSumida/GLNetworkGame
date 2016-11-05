//------------------------------------------------------------------------------
// Title:			GameApp
// File Name:		gameApp.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/18
// Updated:			2016/04/22
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "gameApp.h"
#include "input.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::GameApp()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		GameApp Constructor
// 説明:
//		GameAppのコンストラクタ
//------------------------------------------------------------------------------
GameApp::GameApp() :
	m_playingGame( true ),
	m_rendererGL( nullptr )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::~GameApp()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		GameApp Deconstructor
// 説明:
//		GameAppのデストラクタ
//------------------------------------------------------------------------------
GameApp::~GameApp()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Init
// Arguments:
//		HINSTANCE hInstance		Instance Handle
//		HWND hWnd				Window Handle
//		bool bWindow			Windowed / Fullscreen Setting
// Return Value:
//		bool
// Description:
//		Initializes GameApp
// 説明:
//		GameAppの初期化
//------------------------------------------------------------------------------
bool GameApp::Init( HINSTANCE hInstance, HWND hWnd, bool bWindow )
{
	// Initialize Renderer
	// Rendererの初期化
	m_rendererGL = new RendererGL;
	m_rendererGL->Init( hInstance, hWnd, bWindow );

	// Initialize Input
	// 入力の初期化
	Input::InitKeyboard( hWnd, hInstance );
	Input::InitMouse( hWnd, hInstance );

	// Initialize Camera
	// カメラの初期化
	//m_camera = new CameraGL;

	// Scene Initialization
	// Sceneの初期化
	//m_scene[ 0 ] = new Scene3DGL;
	//m_scene[ 0 ]->Init();
	//m_scene[ 0 ] = Scene3DGL::Create( Vector3(), 10, 10, "./data/texture/game_logo.jpg" );
	//
	//m_scene[ 1 ] = MeshBoxGL::Create(
	//	Vector3( 0.0f, 2.0f, 0.0f ),
	//	Vector3( 3.0f, 3.0f, 3.0f ),
	//	Vector3(),
	//	1,
	//	1,
	//	1,
	//	1,
	//	"./data/texture/testPNG.png" );
	//
	//m_scene[ 2 ] = Scene2DGL::Create(
	//	SCREEN_WIDTH * 0.2f,
	//	SCREEN_HEIGHT * 0.2f,
	//	SCREEN_WIDTH * 0.3f,
	//	SCREEN_HEIGHT * 0.3f,
	//	"./data/texture/testPNG.png" );
	//
	//m_scene[ 3 ] = Scene2DGL::Create(
	//	SCREEN_WIDTH * 0.6f,
	//	SCREEN_HEIGHT * 0.3f,
	//	SCREEN_WIDTH * 0.3f,
	//	SCREEN_HEIGHT * 0.3f,
	//	"./data/texture/testJPG.jpg" );

	return true;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes GameApp
// 説明:
//		GameAppの終了処理
//------------------------------------------------------------------------------
void GameApp::Uninit( void )
{
	// Uninitialize Input
	// 入力の終了処理
	Input::UninitKeyboard();
	Input::UninitMouse();

	// Unitialize Camera
	// カメラの終了処理
	//delete m_camera;
	//m_camera = nullptr;

	// Uninitialize Renderer
	// Rendererの終了処理
	m_rendererGL->Uninit();
	delete m_rendererGL;
	m_rendererGL = nullptr;

}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates GameApp
// 説明:
//		GameAppの更新処理
//------------------------------------------------------------------------------
void GameApp::Update( void )
{
	// Update Input
	// 入力の更新
	Input::Update();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws GameApp
// 説明:
//		GameApp描画処理
//------------------------------------------------------------------------------
void GameApp::Draw( void )
{
	// Begin Draw
	// 描画開始
	m_rendererGL->Begin();
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
		m_rendererGL->Begin2D();
		{
			
		}
		m_rendererGL->End2D();
		// End 2D Draw
		// 2D描画終了処理
	}
	m_rendererGL->End();
	// End Draw
	// 描画終了
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::PlayingGame
// Arguments:
//		void
// Return Value:
//		bool
// Description:
//		If Playing Game
// 説明:
//		プレイしているかどうか
//------------------------------------------------------------------------------
bool GameApp::PlayingGame( void )
{
	return m_playingGame;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GameApp::QuitGame
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Quits Game
// 説明:
//		ゲーム終了
//------------------------------------------------------------------------------
void GameApp::QuitGame( void )
{
	m_playingGame = false;
}