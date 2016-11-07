#pragma once
//------------------------------------------------------------------------------
// Title:			SoundAL
// File Name:		soundAL.h
// Creator:			Nicholas Dahms
// Creation Date:	2016/06/17
// Updated:			2016/06/20
//------------------------------------------------------------------------------
#ifndef SOUND_AL_H_INCLUDED
#define SOUND_AL_H_INCLUDED

//------------------------------------------------------------------------------
// NAMESPACE
//------------------------------------------------------------------------------
namespace SoundAL
{
	//--------------------------------------
	// ENUMERATES
	//--------------------------------------
	// Sound Labels
	enum Label
	{
		// BGM
		BGM_000,

		// SE
		//SE_EXPLOSION_SOFT,

		// LabelMax
		LabelMax
	};

	//--------------------------------------
	// FUNCTIONS
	//--------------------------------------
	bool Init( HWND hWnd );
	void Uninit( void );

	// Sound Functions
	int Play( Label label );
	int PlayPosition( SoundAL::Label label, float x, float y, float z );
	void PlaySwap( Label label );
	void Pause( Label label );
	void Rewind( Label label );
	bool IsPlaying( Label label );
	void Stop( Label label );
	void StopIdx( int idx );
	void StopAll( void );

	// Listenter Functions
	void SetListenerPosition( float x, float y, float z );
	void SetListenerOrientation( float atX, float atY, float atZ, float upX, float upY, float upZ );
	
};

//------------------------------------------------------------------------------
// HEADER END
//------------------------------------------------------------------------------
#endif