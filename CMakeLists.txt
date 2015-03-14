# Debug Releaseに限定
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE )

# プロジェクト名
project(Culling2D)

# CMake バージョンチェック
if (MSVC)
cmake_minimum_required(VERSION 2.8.11)
else()
cmake_minimum_required(VERSION 2.8)
endif()

# コンパイル設定
if (MSVC)
	# 特に何も
else()
	set(CMAKE_CXX_FLAGS "-std=c++11 -fPIC" ${CMAKE_CXX_FLAGS})
endif()

# ソースコード設定
set(src
	Culling2D/Common/Math/culling2d.Vector2DF.cpp
	Culling2D/Common/Math/culling2d.Vector2DI.cpp
	Culling2D/Common/Math/culling2d.Vector3DF.cpp
	Culling2D/Common/Math/culling2d.Vector4DF.cpp
	Culling2D/Common/Math/culling2d.RectF.cpp
	Culling2D/Common/Math/culling2d.RectI.cpp
	Culling2D/Common/Math/culling2d.Matrix33.cpp
	Culling2D/Common/Math/culling2d.Matrix44.cpp
	Culling2D/Culling/culling2d.World.cpp
	Culling2D/Culling/culling2d.Layer.cpp
	Culling2D/Culling/culling2d.Grid.cpp
	Culling2D/Culling/culling2d.Object.cpp
	Culling2D/culling2d.ReferenceObject.cpp
)

set(test_src
	Culling2DTest/main.cpp)

list(APPEND test_src
	${src})

# インクルードの設定
include_directories(
	./
)

link_directories(${PROJECT_SOURCE_DIR}/bin/)
link_directories(${PROJECT_BINARY_DIR}/bin/)

# コンパイル先を追加
add_executable( culling2dtest ${test_src} )
add_library( culling2d STATIC ${src} )

# フラグ処理
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

# 出力先の設定
if (MSVC)
set_target_properties(culling2d PROPERTIES OUTPUT_NAME_DEBUG "Culling2D_debug" )
set_target_properties(culling2d PROPERTIES OUTPUT_NAME_RELEASE "Culling2D" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME_DEBUG "Culling2DTest_debug" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME_RELEASE "Culling2DTest" )
else()
set_target_properties(culling2d PROPERTIES OUTPUT_NAME "Culling2D" )
set_target_properties(culling2dtest PROPERTIES OUTPUT_NAME "Culling2DTest" )

set_target_properties(culling2d PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "bin/" )
set_target_properties(culling2d PROPERTIES LIBRARY_OUTPUT_DIRECTORY "bin/" )
endif()

install(
	TARGETS culling2d
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
