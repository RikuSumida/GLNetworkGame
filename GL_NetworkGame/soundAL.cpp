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
// ノート： 基底ソースが直接のインデックスでバッファと繋がっている
// ソースのextraの数を設定することで同じバッファを複数のソースで使える
// ようになる。（例：同じSEを複数再生する時）
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
// 説明:
//		SoundALの初期化
//------------------------------------------------------------------------------
bool SoundAL::Init( HWND hWnd )
{
	// Initialize AL Variables
	// AL変数の初期化
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
	// エラーメッセージをクリア
	alGetError();

	// Create Buffers
	// バッファを作る
	alGenBuffers( LabelMax, g_buffer );
	if( alGetError() != AL_NO_ERROR )
	{
		MessageBox( hWnd, "GenBuffer error!\n", "Error!", MB_ICONWARNING );
		return false;
	}

	// Read Files and Set Buffer Data
	// ファイル読み込んで、バッファデータの設定
	for( int labelCount = 0; labelCount < LabelMax; labelCount++ )
	{
		if( !LoadWavFile( g_param[ labelCount ].fileName, g_buffer[ labelCount ], hWnd ) )
		{
			return false;
		}
	}

	// Generate Sources
	// ソースの生成
	alGenSources( SOURCE_NUM, &g_source[ 0 ] );
	if( alGetError() != AL_NO_ERROR )
	{
		MessageBox( hWnd, "alutGenSource error!\n", "Error!", MB_ICONWARNING );
		return false;
	}

	// Set Base Sources
	// 基底ソースの設定
	for( int labelCount = 0; labelCount < LabelMax; labelCount++ )
	{
		alSourcei( g_source[ labelCount ], AL_BUFFER, g_buffer[ labelCount ] );			// Place Buffer into Source
		alSourcei( g_source[ labelCount ], AL_LOOPING, g_param[ labelCount ].loop );	// Set Looping
	}
	
	// Source Max Sound Distance
	// ソースの最大音声距離
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
// 説明:
//		SoundALの終了処理
//------------------------------------------------------------------------------
void SoundAL::Uninit( void )
{
	// Delete Sources and Buffers
	// ソースとバッファの削除
	alDeleteSources( SOURCE_NUM, g_source );
	alDeleteBuffers( SoundAL::LabelMax, g_buffer );

	// Exit
	// 終了処理
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
// 説明:
//		音声の再生
//------------------------------------------------------------------------------
int SoundAL::Play( SoundAL::Label label )
{
	ALuint idx = GetOpenSourceIdx( label );
	if( idx == -1 )
		return -1;

	// Check if Direct Index
	// ダイレクト・インデックスかどうかを確認
	if( idx != label )
	{
		// Get Base Source Settings
		// 基底ソースの設定を取得
		ALfloat pitch;
		ALfloat gain;

		alGetSourcef( g_source[ label ], AL_PITCH, &pitch );
		alGetSourcef( g_source[ label ], AL_GAIN, &gain );

		// Set Source Settings if Not Direct
		// ダイレクトじゃない時はソースの設定をする
		alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
		alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );				// Set Looping
		alSourcef( g_source[ idx ], AL_PITCH, pitch );
		alSourcef( g_source[ idx ], AL_GAIN, gain );
	}

	// Set Position to Listener Position
	// 位置設定
	ALfloat pos[ 3 ] = { 0 };
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_TRUE );

	// Play
	// 再生
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
// 説明:
//		特定位置から音声の再生
//------------------------------------------------------------------------------
int SoundAL::PlayPosition( SoundAL::Label label, float x, float y, float z )
{
	ALuint idx = GetOpenSourceIdx( label );
	if( idx == -1 )
		return -1;

	// Check if Direct Index
	// ダイレクト・インデックスかどうかを確認
	if( idx != label )
	{
		// Get Base Source Settings
		// 基底ソースの設定を取得
		ALfloat pitch;
		ALfloat gain;
		
		alGetSourcef( g_source[ label ], AL_PITCH, &pitch );
		alGetSourcef( g_source[ label ], AL_GAIN, &gain );

		// Set Source Settings if Not Direct
		// ダイレクトじゃない時はソースの設定をする
		alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
		alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop ); // Set Looping
		alSourcef( g_source[ idx ], AL_PITCH, pitch );
		alSourcef( g_source[ idx ], AL_GAIN, gain );
	}

	// Set Position
	// 位置設定
	ALfloat pos[ 3 ];
	pos[ 0 ] = x;
	pos[ 1 ] = y;
	pos[ 2 ] = z;
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_FALSE );
	alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );	

	// Play
	// 再生
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
// 説明:
//		音声の再生
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
	// 音声を止める
	StopAll();

	// Get Open Source Id
	// ソースIDを取得
	idx = GetOpenSourceIdx( label );
	if( idx == -1 )
	{
		// No Open Sources
		return;
	}

	// Source Settings
	// ソース設定
	alSourcei( g_source[ idx ], AL_BUFFER, g_buffer[ label ] );
	alSourcei( g_source[ idx ], AL_LOOPING, g_param[ label ].loop );				// Set Looping

	// Set Position to Listener Position
	// 位置設定
	ALfloat pos[ 3 ] = { 0 };
	alSourcefv( g_source[ idx ], AL_POSITION, pos );
	alSourcei( g_source[ idx ], AL_SOURCE_RELATIVE, AL_TRUE );

	// Play
	// 再生
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
// 説明:
//		音声の一時停止
//------------------------------------------------------------------------------
void SoundAL::Pause( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Pause
	// 一時停止
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
// 説明:
//		音声の巻き戻し
//------------------------------------------------------------------------------
void SoundAL::Rewind( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Rewind
	// 巻き戻し
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
// 説明:
//		音声が再生しているかどうか
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
// 説明:
//		音声の停止
//------------------------------------------------------------------------------
void SoundAL::Stop( SoundAL::Label label )
{
	ALuint idx = GetSourceIdxFromLabel( label );
	if( idx == -1 )
	{
		return;
	}

	// Stop
	// 停止
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
// 説明:
//		音声の停止
//------------------------------------------------------------------------------
void SoundAL::StopIdx( int idx )
{
	if( idx < 0 || idx >= SOURCE_NUM )
	{
		return;
	}

	// Stop
	// 停止
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
// 説明:
//		全ての音声の停止
//------------------------------------------------------------------------------
void SoundAL::StopAll(void )
{
	for( int count = 0; count < SOURCE_NUM; count++ )
	{
		if( g_source[ count ] )
		{
			// Stop
			// 停止
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
// 説明:
//		聞き手の位置設定
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
// 説明:
//		聞き手の位置設定
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
// 説明:
//		ソースインデックスをラベルから取得
//------------------------------------------------------------------------------
ALuint GetSourceIdxFromLabel( SoundAL::Label label )
{
	// Check Base Source
	// 基底ソースを確認
	// Get Source State
	// ソースの状態を取得する
	ALint sourceState;
	alGetSourcei( g_source[ label ], AL_SOURCE_STATE, &sourceState );

	// If Playing
	// 再生している
	if( sourceState == AL_PLAYING )
		return label;

	// If Base Source is in Use, Find Empty Source
	// 基底ソースが使われている場合、空のソースを探す
	if( SOURCE_EXTRA > 0 )
	{
		ALint id;

		for( ALuint sourceCount = 0; sourceCount < SOURCE_NUM; sourceCount++ )
		{
			alGetSourcei( g_source[ sourceCount ], AL_BUFFER, &id );

			if( id == g_buffer[ label ] )
			{
				// Get Source State
				// ソースの状態を取得する
				alGetSourcei( g_source[ sourceCount ], AL_SOURCE_STATE, &sourceState );

				// If Playing
				// 再生している
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
// 説明:
//		再生していないソースを探して、idを返す
//------------------------------------------------------------------------------
ALuint GetOpenSourceIdx( SoundAL::Label label )
{
	// Check Base Source
	// 基底ソースを確認
	// Get Source State
	// ソースの状態を取得する
	ALint sourceState;
	alGetSourcei( g_source[ label ], AL_SOURCE_STATE, &sourceState );

	// If Not Playing
	// 再生していない場合
	if( sourceState != AL_PLAYING )
		return label;

	// If Base Source is in Use, Find Empty Source
	// 基底ソースが使われている場合、空のソースを探す
	if( SOURCE_EXTRA > 0 )
	{
		// Find Source Not in Use
		// 使われていないソースを探す
		for( ALuint sourceCount = SoundAL::LabelMax; sourceCount < SOURCE_NUM; sourceCount++ )
		{
			// Get Source State
			// ソースの状態を取得する
			alGetSourcei( g_source[ sourceCount ], AL_SOURCE_STATE, &sourceState );

			// If Not Playing
			// 再生していない場合
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
// 説明:
//		再生していないソースを探して、idを返す
//------------------------------------------------------------------------------
bool LoadWavFile( const char* fileName, ALuint& buffer, HWND hWnd )
{
	using namespace std;

	// Wave Structures
	// Wave構造体
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
	// 変数
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
	// メモリの初期化
	memset( &wave_format, 0, sizeof( WAVE_Format ) );
	memset( &riff_header, 0, sizeof( RIFF_Header ) );
	memset( &wave_data, 0, sizeof( WAVE_Data ) );

	// Try Loading file
	// ファイル読み込みを
	try
	{
		// Open File
		// ファイルを開く
		file.open( fileName,	// Name of File to Write
			ios::in |			// Read Setting
			ios::binary );		// Open in Binary Mode

		// If File Failed to Open
		// ファイルが開けなかった場合
		if( !file.is_open() )
		{
			throw ( "Wave file open error!" );
		}

		// Read the First Chunk into the RIFF Struct
		// 一番目のチャンクを読み込む
		file.read( ( char* )&riff_header, sizeof( RIFF_Header ) );

		// Check Chunk and Format Info
		// チャンクとフォーマット情報を確認
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
		// 二番目のチャンクを読み込む
		while( file.read( ( char* )&wave_format, sizeof( wave_format.subChunkID ) ) )
		{
			// Check fmt tag
			// fmtタグの確認
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
		// Waveフォーマットの位置の取得が失敗した場合
		if( !success )
		{
			throw( "Invalid Wave Format!\n" );
		}

		// Load Remaining Format Data
		// 残りのフォーマットデータを読み込む
		file.read( ( char* )&wave_format.subChunkSize, sizeof( wave_format ) - sizeof( wave_format.subChunkID ) );

		// Check for Extra Parameters
		// 追加パラメータの確認
		if( wave_format.subChunkSize > 16 )
		{
			file.seekg( sizeof( short ), ios::cur );
		}

		// Search for the data tag
		// dataタグを探す
		success = false;
		while( file.read( ( char* )&wave_data, sizeof( char ) ) )
		{
			if( wave_data.subChunkID[ 0 ] == 'd' )
			{
				file.read( ( char* )&wave_data.subChunkID[ 1 ], sizeof( char ) * 3 );
				// Check fmt tag
				// fmtタグの確認
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
		// 残りのデータを読み込む
		file.read( ( char* )&wave_data.subChunkSize, sizeof( wave_data.subChunkSize ) );

		// Allocate memory for the Data
		// データのメモリ確保
		data = new unsigned char[ wave_data.subChunkSize ];

		// Read in the Sound Data into the Sound Data Variable
		// サウンドのデータを読み込む
		if( !file.read( ( char* )data, wave_data.subChunkSize ) )
		{
			throw( "Error loading WAVE data into struct!\n" );
		}

		// Set Variables
		// 変数の設定
		size = wave_data.subChunkSize;
		frequency = wave_format.sampleRate;

		// Work out format
		// フォーマットの設定
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
		// データをバッファに入れる
		alBufferData( buffer, format, ( void* )data, size, frequency );
		if( alGetError() != AL_NO_ERROR )
		{
			throw( "WAVE buffer data error!\n" );
		}

		// Free Data
		// データの解放
		if( data )
		{
			delete[] data;
			data = nullptr;
		}

		// Close File
		// ファイルを閉じる
		file.close();
		return true;
	}
	
	// Catch Errors
	// エラーの処理
	catch( LPCSTR str )
	{
		// Error Message
		// エラーメッセージ
		MessageBox( hWnd, str, "Error!", MB_ICONWARNING );

		// Close file if Open
		// ファイルが開いている場合、閉じる
		if( file.is_open() )
		{
			file.close();
		}

		// Free Data
		// データの解放
		if( data )
		{
			delete[] data;
			data = nullptr;
		}

		return false;
	}
}
