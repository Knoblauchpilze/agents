
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Initializer.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Component.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Entity.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Environment.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Launcher.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
