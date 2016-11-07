//------------------------------------------------------------------------------
// Title:			RendererGL
// File Name:		rendererGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/13
// Updated:			2016/05/13
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "rendererGL.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::RendererGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		RendererGL Constructor
// 説明:
//		RendererGLのコンストラクタ
//------------------------------------------------------------------------------
RendererGL::RendererGL() :
	m_screenWidth( 0 ),
	m_screenHeight( 0 ),
	m_wireframeEnabled( false )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::~RendererGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		RendererGL Deconstructor
// 説明:
//		RendererGLのデストラクタ
//------------------------------------------------------------------------------
RendererGL::~RendererGL()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Renderer::Init
// Arguments:
//		HINSTANCE hInstance		Instance Handle
//		HWND hWnd				Window Handle
//		bool bWindow			Windowed / Fullscreen Setting
// Return Value:
//		bool
// Description:
//		Initializes Renderer
// 説明:
//		Rendererの初期化
//------------------------------------------------------------------------------
bool RendererGL::Init( HINSTANCE hInstance, HWND hWnd, bool bWindow )
{
	// Get DC
	// DCを習得
	if( !( m_dc = GetDC( hWnd ) ) )
	{
		return false;
	}

	try
	{
		// Pixel Format
		// ピクセルのフォマット
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof( PIXELFORMATDESCRIPTOR ),	// Size of Pixel Format
			1,									// Version Number
			PFD_DRAW_TO_WINDOW |				// Support Window
			PFD_SUPPORT_OPENGL |				// Support OpenGL
			PFD_DOUBLEBUFFER,					// Double Buffer
			PFD_TYPE_RGBA,						// RGBA Type
			24,									// 24 Bit Color Depth
			0, 0, 0, 0, 0, 0,					// Color Bits Ignored
			0,									// No Alpha Buffer
			0,									// Shift Bit Ignored
			0,									// No Accumulation Buffer
			0, 0, 0, 0,							// Accumulation Bits Ignored
			32,									// 32 Bit Z Buffer
			0,									// No Stencil Buffer
			0,									// No Auxiliary Buffer
			PFD_MAIN_PLANE,						// Main Layer
			0,									// Reserved
			0, 0, 0								// Layer Masks Ignored
		};

		// Choose Pixel Format match Settings
		// 設定通りのピクセルフォマットを選ぶ
		int format = ChoosePixelFormat( m_dc, &pfd );
		if( format == 0 )
			throw "";

		// Set Pixel Format
		// ピクセルフォマットの設定
		if( !SetPixelFormat( m_dc, format, &pfd ) )
			throw"";

		// Create Rendering Context
		// レンダリングコンテキスト作成
		m_glrc = wglCreateContext( m_dc );
		if( !m_glrc )
			throw "";

		// Make Rendering Context Active
		// レンダリングコンテキストを有効にする
		if( !wglMakeCurrent( m_dc, m_glrc ) )
			throw "";
	}

	catch( ... )
	{
		ReleaseDC( hWnd, m_dc );
		return false;
	}

	// Set Windows Variables
	// Windowsの変数設定
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	// View Settings Based on Window Size
	// 画面表示設定
	m_screenWidth = SCREEN_WIDTH;
	m_screenHeight = SCREEN_HEIGHT;
	OnScreenResize( m_screenWidth, m_screenHeight );

	// GL Initial Settings
	// 初期化設定
	glShadeModel( GL_SMOOTH );								// Enable Smooth Shading
	glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );					// Clear Color
	glClearDepth( 1.0f );									// Depth Buffer Setup

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Perspective Correction

	// Display Settings
	// 表示設定
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_ALPHA_TEST );
	glAlphaFunc( GL_GREATER, 0.5f );

	glEnable( GL_DEPTH_TEST );								// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );								// Depth Test Type

	glEnable( GL_CULL_FACE );
	m_cullFace = GL_BACK;
	glCullFace( m_cullFace );

	glEnable( GL_NORMALIZE );
	//glEnable( GL_RESCALE_NORMAL );

	// Texture Wrap
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	return true;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Renderer
// 説明:
//		Rendererの終了処理
//------------------------------------------------------------------------------
void RendererGL::Uninit( void )
{
	// Release Rendering Context
	// レンダリングコンテキスト
	wglMakeCurrent( m_dc, m_glrc );
	wglDeleteContext( m_glrc );
	ReleaseDC( m_hWnd, m_dc );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::GetScreenWidth
// Arguments:
//		void
// Return Value:
//		int
// Description:
//		Gets Game Screen Width
// 説明:
//		画面の幅を習得
//------------------------------------------------------------------------------
int RendererGL::GetScreenWidth( void )
{
	return m_screenWidth;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::GetScreenHeight
// Arguments:
//		void
// Return Value:
//		int
// Description:
//		Gets Game Screen Height
// 説明:
//		画面の高さを習得
//------------------------------------------------------------------------------
int RendererGL::GetScreenHeight( void )
{
	return m_screenHeight;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::OnScreenResize
// Arguments:
//		int width
//		int height
// Return Value:
//		void
// Description:
//		Updates Screen Settings on Resize
// 説明:
//		画面のりサイズした時に設定を更新
//------------------------------------------------------------------------------
void RendererGL::OnScreenResize( int width, int height )
{
	m_screenWidth = width;
	m_screenHeight = height > 0 ? height : 1;

	glViewport( 0, 0, m_screenWidth, m_screenHeight );

	glMatrixMode( GL_PROJECTION );	// Select The Projection Matrix
	glLoadIdentity();				// Reset The Projection Matrix

	// Set Perspective
	gluPerspective(
		45.0f,												// FOV
		( float )m_screenWidth / ( float )m_screenHeight,	// Aspect Ratio
		0.1f,												// Near Z
		100.0f );											// Far Z

	glMatrixMode( GL_MODELVIEW );	// Select The Modelview Matrix
	glLoadIdentity();				// Reset The Modelview Matrix

}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::Begin
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Begins Draw
// 説明:
//		描画の開始
//------------------------------------------------------------------------------
void RendererGL::Begin( void )
{
	// Clear Screen
	// 画面クリア
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::End
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Ends Draw
// 説明:
//		描画の終了
//------------------------------------------------------------------------------
void RendererGL::End( void )
{
	// Swap Buffers
	// バッファ切り替え
	SwapBuffers( m_dc );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::Begin2D
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Begins 2D Draw
// 説明:
//		2D描画の開始
//------------------------------------------------------------------------------
void RendererGL::Begin2D( void )
{
	glDisable(GL_LIGHTING);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( 0 );
	//glDisable( GL_CULL_FACE );

	// Projection Matrix Setting
	// プロジェクションのマトリクスの設定
	glMatrixMode( GL_PROJECTION );	// Select The Projection Matrix
	glPushMatrix();					// Push Current Matrix
	glLoadIdentity();				// Initialize Matrix

	// Model View Matrix Setting
	// モデル・ビューのマトリクスの設定
	glMatrixMode( GL_MODELVIEW );	// Select The Model View Matrix
	glPushMatrix();					// Push Current Matrix
	glLoadIdentity();				// Reset The Model View Matrix

	// Ortho Settings
	glOrtho(
		0.0,						// Left
		SCREEN_WIDTH,				// Right
		SCREEN_HEIGHT,				// Bottom
		0,							// Top
		-1.0,						// Z Near
		1.0 );						// Z Far
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::End2D
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Ends 2D Draw
// 説明:
//		2D描画の終わり
//------------------------------------------------------------------------------
void RendererGL::End2D( void )
{
	// Reset Matrix Settings
	// マトリクスの設定を戻す
	glMatrixMode( GL_PROJECTION );	// Select The Projection Matrix
	glPopMatrix();					// Pop Previous Matrix
	glMatrixMode( GL_MODELVIEW );	// Select The Model View Matrix
	glPopMatrix();					// Pop Previous Matrix

	glEnable( GL_DEPTH_TEST );
	glEnable(GL_LIGHTING);
	//glEnable( GL_CULL_FACE );
	glDepthMask( 1 );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::End2D
// Arguments:
//		bool
// Return Value:
//		void
// Description:
//		Ends 2D Draw
// 説明:
//		2D描画の終わり
//------------------------------------------------------------------------------
bool RendererGL::ToggleWireframe( void )
{
	if( m_wireframeEnabled )
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		m_wireframeEnabled = false;
	}

	else
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		m_wireframeEnabled = true;
	}

	return m_wireframeEnabled;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::SetCullBack
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Sets Cull Face to Back
// 説明:
//		裏面を表示しない
//------------------------------------------------------------------------------
void RendererGL::SetCullBack( void )
{
	glEnable( GL_CULL_FACE );
	m_cullFace = GL_BACK;
	glCullFace( m_cullFace );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::SetCullFront
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Sets Cull Face to Front
// 説明:
//		表面を表示しない
//------------------------------------------------------------------------------
void RendererGL::SetCullFront( void )
{
	glEnable( GL_CULL_FACE );
	m_cullFace = GL_FRONT;
	glCullFace( m_cullFace );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::DisableCull
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Disables Culling
// 説明:
//		全部表示
//------------------------------------------------------------------------------
void RendererGL::DisableCull( void )
{
	glDisable( GL_CULL_FACE );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RendererGL::GetCullFace
// Arguments:
//		void
// Return Value:
//		int
// Description:
//		Gets Cull Face Setting
// 説明:
//		Cull表示設定を取得
//------------------------------------------------------------------------------
int RendererGL::GetCullFace( void )
{
	return m_cullFace;
}
