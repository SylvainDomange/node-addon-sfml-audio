#pragma once

#include <filesystem>
#include <optional>
#include <vector>

#include <napi.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Audio/Music.hpp>

namespace param_helper {

Napi::Object as_object(const Napi::Value& value);
void* as_pointer(const Napi::Value& value);
float as_float(const Napi::Value& value);
double as_double(const Napi::Value& value);
int as_int32(const Napi::Value& value);
unsigned as_uint32(const Napi::Value& value);
long long as_int64(const Napi::Value& value);
bool as_bool(const Napi::Value& value);
std::string as_string_utf8(const Napi::Value& value);
sf::Vector3f as_sf_vec3(const Napi::Value& value);
Napi::Value from_sf_vec3(Napi::Env env, const sf::Vector3f& value);
sf::Time as_sf_time(const Napi::Value& value);
Napi::Value from_sf_time(Napi::Env env, sf::Time value);
sf::Music::TimeSpan as_sf_music_time_span(const Napi::Value& value);
Napi::Value from_sf_music_time_span(Napi::Env env, sf::Music::TimeSpan value);
std::filesystem::path as_path(const Napi::Value value);

}
