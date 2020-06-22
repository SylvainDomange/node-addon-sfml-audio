#pragma once

#include <napi.h>

namespace sf {

class SoundStream;

}

struct soundstream_impl {
    sf::SoundStream* instance;

    Napi::Value channel_count(const Napi::CallbackInfo& info);
    Napi::Value sample_rate(const Napi::CallbackInfo& info);
    void set_playing_offset(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value playing_offset(const Napi::CallbackInfo& info);
    void set_loop(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value loop(const Napi::CallbackInfo& info);
};

#define SOUNDSTREAMIMPL_INSTANCEACCESSORS_IMPL() \
Napi::Value channel_count(const Napi::CallbackInfo& info) { return soundstream_impl::channel_count(info); } \
Napi::Value sample_rate(const Napi::CallbackInfo& info) { return soundstream_impl::sample_rate(info); } \
void set_playing_offset(const Napi::CallbackInfo& info, const Napi::Value& value) { soundstream_impl::set_playing_offset(info, value); } \
Napi::Value playing_offset(const Napi::CallbackInfo& info) { return soundstream_impl::playing_offset(info); } \
void set_loop(const Napi::CallbackInfo& info, const Napi::Value& value) { soundstream_impl::set_loop(info, value); } \
Napi::Value loop(const Napi::CallbackInfo& info) { return soundstream_impl::loop(info); }

#define SOUNDSTREAMIMPL_INSTANCEACCESSORS(X) \
InstanceAccessor<&X::channel_count>("channelCount"), \
InstanceAccessor<&X::sample_rate>("sampleRate"), \
InstanceAccessor<&X::playing_offset, &X::set_playing_offset>("playingOffset"), \
InstanceAccessor<&X::loop, &X::set_loop>("loop")
