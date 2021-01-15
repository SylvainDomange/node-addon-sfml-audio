add_library(sfml-system UNKNOWN IMPORTED)
set_target_properties(sfml-system PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/sfml-system-s.lib"
	IMPORTED_LOCATION_DEBUG "${VCPKG_LIB_DIR}/sfml-system-s-d.lib")

add_library(sfml-audio UNKNOWN IMPORTED)
set_target_properties(sfml-audio PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/sfml-audio-s.lib"
	IMPORTED_LOCATION_DEBUG "${VCPKG_LIB_DIR}/sfml-audio-s-d.lib")

add_library(openal UNKNOWN IMPORTED)
set_target_properties(openal PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/OpenAL32.lib")

add_library(flac UNKNOWN IMPORTED)
set_target_properties(flac PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/FLAC.lib")

add_library(ogg UNKNOWN IMPORTED)
set_target_properties(ogg PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/ogg.lib")

add_library(vorbis UNKNOWN IMPORTED)
set_target_properties(vorbis PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/vorbis.lib")

add_library(vorbisenc UNKNOWN IMPORTED)
set_target_properties(vorbisenc PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/vorbisenc.lib")

add_library(vorbisfile UNKNOWN IMPORTED)
set_target_properties(vorbisfile PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/vorbisfile.lib")

add_library(mpg123 UNKNOWN IMPORTED)
set_target_properties(mpg123 PROPERTIES
	IMPORTED_LOCATION "${VCPKG_LIB_DIR}/libmpg123.lib")

add_library(libs::audio INTERFACE IMPORTED)
target_link_libraries(libs::audio INTERFACE sfml-system sfml-audio openal flac ogg vorbis vorbisenc vorbisfile mpg123 winmm.lib)
target_include_directories(libs::audio INTERFACE ${VCPKG_INC_DIR})
target_compile_definitions(libs::audio INTERFACE SFML_STATIC)
