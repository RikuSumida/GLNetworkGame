//------------------------------------------------------------------------------
// Title:			CameraGL
// File Name:		cameraGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/02/28
// Updated:			2016/04/25
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "gameFunctions.h"
#include "cameraGL.h"

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
#define BASE_FOV			( PI * 0.25f )
#define BASE_NEAR_Z			( 0.1f )
#define BASE_FAR_Z			( 1000.0f )

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		CameraGL::CameraGL
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Camera Constructor
// ����:
//		�J�����̃R���X�g���N�^
//------------------------------------------------------------------------------
CameraGL::CameraGL() :
	m_dist( 15.0f ),
	m_nearZ( BASE_NEAR_Z ),
	m_farZ( BASE_FAR_Z ),
	m_fov( BASE_FOV )
{
	m_upVec = Vector3( 0.0f, 1.0f, 0.0f );
	m_pos = Vector3( 0.0f, 10.0f, 0.0f );
	m_rot.y = PI;
	m_rot.x = PI * 0.1f;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		CameraGL::~CameraGL
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Camera Destructor
// ����:
//		�J�����̃f�X�g���N�^
//------------------------------------------------------------------------------
CameraGL::~CameraGL()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		CameraGL::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Updates Camera
// ����:
//		�J�����X�Vs
//------------------------------------------------------------------------------
void CameraGL::Update( void )
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		CameraGL::Set
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Sets Camera
// ����:
//		�J�����ݒ�
//------------------------------------------------------------------------------
void CameraGL::Set( void )
{
	// Projection Matrix Settings
	// ���e�s��ݒ�
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	gluPerspective(
		45.0f,											// FOV
		( float )SCREEN_WIDTH / ( float )SCREEN_HEIGHT,	// Aspect Ratio
		m_nearZ,										// Near Z
		m_farZ );										// Far Z

	// View Matrix Settings
	// �r���[�s��ݒ�
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	m_pos = PointTransMatrix( Vector3( 0.0f, 0.0f, -m_dist ), m_rot, m_focus );

	gluLookAt(
		m_pos.x, m_pos.y, m_pos.z,						// Camera Position  
		m_focus.x, m_focus.y, m_focus.z,				// Focus Point
		m_upVec.x, m_upVec.y, m_upVec.z );				// Camera Up Vector
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Camera::GetPosition
// Arguments:
//		void
// Return Value:
//		D3DXVECTOR3
// Description:
//		Get Camera Position
// ����:
//		�J�����̈ʒu���K��
//------------------------------------------------------------------------------
Vector3 CameraGL::GetPosition( void )
{
	return m_pos;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Camera::GetFocus
// Arguments:
//		void
// Return Value:
//		D3DXVECTOR3
// Description:
//		Get Camera Focus Point
// ����:
//		�J�����̒����_���K��
//------------------------------------------------------------------------------
Vector3 CameraGL::GetFocus( void )
{
	return m_focus;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Camera::GetRotation
// Arguments:
//		void
// Return Value:
//		D3DXVECTOR3
// Description:
//		Get Camera Rotation
// ����:
//		�J�����̉�]���K��
//------------------------------------------------------------------------------
Vector3 CameraGL::GetRotation( void )
{
	return m_rot;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Camera::GetViewVec
// Arguments:
//		void
// Return Value:
//		D3DXVECTOR3
// Description:
//		Get Camera View Vector
// ����:
//		�J�����̃r���[�x�N�g��
//------------------------------------------------------------------------------
Vector3 CameraGL::GetViewVec( void )
{
	Vector3 viewVec = m_focus - m_pos;
	viewVec.Normalize();
	return viewVec;
}
