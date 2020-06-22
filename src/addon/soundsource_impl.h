#pragma once

#include <napi.h>

namespace sf {

class SoundSource;

}

struct soundsource_impl {
    sf::SoundSource* instance;

    void set_pitch(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_volume(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_position(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_relative_to_listener(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_min_distance(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_attenuation(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value pitch(const Napi::CallbackInfo& info);
    Napi::Value volume(const Napi::CallbackInfo& info);
    Napi::Value position(const Napi::CallbackInfo& info);
    Napi::Value relative_to_listener(const Napi::CallbackInfo& info);
    Napi::Value min_distance(const Napi::CallbackInfo& info);
    Napi::Value attenuation(const Napi::CallbackInfo& info);
    Napi::Value play(const Napi::CallbackInfo& info);
    Napi::Value pause(const Napi::CallbackInfo& info);
    Napi::Value stop(const Napi::CallbackInfo& info);
    Napi::Value status(const Napi::CallbackInfo& info);
};

#define SOUNDSOURCEIMPL_INSTANCEACCESSORS_IMPL() \
void set_pitch(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_pitch(info, value); } \
void set_volume(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_volume(info, value); } \
void set_position(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_position(info, value); } \
void set_relative_to_listener(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_relative_to_listener(info, value); } \
void set_min_distance(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_min_distance(info, value); } \
void set_attenuation(const Napi::CallbackInfo& info, const Napi::Value& value) { soundsource_impl::set_attenuation(info, value); } \
Napi::Value pitch(const Napi::CallbackInfo& info) { return soundsource_impl::pitch(info); } \
Napi::Value volume(const Napi::CallbackInfo& info) { return soundsource_impl::volume(info); } \
Napi::Value position(const Napi::CallbackInfo& info) { return soundsource_impl::position(info); } \
Napi::Value relative_to_listener(const Napi::CallbackInfo& info) { return soundsource_impl::relative_to_listener(info); } \
Napi::Value min_distance(const Napi::CallbackInfo& info) { return soundsource_impl::min_distance(info); } \
Napi::Value attenuation(const Napi::CallbackInfo& info) { return soundsource_impl::attenuation(info); } \
Napi::Value status(const Napi::CallbackInfo& info) { return soundsource_impl::status(info); }

#define SOUNDSOURCEIMPL_INSTANCEACCESSORS(X) \
InstanceAccessor<&X::pitch, &X::set_pitch>("pitch"), \
InstanceAccessor<&X::volume, &X::set_volume>("volume"), \
InstanceAccessor<&X::position, &X::set_position>("position"), \
InstanceAccessor<&X::relative_to_listener, &X::set_relative_to_listener>("relativeToListener"), \
InstanceAccessor<&X::min_distance, &X::set_min_distance>("minDistance"), \
InstanceAccessor<&X::attenuation, &X::set_attenuation>("attenuation"), \
InstanceAccessor<&X::status>("status")

#define SOUNDSOURCEIMPL_INSTANCEMETHODS() \
InstanceMethod("play", &soundsource_impl::play), \
InstanceMethod("pause", &soundsource_impl::pause), \
InstanceMethod("stop", &soundsource_impl::stop)
