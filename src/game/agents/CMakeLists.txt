
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Agent.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Animat.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Body.cc

	${CMAKE_CURRENT_SOURCE_DIR}/BodyDrawer.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Perception.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
