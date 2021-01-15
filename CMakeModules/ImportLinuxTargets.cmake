find_library(SFML_SYSTEM_LIB NAMES sfml-system)
find_library(SFML_AUDIO_LIB NAMES sfml-audio)
find_library(MPG123_LIB NAMES mpg123)

add_library(sfml-system UNKNOWN IMPORTED)
set_target_properties(sfml-system PROPERTIES
	IMPORTED_LOCATION ${SFML_SYSTEM_LIB})

add_library(sfml-audio UNKNOWN IMPORTED)
set_target_properties(sfml-audio PROPERTIES
	IMPORTED_LOCATION ${SFML_AUDIO_LIB})

add_library(mpg123 UNKNOWN IMPORTED)
set_target_properties(mpg123 PROPERTIES
	IMPORTED_LOCATION ${MPG123_LIB})

add_library(libs::audio INTERFACE IMPORTED)
target_link_libraries(libs::audio INTERFACE sfml-system sfml-audio mpg123)
