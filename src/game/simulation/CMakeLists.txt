
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Impulse.cc

	${CMAKE_CURRENT_SOURCE_DIR}/MoveTo.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Fish.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Initialization.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
