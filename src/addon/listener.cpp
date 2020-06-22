#include "listener.h"
#include "param_helper.h"

#include <SFML/Audio/Listener.hpp>

using namespace param_helper;

Napi::FunctionReference listener::constructor;

listener::listener(const Napi::CallbackInfo& info) :
    Napi::ObjectWrap<listener>{info}
{}

Napi::Object listener::init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope{env};

    Napi::Function func =
    DefineClass(env, "Listener", {
        StaticAccessor<&listener::global_volume, &listener::set_global_volume>("globalVolume"),
        StaticAccessor<&listener::position, &listener::set_position>("position"),
        StaticAccessor<&listener::direction, &listener::set_direction>("direction"),
        StaticAccessor<&listener::up_vector, &listener::set_up_vector>("upVector"),
        });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Listener", func);

    return exports;
}

Napi::Value listener::global_volume(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), sf::Listener::getGlobalVolume());
}

void listener::set_global_volume(const Napi::CallbackInfo& info, const Napi::Value& value) {
    sf::Listener::setGlobalVolume(std::clamp(as_float(value), 0.0f, 100.0f));
}

Napi::Value listener::position(const Napi::CallbackInfo& info) {
    return from_sf_vec3(info.Env(), sf::Listener::getPosition());
}

void listener::set_position(const Napi::CallbackInfo& info, const Napi::Value& value) {
    sf::Listener::setPosition(as_sf_vec3(value));
}

Napi::Value listener::direction(const Napi::CallbackInfo& info) {
    return from_sf_vec3(info.Env(), sf::Listener::getDirection());
}

void listener::set_direction(const Napi::CallbackInfo& info, const Napi::Value& value) {
    sf::Listener::setDirection(as_sf_vec3(value));
}

Napi::Value listener::up_vector(const Napi::CallbackInfo& info) {
	return from_sf_vec3(info.Env(), sf::Listener::getUpVector());
}

void listener::set_up_vector(const Napi::CallbackInfo& info, const Napi::Value& value) {
    sf::Listener::setUpVector(as_sf_vec3(value));
}
