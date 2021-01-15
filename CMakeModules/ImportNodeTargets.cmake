execute_process(COMMAND node -p "require('node-addon-api').include"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE NODE_ADDON_API_DIR)
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

add_library(node::node-addon-api INTERFACE IMPORTED)
set_target_properties(node::node-addon-api PROPERTIES
	INTERFACE_COMPILE_DEFINITIONS NAPI_VERSION=5
	INTERFACE_COMPILE_DEFINITIONS NAPI_CPP_EXCEPTIONS
	INTERFACE_INCLUDE_DIRECTORIES ${NODE_ADDON_API_DIR})

if(WIN32)
	add_library(node::cmake-js UNKNOWN IMPORTED)
	set_target_properties(node::cmake-js PROPERTIES
		IMPORTED_LOCATION ${CMAKE_JS_LIB}
		INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_JS_INC})
elseif(UNIX)
	add_library(node::cmake-js INTERFACE IMPORTED)
	set_target_properties(node::cmake-js PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_JS_INC})
endif()

add_library(libs::node INTERFACE IMPORTED)
target_link_libraries(libs::node INTERFACE node::node-addon-api node::cmake-js)

if(WIN32)
	target_sources(libs::node INTERFACE ${CMAKE_JS_SRC})
endif()
