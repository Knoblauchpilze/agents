
target_sources (main-app_lib PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Behavior.cc

	${CMAKE_CURRENT_SOURCE_DIR}/MotionBehavior.cc
	${CMAKE_CURRENT_SOURCE_DIR}/FixedSpeedBehavior.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ForceBasedBehavior.cc

	${CMAKE_CURRENT_SOURCE_DIR}/DirectedMotionBehavior.cc
	${CMAKE_CURRENT_SOURCE_DIR}/DirectedFixedSpeedBehavior.cc

	${CMAKE_CURRENT_SOURCE_DIR}/WanderBehavior.cc
	${CMAKE_CURRENT_SOURCE_DIR}/ImpulseBehavior.cc
	)

target_include_directories (main-app_lib PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	)
