
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/RigidBody.cc
	${CMAKE_CURRENT_SOURCE_DIR}/MovingObject.cc
	${CMAKE_CURRENT_SOURCE_DIR}/CollisionSolver.cc
	${CMAKE_CURRENT_SOURCE_DIR}/PhysicEngine.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
