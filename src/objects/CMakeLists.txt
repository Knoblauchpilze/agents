
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/BoundingBox.cc

	${CMAKE_CURRENT_SOURCE_DIR}/MovingObject.cc

	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentalObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentalObjectDrawer.cc
	${CMAKE_CURRENT_SOURCE_DIR}/EnvironmentalObjectListener.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)

add_subdirectory (
	${CMAKE_CURRENT_SOURCE_DIR}/frustum
	)
