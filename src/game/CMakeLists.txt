
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Game.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SavedGames.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GameState.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

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
