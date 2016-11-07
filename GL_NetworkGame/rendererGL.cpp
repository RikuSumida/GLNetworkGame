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
// ����:
//		RendererGL�̃R���X�g���N�^
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
// ����:
//		RendererGL�̃f�X�g���N�^
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
// ����:
//		Renderer�̏�����
//------------------------------------------------------------------------------
bool RendererGL::Init( HINSTANCE hInstance, HWND hWnd, bool bWindow )
{
	// Get DC
	// DC���K��
	if( !( m_dc = GetDC( hWnd ) ) )
	{
		return false;
	}

	try
	{
		// Pixel Format
		// �s�N�Z���̃t�H�}�b�g
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
		// �ݒ�ʂ�̃s�N�Z���t�H�}�b�g��I��
		int format = ChoosePixelFormat( m_dc, &pfd );
		if( format == 0 )
			throw "";

		// Set Pixel Format
		// �s�N�Z���t�H�}�b�g�̐ݒ�
		if( !SetPixelFormat( m_dc, format, &pfd ) )
			throw"";

		// Create Rendering Context
		// �����_�����O�R���e�L�X�g�쐬
		m_glrc = wglCreateContext( m_dc );
		if( !m_glrc )
			throw "";

		// Make Rendering Context Active
		// �����_�����O�R���e�L�X�g��L���ɂ���
		if( !wglMakeCurrent( m_dc, m_glrc ) )
			throw "";
	}

	catch( ... )
	{
		ReleaseDC( hWnd, m_dc );
		return false;
	}

	// Set Windows Variables
	// Windows�̕ϐ��ݒ�
	m_hWnd = hWnd;
	m_hInstance = hInstance;

	// View Settings Based on Window Size
	// ��ʕ\���ݒ�
	m_screenWidth = SCREEN_WIDTH;
	m_screenHeight = SCREEN_HEIGHT;
	OnScreenResize( m_screenWidth, m_screenHeight );

	// GL Initial Settings
	// �������ݒ�
	glShadeModel( GL_SMOOTH );								// Enable Smooth Shading
	glClearColor( 0.0f, 1.0f, 1.0f, 1.0f );					// Clear Color
	glClearDepth( 1.0f );									// Depth Buffer Setup

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// Perspective Correction

	// Display Settings
	// �\���ݒ�
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
// ����:
//		Renderer�̏I������
//------------------------------------------------------------------------------
void RendererGL::Uninit( void )
{
	// Release Rendering Context
	// �����_�����O�R���e�L�X�g
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
// ����:
//		��ʂ̕����K��
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
// ����:
//		��ʂ̍������K��
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
// ����:
//		��ʂ̂�T�C�Y�������ɐݒ���X�V
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
// ����:
//		�`��̊J�n
//------------------------------------------------------------------------------
void RendererGL::Begin( void )
{
	// Clear Screen
	// ��ʃN���A
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
// ����:
//		�`��̏I��
//------------------------------------------------------------------------------
void RendererGL::End( void )
{
	// Swap Buffers
	// �o�b�t�@�؂�ւ�
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
// ����:
//		2D�`��̊J�n
//------------------------------------------------------------------------------
void RendererGL::Begin2D( void )
{
	glDisable(GL_LIGHTING);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( 0 );
	//glDisable( GL_CULL_FACE );

	// Projection Matrix Setting
	// �v���W�F�N�V�����̃}�g���N�X�̐ݒ�
	glMatrixMode( GL_PROJECTION );	// Select The Projection Matrix
	glPushMatrix();					// Push Current Matrix
	glLoadIdentity();				// Initialize Matrix

	// Model View Matrix Setting
	// ���f���E�r���[�̃}�g���N�X�̐ݒ�
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
// ����:
//		2D�`��̏I���
//------------------------------------------------------------------------------
void RendererGL::End2D( void )
{
	// Reset Matrix Settings
	// �}�g���N�X�̐ݒ��߂�
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
// ����:
//		2D�`��̏I���
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
// ����:
//		���ʂ�\�����Ȃ�
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
// ����:
//		�\�ʂ�\�����Ȃ�
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
// ����:
//		�S���\��
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
// ����:
//		Cull�\���ݒ���擾
//------------------------------------------------------------------------------
int RendererGL::GetCullFace( void )
{
	return m_cullFace;
}
