//------------------------------------------------------------------------------
// Title:			SoundAL
// File Name:		soundAL.cpp
// Creator:			Nicholas Dahms
// Creation Date:	2016/06/17
// Updated:			2016/06/20
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include <Windows.h>		// Windows Header
#include <fstream>			// Filestream
#include "al.h"				// OpenAL
#include "alc.h"			// OpenAL
#include "soundAL.h"

//------------------------------------------------------------------------------
// LIBRARIES
//------------------------------------------------------------------------------
#pragma comment( lib, "OpenAL32.lib" )

//------------------------------------------------------------------------------
// DEFINES
//------------------------------------------------------------------------------
// Note: Base Sources have Direct Index to Buffers
// Setting number of extra sources allow for same buffer to be used with
// additional sources. ( e.g. Multiple SE sounds )
// �m�[�g�F ���\�[�X�����ڂ̃C���f�b�N�X�Ńo�b�t�@�ƌq�����Ă���
// �\�[�X��extra�̐���ݒ肷�邱�Ƃœ����o�b�t�@�𕡐��̃\�[�X�Ŏg����
// �悤�ɂȂ�B�i��F����SE�𕡐��Đ����鎞�j
#define SOURCE_EXTRA			( 10 )
#define SOURCE_NUM				( SoundAL::LabelMax + SOURCE_EXTRA )

#define SOUND_MAX_DISTANCE		( 1600.0f )
#define SOUND_REF_DISTANCE		( 100.0f )

//------------------------------------------------------------------------------
// PROTOTYPES
//------------------------------------------------------------------------------
ALuint GetSourceIdxFromLabel( SoundAL::Label label );
ALuint GetOpenSourceIdx( SoundAL::Label label );
bool LoadWavFile( const char* fileName, ALuint& buffer, HWND hWnd );

namespace
{
//------------------------------------------------------------------------------
// STRUCTURES
//------------------------------------------------------------------------------
	struct SoundParam
	{
		char* fileName;		// Sound File Name
		bool loop;			// If Sound Loops
	};

//------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------
	// Dynamic Library
	HMODULE g_openALModule = NULL;

	// OpenAL Variables
	ALCdevice* g_device = nullptr;
	ALCcontext* g_context = nullptr;

	// Listener Variables
	ALfloat g_listenerPos[] = { 0.0f, 0.0f, 0.0f };		// Position
	ALfloat g_listenerVel[] = { 0.0f, 0.0f, 0.0f };		// Velocity
	ALfloat g_listenerOri[] = { 0.0f, 0.0f, -1.0f,		// At Orientation ( Direction Head is Facing )
								0.0f, 1.0f, 0.0f };		// Up Orientation ( Vector from top of Head )

	// Sound Buffers
	ALuint g_buffer[ SoundAL::LabelMax ];				// Holds Sound Data
	ALuint g_source[ SOURCE_NUM ];						// Sources to Play Sound

	// Sound Label Parameters
	SoundParam g_param[ SoundAL::LabelMax ] =
	{
		// BGM
		{ "./data/bgm/bgm000.wav", true },

		// SE
		//{ "./data/se/sfx_exp_short_soft6.wav", false },
	};
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Init
// Arguments:
//		HWND hWnd
// Return Value:
//		bool
// Description:
//		Initializes SoundAL
// ����:
//		SoundAL�̏�����
//------------------------------------------------------------------------------
bool SoundAL::Init( HWND hWnd )
{
	// Initialize AL Variables
	// AL�ϐ��̏�����
	g_device = alcOpenDevice( NULL );
	if( !g_device )
	{
		MessageBox( hWnd, "Open device error!\n", "Error!", MB_ICONWARNING );
	}

	g_context = alcCreateContext( g_device, NULL );
	alcMakeContextCurrent( g_context );
	if( !g_context )
	{
		MessageBox( hWnd, "Context creation error!\n", "Error!", MB_ICONWARNING );
	}

	// Clear Error Messages
	// �G���[���b�Z�[�W���N���A
	alGetError();

	// Create Buffers
	// �o�b�t�@�����
	alGenBuffers( LabelMax, g_buffer );
	if( alGetError() != AL_NO_ERROR )
	{
		MessageBox( hWnd, "GenBuffer error!\n", "Error!", MB_ICONWARNING );
		return false;
	}

	// Read Files and Set Buffer Data
	// �t�@�C���ǂݍ���ŁA�o�b�t�@�f�[�^�̐ݒ�
	for( int labelCount = 0; labelCount < LabelMax; labelCount++ )
	{
		if( !LoadWavFile( g_param[ labelCount ].fileName, g_buffer[ labelCount ], hWnd ) )
		{
			return false;
		}
	}

	// Generate Sources
	// �\�[�X�̐���
	alGenSources( SOURCE_NUM, &g_source[ 0 ] );
	if( alGetError() != AL_NO_ERROR )
	{
		MessageBox( hWnd, "alutGenSource error!\n", "Error!", MB_ICONWARNING );
		return false;
	}

	// Set Base Sources
	// ���\�[�X�̐ݒ�
	for( int labelCount = 0; labelCount < LabelMax; labelCount++ )
	{
		alSourcei( g_source[ labelCount ], AL_BUFFER, g_buffer[ labelCount ] );			// Place Buffer into Source
		alSourcei( g_source[ labelCount ], AL_LOOPING, g_param[ labelCount ].loop );	// Set Looping
	}
	
	// Source Max Sound Distance
	// �\�[�X�̍ő剹������
	for( int sourceCount = 0; sourceCount < SOURCE_NUM; sourceCount++ )
	{
		alSourcef( g_source[ sourceCount ], AL_MAX_DISTANCE, SOUND_MAX_DISTANCE );
		alSourcef( g_source[ sourceCount ], AL_REFERENCE_DISTANCE, SOUND_REF_DISTANCE );
	}

	// Sound Distance Model
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	// Initial Listener Settings
	alListenerfv( AL_POSITION, g_listenerPos );
	alListenerfv( AL_VELOCITY, g_listenerVel );
	alListenerfv( AL_ORIENTATION, g_listenerOri );

	alSourcef( g_source[ SoundAL::BGM_000 ], AL_GAIN, 0.5f );

	return true;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Uninit
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Uninitializes SoundAL
// ����:
//		SoundAL�̏I������
//------------------------------------------------------------------------------
void SoundAL::Uninit( void )
{
	// Delete Sources and Buffers
	// �\�[�X�ƃo�b�t�@�̍폜
	alDeleteSources( SOURCE_NUM, g_source );
	alDeleteBuffers( SoundAL::LabelMax, g_buffer );

	// Exit
	// �I������
	g_context = alcGetCurrentContext();
	g_device = alcGetContextsDevice( g_context );
	alcMakeContextCurrent( NULL );
	alcDestroyContext( g_context );
	alcCloseDevice( g_device );
}

//------------------------------------------------------------------------------
// SOUND FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Play
// Arguments:
//		Label label
// Return Value:
//		int sourceIdx
// Description:
//		Plays Sound Label
// ����:
//		�����̍Đ�
//------------------------------------------------------------------------------
int SoundAL::Play( SoundAL::Label label )
{
	ALuint idx = GetOpenSourceIdx( label );
	if( idx == -1 )
		return -1;

	// Check if Direct Index
	// �_�C���N�g�E�C���f�b�N�X���ǂ������m�F
	if( idx != label )
	{
		// Get Base Source Settings
		// ���\�[�X�̐ݒ���擾
		ALfloat pitch;
		ALfloat gain;

		alGetSourcef( g_source[ label ], AL_PITCH, &pitch );
		alGetSourcef( g_source[ label ], AL_GAIN, &gain );

		// Set Source Settings if Not Direct
		// �_�C���N�g����Ȃ����̓\�[�X�̐ݒ������
		alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
		alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );				// Set Looping
		alSourcef( g_source[ idx ], AL_PITCH, pitch );
		alSourcef( g_source[ idx ], AL_GAIN, gain );
	}

	// Set Position to Listener Position
	// �ʒu�ݒ�
	ALfloat pos[ 3 ] = { 0 };
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_TRUE );

	// Play
	// �Đ�
	alSourcePlay( g_source[ idx ] );

	return idx;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::PlayPosition
// Arguments:
//		Label label
//		float x
//		float y
//		float z
// Return Value:
//		int sourceIdx
// Description:
//		Plays Sound Label from a Position
// ����:
//		����ʒu���特���̍Đ�
//------------------------------------------------------------------------------
int SoundAL::PlayPosition( SoundAL::Label label, float x, float y, float z )
{
	ALuint idx = GetOpenSourceIdx( label );
	if( idx == -1 )
		return -1;

	// Check if Direct Index
	// �_�C���N�g�E�C���f�b�N�X���ǂ������m�F
	if( idx != label )
	{
		// Get Base Source Settings
		// ���\�[�X�̐ݒ���擾
		ALfloat pitch;
		ALfloat gain;
		
		alGetSourcef( g_source[ label ], AL_PITCH, &pitch );
		alGetSourcef( g_source[ label ], AL_GAIN, &gain );

		// Set Source Settings if Not Direct
		// �_�C���N�g����Ȃ����̓\�[�X�̐ݒ������
		alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
		alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop ); // Set Looping
		alSourcef( g_source[ idx ], AL_PITCH, pitch );
		alSourcef( g_source[ idx ], AL_GAIN, gain );
	}

	// Set Position
	// �ʒu�ݒ�
	ALfloat pos[ 3 ];
	pos[ 0 ] = x;
	pos[ 1 ] = y;
	pos[ 2 ] = z;
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_FALSE );
	alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );	

	// Play
	// �Đ�
	alSourcePlay( g_source[ idx ] );

	return idx;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::PlaySwap
// Arguments:
//		Label label
// Return Value:
//		void
// Description:
//		Stops and Swaps Playing Sound if Label not Being Played
// ����:
//		�����̍Đ�
//------------------------------------------------------------------------------
void SoundAL::PlaySwap( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx != -1 )
	{
		// Return if Label is Being Played
		return;
	}

	// Stop All Sounds
	// �������~�߂�
	StopAll();

	// Get Open Source Id
	// �\�[�XID���擾
	idx = GetOpenSourceIdx( label );
	if( idx == -1 )
	{
		// No Open Sources
		return;
	}

	// Source Settings
	// �\�[�X�ݒ�
	alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
	alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );				// Set Looping

	// Set Position to Listener Position
	// �ʒu�ݒ�
	ALfloat pos[ 3 ] = { 0 };
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_TRUE );

	// Play
	// �Đ�
	alSourcePlay( g_source[ idx ] );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Pause
// Arguments:
//		Label label
// Return Value:
//		void
// Description:
//		Pause Sound Label
// ����:
//		�����̈ꎞ��~
//------------------------------------------------------------------------------
void SoundAL::Pause( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Pause
	// �ꎞ��~
	alSourcePause( g_source[ idx ] );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Rewind
// Arguments:
//		Label label
// Return Value:
//		void
// Description:
//		Rewinds and Plays Sound Label from Beginning
// ����:
//		�����̊����߂�
//------------------------------------------------------------------------------
void SoundAL::Rewind( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Rewind
	// �����߂�
	alSourceRewind( g_source[ idx ] );
	alSourcePlay( g_source[ idx ] );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::IsPlaying
// Arguments:
//		Label label
// Return Value:
//		bool
// Description:
//		If Sound Label is Playing
// ����:
//		�������Đ����Ă��邩�ǂ���
//------------------------------------------------------------------------------
bool SoundAL::IsPlaying( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::Stop
// Arguments:
//		Label label
// Return Value:
//		void
// Description:
//		Stop Sound Label
// ����:
//		�����̒�~
//------------------------------------------------------------------------------
void SoundAL::Stop( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Stop
	// ��~
	alSourceStop( g_source[ idx ] );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::StopIdx
// Arguments:
//		int idx
// Return Value:
//		void
// Description:
//		Stop Sound Source with Index
// ����:
//		�����̒�~
//------------------------------------------------------------------------------
void SoundAL::StopIdx( int idx )
{
	if( idx < 0 || idx >= SOURCE_NUM )
	{
		return;
	}

	// Stop
	// ��~
	alSourceStop( g_source[ idx ] );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::StopAll
// Arguments:
//		void
// Return Value:
//		void
// Description:
//		Stop All Sound
// ����:
//		�S�Ẳ����̒�~
//------------------------------------------------------------------------------
void SoundAL::StopAll(void )
{
	for( int count = 0; count < SOURCE_NUM; count++ )
	{
		if( g_source[ count ] )
		{
			// Stop
			// ��~
			alSourceStop( g_source[ count ] );
		}
	}
}

//------------------------------------------------------------------------------
// LISTENER FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::SetListenerPosition
// Arguments:
//		float x
//		float y
//		float z
// Return Value:
//		void
// Description:
//		Sets Listener Position
// ����:
//		������̈ʒu�ݒ�
//------------------------------------------------------------------------------
void SoundAL::SetListenerPosition( float x, float y, float z )
{
	g_listenerPos[ 0 ] = x;
	g_listenerPos[ 1 ] = y;
	g_listenerPos[ 2 ] = z;

	alListenerfv( AL_POSITION, g_listenerPos );
}

//------------------------------------------------------------------------------
// Fuction Name:
//		SoundAL::SetListenerOrientation
// Arguments:
//		float atX
//		float atY
//		float atZ
//		float upX
//		float upY
//		float upZ
// Return Value:
//		void
// Description:
//		Sets Listener Position
// ����:
//		������̈ʒu�ݒ�
//------------------------------------------------------------------------------
void SoundAL::SetListenerOrientation( float atX, float atY, float atZ, float upX, float upY, float upZ )
{
	g_listenerOri[ 0 ] = atX;
	g_listenerOri[ 1 ] = atY;
	g_listenerOri[ 2 ] = atZ;
	g_listenerOri[ 3 ] = upX;
	g_listenerOri[ 4 ] = upY;
	g_listenerOri[ 5 ] = upZ;

	alListenerfv( AL_ORIENTATION, g_listenerOri );
}

//------------------------------------------------------------------------------
// HELPER FUNCTIONS
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Fuction Name:
//		GetSourceIdxFromLabel
// Arguments:
//		SoundAL::Label
// Return Value:
//		ALuint sourceCount
// Description:
//		Gets a Playing Source Index using Buffer Label
// ����:
//		�\�[�X�C���f�b�N�X�����x������擾
//------------------------------------------------------------------------------
ALuint GetSourceIdxFromLabel( SoundAL::Label label )
{
	// Check Base Source
	// ���\�[�X���m�F
	// Get Source State
	// �\�[�X�̏�Ԃ��擾����
	ALint sourceState;
	alGetSourcei( g_source[ label ], AL_SOURCE_STATE, &sourceState );

	// If Playing
	// �Đ����Ă���
	if( sourceState == AL_PLAYING )
		return label;

	// If Base Source is in Use, Find Empty Source
	// ���\�[�X���g���Ă���ꍇ�A��̃\�[�X��T��
	if( SOURCE_EXTRA > 0 )
	{
		ALint id;

		for( ALuint sourceCount = 0; sourceCount < SOURCE_NUM; sourceCount++ )
		{
			alGetSourcei( g_source[ sourceCount ], AL_BUFFER, &id );

			if( id == g_buffer[ label ] )
			{
				// Get Source State
				// �\�[�X�̏�Ԃ��擾����
				alGetSourcei( g_source[ sourceCount ], AL_SOURCE_STATE, &sourceState );

				// If Playing
				// �Đ����Ă���
				if( sourceState == AL_PLAYING )
					return sourceCount;
			}
		}
	}

	return -1;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		GetOpenSourceIdx
// Arguments:
//		SoundAL::Label label
// Return Value:
//		ALuint sourceCount
// Description:
//		Finds open source ID ( Source that isn't playing )
// ����:
//		�Đ����Ă��Ȃ��\�[�X��T���āAid��Ԃ�
//------------------------------------------------------------------------------
ALuint GetOpenSourceIdx( SoundAL::Label label )
{
	// Check Base Source
	// ���\�[�X���m�F
	// Get Source State
	// �\�[�X�̏�Ԃ��擾����
	ALint sourceState;
	alGetSourcei( g_source[ label ], AL_SOURCE_STATE, &sourceState );

	// If Not Playing
	// �Đ����Ă��Ȃ��ꍇ
	if( sourceState != AL_PLAYING )
		return label;

	// If Base Source is in Use, Find Empty Source
	// ���\�[�X���g���Ă���ꍇ�A��̃\�[�X��T��
	if( SOURCE_EXTRA > 0 )
	{
		// Find Source Not in Use
		// �g���Ă��Ȃ��\�[�X��T��
		for( ALuint sourceCount = SoundAL::LabelMax; sourceCount < SOURCE_NUM; sourceCount++ )
		{
			// Get Source State
			// �\�[�X�̏�Ԃ��擾����
			alGetSourcei( g_source[ sourceCount ], AL_SOURCE_STATE, &sourceState );

			// If Not Playing
			// �Đ����Ă��Ȃ��ꍇ
			if( sourceState != AL_PLAYING )
				return sourceCount;
		}
	}

	return -1;
}

//------------------------------------------------------------------------------
// Fuction Name:
//		LoadWavFile
// Arguments:
//		const char* fileName
//		ALuint& buffer
//		HWND hWnd
// Return Value:
//		bool
// Description:
//		Creates a Buffer from a WAV File
// ����:
//		�Đ����Ă��Ȃ��\�[�X��T���āAid��Ԃ�
//------------------------------------------------------------------------------
bool LoadWavFile( const char* fileName, ALuint& buffer, HWND hWnd )
{
	using namespace std;

	// Wave Structures
	// Wave�\����
	struct RIFF_Header
	{
		char chunkID[ 4 ];
		long chunkSize;
		char format[ 4 ];
	};

	struct WAVE_Format
	{
		char subChunkID[ 4 ];
		long subChunkSize;
		short audioFormat;
		short numChannels;
		long sampleRate;
		long byteRate;
		short blockAlign;
		short bitsPerSample;
	};

	struct WAVE_Data
	{
		char subChunkID[ 4 ];
		long subChunkSize;
	};

	// Variables
	// �ϐ�
	bool success = false;
	ifstream file;						// File Stream
	WAVE_Format wave_format;			// Wave Format Struct
	RIFF_Header riff_header;			// Riff Header Struct
	WAVE_Data wave_data;				// Wave Data Struct
	unsigned char* data = nullptr;		// Sound Data Holder
	ALsizei size = 0;					// Sound Size
	ALsizei frequency = 0;				// Sound Frequency
	ALenum format = 0;					// Sound Format

	// Initialize Memory
	// �������̏�����
	memset( &wave_format, 0, sizeof( WAVE_Format ) );
	memset( &riff_header, 0, sizeof( RIFF_Header ) );
	memset( &wave_data, 0, sizeof( WAVE_Data ) );

	// Try Loading file
	// �t�@�C���ǂݍ��݂�
	try
	{
		// Open File
		// �t�@�C�����J��
		file.open( fileName,	// Name of File to Write
			ios::in |			// Read Setting
			ios::binary );		// Open in Binary Mode

		// If File Failed to Open
		// �t�@�C�����J���Ȃ������ꍇ
		if( !file.is_open() )
		{
			throw ( "Wave file open error!" );
		}

		// Read the First Chunk into the RIFF Struct
		// ��Ԗڂ̃`�����N��ǂݍ���
		file.read( ( char* )&riff_header, sizeof( RIFF_Header ) );

		// Check Chunk and Format Info
		// �`�����N�ƃt�H�[�}�b�g�����m�F
		if( ( riff_header.chunkID[ 0 ] != 'R' ||
			riff_header.chunkID[ 1 ] != 'I' ||
			riff_header.chunkID[ 2 ] != 'F' ||
			riff_header.chunkID[ 3 ] != 'F' ) ||
			( riff_header.format[ 0 ] != 'W' ||
			riff_header.format[ 1 ] != 'A' ||
			riff_header.format[ 2 ] != 'V' ||
			riff_header.format[ 3 ] != 'E' ) )
		{
			throw( "Invalid RIFF or WAVE Header!\n" );
		}

		// Read in the 2nd Chunk for the Wave Info
		// ��Ԗڂ̃`�����N��ǂݍ���
		while( file.read( ( char* )&wave_format, sizeof( wave_format.subChunkID ) ) )
		{
			// Check fmt tag
			// fmt�^�O�̊m�F
			if( wave_format.subChunkID[ 0 ] == 'f' &&
				wave_format.subChunkID[ 1 ] == 'm' &&
				wave_format.subChunkID[ 2 ] == 't' &&
				wave_format.subChunkID[ 3 ] == ' ' )
			{
				success = true;
				break;
			}
		}

		// If Failed to get Wave Format Location
		// Wave�t�H�[�}�b�g�̈ʒu�̎擾�����s�����ꍇ
		if( !success )
		{
			throw( "Invalid Wave Format!\n" );
		}

		// Load Remaining Format Data
		// �c��̃t�H�[�}�b�g�f�[�^��ǂݍ���
		file.read( ( char* )&wave_format.subChunkSize, sizeof( wave_format ) - sizeof( wave_format.subChunkID ) );

		// Check for Extra Parameters
		// �ǉ��p�����[�^�̊m�F
		if( wave_format.subChunkSize > 16 )
		{
			file.seekg( sizeof( short ), ios::cur );
		}

		// Search for the data tag
		// data�^�O��T��
		success = false;
		while( file.read( ( char* )&wave_data, sizeof( char ) ) )
		{
			if( wave_data.subChunkID[ 0 ] == 'd' )
			{
				file.read( ( char* )&wave_data.subChunkID[ 1 ], sizeof( char ) * 3 );
				// Check fmt tag
				// fmt�^�O�̊m�F
				if( wave_data.subChunkID[ 0 ] == 'd' &&
					wave_data.subChunkID[ 1 ] == 'a' &&
					wave_data.subChunkID[ 2 ] == 't' &&
					wave_data.subChunkID[ 3 ] == 'a' )
				{
					success = true;
					break;
				}
			}
		}

		if( !success )
		{
			throw( "Invalid data header!\n" );
		}

		// Load Remaining Data
		// �c��̃f�[�^��ǂݍ���
		file.read( ( char* )&wave_data.subChunkSize, sizeof( wave_data.subChunkSize ) );

		// Allocate memory for the Data
		// �f�[�^�̃������m��
		data = new unsigned char[ wave_data.subChunkSize ];

		// Read in the Sound Data into the Sound Data Variable
		// �T�E���h�̃f�[�^��ǂݍ���
		if( !file.read( ( char* )data, wave_data.subChunkSize ) )
		{
			throw( "Error loading WAVE data into struct!\n" );
		}

		// Set Variables
		// �ϐ��̐ݒ�
		size = wave_data.subChunkSize;
		frequency = wave_format.sampleRate;

		// Work out format
		// �t�H�[�}�b�g�̐ݒ�
		if( wave_format.numChannels == 1 )
		{
			if( wave_format.bitsPerSample == 8 )
			{
				format = AL_FORMAT_MONO8;
			}

			else if( wave_format.bitsPerSample == 16 )
			{
				format = AL_FORMAT_MONO16;
			}
		}

		else if( wave_format.numChannels == 2 )
		{
			if( wave_format.bitsPerSample == 8 )
			{
				format = AL_FORMAT_STEREO8;
			}

			else if( wave_format.bitsPerSample == 16 )
			{
				format = AL_FORMAT_STEREO16;
			}
		}

		// Put Data into OpenAL Buffer
		// �f�[�^���o�b�t�@�ɓ����
		alBufferData( buffer, format, ( void* )data, size, frequency );
		if( alGetError() != AL_NO_ERROR )
		{
			throw( "WAVE buffer data error!\n" );
		}

		// Free Data
		// �f�[�^�̉��
		if( data )
		{
			delete[] data;
			data = nullptr;
		}

		// Close File
		// �t�@�C�������
		file.close();
		return true;
	}
	
	// Catch Errors
	// �G���[�̏���
	catch( LPCSTR str )
	{
		// Error Message
		// �G���[���b�Z�[�W
		MessageBox( hWnd, str, "Error!", MB_ICONWARNING );

		// Close file if Open
		// �t�@�C�����J���Ă���ꍇ�A����
		if( file.is_open() )
		{
			file.close();
		}

		// Free Data
		// �f�[�^�̉��
		if( data )
		{
			delete[] data;
			data = nullptr;
		}

		return false;
	}
}
