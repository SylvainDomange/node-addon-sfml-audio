cmake_minimum_required(VERSION 3.16)
project(sfml-audio-node)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeModules")

include(Config)
include(ImportNodeTargets)
if(WIN32)
	include(Vcpkg)
	include(ImportWindowsTargets)
elseif(UNIX)
	include(ImportLinuxTargets)
	add_compile_options(-Wall -Wextra)
endif()

file(GLOB SRC "src/addon/*.cpp")
add_library(addon SHARED ${SRC})
target_compile_features(addon PRIVATE cxx_std_17)

set_target_properties(addon PROPERTIES
	PREFIX ""
	SUFFIX ".node"
	OUTPUT_NAME "sfml_audio")

target_link_libraries(addon PRIVATE
	libs::node libs::audio)

if(WIN32)
	install(TARGETS addon RUNTIME DESTINATION .)
elseif(UNIX)
	install(TARGETS addon LIBRARY DESTINATION .)
endif()
install(FILES "src/Ts/sfml_audio.d.ts" DESTINATION .)
