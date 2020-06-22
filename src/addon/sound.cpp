#include "sound.h"
#include "soundbuffer.h"
#include "param_helper.h"

using namespace param_helper;

Napi::FunctionReference sound::constructor;

sound::sound(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<sound>(info),
    instance{std::make_unique<sf::Sound>()}
{
    this->soundsource_impl::instance = instance.get();

    if (info.Length() >= 1) {
        auto buffer_object = as_object(info[0]);
        auto buffer = soundbuffer::Unwrap(as_object(info[0]));

        instance->setBuffer(*buffer->instance.get());
        buffer_ref_ = Napi::Persistent(buffer_object);
    }
}

Napi::Object sound::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope{env};

    Napi::Function func =
    DefineClass(env, "Sound", {
        InstanceMethod("ref", &sound::ref),
        InstanceMethod("unref", &sound::unref),
        InstanceMethod("release", &sound::release),
        SOUNDSOURCEIMPL_INSTANCEACCESSORS(sound),
        SOUNDSOURCEIMPL_INSTANCEMETHODS(),
        InstanceAccessor<&sound::loop, &sound::set_loop>("loop"),
        InstanceAccessor<&sound::playing_offset, &sound::set_playing_offset>("playingOffset"),
        InstanceAccessor<&sound::buffer, &sound::set_buffer>("buffer")
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Sound", func);

    return exports;
}

Napi::Value sound::ref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Ref());
}

Napi::Value sound::unref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Unref());
}

Napi::Value sound::release(const Napi::CallbackInfo& info) {
    Reset();

    return info.Env().Undefined();
}

void sound::set_loop(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setLoop(as_bool(value));
}

void sound::set_playing_offset(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setPlayingOffset(as_sf_time(value));
}

Napi::Value sound::loop(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), instance->getLoop());
}

Napi::Value sound::playing_offset(const Napi::CallbackInfo& info) {
    return from_sf_time(info.Env(), instance->getPlayingOffset());
}

Napi::Value sound::buffer(const Napi::CallbackInfo& info) {
    return buffer_ref_.Value();
}

void sound::set_buffer(const Napi::CallbackInfo& info, const Napi::Value& value) {
    auto buffer_object = as_object(info[0]);
    auto buffer = soundbuffer::Unwrap(as_object(info[0]));

    instance->setBuffer(*buffer->instance.get());
    buffer_ref_ = Napi::Persistent(buffer_object);
}
