#include "UtilsWrapper.h"
#include <string>
#include <QApplication>

using namespace std;
constexpr auto DL_D3D11 = "libobs-d3d11.dll";
constexpr auto DL_OPENGL = "libobs-opengl.dll";
constexpr auto FPS = 60;
constexpr auto WIDTH = 1920;
constexpr auto HEIGHT = 1080;

enum SOURCE_CHANNELS {
	SOURCE_CHANNEL_TRANSITION,
	SOURCE_CHANNEL_AUDIO_OUTPUT,
	SOURCE_CHANNEL_AUDIO_INPUT,
};


UtilsWrapper::UtilsWrapper()
{
}

UtilsWrapper::~UtilsWrapper()
{
}

bool UtilsWrapper::InitUtils()
{
	// start initialization
	string locale = "en-US";
	string module_config_path = "../config";
	if (!obs_initialized()) {
		if (!obs_startup(locale.c_str(), module_config_path.c_str(), NULL)) {
			return false;
		}
	}
	
	// load plugins
	if (!LoadPlugins()) {
		return false;
	}

	// setup audio
	if (!SetupAudio()) {
		return false;
	}	
	
	// setup video
	if (SetupVideo() != OBS_VIDEO_SUCCESS) {
		return false;
	}

	// end initialization
	return true;
}

bool UtilsWrapper::LoadPlugins() {
	string app_path = qApp->applicationDirPath().toStdString();
	string plugin_path = app_path + "/obs-plugins/32bit";
	string data_path = app_path + "/data/obs-plugins/%module%";
	obs_add_module_path(plugin_path.c_str(), data_path.c_str());
	obs_load_all_modules();
	return true;
}

bool UtilsWrapper::SetupAudio() {
	struct obs_audio_info audio_info;
	audio_info.samples_per_sec = 48000;
	audio_info.speakers = SPEAKERS_STEREO;
	return obs_reset_audio(&audio_info);
}

int UtilsWrapper::SetupVideo() {
	struct obs_video_info video_info;
	video_info.graphics_module = DL_D3D11;
	video_info.fps_num = FPS;
	video_info.fps_den = 1;
	video_info.base_width = WIDTH;
	video_info.base_height = HEIGHT;
	video_info.output_width = WIDTH;
	video_info.output_height = HEIGHT;
	video_info.output_format = VIDEO_FORMAT_RGBA;
	video_info.adapter = 0;
	video_info.gpu_conversion = true;
	video_info.colorspace = VIDEO_CS_DEFAULT;
	video_info.range = VIDEO_RANGE_DEFAULT;
	video_info.scale_type = OBS_SCALE_DISABLE;
	return obs_reset_video(&video_info);
}

int UtilsWrapper::SetupScene()
{
	obs_set_output_source(SOURCE_CHANNEL_TRANSITION, nullptr);
	obs_set_output_source(SOURCE_CHANNEL_AUDIO_OUTPUT, nullptr);
	obs_set_output_source(SOURCE_CHANNEL_AUDIO_INPUT, nullptr);

	return 0;
}

bool UtilsWrapper::StartRec()
{
	if (!obs_output_start(output)) {
		return false;
	};
	return true;
}

bool UtilsWrapper::StopRec()
{
	obs_output_stop(output);
	return true;
}
