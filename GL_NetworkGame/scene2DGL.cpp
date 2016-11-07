//------------------------------------------------------------------------------
// Title:			Scene2DGL
// File Name:		scene2DGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2DGL.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Scene2DGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		Scene2DGL Constructor
// 説明:
//		Scene2DGLのコンストラクタ
//------------------------------------------------------------------------------
Scene2DGL::Scene2DGL( DrawPriority priority ) :
	m_width( 0 ),
	m_height( 0 ),
	m_texture( 0 ),
	SceneGL( priority )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::~Scene2DGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		Scene2DGL Deconstructor
// 説明:
//		Scene2DGLのデストラクタ
//------------------------------------------------------------------------------
Scene2DGL::~Scene2DGL()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Create
// Arguments:
//		void
// Return Value:
//		Scene2DGL*
// Description:
//		Creates Scene2DGL
// 説明:
//		Scene2DGLの作成
//------------------------------------------------------------------------------
Scene2DGL* Scene2DGL::Create( float xPos, float yPos, float width, float height, const char* texName, DrawPriority priority )
{
	// Create Scene
	// Sceneの作成
	Scene2DGL* scene = new Scene2DGL( priority );

	// Size Settings
	// サイズ設定
	scene->m_pos.x = xPos;
	scene->m_pos.y = yPos;
	scene->m_width = width;
	scene->m_height = height;

	// Create Texture
	// テクスチャの作成
	scene->m_texture = TextureManager::Load( texName );

	// Initialization
	// 初期化
	scene->Init();

	return scene;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Init
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Initializes Scene2DGL
// 説明:
//		Scene2DGLの初期化処理
//------------------------------------------------------------------------------
void Scene2DGL::Init( void )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Scene2DGL
// 説明:
//		Scene2DGLの終了処理
//------------------------------------------------------------------------------
void Scene2DGL::Uninit( void )
{
	// Delete Loaded Texture
	// 読み込んだテクスチャを解放
	TextureManager::Release( m_texture );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Scene2DGL
// 説明:
//		Scene2DGLの更新処理
//------------------------------------------------------------------------------
void Scene2DGL::Update( void )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene2DGL::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws Scene2DGL
// 説明:
//		Scene2DGLの描画処理
//------------------------------------------------------------------------------
void Scene2DGL::Draw( void )
{
	// Begin Drawing
	// 描画開始
	
	glBindTexture( GL_TEXTURE_2D, m_texture );
	glBegin( GL_TRIANGLE_STRIP );
	{
		// Top Right
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 0.0f );
		glVertex3f( m_pos.x + m_width * 0.5f, m_pos.y - m_height * 0.5f, 0.0 );

		// Bottom Right
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 1.0f, 1.0f );
		glVertex3f( m_pos.x + m_width * 0.5f, m_pos.y + m_height * 0.5f, 0.0 );

		// Top Left
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 0.0f );
		glVertex3f( m_pos.x - m_width * 0.5f, m_pos.y - m_height * 0.5f, 0.0 );

		// Bottom Left
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glTexCoord2f( 0.0f, 1.0f );
		glVertex3f( m_pos.x - m_width * 0.5f, m_pos.y + m_height * 0.5f, 0.0 );
	}
	glEnd();
	glBindTexture( GL_TEXTURE_2D, 0 );

	// End Drawing
	// 描画終了
}