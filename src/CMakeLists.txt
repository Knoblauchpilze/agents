project (main-app_lib)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library (main-app_lib SHARED "")

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/utils
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/core
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/agents
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/app
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/behaviors
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/environment
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/influences
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/objects
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/physics
	)

target_sources (main-app_lib PRIVATE
	)
