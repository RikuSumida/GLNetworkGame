#pragma once
//------------------------------------------------------------------------------
// Title:			Input
// File Name:		input.h
// Creator:			Nicholas Dahms
// Creation Date:	2015/05/20
// Updated:			2016/05/10
//------------------------------------------------------------------------------
#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

//------------------------------------------------------------------------------
// LIBRARY LINKS
//------------------------------------------------------------------------------
#pragma comment( lib, "dinput8.lib" )	// Necessary for Input - ì¸óÕèàóùÇ…ïKóv
#pragma comment( lib, "dxguid.lib" )	// Necessary to DirectX Components #include <initguid.h>

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION		( 0x0800 )
#include <dinput.h>				// Direct Input

//------------------------------------------------------------------------------
// NAMESPACE
//------------------------------------------------------------------------------
namespace Input
{
	//--------------------------------------
	// ENUMERATES
	//--------------------------------------
	// Mouse Buttons
	enum MouseButton
	{
		MOUSE_LEFT,							// Left Mouse Button
		MOUSE_RIGHT,						// Right Mouse Button
		MOUSE_MIDDLE,						// Middle Mouse Button
		MOUSE_BUTTON_MAX					// Max Number of Mouse Buttons
	};

	//--------------------------------------
	// STRUCTURES
	//--------------------------------------
	// Mouse Data
	struct Mouse
	{
		DIMOUSESTATE2 state;				// Mouse State Data
		float xPos;							// X Position
		float yPos;							// Y Position
		int trigger[ MOUSE_BUTTON_MAX ];	// Mouse Button Trigger
		int release[ MOUSE_BUTTON_MAX ];	// Mouse Button Release
		bool moved;							// If Mouse Moved
	};

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// General
	void Update( void );

	// Mouse
	HRESULT InitMouse( HWND hWnd, HINSTANCE hInstance );
	void UninitMouse( void );
	void UpdateMouse( void );
	bool GetMousePress( MouseButton mouseButton );
	bool GetMouseTrigger( MouseButton mouseButton );
	bool GetMouseRelease( MouseButton mouseButton );
	Mouse GetMouse( void );

	// Keyboard
	HRESULT InitKeyboard( HWND hWnd, HINSTANCE hInstance );
	void UninitKeyboard( void );
	void UpdateKeyboard( void );

	bool GetKeyboardPress( int nKey );
	bool GetKeyboardTrigger( int nKey );
	bool GetKeyboardRelease( int nKey );
	bool GetKeyboardRepeat( int nKey );
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif