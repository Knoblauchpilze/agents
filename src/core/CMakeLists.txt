
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/InternalException.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ProgramOptions.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Uuid.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
