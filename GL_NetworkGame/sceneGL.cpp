//------------------------------------------------------------------------------
// Title:			SceneGL
// File Name:		sceneGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/11/07
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "sceneGL.h"
#include "list.h"

//------------------------------------------------------------------------------
// STATIC VARIABLES
//------------------------------------------------------------------------------
List< SceneGL* > SceneGL::m_sceneList;

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::SceneGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		SceneGL Constructor
// ����:
//		SceneGL�̃R���X�g���N�^
//------------------------------------------------------------------------------
SceneGL::SceneGL( DrawPriority priority ) : m_drawPriority( priority )
{
	m_scl = Vector3( 1.0f, 1.0f, 1.0f );

	// Check if Outside List
	// ���X�g�̊O���ǂ���
	if( priority == DrawOutsideList )
	{
		return;
	}

	// If First In List
	// ���X�g�̍ŏ��̏ꍇ
	if( m_sceneList.Empty() )
	{
		m_sceneList.PushFront( this );
		return;
	}

	// Check for Middle of List Placement
	// ���X�g���̔z�u
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		if( this->m_drawPriority < ( *it )->m_drawPriority )
		{
			m_sceneList.Insert( this, it );
			return;
		}
	}

	// Last Item of List
	// ���X�g�̍Ō�
	m_sceneList.PushBack( this );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::~SceneGL()
// Arguments:
//		n/a
// Return Value:
//		n/a
// Description:
//		SceneGL Deconstructor
// ����:
//		SceneGL�̃f�X�g���N�^
//------------------------------------------------------------------------------
SceneGL::~SceneGL()
{
	m_sceneList.Remove( this );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::Release
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Releases Scene
// ����:
//		Scene�̉��
//------------------------------------------------------------------------------
void SceneGL::Release( void )
{
	Uninit();
	delete this;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::SetPosition
// Arguments:
//		Vector3 pos
// Return Value:
//		void
// Description:
//		Sets Scene Position
// ����:
//		Scene�̈ʒu��ݒ肷��
//------------------------------------------------------------------------------
void SceneGL::SetPosition( Vector3 pos )
{
	m_pos = pos;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::GetPosition
// Arguments:
//		void
// Return Value:
//		Vector3
// Description:
//		Gets Scene Position
// ����:
//		Scene�̈ʒu���K������
//------------------------------------------------------------------------------
Vector3 SceneGL::GetPosition( void )
{
	return m_pos;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::SetRotation
// Arguments:
//		Vector3 rot
// Return Value:
//		void
// Description:
//		Sets Model Rotation
// ����:
//		Scene�̉�]��ݒ肷��
//------------------------------------------------------------------------------
void SceneGL::SetRotation( Vector3 rot )
{
	m_rot = rot;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::GetRotation
// Arguments:
//		void
// Return Value:
//		Vector3
// Description:
//		Gets Scene Rotation
// ����:
//		Scene�̉�]���K������
//------------------------------------------------------------------------------
Vector3 SceneGL::GetRotation( void )
{
	return m_rot;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::SetScale
// Arguments:
//		Vector3 scl
// Return Value:
//		void
// Description:
//		Sets Model Scale
// ����:
//		Scene�̃X�P�[����ݒ肷��
//------------------------------------------------------------------------------
void SceneGL::SetScale( Vector3 scl )
{
	m_scl = scl;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::GetScale
// Arguments:
//		void
// Return Value:
//		Vector3
// Description:
//		Gets Scene Scale
// ����:
//		Scene�̃X�P�[�����K������
//------------------------------------------------------------------------------
Vector3 SceneGL::GetScale( void )
{
	return m_scl;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::UpdateAll
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Update All
// ����:
//		�S�čX�V
//------------------------------------------------------------------------------
void SceneGL::UpdateAll( void )
{
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		( *it )->Update();
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::DrawAll
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws All
// ����:
//		�S�ĕ`��
//------------------------------------------------------------------------------
void SceneGL::DrawAll( void )
{
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		( *it )->Draw();
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::DrawAll2D
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws All 2D
// ����:
//		�S��2D�`��
//------------------------------------------------------------------------------
void SceneGL::DrawAll2D( void )
{
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		if( ( *it )->m_drawPriority > DrawPriority::DrawAfter3D )
		{
			( *it )->Draw();
		}
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::DrawAll3D
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Draws All 3D
// ����:
//		�S��3D�`��
//------------------------------------------------------------------------------
void SceneGL::DrawAll3D( void )
{
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		if( ( *it )->m_drawPriority < DrawPriority::DrawBefore2D )
		{
			( *it )->Draw();
		}

		else
		{
			break;
		}
	}
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SceneGL::ReleaseAll
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Releases All
// ����:
//		�S�Ă̏I���Ɖ������
//------------------------------------------------------------------------------
void SceneGL::ReleaseAll( void )
{
	while( !m_sceneList.Empty() )
	{
		m_sceneList.Front()->Release();
	}
}