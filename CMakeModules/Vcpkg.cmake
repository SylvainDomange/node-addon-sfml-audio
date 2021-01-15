if(NOT DEFINED ENV{VcpkgDir})
	message(FATAL_ERROR "env variable 'VcpkgDir' not defined")
else()
	set(VcpkgDir $ENV{VcpkgDir})
endif()

if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
	set(VCPKG_BASE_DIR "${VcpkgDir}/installed/x64-windows-static")
elseif(${CMAKE_VS_PLATFORM_NAME} STREQUAL "Win32")
	set(VCPKG_BASE_DIR "${VcpkgDir}/installed/x86-windows-static")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(VCPKG_LIB_DIR "${VCPKG_BASE_DIR}/debug/lib")
else()
	set(VCPKG_LIB_DIR "${VCPKG_BASE_DIR}/lib")
endif()

set(VCPKG_INC_DIR "${VCPKG_BASE_DIR}/include")
