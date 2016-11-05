//------------------------------------------------------------------------------
// Title:			LightGL
// File Name:		LightGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/27
// Updated:			2016/05/27
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "lightGL.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::LightGL
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Light Constructor
// 説明:
//		Lightのコンストラクタ
//------------------------------------------------------------------------------
LightGL::LightGL() :
	m_isEnabled( true )
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::~LightGL
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Light Destructor
// 説明:
//		Lightのデストラクタ
//------------------------------------------------------------------------------
LightGL::~LightGL()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::Enable
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Enables Light
// 説明:
//		Lightを有効にする
//------------------------------------------------------------------------------
void LightGL::Enable( void )
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	m_isEnabled = true;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::Disable
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Disables Light
// 説明:
//		Lightを無効にする
//------------------------------------------------------------------------------
void LightGL::Disable( void )
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	m_isEnabled = false;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::IsEnabled
// Arguments:
//		bool
// Return Value:
//		void
// Description:
//		Gets Light Enabled Status
// 説明:
//		Lightを有効かどうか
//------------------------------------------------------------------------------
bool LightGL::IsEnabled( void )
{
	return m_isEnabled;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		LightGL::Set
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Sets Light
// 説明:
//		Light設定
//------------------------------------------------------------------------------
void LightGL::Set( void )
{
	if( m_isEnabled )
	{
		GLfloat lightPosition[ 4 ] = { 1.0f, 1.0f, 1.0f, 0.0f };	//光源の位置 Direction Light
		GLfloat lightAmbient[ 3 ] = { 1.0f, 1.0f, 1.0f };			//環境光
		GLfloat lightDiffuse[ 3 ] = { 1.0f, 1.0f, 1.0f };			//拡散光
		GLfloat lightSpecular[ 3 ] = { 1.0f, 1.0f, 1.0f };			//鏡面光
		GLfloat lightDirection[ 3 ] = { 0.7f, 0.7f, 0.7f };

		glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse );
		glLightfv( GL_LIGHT0, GL_AMBIENT, lightAmbient );
		glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpecular );

		GLfloat global_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );

		//GLfloat lightPosition[ 4 ] = { 0.0f, 10.0f, 0.0f, 1.0f }; //光源の位置
		//glLightf( GL_LIGHT0, GL_SPOT_CUTOFF,  30.0f );// スポットライトの絞り（デフォルト 180.0）
		//glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 0.1f );// スポットライトの中心からの減衰の度合い（デフォルト 0 )
		//glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
	}
}
