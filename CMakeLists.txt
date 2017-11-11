set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

project(Culling2D)

if (MSVC)
cmake_minimum_required(VERSION 2.8.11)
else()
cmake_minimum_required(VERSION 2.8)
endif()

if (MSVC)
	option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" OFF)
else()
	set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC" ${CMAKE_CXX_FLAGS})
endif()

set(src_common
	culling2d_common/src/Math/culling2d_common.Vector2DF.cpp
	culling2d_common/src/Math/culling2d_common.Vector2DI.cpp
	culling2d_common/src/Math/culling2d_common.RectF.cpp
	culling2d_common/src/Math/culling2d_common.RectI.cpp
	culling2d_common/src/culling2d_common.ReferenceObject.cpp
)


set(src
	Culling2D/Culling/culling2d.World.cpp
	Culling2D/Culling/culling2d.Layer.cpp
	Culling2D/Culling/culling2d.Grid.cpp
	Culling2D/Culling/culling2d.Object.cpp
)

set(src_aabb
	Culling2D_AABB/src/Culling2D_AABB/culling2d_aabb.World.cpp
	Culling2D_AABB/src/Culling2D_AABB/culling2d_aabb.Layer.cpp
	Culling2D_AABB/src/Culling2D_AABB/culling2d_aabb.Grid.cpp
	Culling2D_AABB/src/Culling2D_AABB/culling2d_aabb.Object.cpp
)

list(APPEND src
	${src_common})

list(APPEND src_aabb
	${src_common})

set(test_src
	Culling2DTest/main.cpp)

list(APPEND test_src
	${src})


list(APPEND test_src
	${src_aabb})
	


include_directories(
	./culling2d_common/src
	./Culling2D
	./Culling2D_AABB
)

link_directories(${PROJECT_SOURCE_DIR}/bin/)
link_directories(${PROJECT_BINARY_DIR}/bin/)


add_executable( culling2dtest ${test_src} )
add_library( culling2d_common STATIC ${src_common} )
add_library( culling2d STATIC ${src} )
add_library( culling2d_aabb STATIC ${src_aabb} )


if (MSVC)
	if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		foreach (flag CMAKE_C_FLAGS
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_RELEASE
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE)

			if (${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
			endif()
			if (${flag} MATCHES "/MDd")
				string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
			endif()
		endforeach()
	endif()
endif()


if (MSVC)
set_target_properties(culling2d_common PROPERTIES OUTPUT_NAME_DEBUG "Culling2D_Common_debug" )
set_target_properties(culling2d_common PROPERTIES OUTPUT_NAME_RELEASE "Culling2D_Common" )
set_target_properties(culling2d PROPERTIES OUTPUT_NAME_DEBUG "Culling2D_debug" )
set_target_properties(culling2d PROPERTIES OUTPUT_NAME_RELEASE "Culling2D" )
set_target_properties(culling2d_aabb PROPERTIES OUTPUT_NAME_DEBUG "Culling2D_AABB_debug" )
set_target_properties(culling2d_aabb PROPERTIES OUTPUT_NAME_RELEASE "Culling2D_AABB" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME_DEBUG "Culling2DTest_debug" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME_RELEASE "Culling2DTest" )
else()
set_target_properties(culling2d_common PROPERTIES OUTPUT_NAME_DEBUG "Culling2D_Common" )
set_target_properties(culling2d PROPERTIES OUTPUT_NAME "Culling2D" )
set_target_properties(culling2d_aabb PROPERTIES OUTPUT_NAME "Culling2D_AABB" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME "Culling2DTest" )

set_target_properties(culling2d PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "bin/" )
set_target_properties(culling2d PROPERTIES LIBRARY_OUTPUT_DIRECTORY "bin/" )
endif()

install(
	TARGETS culling2d
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)

install(
	TARGETS culling2d_aabb
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib)

install(
	TARGETS culling2dtest
	RUNTIME DESTINATION bin
	ARCHIVE DESTINATION bin
	LIBRARY DESTINATION bin)

# ForACE
if (MSVC)
else()
	add_definitions(-fPIC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fPIC")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fPIC")
	set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -fPIC")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -fPIC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()
