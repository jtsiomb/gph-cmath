cmake_minimum_required(VERSION 2.8.8)
project(gph-cmath)

include(GNUInstallDirs)

set(SO_MAJOR 0)
set(SO_MINOR 1)

file(GLOB hdr "src/*.h")
file(GLOB inl "src/*.inl")
list(APPEND hdr ${inl})
file(GLOB src "src/*.c")

add_library(cgmath SHARED ${src} ${hdr})
add_library(cgmath-static STATIC ${src} ${hdr})

set_target_properties(cgmath PROPERTIES VERSION ${SO_MAJOR}.${SO_MINOR})
set_target_properties(cgmath PROPERTIES SOVERSION ${SO_MAJOR})

if(MSVC)
	set_target_properties(cgmath PROPERTIES PREFIX "lib")
	set_target_properties(cgmath PROPERTIES IMPORT_PREFIX "lib")
	set_target_properties(cgmath-static PROPERTIES PREFIX "lib")

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4996")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall")
endif()

if(NOT WIN32)
	set_target_properties(cgmath-static PROPERTIES OUTPUT_NAME cgmath)
endif()

install(TARGETS cgmath
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS cgmath-static
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES ${hdr} DESTINATION include/cgmath)
