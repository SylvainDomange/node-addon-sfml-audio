#include "soundsource_impl.h"
#include "param_helper.h"

#include <SFML/Audio/SoundSource.hpp>

using namespace param_helper;

void soundsource_impl::set_pitch(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setPitch(as_float(value));
}

void soundsource_impl::set_volume(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setVolume(std::clamp(as_float(value), 0.0f, 100.0f));
}

void soundsource_impl::set_position(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setPosition(as_sf_vec3(value));
}

void soundsource_impl::set_relative_to_listener(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setRelativeToListener(as_bool(value));
}

void soundsource_impl::set_min_distance(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setMinDistance(as_float(value));
}

void soundsource_impl::set_attenuation(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setAttenuation(as_float(value));
}

Napi::Value soundsource_impl::pitch(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getPitch());
}

Napi::Value soundsource_impl::volume(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getVolume());
}

Napi::Value soundsource_impl::position(const Napi::CallbackInfo& info) {
	return from_sf_vec3(info.Env(), instance->getPosition());
}

Napi::Value soundsource_impl::relative_to_listener(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), instance->isRelativeToListener());
}

Napi::Value soundsource_impl::min_distance(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getMinDistance());
}

Napi::Value soundsource_impl::attenuation(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getAttenuation());
}

Napi::Value soundsource_impl::play(const Napi::CallbackInfo& info) {
    instance->play();

    return info.Env().Undefined();
}

Napi::Value soundsource_impl::pause(const Napi::CallbackInfo& info) {
    instance->pause();

    return info.Env().Undefined();
}

Napi::Value soundsource_impl::stop(const Napi::CallbackInfo& info) {
    instance->stop();

    return info.Env().Undefined();
}

Napi::Value soundsource_impl::status(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getStatus());
}
