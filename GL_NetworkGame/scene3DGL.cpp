//------------------------------------------------------------------------------
// Title:			Scene3DGL
// File Name:		scene3DGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "scene3DGL.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Scene3DGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		Scene3DGL Constructor
// ����:
//		Scene3DGL�̃R���X�g���N�^
//------------------------------------------------------------------------------
Scene3DGL::Scene3DGL() :
	m_idxBuff( nullptr ),
	m_vtxBuff( nullptr ),
	m_texture( 0 ),
	m_idxNum( 0 ),
	m_primNum( 0 ),
	m_vtxNum( 0 ),
	SceneGL( DrawPriority::DrawDuring3D )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::~Scene3DGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		Scene3DGL Deconstructor
// ����:
//		Scene3DGL�̃f�X�g���N�^
//------------------------------------------------------------------------------
Scene3DGL::~Scene3DGL()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Create
// Arguments:
//		Vector3 pos
//		float width
//		float depth
//		char* texName
// Return Value:
//		Scene3D*
// Description:
//		Creates a Scene3D
// ����:
//		Scene3D�̍쐬
//------------------------------------------------------------------------------
Scene3DGL* Scene3DGL::Create( Vector3 pos, float width, float depth, const char* texName )
{
	// Create a Scene3D
	// Scene3D�̍쐬
	Scene3DGL *scene;
	scene = new Scene3DGL;

	// Set Variables
	// �ϐ��̐ݒ�
	scene->m_pos = pos;

	// Temporarily Store Size in Scale
	// �ꎞ�I�ɃT�C�Y������
	scene->m_scl.x = width;
	scene->m_scl.y = 1.0f;
	scene->m_scl.z = depth;

	// Load Texture
	// �e�N�X�`���̓Ǎ�
	scene->m_texture = TextureManager::Load( texName );

	// Initialize Scene
	// ������
	scene->Init();

	return scene;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Init
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Initializes Scene3DGL
// ����:
//		Scene3DGL�̏���������
//------------------------------------------------------------------------------
void Scene3DGL::Init( void )
{
	// Set Variables
	// �ϐ��̐ݒ�
	m_vtxNum = 4;
	m_primNum = 2;
	m_idxNum = m_primNum + 2;

	// Create Vertex Buffer
	// ���_�o�b�t�@�Đ�
	m_vtxBuff = new Vertex3D[ m_vtxNum ];

	// Create Index Buffer
	// �C���f�b�N�X�o�b�t�@���m��
	m_idxBuff = new int[ m_idxNum ];

	// Set Vertex Data
	for( int count = 0; count < 4; count++ )
	{
		m_vtxBuff[ count ].norm = Vector3( 0.0f, 1.0f, 0.0f );
		m_vtxBuff[ count ].col = Vector4Color( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// Texture UV
	m_vtxBuff[ 0 ].tex.x =
		m_vtxBuff[ 1 ].tex.x = 0.0f;
	m_vtxBuff[ 2 ].tex.x =
		m_vtxBuff[ 3 ].tex.x = 1.0f;

	m_vtxBuff[ 0 ].tex.y =
		m_vtxBuff[ 2 ].tex.y = 1.0f;
	m_vtxBuff[ 1 ].tex.y =
		m_vtxBuff[ 3 ].tex.y = 0.0f;

	// Position
	m_vtxBuff[ 0 ].pos.z =
		m_vtxBuff[ 2 ].pos.z = 0.5f * m_scl.z;
	m_vtxBuff[ 1 ].pos.z =
		m_vtxBuff[ 3 ].pos.z = -0.5f * m_scl.z;

	m_vtxBuff[ 0 ].pos.x =
		m_vtxBuff[ 1 ].pos.x = -0.5f * m_scl.x;
	m_vtxBuff[ 2 ].pos.x =
		m_vtxBuff[ 3 ].pos.x = 0.5f * m_scl.x;

	m_vtxBuff[ 0 ].pos.y =
		m_vtxBuff[ 1 ].pos.y =
		m_vtxBuff[ 2 ].pos.y =
		m_vtxBuff[ 3 ].pos.y = 0.0f;

	// Set Index Data
	m_idxBuff[ 0 ] = 2;
	m_idxBuff[ 1 ] = 0;
	m_idxBuff[ 2 ] = 3;
	m_idxBuff[ 3 ] = 1;

	// Reset Scaling to 1
	// �X�P�[����1�ɖ߂�
	m_scl = Vector3( 1.0f, 1.0f, 1.0f );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes Scene3DGL
// ����:
//		Scene3DGL�̏I������
//------------------------------------------------------------------------------
void Scene3DGL::Uninit( void )
{
	// Delete Index Buffer
	// �C���f�b�N�X�o�b�t�@�̉��
	if( m_idxBuff )
	{
		delete[] m_idxBuff;
		m_idxBuff = nullptr;
	}

	// Delete Vertex Buffer
	// ���_�o�b�t�@�̉��
	if( m_vtxBuff )
	{
		delete[] m_vtxBuff;
		m_vtxBuff = nullptr;
	}

	// Delete Texture
	// �e�N�X�`���̉��
	TextureManager::Release( m_texture );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Scene3DGL
// ����:
//		Scene3DGL�̍X�V����
//------------------------------------------------------------------------------
void Scene3DGL::Update( void )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Scene3DGL::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws Scene3DGL
// ����:
//		Scene3DGL�̕`�揈��
//------------------------------------------------------------------------------
void Scene3DGL::Draw( void )
{
	// Model View Matrix Setting
	// ���f���E�r���[�̃}�g���N�X�̐ݒ�
	glMatrixMode( GL_MODELVIEW );	// Select The Model View Matrix
	glPushMatrix();					// Push Current Matrix

	// World Matrix Setting
	// ���[���h�}�g���N�X�ݒ�
	glTranslatef( m_pos.x, m_pos.y, m_pos.z );
	glRotatef( m_rot.z, 0.0f, 0.0f, 1.0f );
	glRotatef( m_rot.x, 1.0f, 0.0f, 0.0f );
	glRotatef( m_rot.y, 0.0f, 1.0f, 0.0f );
	glScalef( m_scl.x, m_scl.y, m_scl.z );

	// Draw Indexed Primitive
	// �C���f�b�N�X�`��
	glBindTexture( GL_TEXTURE_2D, m_texture );

	glBegin( GL_TRIANGLE_STRIP );
	for( int idx = 0; idx < m_idxNum; idx++ )
	{
		Vertex3D vtx = m_vtxBuff[ m_idxBuff[ idx ] ];
		glColor4f( vtx.col.r, vtx.col.b, vtx.col.g, vtx.col.a );
		glTexCoord2f( vtx.tex.x, vtx.tex.y );
		glNormal3f( vtx.norm.x, vtx.norm.y, vtx.norm.z );
		glVertex3f( vtx.pos.x, vtx.pos.y, vtx.pos.z );
	}
	glEnd();

	glBindTexture( GL_TEXTURE_2D, 0 );

	// Reset Matrix Settings
	// �}�g���N�X�̐ݒ��߂�
	glMatrixMode( GL_MODELVIEW );	// Select The Model View Matrix
	glPopMatrix();					// Pop Previous Matrix
}