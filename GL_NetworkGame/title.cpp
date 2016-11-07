//------------------------------------------------------------------------------
// Title:			Title
// File Name:		title.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/07/11
// Updated:			2016/11/07
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "title.h"
#include "input.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Title
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Constructor
// ����:
//		Title�̃R���X�g���N�^
//------------------------------------------------------------------------------
Title::Title()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::~Title
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Destructor
// ����:
//		Title�̃f�X�g���N�^
//------------------------------------------------------------------------------
Title::~Title()
{}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Init
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Initialization
// ����:
//		Title�̏�����
//------------------------------------------------------------------------------
void Title::Init( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Uninitialization
// ����:
//		Title�̏I������
//------------------------------------------------------------------------------
void Title::Uninit( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Update
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Update
// ����:
//		Title�̍X�V����
//------------------------------------------------------------------------------
void Title::Update( void )
{
}

//------------------------------------------------------------------------------
// Fuction Name:
//		Title::Draw
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Title Draw
// ����:
//		Title�̕`�揈��
//------------------------------------------------------------------------------
void Title::Draw( void )
{
	// Begin 3D Draw
	// 3D�`��J�n
	{
		//m_camera->Set();


	}
	// End 3D Draw
	// 3D�`��I������

	// Begin 2D Draw
	// 2D�`��J�n
	GetGameApp()->GetRenderer()->Begin2D();
	{
			
	}
	GetGameApp()->GetRenderer()->End2D();
	// End 2D Draw
	// 2D�`��I������

}