
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/UserData.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Perception.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Frustum.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Animat.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Agent.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
