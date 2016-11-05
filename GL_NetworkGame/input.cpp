//------------------------------------------------------------------------------
// Title:			Input
// File Name:		input.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2015/05/20
// Updated:			2016/05/10
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
#define KEY_STATE_MAX		( 256 )			// Max Number of Keys

//------------------------------------------------------------------------------
// PROTOTYPES
//------------------------------------------------------------------------------
HRESULT Init( HINSTANCE hInstance );
void Uninit( void );

namespace
{
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
	LPDIRECTINPUT8 g_input = nullptr;						// Input Pointer
	LPDIRECTINPUTDEVICE8 g_devKeyboard = nullptr;			// Keyboard Device Pointer
	LPDIRECTINPUTDEVICE8 g_devMouse = nullptr;				// Mouse Device Pointer

	BYTE g_keyState[ KEY_STATE_MAX ] = { 0 };				// Keyboard Press State
	BYTE g_keyStateTrigger[ KEY_STATE_MAX ] = { 0 };		// Keyboard Trigger State
	BYTE g_keyStateRelease[ KEY_STATE_MAX ] = { 0 };		// Keyboard Release State
	int g_keyStateRepeatCount[ KEY_STATE_MAX ] = { 0 };		// Keyboard Repeat Count

	Input::Mouse g_mouse = { 0 };							// Mouse Data
}

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Input::Init
// Arguments:
//		HINSTANCE hInstance
// Return Value:
//		HRESULT
// Description:
//		Initializes Input
// ����:
//		���͏�����
//------------------------------------------------------------------------------
HRESULT Init( HINSTANCE hInstance )
{
	if( !g_input )
	{
		if( FAILED( DirectInput8Create( hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			( void** )&g_input, NULL ) ) )
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Input
// ����:
//		���͏I������
//------------------------------------------------------------------------------
void Uninit( void )
{
	if( !g_input )
	{
		g_input->Release();
		g_input = nullptr;
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Input
// ����:
//		���͍X�V����
//------------------------------------------------------------------------------
void Input::Update( void )
{
	if( g_devMouse )
	{
		UpdateMouse();
	}

	if( g_devKeyboard )
	{
		UpdateKeyboard();
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::InitMouse
// Arguments:
//		HWND hWnd
//		HINSTANCE hInstance
// Return Value:
//		HRESULT
// Description:
//		Initializes Mouse
// ����:
//		Mouse ������
//------------------------------------------------------------------------------
HRESULT Input::InitMouse( HWND hWnd, HINSTANCE hInstance )
{
	if( FAILED( Init( hInstance ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_input->CreateDevice( GUID_SysMouse, &g_devMouse, NULL ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_devMouse->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_devMouse->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL;
	}

	// Acquire Mouse Device
	// �}�E�X�f�̃o�C�X�擾
	g_devMouse->Acquire();

	// Initialize Mouse Data
	// �}�E�X�f�[�^������
	memset( &g_mouse, 0, sizeof( Mouse ) );

	return S_OK;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::UninitMouse
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Mouse
// ����:
//		Mouse �I������
//------------------------------------------------------------------------------
void Input::UninitMouse( void )
{
	if( !g_devMouse )
	{
		g_devMouse->Unacquire();
		g_devMouse->Release();
		g_devMouse = nullptr;
	}

	Uninit();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::UpdateMouse
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Mouse
// ����:
//		Mouse �X�V����
//------------------------------------------------------------------------------
void Input::UpdateMouse( void )
{
	// Get Window Handle
	// �E�B���h�E�̃n���h�����擾
	HWND hWnd = GetHWND();

	// Mouse Variables
	// �}�E�X�̕ϐ�
	DIMOUSESTATE2 mouseState;		// Mouse State
	POINT mousePoint = { 0 };		// Mouse Location
	POINT screenPoint = { 0 };		// Screen Location
	RECT winRect = { 0 };			// Window Rect Location
	g_mouse.moved = false;			// Reset Mouse Moved to False

	// Get Presetation Parameters Size
	// �v���[���g�p�����[�^�̃T�C�Y���擾
	float screenWidth = ( float )GetGameApp()->GetRenderer()->GetScreenWidth();
	float screenHeight = ( float )GetGameApp()->GetRenderer()->GetScreenHeight();

	// If Mouse is Accessible
	// �}�E�X�ɃA�N�Z�X�o����ꍇ
	if( SUCCEEDED( g_devMouse->GetDeviceState( sizeof( DIMOUSESTATE2 ), &mouseState ) ) )
	{
		// Get Mouse Screen Position
		// �X�N������̃}�E�X���W���擾
		GetCursorPos( &screenPoint );

		// Get Client Rect
		// �N���C�G���g�̃T�C�Y���擾
		GetClientRect( hWnd, &winRect );
		const LONG CLIENT_WIDTH = winRect.right - winRect.left;
		const LONG CLIENT_HEIGHT = winRect.bottom - winRect.top;

		// Get Mouse Client Position
		// �N���C�G���g��̃}�E�X���W���擾
		mousePoint = screenPoint;
		ScreenToClient( hWnd, &mousePoint );

		// Adjust Mouse Position based on Client Size
		// �N���C�G���g�̃T�C�Y�ɂ���āA�}�E�X���W�𒲐�����
		float xMult = CLIENT_WIDTH > 0 ? screenWidth / ( float )CLIENT_WIDTH : 1;
		float yMult = CLIENT_HEIGHT > 0 ? screenHeight / ( float )CLIENT_HEIGHT : 1;
		g_mouse.xPos = ( float )mousePoint.x;
		g_mouse.xPos *= xMult;
		g_mouse.yPos = ( float )mousePoint.y;
		g_mouse.yPos *= yMult;

		// Update Mouse Status
		// �}�E�X�̃X�e�[�^�X���X�V����
		for( int buttonCount = 0; buttonCount < MOUSE_BUTTON_MAX; buttonCount++ )
		{
			g_mouse.trigger[ buttonCount ] = ~g_mouse.state.rgbButtons[ buttonCount ] & mouseState.rgbButtons[ buttonCount ];
			g_mouse.release[ buttonCount ] = g_mouse.state.rgbButtons[ buttonCount ] & ~mouseState.rgbButtons[ buttonCount ];
		}

		// If Mouse Moved
		// �}�E�X�������ꍇ
		if( g_mouse.state.lX != 0 || g_mouse.state.lY != 0 )
		{
			g_mouse.moved = true;
		}

		// Set New Mouse State
		// �V�����}�E�X�X�e�[�g���Z�b�g����
		g_mouse.state = mouseState;
	}

	else
	{
		// Reaquire Mouse
		g_devMouse->Acquire();
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetMousePress
// Arguments:
//		MOUSE_BUTTON mouseButton
// Return Value:
//		bool
// Description:
//		Gets Mouse Press Status
// ����:
//		Mouse �v���X��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetMousePress( MouseButton mouseButton )
{
	int buttonID = ( int )mouseButton;

	if( buttonID < 0 || buttonID >= MOUSE_BUTTON_MAX )
	{
		return false;
	}

	return( g_mouse.state.rgbButtons[ buttonID ] & 0x80 ? true : false );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetMouseTrigger
// Arguments:
//		MOUSE_BUTTON mouseButton
// Return Value:
//		bool
// Description:
//		Gets Mouse Trigger Status
// ����:
//		Mouse �g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetMouseTrigger( MouseButton mouseButton )
{
	int buttonID = ( int )mouseButton;

	if( buttonID < 0 || buttonID >= MOUSE_BUTTON_MAX )
	{
		return false;
	}

	return( g_mouse.trigger[ buttonID ] & 0x80 ? true : false );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetMouseRelease
// Arguments:
//		MOUSE_BUTTON mouseButton
// Return Value:
//		bool
// Description:
//		Gets Mouse Release Status
// ����:
//		Mouse �����[�X��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetMouseRelease( MouseButton mouseButton )
{
	int buttonID = ( int )mouseButton;

	if( buttonID < 0 || buttonID >= MOUSE_BUTTON_MAX )
	{
		return false;
	}

	return( g_mouse.release[ buttonID ] & 0x80 ? true : false );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetMouse
// Arguments:
//		void
// Return Value:
//		Input::Mouse
// Description:
//		Gets Mouse Data
// ����:
//		Mouse�f�[�^���擾
//------------------------------------------------------------------------------
Input::Mouse Input::GetMouse( void )
{
	return g_mouse;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::InitKeyboard
// Arguments:
//		HWND hWnd
//		HINSTANCE hInstance
// Return Value:
//		HRESULT
// Description:
//		Initializes Keyboard
// ����:
//		Keyboard ������
//------------------------------------------------------------------------------
HRESULT Input::InitKeyboard( HWND hWnd, HINSTANCE hInstance )
{
	if( FAILED( Init( hInstance ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_input->CreateDevice( GUID_SysKeyboard, &g_devKeyboard, NULL ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_devKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_devKeyboard->SetCooperativeLevel( hWnd, ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL;
	}

	// Acquire Keyboard Device
	// �L�[�{�[�h�f�̃o�C�X�擾
	g_devKeyboard->Acquire();

	return S_OK;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::UninitKeyboard
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Keyboard
// ����:
//		Keyboard �I������
//------------------------------------------------------------------------------
void Input::UninitKeyboard( void )
{
	if( !g_devKeyboard )
	{
		g_devKeyboard->Unacquire();
		g_devKeyboard->Release();
		g_devKeyboard = NULL;
	}

	Uninit();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::UpdateKeyboard
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Keyboard
// ����:
//		Keyboard �X�V����
//------------------------------------------------------------------------------
void Input::UpdateKeyboard( void )
{
	// New Key State Variable
	// �V�����L�[�X�e�[�g�ϐ�
	BYTE keyState[ KEY_STATE_MAX ];

	// If Device State is Accessible
	// �f�o�C�X�̃X�e�[�g���擾�o����Ȃ�
	if( SUCCEEDED( g_devKeyboard->GetDeviceState( sizeof( keyState ),
		&keyState[ 0 ] ) ) )
	{
		// Record Key States
		// �L�[�̃X�e�[�g���L�^����
		for( int keyCount = 0; keyCount < KEY_STATE_MAX; keyCount++ )
		{
			g_keyStateTrigger[ keyCount ] = ( ( ~g_keyState[ keyCount ] ) & keyState[ keyCount ] );
			g_keyStateRelease[ keyCount ] = ( g_keyState[ keyCount ] & ( ~keyState[ keyCount ] ) );
			g_keyState[ keyCount ] = keyState[ keyCount ];
		}
	}

	// Else Reacquire Device
	// �f�o�C�X���擾����
	else
	{
		g_devKeyboard->Acquire();
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetKeyboardPress
// Arguments:
//		int key
// Return Value:
//		bool
// Description:
//		Gets Keyboard Press Status
// ����:
//		Keyboard �v���X��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetKeyboardPress( int key )
{
	return( g_keyState[ key ] & 0x80 ) ? true : false;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetKeyboardTrigger
// Arguments:
//		int key
// Return Value:
//		bool
// Description:
//		Gets Keyboard Trigger Status
// ����:
//		Keyboard �g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetKeyboardTrigger( int key )
{
	return ( g_keyStateTrigger[ key ] & 0x80 ) ? true : false;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetKeyboardRelease
// Arguments:
//		int key
// Return Value:
//		bool
// Description:
//		Gets Keyboard Trigger Status
// ����:
//		Keyboard �g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetKeyboardRelease( int key )
{
	return ( g_keyStateRelease[ key ] & 0x80 ) ? true : false;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Input::GetKeyboardRepeat
// Arguments:
//		int key
// Return Value:
//		bool
// Description:
//		Gets Keyboard Trigger Status
// ����:
//		Keyboard �g���K�[��Ԃ��擾
//------------------------------------------------------------------------------
bool Input::GetKeyboardRepeat( int key )
{
	// Check for Key Press
	// �L�[�������Ă��邩�ǂ������m�F
	g_keyState[ key ] & 0x80 ? g_keyStateRepeatCount[ key ]++ : g_keyStateRepeatCount[ key ] = 0;

	// Key Repeat Switch
	// �L�[�̃��s�[�g�̃X�C�b�`
	switch( g_keyStateRepeatCount[ key ] )
	{
	case 0:
		return false;
		break;

	case 1:
		return true;
		break;

	case 10:
		return true;
		break;

	case 20:
		return true;
		break;

	case 25:
		return true;
		break;

	case 30:
		return true;
		break;

	default:
		if( g_keyStateRepeatCount[ key ] >= 35 )
		{
			return true;
		}

		return false;
		break;
	}

	return false;
}