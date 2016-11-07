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
// ����:
//		Scene2DGL�̃R���X�g���N�^
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
// ����:
//		Scene2DGL�̃f�X�g���N�^
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
// ����:
//		Scene2DGL�̍쐬
//------------------------------------------------------------------------------
Scene2DGL* Scene2DGL::Create( float xPos, float yPos, float width, float height, const char* texName, DrawPriority priority )
{
	// Create Scene
	// Scene�̍쐬
	Scene2DGL* scene = new Scene2DGL( priority );

	// Size Settings
	// �T�C�Y�ݒ�
	scene->m_pos.x = xPos;
	scene->m_pos.y = yPos;
	scene->m_width = width;
	scene->m_height = height;

	// Create Texture
	// �e�N�X�`���̍쐬
	scene->m_texture = TextureManager::Load( texName );

	// Initialization
	// ������
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
// ����:
//		Scene2DGL�̏���������
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
// ����:
//		Scene2DGL�̏I������
//------------------------------------------------------------------------------
void Scene2DGL::Uninit( void )
{
	// Delete Loaded Texture
	// �ǂݍ��񂾃e�N�X�`�������
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
// ����:
//		Scene2DGL�̍X�V����
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
// ����:
//		Scene2DGL�̕`�揈��
//------------------------------------------------------------------------------
void Scene2DGL::Draw( void )
{
	// Begin Drawing
	// �`��J�n
	
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
	// �`��I��
}