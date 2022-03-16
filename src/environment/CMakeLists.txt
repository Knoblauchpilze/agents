
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/TimeManager.cc

	${CMAKE_CURRENT_SOURCE_DIR}/DrawablesUpdater.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Environment.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentDrawer.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentListener.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentLauncher.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentInitializer.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
