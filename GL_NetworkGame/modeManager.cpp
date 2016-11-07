///------------------------------------------------------------------------------
// Title:			Mode Manager
// File Name:		modeManager.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/07/11
// Updated:			2016/10/01
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "modeManager.h"

namespace
{
//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
	Mode* g_mode = nullptr;
}

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		ModeManager::SetMode
// Arguments:
//		Mode* mode
// Return Value:
//		void
// Description:
//		Sets New Mode
// ����:
//		���[�h�̐ݒ�
//------------------------------------------------------------------------------
void ModeManager::SetMode( Mode* mode )
{
	// Start Loading Screen
	// ���[�h��ʂ̎n�܂�
	//LoadScreen::Begin();

	// Uninitialize Previous Mode
	// �O�̃��[�h�I������
	if( g_mode )
	{
		g_mode->Uninit();
		delete g_mode;
		g_mode = nullptr;
	}

	// Initialize New Mode
	// �V�������[�h��������
	if( mode )
	{
		g_mode = mode;
		g_mode->Init();	
	}

	// End Loading Screen
	// ���[�h��ʂ̏I���
	//LoadScreen::End();
}

//------------------------------------------------------------------------------
// Fuction Name:
//		ModeManager::GetMode
// Arguments:
//		void
// Return Value:
//		Mode* mode
// Description:
//		Gets New Mode
// ����:
//		���[�h���擾
//------------------------------------------------------------------------------
Mode* ModeManager::GetMode( void )
{
	return g_mode;
}