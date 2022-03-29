
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/ComparisonUtils.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Area.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Vector2d.cc
	${CMAKE_CURRENT_SOURCE_DIR}/Vector3d.cc

	${CMAKE_CURRENT_SOURCE_DIR}/RandomPositionGenerator.cc

	${CMAKE_CURRENT_SOURCE_DIR}/StringUtils.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
