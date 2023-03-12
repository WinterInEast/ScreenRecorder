#pragma once
#include "obs.h"
#include "obs.hpp"
#include <string>
#include <unordered_map>

#ifdef __APPLE__
#define INPUT_AUDIO_SOURCE "coreaudio_input_capture"
#define OUTPUT_AUDIO_SOURCE "coreaudio_output_capture"
#elif _WIN32
#define INPUT_AUDIO_SOURCE "wasapi_input_capture"
#define OUTPUT_AUDIO_SOURCE "wasapi_output_capture"
#else
#define INPUT_AUDIO_SOURCE "pulse_input_capture"
#define OUTPUT_AUDIO_SOURCE "pulse_output_capture"
#endif

#define DL_D3D11 "libobs-d3d11.dll"
#define DL_OPENGL "libobs-opengl.dll"
#define FPS	60
#define WIDTH 1920
#define HEIGHT 1080
#define VIDEO_ENCODER_ID AV_CODEC_ID_H264
#define VIDEO_ENCODER_NAME "libx264"
#define RECORD_OUTPUT_FORMAT "mp4"
#define RECORD_OUTPUT_FORMAT_MIME "video/mp4"
#define AUDIO_BITRATE 128 
#define VIDEO_BITRATE 150
#define OUT_WIDTH  1920
#define OUT_HEIGHT 1080

using namespace std;
using REC_OBJ = vector<string>;


enum SOURCE_CHANNELS {
	SOURCE_CHANNEL_TRANSITION,
	SOURCE_CHANNEL_AUDIO_OUTPUT,
	SOURCE_CHANNEL_AUDIO_INPUT,
};


enum REC_TYPE
{
	REC_MONITOR,
	REC_WINDOW
};


class UtilsWrapper
{
public:
	UtilsWrapper();
	~UtilsWrapper();

	bool InitUtils();
	bool StartRec();
	bool StopRec();
	bool SearchSource(REC_TYPE rec_type, REC_OBJ& m_RecObj);
	bool SetSource(REC_TYPE rec_type, const char* rec_obj);

private:
	bool LoadPlugins();
	bool SetupAudio();
	bool SetupVideo();
	bool SetupScene();
	bool SetupOutputMode();
	bool SetupFFmpeg();

private:
	OBSOutput output;
	obs_source_t* fadeTransition = nullptr;
	obs_source_t* captureSource = nullptr;
	obs_properties_t* properties = nullptr;
	obs_scene_t* scene = nullptr;
	obs_data_t* setting = nullptr;
	obs_property_t* property = nullptr;
	OBSEncoder aacTrack[MAX_AUDIO_MIXES];
	string aacEncoderID[MAX_AUDIO_MIXES];
};

