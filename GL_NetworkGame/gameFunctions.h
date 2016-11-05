#pragma once
//------------------------------------------------------------------------------
// Title:			GameFunctions
// File Name:		gameFunctions.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/06/09
// Updated:			2016/06/09
//------------------------------------------------------------------------------
#ifndef GAME_FUNCTIONS_H_INCLUDED
#define GAME_FUNCTIONS_H_INCLUDED

//------------------------------------------------------------------------------
// PROTOTYPES
//------------------------------------------------------------------------------
//--------------------------------------
// Vector Functions
//--------------------------------------
Vector2 Vec2Interpolate( Vector2 v0, Vector2 v1, float t );
Vector2 Vec2Interpolate( Vector2 v0, Vector2 v1, float t, float t0, float t1 );

//--------------------------------------
// Curve Functions
//--------------------------------------
float CalcBezierCurve4( float p0, float p1, float p2, float p3, float t );
Vector2 CalcBezierCurve4( Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t );
Vector2 CalcHermiteCurve( Vector2 p0, Vector2 p1, Vector2 v0, Vector2 v1, float t );
Vector3 CalcHermiteCurve( Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t );

//--------------------------------------
// Other Functions
//--------------------------------------
float FloatInterpolate( float f0, float f1, float t, float t0, float t1 );
float RotOpt( float ang );
Vector3 PointTransMatrix( Vector3 point, Vector3 rot, Vector3 trans );
Vector3 Vec3Proj( Vector3 onVec, Vector3 fromVec );

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif