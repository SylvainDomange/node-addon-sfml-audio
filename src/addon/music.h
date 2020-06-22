#pragma once

#include "soundsource_impl.h"
#include "soundstream_impl.h"

#include <memory>

#include <napi.h>

#include <SFML/Audio/Music.hpp>

struct music : Napi::ObjectWrap<music>, soundsource_impl, soundstream_impl {
    static Napi::FunctionReference constructor;
    std::unique_ptr<sf::Music> instance;

    music(const Napi::CallbackInfo& info);

    static Napi::Object init(Napi::Env env, Napi::Object exports);

    Napi::Value ref(const Napi::CallbackInfo& info);
    Napi::Value unref(const Napi::CallbackInfo& info);
    Napi::Value release(const Napi::CallbackInfo& info);

    Napi::Value open_from_file(const Napi::CallbackInfo& info);
    Napi::Value open_from_memory(const Napi::CallbackInfo& info);
    Napi::Value duration(const Napi::CallbackInfo& info);
    Napi::Value loop_points(const Napi::CallbackInfo& info);
    void set_loop_points(const Napi::CallbackInfo& info, const Napi::Value& value);

    SOUNDSOURCEIMPL_INSTANCEACCESSORS_IMPL()
    SOUNDSTREAMIMPL_INSTANCEACCESSORS_IMPL()

private:
    Napi::ObjectReference membuf_ref_;
};
