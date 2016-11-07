#pragma once
//------------------------------------------------------------------------------
// Title:			Scene3DGL
// File Name:		scene3DGL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
#ifndef SCENE_3D_GL_H_INCLUDED
#define SCENE_3D_GL_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "sceneGL.h"

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class Scene3DGL : public SceneGL
{
public:
	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor / Destructor
	Scene3DGL();
	~Scene3DGL();

	// Static Functions
	static Scene3DGL* Create( Vector3 pos, float width, float depth, const char* texName );

	// General Functions
	virtual void Init( void );
	virtual void Uninit( void );
	virtual void Update( void );
	virtual void Draw( void );

protected:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	int m_vtxNum;				// Number of Vertices
	int m_primNum;				// Number of Primitives
	int m_idxNum;				// Number of Indices

	Vertex3D* m_vtxBuff;		// Vertex Buffer
	int* m_idxBuff;				// Index Buffer
	GLuint m_texture;			// Texture Pointer
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif