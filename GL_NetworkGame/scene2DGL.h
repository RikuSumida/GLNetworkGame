#pragma once
//------------------------------------------------------------------------------
// Title:			Scene2DGL
// File Name:		scene2DGL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/04/22
//------------------------------------------------------------------------------
#ifndef SCENE_2D_GL_H_INCLUDED
#define SCENE_2D_GL_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "sceneGL.h"

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class Scene2DGL : public SceneGL
{
public:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	static const int BASE_WIDTH	= 1280;		// Base 2D Screen Width
	static const int BASE_HEIGHT = 720;		// Base 2D Screen Height

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor / Destructor
	Scene2DGL( DrawPriority priority = DrawDuring2D );
	~Scene2DGL();

	// Static Functions
	static Scene2DGL* Create( float xPos, float yPos, float width, float height, const char* texName, DrawPriority priority = DrawDuring2D );

	// General Functions
	void Init( void );
	void Uninit( void );
	void Update( void );
	void Draw( void );

private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	float m_width, m_height;
	GLuint m_texture;
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif