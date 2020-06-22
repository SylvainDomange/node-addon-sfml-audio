{
    'targets': [{
        'target_name': 'sfml_audio',
        'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
        'conditions': [
            ['OS=="win"', {
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'RuntimeLibrary': 1,
                        'ExceptionHandling': 1,
                        'AdditionalOptions': ['/std:c++17']
                    },
                    'VCLinkerTool': {
                        'AdditionalLibraryDirectories': [
                            '<(module_root_dir)/deps/windows-<(target_arch)/lib'
                        ]
                    }
                },
                'defines': ['_HAS_EXCEPTIONS=1'],
                'include_dirs': [
                    '<(module_root_dir)/deps/windows-<(target_arch)/include'
                ],
                'libraries': [
                    'sfml-system-s.lib', 'sfml-audio-s.lib', 'OpenAL32.lib', 'FLAC.lib', 'ogg.lib',
                    'vorbis.lib', 'vorbisenc.lib', 'vorbisfile.lib', 'Winmm.lib', 'libmpg123.lib'
                ]
            }],
            ['OS=="linux"', {
                'cflags_cc': ['-std=c++17', '-fexceptions'],
                'libraries': ['-lsfml-system', '-lsfml-audio', '-lmpg123']
            }]
        ],
        'defines': ['NAPI_CPP_EXCEPTIONS', 'GUI', 'SFML_STATIC'],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
        ],
        'sources': [
            'src/addon/listener.cpp',
            'src/addon/main.cpp',
            'src/addon/mp3_reader.cpp',
            'src/addon/music.cpp',
            'src/addon/param_helper.cpp',
            'src/addon/sound.cpp',
            'src/addon/soundbuffer.cpp',
            'src/addon/soundsource_impl.cpp',
            'src/addon/soundstream_impl.cpp'
        ]
    }]
}
