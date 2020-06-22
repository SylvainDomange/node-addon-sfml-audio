#include "music.h"
#include "param_helper.h"

using namespace param_helper;

Napi::FunctionReference music::constructor;

music::music(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<music>(info),
    instance{std::make_unique<sf::Music>()}
{
    this->soundsource_impl::instance = instance.get();
    this->soundstream_impl::instance = instance.get();
}

Napi::Object music::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope{env};

    Napi::Function func =
    DefineClass(env, "Music", {
        InstanceMethod("ref", &music::ref),
        InstanceMethod("unref", &music::unref),
        InstanceMethod("release", &music::release),
        SOUNDSOURCEIMPL_INSTANCEACCESSORS(music),
        SOUNDSOURCEIMPL_INSTANCEMETHODS(),
        SOUNDSTREAMIMPL_INSTANCEACCESSORS(music),
        InstanceMethod("openFromFile", &music::open_from_file),
        InstanceMethod("openFromMemory", &music::open_from_memory),
        InstanceAccessor<&music::duration>("duration"),
        InstanceAccessor<&music::loop_points, &music::set_loop_points>("loopPoints")
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Music", func);

    return exports;
}

Napi::Value music::ref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Ref());
}

Napi::Value music::unref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Unref());
}

Napi::Value music::release(const Napi::CallbackInfo& info) {
    Reset();

    return info.Env().Undefined();
}

Napi::Value music::open_from_file(const Napi::CallbackInfo& info) {
    auto path = as_path(info[0]).string();
    auto ok = instance->openFromFile(path);

    if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to open sound file " + path);

    return info.Env().Undefined();
}

Napi::Value music::open_from_memory(const Napi::CallbackInfo& info) {
    auto buffer = info[0].As<Napi::Uint8Array>();
    auto ok = instance->openFromMemory(buffer.Data(), buffer.ByteLength());

     if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to open sound file from memory");

    membuf_ref_ = Napi::Persistent(as_object(info[0]));

    return info.Env().Undefined();
}

Napi::Value music::duration(const Napi::CallbackInfo& info) {
	return from_sf_time(info.Env(), instance->getDuration());
}

Napi::Value music::loop_points(const Napi::CallbackInfo& info) {
    return from_sf_music_time_span(info.Env(), instance->getLoopPoints());
}

void music::set_loop_points(const Napi::CallbackInfo& info, const Napi::Value& value) {
    instance->setLoopPoints(as_sf_music_time_span(value));
}
