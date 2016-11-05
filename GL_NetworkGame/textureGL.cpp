//------------------------------------------------------------------------------
// Title:			TextureGL
// File Name:		textureGL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/05/11
// Updated:			2016/05/11
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "main.h"
#include "textureGL.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		TextureGL::CreateTexture
// Arguments:
//		const char* fileName
// Return Value:
//		GLuint
// Description:
//		Creates Texture
// ����:
//		�e�N�X�`���̍쐬
//------------------------------------------------------------------------------
GLuint TextureGL::CreateTexture( const char* fileName )
{
	int width;		// Image Width
	int height;		// Image Height
	int comp;		// Image Comp Type

	unsigned char* image = stbi_load( fileName, &width, &height, &comp, STBI_rgb_alpha );

	// If Image Failed to Load
	// �C���[�W�ǂݍ��݂̎��s
	if( !image )
	{
		return 0;
	}

	/*// Set Texture Type
	// �e�N�X�`���^�C�v�̐ݒ�
	if( comp == 3 )
	{
		type = GL_RGBA;
	}
	
	else if( comp == 4 )
	{
		type = GL_RGBA;
	}
	
	else
	{
		return 0;
	}*/

	// Create OpenGL Texture from Data
	// �f�[�^����OpenGL�e�N�X�`�������
	GLuint texture = 0;
	glGenTextures( 1, &texture );
	
	// Bind Texture to Edit Contents
	// �e�N�X�`���̒��g��ς��邽�߂Ƀo�C���h����
	glBindTexture( GL_TEXTURE_2D, texture );
	
	// Load Data to Texture
	// �f�[�^���e�N�X�`���ɓ����
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );


	// Texture Settings
	// �e�N�X�`���̐ݒ�
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

	glBindTexture( GL_TEXTURE_2D, 0 );

	stbi_image_free( image );

	return texture;
}