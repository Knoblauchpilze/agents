
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/RigidBody.cc
	${CMAKE_CURRENT_SOURCE_DIR}/RigidBodyListener.cc

	${CMAKE_CURRENT_SOURCE_DIR}/PhysicEngine.cc

	${CMAKE_CURRENT_SOURCE_DIR}/CollisionsSolver.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
