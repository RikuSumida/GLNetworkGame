#pragma once
//------------------------------------------------------------------------------
// Title:			Vertex
// File Name:		vertex.h
// Creator:			Nicholas Dahms
// Creation Date:	2015/02/23
// Updated:			2016/03/01
//------------------------------------------------------------------------------
#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "gameVariables.h"

//------------------------------------------------------------------------------
// STRUCTURES
//------------------------------------------------------------------------------
// Declaration Structure
struct Vertex2D
{
	Vector3 pos;			// Vector Position
	Vector4Color col;		// Color
	Vector2 tex;			// Texture Position
};

struct Vertex3D
{
	Vector3 pos;			// Vector Position
	Vector3 norm;			// Vertex Normal
	Vector4Color col;		// Vertex Color
	Vector2 tex;			// Texture Position
};

struct Vertex3DBlend
{
	Vector3 pos;			// Vector Position
	Vector4 blendIdx;		// Blend Indices
	Vector4 blendWeight;	// Blend Weights
	Vector3 norm;			// Vertex Normal
	Vector2 tex;			// Texture Position
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif
