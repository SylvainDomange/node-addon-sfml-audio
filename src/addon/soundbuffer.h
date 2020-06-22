#pragma once

#include <memory>

#include <napi.h>

#include <SFML/Audio/SoundBuffer.hpp>

struct soundbuffer : Napi::ObjectWrap<soundbuffer> {
    static Napi::FunctionReference constructor;
    std::unique_ptr<sf::SoundBuffer> instance;

    soundbuffer(const Napi::CallbackInfo& info);

    static Napi::Object init(Napi::Env env, Napi::Object exports);

    Napi::Value ref(const Napi::CallbackInfo& info);
    Napi::Value unref(const Napi::CallbackInfo& info);
    Napi::Value release(const Napi::CallbackInfo& info);

    Napi::Value load_from_file(const Napi::CallbackInfo& info);
    Napi::Value load_from_memory(const Napi::CallbackInfo& info);
    Napi::Value load_from_samples(const Napi::CallbackInfo& info);
    Napi::Value save_to_file(const Napi::CallbackInfo& info);
    Napi::Value samples(const Napi::CallbackInfo& info);
    Napi::Value sample_count(const Napi::CallbackInfo& info);
    Napi::Value sample_rate(const Napi::CallbackInfo& info);
    Napi::Value channel_count(const Napi::CallbackInfo& info);
    Napi::Value duration(const Napi::CallbackInfo& info);

private:
    Napi::ObjectReference membuf_ref_;
};
