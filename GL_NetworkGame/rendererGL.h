#pragma once
//------------------------------------------------------------------------------
// Title:			RendererGL
// File Name:		rendererGL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/13
// Updated:			2016/05/13
//------------------------------------------------------------------------------
#ifndef RENDERER_GL_H_INCLUDED
#define RENDERER_GL_H_INCLUDED

//------------------------------------------------------------------------------
// LIBRARY LINKS
//------------------------------------------------------------------------------
#pragma comment ( lib, "OpenGL32.lib" )		// OpenGL Library
#pragma comment ( lib, "glu32.lib" )		// OpenGL Library

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include <gl/GL.h>							// OpenGL
#include <gl/GLU.h>							// OpenGL

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class RendererGL
{
public:
	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor/Destructor
	RendererGL();
	~RendererGL();

	// General Functions
	bool Init( HINSTANCE hInstance, HWND hWnd, bool bWindow );
	void Uninit( void );

	// Draw Functions
	void Begin( void );
	void End( void );
	void Begin2D( void );
	void End2D( void );

	// OpenGL Functions
	int GetScreenWidth( void );
	int GetScreenHeight( void );

	// Render Functions
	bool ToggleWireframe( void );
	void SetCullBack( void );
	void SetCullFront( void );
	void DisableCull( void );
	int GetCullFace( void );
	void OnScreenResize( int width, int height );

private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	// OpenGL Variables
	HDC m_dc;					// OpenGL Device Context
	HGLRC m_glrc;				// OpenGL Rendering Context

	// Screen Variables
	int m_screenWidth;			// Screen Width
	int m_screenHeight;			// Screen Height

	// Windows Handles
	HWND m_hWnd;				// Window Handle
	HINSTANCE m_hInstance;		// Instance Handle

	// Render States
	bool m_wireframeEnabled;	// If Wireframe Display is Enabled
	int m_cullFace;				// Current Cullface

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Display Settings
	// ï`âÊê›íË
	void InitRenderState( void );
	void InitTextureState( void );
	void InitSamplerState( void );
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif