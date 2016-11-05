//------------------------------------------------------------------------------
// Title:			Game Functions
// File Name:		gameFunctions.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/06/09
// Updated:			2016/06/09
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "gameVariables.h"
#include "gameFunctions.h"

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
namespace
{
	Matrix44 mtxBezier = Matrix44(
		Vector4( 1, 0, 0, 0 ),
		Vector4( -3, 3, 0, 0 ),
		Vector4( 3, -6, 3, 0 ),
		Vector4( -1, 3, -3, 1 ) );

	Matrix44 mtxHermite = Matrix44(
		Vector4( 2, -2, 1, 1 ),
		Vector4( -3, 3, -2, -1 ),
		Vector4( 0, 0, 1, 0 ),
		Vector4( 1, 0, 0, 0 ) );
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// VECTOR FUNCTIONS
//------------------------------------------------------------------------------
Vector2 Vec2Interpolate( Vector2 v0, Vector2 v1, float t )
{
	Vector2 vec;
	vec.x = v0.x + ( v1.x - v0.x ) * t;
	vec.y = v0.y + ( v1.y - v0.y ) * t;

	return vec;
}

Vector2 Vec2Interpolate( Vector2 v0, Vector2 v1, float t, float t0, float t1 )
{
	Vector2 hold;
	float deltaT = ( ( t - t0 ) / ( t1 - t0 ) );	// How Far Along Point ( 0 ~ 1 )
	hold.x = v0.x + ( v1.x - v0.x ) * deltaT;
	hold.y = v0.y + ( v1.y - v0.y ) * deltaT;

	return hold;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// CURVE FUNCTIONS
//------------------------------------------------------------------------------
float CalcBezierCurve4( float p0, float p1, float p2, float p3, float t )
{
	//float pt = ( 1 - t ) * ( 1 - t ) * ( 1 - t ) * p0 + 3 * ( 1 - t ) * ( 1 - t )
	//	* t * p1 + 3 * ( 1 - t ) * t * t * p2 + t * t * t * p3;

	Vector4 vP = Vector4( p0, p1, p2, p3 );
	Vector4 vT = Vector4( 1, t, t * t, t * t * t );

	return vT.MultColumnVec4( mtxBezier * vP );
}

Vector2 CalcBezierCurve4( Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t )
{
	//float pt = ( 1 - t ) * ( 1 - t ) * ( 1 - t ) * p0 + 3 * ( 1 - t ) * ( 1 - t )
	//	* t * p1 + 3 * ( 1 - t ) * t * t * p2 + t * t * t * p3;

	Vector2 pt;
	Vector4 vP;
	Vector4 vT = Vector4( 1, t, t * t, t * t * t );

	// Point Calculation
	vP = Vector4( p0.x, p1.x, p2.x, p3.x );
	pt.x = vT.MultColumnVec4( mtxBezier * vP );
	vP = Vector4( p0.y, p1.y, p2.y, p3.y );
	pt.y = vT.MultColumnVec4( mtxBezier * vP );

	return pt;
}

Vector2 CalcHermiteCurve( Vector2 p0, Vector2 p1, Vector2 v0, Vector2 v1, float t )
{
	/*Vector2 pt = ( t - 1 ) * ( t - 1 ) * ( 2 * t + 1 ) * p0 + t * t * ( 3 - 2 * t ) * p1 +
		( 1 - t ) * ( 1 - t ) * t * v0 + ( t - 1 ) * t * t * v1;*/

	Vector2 pt;
	Vector4 vH;
	Vector4 vT = Vector4( t * t * t, t * t, t, 1 );

	// Point Calculation
	vH = Vector4( p0.x, p1.x, v0.x, v1.x );
	pt.x = vT.MultColumnVec4( mtxHermite * vH );
	vH = Vector4( p0.y, p1.y, v0.y, v1.y );
	pt.y = vT.MultColumnVec4( mtxHermite * vH );

	return pt;
}

Vector3 CalcHermiteCurve( Vector3 p0, Vector3 p1, Vector3 v0, Vector3 v1, float t )
{
	/*Vector2 pt = ( t - 1 ) * ( t - 1 ) * ( 2 * t + 1 ) * p0 + t * t * ( 3 - 2 * t ) * p1 +
		( 1 - t ) * ( 1 - t ) * t * v0 + ( t - 1 ) * t * t * v1;*/

	Vector3 pt;
	Vector4 vH;
	Vector4 vT = Vector4( t * t * t, t * t, t, 1 );

	// Point Calculation
	vH = Vector4( p0.x, p1.x, v0.x, v1.x );
	pt.x = vT.MultColumnVec4( mtxHermite * vH );
	vH = Vector4( p0.y, p1.y, v0.y, v1.y );
	pt.y = vT.MultColumnVec4( mtxHermite * vH );
	vH = Vector4( p0.z, p1.z, v0.z, v1.z );
	pt.z = vT.MultColumnVec4( mtxHermite * vH );

	return pt;
}

//------------------------------------------------------------------------------
// OTHER FUNCTIONS
//------------------------------------------------------------------------------
float FloatInterpolate( float f0, float f1, float t, float t0, float t1 )
{
	float deltaT = ( ( t - t0 ) / ( t1 - t0 ) );	// How Far Along Point ( 0 ~ 1 )
	return f0 + ( f1 - f0 ) * deltaT;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		RotOpt
// Arguments:
//		float ang	Angle to Check - �m�F����p�x
// Return Value:
//		float ang
// Description:
//		Optimizes Angle for Rotation. Sets bounds to -PI to PI.
// ����:
//		��]�̂��߂Ɋp�x���œK������B-PI����PI�܂łɂ���B
//------------------------------------------------------------------------------
float RotOpt( float ang )
{
	if( ang < -PI )
	{
		ang += PI * 2.0f;
	}

	else if( ang > PI )
	{
		ang -= PI * 2.0f;
	}

	return ang;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		PointTransMatrix
// Arguments:
//		Vector3 point		Start Point
//		Vector3 rot			Rotation
//		Vector3 trans		Translation
// Return Value:
//		Vector3 point
// Description:
//		Transformation Matrix for Moving a Point
// ����:
//		�_�̏ꏊ���ړ�����ϊ��s��
//------------------------------------------------------------------------------
Vector3 PointTransMatrix( Vector3 point, Vector3 rot, Vector3 trans )
{
	// >>>World Matrix
	// �����h�}�g���b�N�X
	Matrix44 mtxWorld44;
	mtxWorld44.SetIdentity();

	// >>>Transformation Matrices
	// �g�����X�t�H�[���[�V�����}�g���b�N�X
	Matrix44 mtxRot44, mtxTrans44;

	//>>> Matrix Translation
	// �ʒu�𔽉f
	mtxTrans44.SetTranslation( trans.x, trans.y, trans.z );
	mtxWorld44 *= mtxTrans44;

	//>>> Matrix Rotation
	// ��]�𔽉f
	mtxRot44.SetRotation( rot.x, rot.y, rot.z );
	mtxWorld44 *= mtxRot44;

	//>>> Matrix Translation
	// �ʒu�𔽉f
	mtxTrans44.SetTranslation( point.x, point.y, point.z );
	mtxWorld44 *= mtxTrans44;

	// Get New Point
	// �V�������W���擾
	point = mtxWorld44.GetVec3Column( 3 );

	return point;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Vec3Proj
// Arguments:
//		Vector3 onVec		Vector to Project On
//		Vector3 fromVec		Vector to Project From
// Return Value:
//		Vector3 projVec
// Description:
//		Projects fromVec onto onVec and returns projVec
// ����:
//		fromVec��onVec�ɓ��e����
//------------------------------------------------------------------------------
Vector3 Vec3Proj( Vector3 onVec, Vector3 fromVec )
{
	// Normalize On Vector
	// onVec �𐳋K��
	onVec.Normalize();

	// Projection Vector
	// ���e�x�N�g��
	Vector3 projVec = onVec;

	// Calculation Variables
	// �v�Z�ϐ�
	float dot = onVec.Dot( fromVec );
	float mag = onVec.GetMagnitude();

	// If Magnitude of Vector is 0, Return
	// �x�N�g���̒������O�̏ꍇ�A�֐��I��
	if( mag == 0 )
	{
		return projVec;
	}

	// Scalar to Calculate Projection Vector
	float scalar = dot / mag;

	// Projection Vector Length
	projVec *= scalar;

	// Return Projection Vector
	return projVec;
}