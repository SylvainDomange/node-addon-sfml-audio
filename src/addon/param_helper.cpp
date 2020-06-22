#include "param_helper.h"

namespace param_helper {

Napi::Object as_object(const Napi::Value& value) {
    return value.As<Napi::Object>();
}

void* as_pointer(const Napi::Value& value) {
	return reinterpret_cast<void*>(value.As<Napi::Number>().Int64Value());
}

float as_float(const Napi::Value& value) {
	return value.As<Napi::Number>().FloatValue();
}

double as_double(const Napi::Value& value) {
	return value.As<Napi::Number>().DoubleValue();
}

int as_int32(const Napi::Value& value) {
	return value.As<Napi::Number>().Int32Value();
}

unsigned as_uint32(const Napi::Value& value) {
	return value.As<Napi::Number>().Uint32Value();
}

long long as_int64(const Napi::Value& value) {
    return value.As<Napi::Number>().Int64Value();
}

bool as_bool(const Napi::Value& value) {
	return value.As<Napi::Boolean>().Value();
}

std::string as_string_utf8(const Napi::Value& value) {
	return value.As<Napi::String>().Utf8Value();
}

sf::Vector3f as_sf_vec3(const Napi::Value& value) {
    auto obj = as_object(value);

    return sf::Vector3f{
        as_float(obj.Get("x")),
        as_float(obj.Get("y")),
        as_float(obj.Get("z"))
        };
}

Napi::Value from_sf_vec3(Napi::Env env, const sf::Vector3f& value) {
    auto v = Napi::Object::New(env);

    v.Set("x", value.x);
    v.Set("y", value.y);
    v.Set("z", value.z);

    return v;
}

sf::Time as_sf_time(const Napi::Value& value) {
    return sf::milliseconds(as_int32(value));
}

Napi::Value from_sf_time(Napi::Env env, sf::Time value) {
    return Napi::Number::New(env, value.asMilliseconds());
}

sf::Music::TimeSpan as_sf_music_time_span(const Napi::Value& value) {
    auto obj = as_object(value);

    return sf::Music::TimeSpan{
        as_sf_time(obj.Get("offset")),
        as_sf_time(obj.Get("length"))
        };
}

Napi::Value from_sf_music_time_span(Napi::Env env, sf::Music::TimeSpan value) {
    auto v = Napi::Object::New(env);

    v.Set("offset", from_sf_time(env, value.offset));
    v.Set("length", from_sf_time(env, value.length));

    return v;
}

std::filesystem::path as_path(const Napi::Value value) {
#ifdef _WIN32
	return value.As<Napi::String>().Utf16Value();
#else
	return value.As<Napi::String>().Utf8Value();
#endif
}

}
