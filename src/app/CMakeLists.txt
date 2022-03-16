
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Drawable.cc

	${CMAKE_CURRENT_SOURCE_DIR}/Application.cc
	${CMAKE_CURRENT_SOURCE_DIR}/GenericApplication.cc

	${CMAKE_CURRENT_SOURCE_DIR}/SdlApplication.cc
	${CMAKE_CURRENT_SOURCE_DIR}/SdlEventListener.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
