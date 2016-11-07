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
// 説明:
//		テクスチャの読込
//------------------------------------------------------------------------------
GLuint TextureManager::Load( const char* texName )
{
	// Return if Name is Null
	// 名前がNullの場合、Nullを返す
	if( !texName )
	{
		return 0;
	}

	// Check if Texture Already Exists
	// テクスチャがすでに存在しているかどうかを確認
	for( unsigned int count = 0; count < g_textures.size(); count++ )
	{
		if( g_textures[ count ].name == texName )
		{
			g_textures[ count ].useCount++;
			return g_textures[ count ].texture;
		}
	}

	// Texture Pointer
	// テクスチャのポインタ
	GLuint texture = 0;

	// Create Texture
	// テクスチャ再生
	texture = TextureGL::CreateTexture( texName );
	if( texture == 0 )
	{
		return 0;
	}

	// Add New Texture Data
	// テクスチャデータを追加する
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
// 説明:
//		テクスチャの解放
//------------------------------------------------------------------------------
void TextureManager::Release( GLuint& texture )
{
	// Return if Texture is Null, Return
	// テクスチャがNullの場合、Return
	if( !texture )
	{
		return;
	}

	// Check if Texture Exists
	// テクスチャが存在しているかどうかを確認
	for( unsigned int count = 0; count < g_textures.size(); count++ )
	{
		if( g_textures[ count ].texture == texture )
		{
			g_textures[ count ].useCount--;
			
			// If Texture No Longer Used, Release
			// テクスチャがもうつかわれて
			if( !g_textures[ count ].useCount )
			{
				// Release Texture
				// テクスチャの解放
				glDeleteTextures( 1, &texture );

				// Clear Texture Data
				// テクスチャデータをクリア
				g_textures.erase( g_textures.begin() + count );
			}

			// Break from  Loop
			// ループからBreak
			break;
		}
	}

	// Set Texture to Null
	// テクスチャをNullに設定
	texture = 0;
}