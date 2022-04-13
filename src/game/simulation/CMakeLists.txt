
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Behaviors.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Agents.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Objects.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Initialization.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
