PROJECT(nemocnicny_system C CXX)

cmake_minimum_required(VERSION 2.4)
cmake_policy(SET CMP0003 NEW)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -fexceptions -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "-O2 -g3 -ggdb -Wall -Wextra -fexceptions -DDEBUG")

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "Configured to compile including full debug information in the executables")
	add_definitions(-DQT_DEBUG)
else(CMAKE_BUILD_TYPE MATCHES Debug)
	message(STATUS "Configured to compile including debug information in the executables")
	set(CMAKE_BUILD_TYPE Release)
	add_definitions(-DQT_NO_DEBUG)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

find_package(Qt4 REQUIRED)

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_BINARY_DIR}/src"
	${QT_INCLUDES}
)

set(nemsys_SRCS
	main.cpp
	src/Comparator.cpp
	src/Meno.cpp
	src/Pacient.cpp
	src/RodCis.cpp
)

#qt4_wrap_cpp(nemsys_MOC_SRCS ${nemsys_MOC_HDRS})
#qt4_wrap_ui(nemsys_UIS_SRCS ${nemsys_UIS})
#qt4_add_resources(nemsys_QRC_SRCS ${nemsys_QRC})
#qt4_add_translation(lrelease_outputs ${nemsys_TRANS})

add_executable(nemsys
	${nemsys_SRCS}
)

target_link_libraries(nemsys ${QT_LIBRARIES})
