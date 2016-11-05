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
// ����:
//		Light�̃R���X�g���N�^
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
// ����:
//		Light�̃f�X�g���N�^
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
// ����:
//		Light��L���ɂ���
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
// ����:
//		Light�𖳌��ɂ���
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
// ����:
//		Light��L�����ǂ���
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
// ����:
//		Light�ݒ�
//------------------------------------------------------------------------------
void LightGL::Set( void )
{
	if( m_isEnabled )
	{
		GLfloat lightPosition[ 4 ] = { 1.0f, 1.0f, 1.0f, 0.0f };	//�����̈ʒu Direction Light
		GLfloat lightAmbient[ 3 ] = { 1.0f, 1.0f, 1.0f };			//����
		GLfloat lightDiffuse[ 3 ] = { 1.0f, 1.0f, 1.0f };			//�g�U��
		GLfloat lightSpecular[ 3 ] = { 1.0f, 1.0f, 1.0f };			//���ʌ�
		GLfloat lightDirection[ 3 ] = { 0.7f, 0.7f, 0.7f };

		glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDiffuse );
		glLightfv( GL_LIGHT0, GL_AMBIENT, lightAmbient );
		glLightfv( GL_LIGHT0, GL_SPECULAR, lightSpecular );

		GLfloat global_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient );

		//GLfloat lightPosition[ 4 ] = { 0.0f, 10.0f, 0.0f, 1.0f }; //�����̈ʒu
		//glLightf( GL_LIGHT0, GL_SPOT_CUTOFF,  30.0f );// �X�|�b�g���C�g�̍i��i�f�t�H���g 180.0�j
		//glLightf( GL_LIGHT0, GL_SPOT_EXPONENT, 0.1f );// �X�|�b�g���C�g�̒��S����̌����̓x�����i�f�t�H���g 0 )
		//glLightfv( GL_LIGHT0, GL_POSITION, lightPosition );
	}
}
