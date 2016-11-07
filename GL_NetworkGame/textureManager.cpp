//------------------------------------------------------------------------------
// Title:			TextureManager
// File Name:		textureManager.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/04/28
// Updated:			2016/11/07
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "textureManager.h"
#include "textureGL.h"
#include <vector>
using namespace std;

//------------------------------------------------------------------------------
// STRUCTURES
//------------------------------------------------------------------------------
struct TextureData
{
	string name;				// Texture File Pass Name
	GLuint texture;				// Texture Pointer
	int useCount;				// Count of Items Using Texture
};

//------------------------------------------------------------------------------
// VARIABLES
//------------------------------------------------------------------------------
vector< TextureData > g_textures;

//------------------------------------------------------------------------------
// Fuction Name:
//		TextureManager::Load
// Arguments:
//		const char* texName
// Return Value:
//		GLuint
// Description:
//		Loads a Texture
// ����:
//		�e�N�X�`���̓Ǎ�
//------------------------------------------------------------------------------
GLuint TextureManager::Load( const char* texName )
{
	// Return if Name is Null
	// ���O��Null�̏ꍇ�ANull��Ԃ�
	if( !texName )
	{
		return 0;
	}

	// Check if Texture Already Exists
	// �e�N�X�`�������łɑ��݂��Ă��邩�ǂ������m�F
	for( unsigned int count = 0; count < g_textures.size(); count++ )
	{
		if( g_textures[ count ].name == texName )
		{
			g_textures[ count ].useCount++;
			return g_textures[ count ].texture;
		}
	}

	// Texture Pointer
	// �e�N�X�`���̃|�C���^
	GLuint texture = 0;

	// Create Texture
	// �e�N�X�`���Đ�
	texture = TextureGL::CreateTexture( texName );
	if( texture == 0 )
	{
		return 0;
	}

	// Add New Texture Data
	// �e�N�X�`���f�[�^��ǉ�����
	TextureData texData;
	texData.name = texName;
	texData.texture = texture;
	texData.useCount = 1;
	g_textures.push_back( texData );

	return texture;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		TextureManager::Release
// Arguments:
//		GLuint texture
// Return Value:
//		void
// Description:
//		Releases a Texture
// ����:
//		�e�N�X�`���̉��
//------------------------------------------------------------------------------
void TextureManager::Release( GLuint& texture )
{
	// Return if Texture is Null, Return
	// �e�N�X�`����Null�̏ꍇ�AReturn
	if( !texture )
	{
		return;
	}

	// Check if Texture Exists
	// �e�N�X�`�������݂��Ă��邩�ǂ������m�F
	for( unsigned int count = 0; count < g_textures.size(); count++ )
	{
		if( g_textures[ count ].texture == texture )
		{
			g_textures[ count ].useCount--;
			
			// If Texture No Longer Used, Release
			// �e�N�X�`��������������
			if( !g_textures[ count ].useCount )
			{
				// Release Texture
				// �e�N�X�`���̉��
				glDeleteTextures( 1, &texture );

				// Clear Texture Data
				// �e�N�X�`���f�[�^���N���A
				g_textures.erase( g_textures.begin() + count );
			}

			// Break from  Loop
			// ���[�v����Break
			break;
		}
	}

	// Set Texture to Null
	// �e�N�X�`����Null�ɐݒ�
	texture = 0;
}