#include "listener.h"
#include "mp3_reader.h"
#include "music.h"
#include "sound.h"
#include "soundbuffer.h"

Napi::Object build_module(Napi::Env env, Napi::Object exports) {
    mp3_reader::init();

    listener::init(env, exports);
    music::init(env, exports);
    sound::init(env, exports);
    soundbuffer::init(env, exports);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, build_module)
