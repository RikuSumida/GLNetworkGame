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
// 説明:
//		SceneGLのコンストラクタ
//------------------------------------------------------------------------------
SceneGL::SceneGL( DrawPriority priority ) : m_drawPriority( priority )
{
	m_scl = Vector3( 1.0f, 1.0f, 1.0f );

	// Check if Outside List
	// リストの外かどうか
	if( priority == DrawOutsideList )
	{
		return;
	}

	// If First In List
	// リストの最初の場合
	if( m_sceneList.Empty() )
	{
		m_sceneList.PushFront( this );
		return;
	}

	// Check for Middle of List Placement
	// リスト内の配置
	for( List< SceneGL* >::Iterator it = m_sceneList.Begin(); !it.AtEnd(); it++ )
	{
		if( this->m_drawPriority < ( *it )->m_drawPriority )
		{
			m_sceneList.Insert( this, it );
			return;
		}
	}

	// Last Item of List
	// リストの最後
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
// 説明:
//		SceneGLのデストラクタ
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
// 説明:
//		Sceneの解放
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
// 説明:
//		Sceneの位置を設定する
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
// 説明:
//		Sceneの位置を習得する
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
// 説明:
//		Sceneの回転を設定する
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
// 説明:
//		Sceneの回転を習得する
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
// 説明:
//		Sceneのスケールを設定する
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
// 説明:
//		Sceneのスケールを習得する
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
// 説明:
//		全て更新
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
// 説明:
//		全て描画
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
// 説明:
//		全て2D描画
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
// 説明:
//		全て3D描画
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
// 説明:
//		全ての終了と解放処理
//------------------------------------------------------------------------------
void SceneGL::ReleaseAll( void )
{
	while( !m_sceneList.Empty() )
	{
		m_sceneList.Front()->Release();
	}
}