#pragma once
//------------------------------------------------------------------------------
// Title:			SceneGL
// File Name:		sceneGL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
#ifndef SCENE_GL_H_INCLUDED
#define SCENE_GL_H_INCLUDED

//------------------------------------------------------------------------------
// FORWARD DECLARATIONS
//------------------------------------------------------------------------------
template < class T >
class List;

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class SceneGL
{
public:
	//--------------------------------------
	// ENUMERATES
	//--------------------------------------
	enum DrawPriority
	{
		DrawOutsideList,	// Not Included in List
		DrawFirst,			// Draw First
		DrawBefore3D,		// Draw Before 3D
		DrawDuring3D,		// Draw During 3D
		DrawAfter3D,		// Draw After 3D
		DrawBefore2D,		// Draw Before 2D
		DrawDuring2D,		// Draw During 2D
		DrawAfter2D,		// Draw After 2D
		DrawPost			// Draw Post
	};

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor / Destructor
	SceneGL( DrawPriority priority );
	virtual ~SceneGL();

	// General Functions
	virtual void Init( void ) = 0;
	virtual void Uninit( void ) = 0;
	virtual void Update( void ) = 0;
	virtual void Draw( void ) = 0;
	void Release( void );

	// Transformation Functions
	virtual void SetPosition( Vector3 pos );
	virtual Vector3 GetPosition( void );
	virtual void SetRotation( Vector3 rot );
	virtual Vector3 GetRotation( void );
	virtual void SetScale( Vector3 scl );
	virtual Vector3 GetScale( void );

	// Static Functions
	static void UpdateAll( void );
	static void DrawAll( void );
	static void DrawAll2D( void );
	static void DrawAll3D( void );
	static void ReleaseAll( void );

protected:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	Vector3 m_pos;
	Vector3 m_rot;
	Vector3 m_scl;
	DrawPriority m_drawPriority;

private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	static List< SceneGL* > m_sceneList;
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif