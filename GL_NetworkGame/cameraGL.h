#pragma once
//------------------------------------------------------------------------------
// Title:			CameraGL
// File Name:		camera.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/13
// Updated:			2016/05/13
//------------------------------------------------------------------------------
#ifndef CAMERA_GL_H_INCLUDED
#define CAMERA_GL_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// CLASS
//------------------------------------------------------------------------------
class CameraGL
{
public:
	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Constructor / Destructor
	CameraGL();
	~CameraGL();

	// General Functions
	virtual void Update( void );
	void Set( void );

	// Get Functions
	Vector3 GetPosition( void );
	Vector3 GetFocus( void );
	Vector3 GetRotation( void );
	Vector3 GetViewVec( void );

protected:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	// Camera Variables
	float m_dist;					// Distance from Camera to Focus Point
	Vector3 m_pos;					// Camera Position
	Vector3 m_focus;				// Camera Focus Position
	Vector3 m_rot;					// Camera Rotation
	Vector3 m_upVec;				// Camera Up Vector

private:
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	// Constants
	float m_fov;					// Camera Field of View
	float m_nearZ;					// Camera Near Z
	float m_farZ;					// Camera Far Z
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif