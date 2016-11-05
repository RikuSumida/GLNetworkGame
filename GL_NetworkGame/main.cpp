//------------------------------------------------------------------------------
// Title:			Main
// File Name:		main.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/15
// Updated:			2016/11/05
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
#define MY_WIN_CLASS		( "MY_WINDOW" )
#define MY_WIN_STYLE		( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX )

//------------------------------------------------------------------------------
// PROTOTYPES
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
// Windows Variables
HWND hWnd;				// Window Handle
HINSTANCE hInstance;	// Window Instance

// Game App
GameApp* g_gameApp = nullptr;

// FPS Variables
int g_countFPS;			
const int MAX_UPDATE_LOOP = 10;


unsigned int g_fpsCap = 60;								// FPS Cap
unsigned int g_msPerFrame = ( MS_PER_SEC / g_fpsCap );	// Milliseconds Per Frame

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// WINMAIN
//------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
	// Update and FPS Variables
	// 更新とFPS変数
	DWORD dwFrameCount;		// Frame Count
	DWORD dwCurrentTime;	// Current Time
	DWORD dwExecLastTime;	// Last Execute Time
	DWORD dwDrawLastTime;	// Last Draw Time
	DWORD dwFPSLastTime;	// Last FPS Display Time

	DWORD dwAccum = 0;		// Accumulates Time Between Updates
	int loopCount = 0;		// Counts Update While Loop

	// Window Rect Size Setting
	// ウインドウのサイズ設定
	RECT rect = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

	// Window Class
	// ウインドウクラス
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ),						// Memory Size
		CS_CLASSDC,									// Window Style
		WndProc,									// Window Procedure Address
		0,
		0,
		hInstance,									// Instance Handle
		NULL,										// Icon Setting
		LoadCursor( NULL, IDC_ARROW ),				// Mouse Cursor Setting
		( HBRUSH )GetStockObject( WHITE_BRUSH ),	// Client Region BG Color
		NULL,										// Menu Settings
		MY_WIN_CLASS,								// Window Class Name
		NULL										// Small Icon
	};

	// Window Event Message Holder
	// ウィンドウのイベントメッセージ変数
	MSG msg;

	// Register Window Class
	// ウィンドウクラスを登録
	RegisterClassEx( &wcex );

	// Create Window and Use in Handle
	// ウインドウハンドルの生成
	hWnd = CreateWindowEx(
		0,
		MY_WIN_CLASS,				// Window Class Name
		"OpenGL",					// Window Caption
		MY_WIN_STYLE,				// Window Style
		CW_USEDEFAULT,				// X Position
		CW_USEDEFAULT,				// Y Position
		rect.right - rect.left,		// Width
		rect.bottom - rect.top,		// Height
		NULL,						// Parent Window
		NULL,						// Menu Settings
		hInstance,					// Instance Handle
		NULL );						// Multiple Windows

	// Initialize Program
	// 初期化処理
	g_gameApp = new GameApp;
	if( !g_gameApp->Init( hInstance, hWnd, false ) )
	{
		return -1;
	}

	// Show Window
	// ウインドウ表示
	ShowWindow( hWnd, nCmdShow );

	// Update Window
	// ウインドウ更新
	UpdateWindow( hWnd );

	// Initialize Time Variables
	// 時間の変数の初期化
	timeBeginPeriod( 1 );
	dwFrameCount =
		dwCurrentTime = 0;

	dwExecLastTime =
		dwDrawLastTime =
		dwFPSLastTime = timeGetTime();

	// Message Loop
	// メッセージループ
	while( g_gameApp->PlayingGame() )
	{
		// If a Message is Present
		// メッセージが存在したら
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			// If Program is to Quit
			//終了する場合
			if( msg.message == WM_QUIT )
			{
				break;
			}

			// Else Translate and Dispatch Messages
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}

		else
		{
			// Get Current Time
			// 現在の時間を習得
			dwCurrentTime = timeGetTime();

			// Calculate FPS
			// FPSを計算する
			if( ( dwCurrentTime - dwFPSLastTime ) >= ( MS_PER_SEC * 0.5 ) )
			{
				g_countFPS = ( dwFrameCount * MS_PER_SEC ) / ( dwCurrentTime - dwFPSLastTime );

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			// If Update Interval Has Come
			// 更新する時間になった場合
			if( ( dwCurrentTime - dwExecLastTime ) >= MS_PER_UPDATE )
			{
				dwAccum += dwCurrentTime - dwExecLastTime;
				dwExecLastTime = dwCurrentTime;

				// Set Loop Count to 0
				// 更新ループを0に設定
				loopCount = 0;

				// Update Until Caught Up to Update Rate
				// 余っている時間がなくなるまで更新
				while( dwAccum >= MS_PER_UPDATE )
				{
					// Update
					// 更新
					g_gameApp->Update();

					// Subtract Update Time
					// 更新時間を引く
					dwAccum -= MS_PER_UPDATE;

					// Increment Loop Count
					// ループを増やす
					loopCount++;

					// Safety Break if Max Loop Number Reached
					// ループの最大繰り返しについた
					if( loopCount > MAX_UPDATE_LOOP )
					{
						dwAccum = 0;
						break;
					}
				}
			}


			// Draw
			// 描画
			if( ( dwCurrentTime - dwDrawLastTime ) >= g_msPerFrame )
			{
				g_gameApp->Draw();	// 描画処理
				dwFrameCount++;			// Increase Frame Count - フレームカウントを増加
				dwDrawLastTime = dwCurrentTime;
			}
		}
	}

	// Unregister Window Class
	// ウィンドウ・クラスの登録の取り消し
	UnregisterClass( MY_WIN_CLASS, wcex.hInstance );

	// End Time Period
	timeEndPeriod( 1 );

	// Return Quit Message to Windows
	// Windowsへの戻り値
	return ( int )msg.wParam;
}

//------------------------------------------------------------------------------
// LRESULT
//------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	// Message ID Holder
	int nID;

	// Message Switch
	switch( uMsg )
	{
	// Close Window Message
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	// Move Window
	case WM_MOVE:
		break;

	// Window Resize
	case WM_SIZE:
		if( g_gameApp )
		{
			//g_gameApp->OnScreenResize( LOWORD( lParam ), HIWORD( lParam ) );	// LoWord=Width, HiWord=Height
		}
		return 0;
		break;

		// Key Press
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			// Confirmation Box
			// 確認ボックス
			nID = MessageBox( hWnd, "終了しますか。", "終了確認", MB_ICONINFORMATION | MB_YESNO );

			// If Yes, Destroy Window
			// 終了する場合
			if( nID == IDYES )
			{
				DestroyWindow( hWnd );
			}
			break;
		}

	// Left Mouse Down Input
	case WM_LBUTTONDOWN:
		// Set Window Focus
		SetFocus( hWnd );
		break;

	default:
		break;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GetGameApp
// Arguments:
//		void
// Return Value:
//		GameApp*
// Description:
//		Gets Game App
// 説明:
//		GameAppを習得する
//------------------------------------------------------------------------------
GameApp* GetGameApp( void )
{
	return g_gameApp;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GetHWND
// Arguments:
//		void
// Return Value:
//		HWND
// Description:
//		Returns Window Handle
// 説明:
//		ウインドウハンドルを習得
//------------------------------------------------------------------------------
HWND GetHWND( void )
{
	return hWnd;
}
