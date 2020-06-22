#include "soundstream_impl.h"
#include "param_helper.h"

#include <SFML/Audio/SoundStream.hpp>

using namespace param_helper;

Napi::Value soundstream_impl::channel_count(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getChannelCount());
}

Napi::Value soundstream_impl::sample_rate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getSampleRate());
}

void soundstream_impl::set_playing_offset(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setPlayingOffset(as_sf_time(value));
}

Napi::Value soundstream_impl::playing_offset(const Napi::CallbackInfo& info) {
	return from_sf_time(info.Env(), instance->getPlayingOffset());
}

void soundstream_impl::set_loop(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setLoop(as_bool(value));
}

Napi::Value soundstream_impl::loop(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), instance->getLoop());
}
