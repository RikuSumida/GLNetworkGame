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
	// �X�V��FPS�ϐ�
	DWORD dwFrameCount;		// Frame Count
	DWORD dwCurrentTime;	// Current Time
	DWORD dwExecLastTime;	// Last Execute Time
	DWORD dwDrawLastTime;	// Last Draw Time
	DWORD dwFPSLastTime;	// Last FPS Display Time

	DWORD dwAccum = 0;		// Accumulates Time Between Updates
	int loopCount = 0;		// Counts Update While Loop

	// Window Rect Size Setting
	// �E�C���h�E�̃T�C�Y�ݒ�
	RECT rect = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect( &rect, WS_OVERLAPPEDWINDOW, false );

	// Window Class
	// �E�C���h�E�N���X
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
	// �E�B���h�E�̃C�x���g���b�Z�[�W�ϐ�
	MSG msg;

	// Register Window Class
	// �E�B���h�E�N���X��o�^
	RegisterClassEx( &wcex );

	// Create Window and Use in Handle
	// �E�C���h�E�n���h���̐���
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
	// ����������
	g_gameApp = new GameApp;
	if( !g_gameApp->Init( hInstance, hWnd, false ) )
	{
		return -1;
	}

	// Show Window
	// �E�C���h�E�\��
	ShowWindow( hWnd, nCmdShow );

	// Update Window
	// �E�C���h�E�X�V
	UpdateWindow( hWnd );

	// Initialize Time Variables
	// ���Ԃ̕ϐ��̏�����
	timeBeginPeriod( 1 );
	dwFrameCount =
		dwCurrentTime = 0;

	dwExecLastTime =
		dwDrawLastTime =
		dwFPSLastTime = timeGetTime();

	// Message Loop
	// ���b�Z�[�W���[�v
	while( g_gameApp->PlayingGame() )
	{
		// If a Message is Present
		// ���b�Z�[�W�����݂�����
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			// If Program is to Quit
			//�I������ꍇ
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
			// ���݂̎��Ԃ��K��
			dwCurrentTime = timeGetTime();

			// Calculate FPS
			// FPS���v�Z����
			if( ( dwCurrentTime - dwFPSLastTime ) >= ( MS_PER_SEC * 0.5 ) )
			{
				g_countFPS = ( dwFrameCount * MS_PER_SEC ) / ( dwCurrentTime - dwFPSLastTime );

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			// If Update Interval Has Come
			// �X�V���鎞�ԂɂȂ����ꍇ
			if( ( dwCurrentTime - dwExecLastTime ) >= MS_PER_UPDATE )
			{
				dwAccum += dwCurrentTime - dwExecLastTime;
				dwExecLastTime = dwCurrentTime;

				// Set Loop Count to 0
				// �X�V���[�v��0�ɐݒ�
				loopCount = 0;

				// Update Until Caught Up to Update Rate
				// �]���Ă��鎞�Ԃ��Ȃ��Ȃ�܂ōX�V
				while( dwAccum >= MS_PER_UPDATE )
				{
					// Update
					// �X�V
					g_gameApp->Update();

					// Subtract Update Time
					// �X�V���Ԃ�����
					dwAccum -= MS_PER_UPDATE;

					// Increment Loop Count
					// ���[�v�𑝂₷
					loopCount++;

					// Safety Break if Max Loop Number Reached
					// ���[�v�̍ő�J��Ԃ��ɂ���
					if( loopCount > MAX_UPDATE_LOOP )
					{
						dwAccum = 0;
						break;
					}
				}
			}


			// Draw
			// �`��
			if( ( dwCurrentTime - dwDrawLastTime ) >= g_msPerFrame )
			{
				g_gameApp->Draw();	// �`�揈��
				dwFrameCount++;			// Increase Frame Count - �t���[���J�E���g�𑝉�
				dwDrawLastTime = dwCurrentTime;
			}
		}
	}

	// Unregister Window Class
	// �E�B���h�E�E�N���X�̓o�^�̎�����
	UnregisterClass( MY_WIN_CLASS, wcex.hInstance );

	// End Time Period
	timeEndPeriod( 1 );

	// Return Quit Message to Windows
	// Windows�ւ̖߂�l
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
			// �m�F�{�b�N�X
			nID = MessageBox( hWnd, "�I�����܂����B", "�I���m�F", MB_ICONINFORMATION | MB_YESNO );

			// If Yes, Destroy Window
			// �I������ꍇ
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
// ����:
//		GameApp���K������
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
// ����:
//		�E�C���h�E�n���h�����K��
//------------------------------------------------------------------------------
HWND GetHWND( void )
{
	return hWnd;
}
