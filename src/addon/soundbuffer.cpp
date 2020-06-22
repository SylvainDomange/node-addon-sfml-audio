#include "soundbuffer.h"
#include "param_helper.h"

using namespace param_helper;

Napi::FunctionReference soundbuffer::constructor;

soundbuffer::soundbuffer(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<soundbuffer>(info),
    instance{std::make_unique<sf::SoundBuffer>()}
{}

Napi::Object soundbuffer::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope{env};

    Napi::Function func =
    DefineClass(env, "SoundBuffer", {
        InstanceMethod("ref", &soundbuffer::ref),
        InstanceMethod("unref", &soundbuffer::unref),
        InstanceMethod("release", &soundbuffer::release),
        InstanceMethod("loadFromFile", &soundbuffer::load_from_file),
        InstanceMethod("loadFromMemory", &soundbuffer::load_from_memory),
        InstanceMethod("loadFromSamples", &soundbuffer::load_from_samples),
        InstanceMethod("saveToFile", &soundbuffer::save_to_file),
        InstanceAccessor<&soundbuffer::samples>("samples"),
        InstanceAccessor<&soundbuffer::sample_rate>("sampleRate"),
        InstanceAccessor<&soundbuffer::channel_count>("channelCount"),
        InstanceAccessor<&soundbuffer::duration>("duration"),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("SoundBuffer", func);

    return exports;
}

Napi::Value soundbuffer::ref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Ref());
}

Napi::Value soundbuffer::unref(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Unref());
}

Napi::Value soundbuffer::release(const Napi::CallbackInfo& info) {
    Reset();

    return info.Env().Undefined();
}

Napi::Value soundbuffer::load_from_file(const Napi::CallbackInfo& info) {
    auto path = as_path(info[0]).string();
    auto ok = instance->loadFromFile(path);

    if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to load sound file " + path);

    return info.Env().Undefined();
}

Napi::Value soundbuffer::load_from_memory(const Napi::CallbackInfo& info) {
    auto buffer = info[0].As<Napi::Uint8Array>();
    auto ok = instance->loadFromMemory(buffer.Data(), buffer.ByteLength());

    if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to load sound file from memory");

    membuf_ref_ = Napi::Persistent(as_object(info[0]));

    return info.Env().Undefined();
}

Napi::Value soundbuffer::load_from_samples(const Napi::CallbackInfo& info) {
    auto samples = info[0].As<Napi::Int16Array>();
    auto ok = instance->loadFromSamples(samples.Data(), samples.ElementLength(), as_uint32(info[1]), as_uint32(info[2]));

    if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to load sound file from samples");

    return info.Env().Undefined();
}

Napi::Value soundbuffer::save_to_file(const Napi::CallbackInfo& info) {
    auto path = as_path(info[0]).string();
    auto ok = instance->saveToFile(path);

    if (!ok)
        throw Napi::Error::New(info.Env(), "Failed to save sound file " + path);

    return info.Env().Undefined();
}

Napi::Value soundbuffer::samples(const Napi::CallbackInfo& info) {
    return Napi::Buffer<int16_t>::New(info.Env(), const_cast<int16_t*>(instance->getSamples()), instance->getSampleCount());
}

Napi::Value soundbuffer::sample_count(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getSampleCount());
}

Napi::Value soundbuffer::sample_rate(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getSampleRate());
}

Napi::Value soundbuffer::channel_count(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), instance->getChannelCount());
}

Napi::Value soundbuffer::duration(const Napi::CallbackInfo& info) {
	return from_sf_time(info.Env(), instance->getDuration());
}
