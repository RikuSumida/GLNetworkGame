#pragma once
//------------------------------------------------------------------------------
// Title:			GameVariables
// File Name:		gameVariables.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/22
// Updated:			2016/05/16
//------------------------------------------------------------------------------
#ifndef GAME_VARIABLES_H_INCLUDED
#define GAME_VARIABLES_H_INCLUDED

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include <math.h>

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
//#define DX_GAME
#ifdef DX_GAME
#define VECTOR2		D3DXVECTOR2
#define VECTOR3		D3DXVECTOR3
#define VECTOR4		D3DXVECTOR4
#define COLOR		D3DXCOLOR
#define PI			D3DX_PI
#else
struct VECTOR2{ float x, y; };
struct VECTOR3{ float x, y, z; };
struct VECTOR4{ float x, y, z, w; };
struct COLOR{ float r, g, b, a; };
#define PI			( 3.141592654f )
#endif

//------------------------------------------------------------------------------
// STRUCTURES
//------------------------------------------------------------------------------
//--------------------------------------
// Vector2
//--------------------------------------
struct Vector2 : public VECTOR2
{
	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2( float x, float y )
	{
		this->x = x;
		this->y = y;
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Vector2 operator +( const Vector2& vec2 )
	{
		Vector2 vecHold;

		vecHold.x = this->x + vec2.x;
		vecHold.y = this->y + vec2.y;

		return vecHold;
	}

	Vector2 operator -( const Vector2& vec2 )
	{
		Vector2 vecHold;

		vecHold.x = this->x - vec2.x;
		vecHold.y = this->y - vec2.y;

		return vecHold;
	}

	Vector2 operator *( const Vector2& vec2 )
	{
		Vector2 vecHold;

		vecHold.x = this->x * vec2.x;
		vecHold.y = this->y * vec2.y;

		return vecHold;
	}

	Vector2 operator *( const float& f )
	{
		Vector2 vecHold;
	
		vecHold.x = this->x * f;
		vecHold.y = this->y * f;
	
		return vecHold;
	}

	Vector2 operator /( const Vector2& vec2 )
	{
		Vector2 vecHold;

		vecHold.x = this->x / vec2.x;
		vecHold.y = this->y / vec2.y;

		return vecHold;
	}

	Vector2 operator /( const float& f )
	{
		Vector2 vecHold;

		vecHold.x = this->x / f;
		vecHold.y = this->y / f;

		return vecHold;
	}

	Vector2 operator +=( const Vector2& vec2 )
	{
		this->x += vec2.x;
		this->y += vec2.y;

		return *this;
	}

	Vector2 operator /=( const float& f )
	{
		this->x /= f;
		this->y /= f;

		return *this;
	}

	Vector2 operator *=( const float& f )
	{
		this->x *= f;
		this->y *= f;

		return *this;
	}

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	// Rotates Vector 90 Degrees and Returns Sign
	float DotRot( const Vector2& vec2 )
	{
		// Returns Sign ( if Vec on left or right )
		return x * -vec2.y + y * vec2.x;
	}
};

//--------------------------------------
// Vector3
//--------------------------------------
struct Vector3 : public VECTOR3
{
	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Vector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3( float x, float y, float z )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3( VECTOR3 vec3 )
	{
		this->x = vec3.x;
		this->y = vec3.y;
		this->z = vec3.z;
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Vector3 operator +( const Vector3& vec3 )
	{
		Vector3 vecHold;
		vecHold.x = this->x + vec3.x;
		vecHold.y = this->y + vec3.y;
		vecHold.z = this->z + vec3.z;

		return vecHold;
	}

	Vector3 operator -( const Vector3& vec3 )
	{
		Vector3 vecHold;
		vecHold.x = this->x - vec3.x;
		vecHold.y = this->y - vec3.y;
		vecHold.z = this->z - vec3.z;

		return vecHold;
	}

	Vector3 operator *( const Vector3& vec3 )
	{
		Vector3 vecHold;
		vecHold.x = this->x * vec3.x;
		vecHold.y = this->y * vec3.y;
		vecHold.z = this->z * vec3.z;

		return vecHold;
	}

	Vector3 operator *( const float& f )
	{
		Vector3 vecHold;
		vecHold.x = this->x * f;
		vecHold.y = this->y * f;
		vecHold.z = this->z * f;

		return vecHold;
	}

	Vector3 operator /( const float& f )
	{
		Vector3 vecHold;
		vecHold.x = this->x / f;
		vecHold.y = this->y / f;
		vecHold.z = this->z / f;

		return vecHold;
	}

	Vector3 operator /( const Vector3& vec3 )
	{
		Vector3 vecHold;
		vecHold.x = this->x / vec3.x;
		vecHold.y = this->y / vec3.y;
		vecHold.z = this->z / vec3.z;

		return vecHold;
	}

	Vector3 operator +=( const Vector3& vec3 )
	{
		this->x += vec3.x;
		this->y += vec3.y;
		this->z += vec3.z;

		return *this;
	}

	Vector3 operator -=( const Vector3& vec3 )
	{
		this->x -= vec3.x;
		this->y -= vec3.y;
		this->z -= vec3.z;

		return *this;
	}

	Vector3 operator *=( const Vector3& vec3 )
	{
		this->x *= vec3.x;
		this->y *= vec3.y;
		this->z *= vec3.z;

		return *this;
	}

	Vector3 operator *=( const float& f )
	{
		this->x *= f;
		this->y *= f;
		this->z *= f;

		return *this;
	}

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	Vector3 Normalize( void )
	{
		// Calculate Magnitude of Vector
		// ベクトルの長さを計算
		float mag = sqrtf( x * x + y * y + z * z );
		x /= mag;
		y /= mag;
		z /= mag;

		return *this;
	}

	float GetMagnitude( void )
	{
		return sqrtf( x * x + y * y + z * z );
	}

	float Dot( const Vector3& vec3 )
	{
		return this->x * vec3.x + this->y * vec3.y + this->z * vec3.z;
	}

	Vector3 Cross( const Vector3& vec3 )
	{
		Vector3 vec;

		vec.x = this->y * vec3.z - this->z * vec3.y;
		vec.y = this->z * vec3.x - this->x * vec3.z;
		vec.z = this->x * vec3.y - this->y * vec3.x;

		return vec;
	}
};

//--------------------------------------
// Vector4
//--------------------------------------
struct Vector4 : public VECTOR4
{
	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Vector4()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	Vector4( Vector3 vec3 )
	{
		this->x = vec3.x;
		this->y = vec3.y;
		this->z = vec3.z;
		this->w = 1.0f;
	}

	Vector4( Vector3 vec3, float w )
	{
		this->x = vec3.x;
		this->y = vec3.y;
		this->z = vec3.z;
		this->w = w;
	}

	Vector4( float x, float y, float z, float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Vector4 operator +( const Vector4& vec4 )
	{
		Vector4 vecHold;
		vecHold.x = this->x + vec4.x;
		vecHold.y = this->y + vec4.y;
		vecHold.z = this->z + vec4.z;
		vecHold.w = this->w + vec4.w;

		return vecHold;
	}

	Vector4 operator -( const Vector4& vec4 )
	{
		Vector4 vecHold;
		vecHold.x = this->x - vec4.x;
		vecHold.y = this->y - vec4.y;
		vecHold.z = this->z - vec4.z;
		vecHold.w = this->w - vec4.w;

		return vecHold;
	}

	Vector4 operator *( const Vector4& vec4 )
	{
		Vector4 vecHold;
		vecHold.x = this->x * vec4.x;
		vecHold.y = this->y * vec4.y;
		vecHold.z = this->z * vec4.z;
		vecHold.w = this->w * vec4.w;

		return vecHold;
	}

	Vector4 operator /( const Vector4& vec4 )
	{
		Vector4 vecHold;
		vecHold.x = this->x / vec4.x;
		vecHold.y = this->y / vec4.y;
		vecHold.z = this->z / vec4.z;
		vecHold.w = this->w / vec4.w;

		return vecHold;
	}

	Vector4 operator +=( const Vector4& vec4 )
	{
		this->x += vec4.x;
		this->y += vec4.y;
		this->z += vec4.z;
		this->w += vec4.w;

		return *this;
	}

	Vector4 operator -=( const Vector4& vec4 )
	{
		this->x -= vec4.x;
		this->y -= vec4.y;
		this->z -= vec4.z;
		this->w -= vec4.w;

		return *this;
	}

	Vector4 operator *=( const Vector4& vec4 )
	{
		this->x *= vec4.x;
		this->y *= vec4.y;
		this->z *= vec4.z;
		this->w *= vec4.w;

		return *this;
	}

	Vector4 operator *=( const float& f )
	{
		this->x *= f;
		this->y *= f;
		this->z *= f;
		this->w *= f;

		return *this;
	}

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	void Normalize( void )
	{
		// Calculate Magnitude of Vector
		// ベクトルの長さを計算
		float mag = sqrtf( x * x + y * y + z * z + w * w );
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
		this->w /= mag;
	}

	float GetMagnitude( void )
	{
		return sqrtf( x * x + y * y + z * z + w * w );
	}

	float MultColumnVec4( Vector4 vec4 )
	{
		return	this->x * vec4.x +
				this->y * vec4.y +
				this->z * vec4.z +
				this->w * vec4.w;
	}
};

//--------------------------------------
// Vector4Color
//--------------------------------------
struct Vector4Color : public COLOR
{
	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Vector4Color()
	{
		this->r = 1.0f;
		this->g = 1.0f;
		this->b = 1.0f;
		this->a = 1.0f;
	}

	Vector4Color( float r, float g, float b, float a )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Vector4Color( Vector3 vec3 )
	{
		this->r = vec3.x;
		this->g = vec3.y;
		this->b = vec3.z;
		this->a = 1.0f;
	}

	Vector4Color( Vector3 vec3, float a )
	{
		this->r = vec3.x;
		this->g = vec3.y;
		this->b = vec3.z;
		this->a = a;
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Vector4Color operator +=( const Vector4Color& vec4col )
	{
		this->r += vec4col.r;
		this->g += vec4col.g;
		this->b += vec4col.b;
		this->a += vec4col.a;

		return *this;
	}
};

//--------------------------------------
// ColorRGBA
//--------------------------------------
struct ColorRGBA
{
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	int r, g, b, a;

	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	ColorRGBA() :
		r( 0 ),
		g( 0 ),
		b( 0 ),
		a( 0 )
	{}

	ColorRGBA( int r, int g, int b )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	ColorRGBA( int r, int g, int b, int a )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
};

//--------------------------------------
// Matrix44
//--------------------------------------
struct Matrix44
{
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	union
	{
		float data[ 4 ][ 4 ];
		struct
		{
			float	_11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
		};
	};

	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Matrix44()
	{
		for( int rowCount = 0; rowCount < 4; rowCount++ )
		{
			for( int colCount = 0; colCount < 4; colCount++ )
			{
				data[ rowCount ][ colCount ] = 0;
			}
		}
	}

	Matrix44( Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4 )
	{
		this->SetRow( row1, 0 );
		this->SetRow( row2, 1 );
		this->SetRow( row3, 2 );
		this->SetRow( row4, 3 );
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Matrix44 operator =( const Matrix44& mtx )
	{
		for( int rowCount = 0; rowCount < 4; rowCount++ )
		{
			for( int colCount = 0; colCount < 4; colCount++ )
			{
				this->data[ rowCount ][ colCount ] =
					mtx.data[ rowCount ][ colCount ];
			}
		}

		return *this;
	}

	Matrix44 operator *( const Matrix44& mtx )
	{
		Matrix44 hold;

		for( int rowCount = 0; rowCount < 4; rowCount++ )
		{
			for( int colCount = 0; colCount < 4; colCount++ )
			{
				for( int multCount = 0; multCount < 4; multCount++ )
				{
					hold.data[ rowCount ][ colCount ] +=
						data[ rowCount ][ multCount ] * mtx.data[ multCount ][ colCount ];
				}
			}
		}

		return hold;
	}

	Matrix44 operator *=( const Matrix44& mtx )
	{
		*this = *this * mtx;
		return *this;
	}

	Vector4 operator*( const Vector4& vec4 )
	{
		Vector4 vec;
		vec.x = this->data[ 0 ][ 0 ] * vec4.x +
				this->data[ 0 ][ 1 ] * vec4.y +
				this->data[ 0 ][ 2 ] * vec4.z +
				this->data[ 0 ][ 3 ] * vec4.w;

		vec.y = this->data[ 1 ][ 0 ] * vec4.x +
				this->data[ 1 ][ 1 ] * vec4.y +
				this->data[ 1 ][ 2 ] * vec4.z +
				this->data[ 1 ][ 3 ] * vec4.w;

		vec.z = this->data[ 2 ][ 0 ] * vec4.x +
				this->data[ 2 ][ 1 ] * vec4.y +
				this->data[ 2 ][ 2 ] * vec4.z +
				this->data[ 2 ][ 3 ] * vec4.w;

		vec.w = this->data[ 3 ][ 0 ] * vec4.x +
				this->data[ 3 ][ 1 ] * vec4.y +
				this->data[ 3 ][ 2 ] * vec4.z +
				this->data[ 3 ][ 3 ] * vec4.w;

		return vec;
	}

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	void SetIdentity( void )
	{
		for( int rowCount = 0; rowCount < 4; rowCount++ )
		{
			for( int colCount = 0; colCount < 4; colCount++ )
			{
				if( rowCount == colCount )
				{
					data[ rowCount ][ colCount ] = 1;
				}

				else
				{
					data[ rowCount ][ colCount ] = 0;
				}
			}
		}
	}
	
	///// Column Base Matrices
	// Set Translation Matrix
	void SetTranslation( float x, float y, float z )
	{
		SetIdentity();
		data[ 0 ][ 3 ] = x;
		data[ 1 ][ 3 ] = y;
		data[ 2 ][ 3 ] = z;
	}

	// Set Rotation Matrix in Order of X first, then Y, then Z last
	void SetRotation( float x, float y, float z )
	{
		SetIdentity();
		
		data[ 0 ][ 0 ] = cosf( y ) * cosf( z );
		data[ 0 ][ 1 ] = sinf( x ) * sinf( y ) * cosf( z ) - cosf( x ) * sinf( z );
		data[ 0 ][ 2 ] = cosf( x ) * sinf( y ) * cosf( z ) + sinf( x ) * sinf( z );
		
		data[ 1 ][ 0 ] = cosf( y ) * sinf( z );
		data[ 1 ][ 1 ] = sinf( x ) * sinf( y ) * sinf( z ) + cosf( x ) * cosf( z );
		data[ 1 ][ 2 ] = cosf( x ) * sinf( y ) * sinf( z ) - sinf( x ) * cosf( z );

		data[ 2 ][ 0 ] = -sinf( y );
		data[ 2 ][ 1 ] = sinf( x ) * cosf( y );
		data[ 2 ][ 2 ] = cosf( x ) * cosf( y );
	}

	void MakeRotationX( float x )
	{
		SetIdentity();

		data[ 1 ][ 1 ] = cosf( x );
		data[ 1 ][ 2 ] = -sinf( x );

		data[ 2 ][ 1 ] = sinf( x );
		data[ 2 ][ 2 ] = cosf( x );
	}

	void MakeRotationY( float y )
	{
		SetIdentity();

		data[ 0 ][ 0 ] = cosf( y );
		data[ 0 ][ 2 ] = sinf( y );

		data[ 2 ][ 0 ] = -sinf( y );
		data[ 2 ][ 2 ] = cosf( y );
	}

	void MakeRotationZ( float z )
	{
		SetIdentity();

		data[ 0 ][ 0 ] = cosf( z );
		data[ 0 ][ 1 ] = -sinf( z );

		data[ 1 ][ 0 ] = sinf( z );
		data[ 1 ][ 1 ] = cosf( z );
	}

	// Set Scale Matrix
	void SetScale( float x, float y, float z )
	{
		SetIdentity();
		data[ 0 ][ 0 ] = x;
		data[ 1 ][ 1 ] = y;
		data[ 2 ][ 2 ] = z;
	}

	// Get Matrix Rows and Columns
	Vector3 GetVec3Row( int y )
	{
		if( y < 0 ) y = 0;
		if( y > 3 ) y = 3;
		return Vector3( data[ y ][ 0 ], data[ y ][ 1 ], data[ y ][ 2 ] );
	}

	Vector4 GetVec4Row( int y )
	{
		if( y < 0 ) y = 0;
		if( y > 3 ) y = 3;
		return Vector4( data[ y ][ 0 ], data[ y ][ 1 ], data[ y ][ 2 ], data[ y ][ 3 ] );
	}

	Vector3 GetVec3Column( int x )
	{
		if( x < 0 ) x = 0;
		if( x > 3 ) x = 3;
		return Vector3( data[ 0 ][ x ], data[ 1 ][ x ], data[ 2 ][ x ] );
	}

	Vector4 GetVec4Column( int x )
	{
		if( x < 0 ) x = 0;
		if( x > 3 ) x = 3;
		return Vector4( data[ 0 ][ x ], data[ 1 ][ x ], data[ 2 ][ x ], data[ 3 ][ x ] );
	}

	// Set Matrix Rows and Columns
	void SetRow( Vector3 vec3, int y )
	{
		if( y < 0 ) y = 0;
		if( y > 3 ) y = 3;
		data[ y ][ 0 ] = vec3.x;
		data[ y ][ 1 ] = vec3.y;
		data[ y ][ 2 ] = vec3.z;
	}

	void SetRow( Vector4 vec4, int y )
	{
		if( y < 0 ) y = 0;
		if( y > 3 ) y = 3;
		data[ y ][ 0 ] = vec4.x;
		data[ y ][ 1 ] = vec4.y;
		data[ y ][ 2 ] = vec4.z;
		data[ y ][ 3 ] = vec4.w;
	}

	void SetColumn( Vector3 vec3, int x )
	{
		if( x < 0 ) x = 0;
		if( x > 3 ) x = 3;

		data[ 0 ][ x ] = vec3.x;
		data[ 1 ][ x ] = vec3.y;
		data[ 2 ][ x ] = vec3.z;
	}

	void SetColumn( Vector4 vec4, int x )
	{
		if( x < 0 ) x = 0;
		if( x > 3 ) x = 3;
		
		data[ 0 ][ x ] = vec4.x;
		data[ 1 ][ x ] = vec4.y;
		data[ 2 ][ x ] = vec4.z;
		data[ 3 ][ x ] = vec4.w;
	}
};

//--------------------------------------
// PointPlane3
//--------------------------------------
struct Plane3
{
	Vector3 point[ 3 ];
	Vector3 norm;

	Plane3()
	{}

	Plane3( Vector3 vec1, Vector3 vec2, Vector3 vec3 )
	{
		point[ 0 ] = vec1;
		point[ 1 ] = vec2;
		point[ 2 ] = vec3;
	}
};

//--------------------------------------
// PointPlane4
//--------------------------------------
struct Plane4
{
	Vector3 point[ 4 ];
	Vector3 norm;

	Plane4()
	{}

	Plane4( Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4 )
	{
		point[ 0 ] = vec1;
		point[ 1 ] = vec2;
		point[ 2 ] = vec3;
		point[ 3 ] = vec4;
	}
};

//--------------------------------------
// Quaternion
//--------------------------------------
struct Quaternion
{
	//--------------------------------------
	// VARIABLES
	//--------------------------------------
	union
	{
		struct
		{
			float x, y, z, w;
		};

		float data[ 4 ];
	};

	//--------------------------------------
	// CONSTRUCTORS
	//--------------------------------------
	Quaternion()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	Quaternion( float x, float y, float z, float w )
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion( Vector4 vec4 )
	{
		this->x = vec4.x;
		this->y = vec4.y;
		this->z = vec4.z;
		this->w = vec4.w;
	}

	//--------------------------------------
	// OPERATORS
	//--------------------------------------
	Quaternion operator*( const Quaternion& quat )
	{
		Quaternion hold;

		hold.w = ( this->w * quat.w -
			this->x * quat.x -
			this->y * quat.y -
			this->z * quat.z );

		hold.x = ( this->w * quat.x +
			this->x * quat.x +
			this->y * quat.y -
			this->z * quat.z );

		hold.y = ( this->w * quat.y -
			this->x * quat.z +
			this->y * quat.w +
			this->z * quat.x );

		hold.z = ( this->w * quat.z +
			this->x * quat.y -
			this->y * quat.x +
			this->z * quat.w );

		return hold;
	}


	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	void Normalize( void )
	{
		// Calculate Magnitude of Vector
		// ベクトルの長さを計算
		float mag = sqrtf( x * x + y * y + z * z + w * w );
		this->x /= mag;
		this->y /= mag;
		this->z /= mag;
		this->w /= mag;
	}

	Vector3 GetEulerAngle( void )
	{
		Vector3 vec;

		vec.x = atan2f( 2 * ( x * y + z * w ), 1 - 2 * ( y * y + z * z ) );
		vec.y = asinf( 2 * ( x * z - w * y ) );
		vec.z = atan2f( 2 * ( x * w + y * z ), 1 - 2 * ( z * z + w * w ) );

		return vec;
	}

	float Dot( const Quaternion& quat )
	{
		return this->x * quat.x + this->y * quat.y + this->z * quat.z + this->w * quat.w;
	}

	Quaternion Slerp( const Quaternion& quat, float t )
	{
		Quaternion hold;
		float theta = acosf( this->Dot( quat ) );
		float weightFrom = sinf( theta * ( 1.0f - t ) ) / sinf( theta );
		float weightTo = sinf( theta * t ) / sinf( theta );

		for( int i = 0; i < 4; i++ )
		{
			hold.data[ i ] = this->data[ i ] * weightFrom +
				quat.data[ i ] * weightTo;
		}

		return hold;
	}

};

//------------------------------------------------------------------------------
// INLINE FUNCTIONS
//------------------------------------------------------------------------------
//--------------------------------------
// Operations
//--------------------------------------
inline Vector2 operator*( float other, Vector2 vec ){ return vec *= other; }
inline Vector3 operator*( float other, Vector3 vec ){ return vec *= other; }
inline Vector4 operator*( float other, Vector4 vec ){ return vec *= other; }

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif