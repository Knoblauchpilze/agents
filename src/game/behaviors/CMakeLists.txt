
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Utils.cc

	${CMAKE_CURRENT_SOURCE_DIR}/DirectedPath.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ForceBased.cc
	${CMAKE_CURRENT_SOURCE_DIR}/AgentData.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Behavior.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
