#pragma once

#include "soundsource_impl.h"

#include <memory>

#include <napi.h>

#include <SFML/Audio/Sound.hpp>

struct sound : Napi::ObjectWrap<sound>, soundsource_impl {
    static Napi::FunctionReference constructor;
    std::unique_ptr<sf::Sound> instance;

    sound(const Napi::CallbackInfo& info);

    static Napi::Object init(Napi::Env env, Napi::Object exports);

    Napi::Value ref(const Napi::CallbackInfo& info);
    Napi::Value unref(const Napi::CallbackInfo& info);
    Napi::Value release(const Napi::CallbackInfo& info);

    void set_loop(const Napi::CallbackInfo& info, const Napi::Value& value);
    void set_playing_offset(const Napi::CallbackInfo& info, const Napi::Value& value);
    Napi::Value loop(const Napi::CallbackInfo& info);
    Napi::Value playing_offset(const Napi::CallbackInfo& info);
    Napi::Value buffer(const Napi::CallbackInfo& info);
    void set_buffer(const Napi::CallbackInfo& info, const Napi::Value& value);

    SOUNDSOURCEIMPL_INSTANCEACCESSORS_IMPL()

private:
    Napi::ObjectReference buffer_ref_;
};
