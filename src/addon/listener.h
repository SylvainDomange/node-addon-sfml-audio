#pragma once

#include <napi.h>

struct listener : Napi::ObjectWrap<listener> {
    static Napi::FunctionReference constructor;

    listener(const Napi::CallbackInfo& info);

    static Napi::Object init(Napi::Env env, Napi::Object exports);

    static Napi::Value global_volume(const Napi::CallbackInfo& info);
    static void set_global_volume(const Napi::CallbackInfo& info, const Napi::Value& value);
    static Napi::Value position(const Napi::CallbackInfo& info);
    static void set_position(const Napi::CallbackInfo& info, const Napi::Value& value);
    static Napi::Value direction(const Napi::CallbackInfo& info);
    static void set_direction(const Napi::CallbackInfo& info, const Napi::Value& value);
    static Napi::Value up_vector(const Napi::CallbackInfo& info);
    static void set_up_vector(const Napi::CallbackInfo& info, const Napi::Value& value);
};
