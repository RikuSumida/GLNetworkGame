#pragma once
//------------------------------------------------------------------------------
// Title:			GameAppGL
// File Name:		gameAppGL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
#ifndef GAME_APP_GL_H_INCLUDED
#define GAME_APP_GL_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "rendererGL.h"						// GL Renderer
#include "gameVariables.h"					// Game Variables
#include "textureManager.h"					// Textures
#include "vertex.h"							// Vertex Structures

//------------------------------------------------------------------------------
// FORWARD DECLARATIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class GameApp
{
public:
	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor/Destructor
	GameApp();
	~GameApp();

	// General Functions
	bool Init( HINSTANCE hInstance, HWND hWnd, bool bWindow );
	void Uninit( void );
	void Update( void );
	void Draw( void );

	// Get Functions
	RendererGL* GetRenderer( void ){ return m_rendererGL; }

	// Game Prototypes
	// ゲームプロトタイプ
	void QuitGame( void );
	bool PlayingGame( void );

private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	// Game Variables
	bool m_playingGame;					// If Game is being Played

	// Class Pointers
	RendererGL* m_rendererGL;			// Renderer
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif