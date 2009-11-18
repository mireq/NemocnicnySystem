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
include(${QT_USE_FILE})

find_package(Boost COMPONENTS serialization REQUIRED)

set(SUBDIRS
	src/lib
	src/model
	src/ui
)

include_directories(
	"${PROJECT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_BINARY_DIR}"
	${QT_INCLUDES}
	${Boost_INCLUDE_DIRS}
)

foreach(SUBDIR ${SUBDIRS})
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}"
		"${CMAKE_CURRENT_BINARY_DIR}/${SUBDIR}"
	)
endforeach(SUBDIR)

set(nemsys_SRCS
	main.cpp
	src/lib/Comparator.cpp
	src/lib/Hospitalizacia.cpp
	src/lib/Meno.cpp
	src/lib/Pacient.cpp
	src/lib/RodCis.cpp
	src/model/Nemocnica.cpp
	src/model/NemocnicnySystem.cpp
	src/model/PacientiInfoModel.cpp
	src/ui/HospitalizaciaEdit.cpp
	src/ui/HospitalizaciaWizard.cpp
	src/ui/MainWindow.cpp
	src/ui/MenoRCEdit.cpp
	src/ui/NemocnicaVyber.cpp
	src/ui/NemocniceList.cpp
	src/ui/PacientEdit.cpp
	src/ui/PacientInfoWidget.cpp
)

set(nemsys_MOC_HDRS
	src/model/NemocnicnySystem.h
	src/model/PacientiInfoModel.h
	src/ui/HospitalizaciaEdit.h
	src/ui/HospitalizaciaWizard.h
	src/ui/MainWindow.h
	src/ui/MenoRCEdit.h
	src/ui/NemocnicaVyber.h
	src/ui/NemocniceList.h
	src/ui/PacientEdit.h
	src/ui/PacientInfoWidget.h
)

set(nemsys_HDRS
	src/lib/serialization.h
	src/lib/AVLTree.h
	src/lib/Comparator.h
	src/lib/Hospitalizacia.h
	src/lib/Iterator.h
	src/lib/Meno.h
	src/lib/Pacient.h
	src/lib/RodCis.h
	src/model/Nemocnica.h
)

set(nemsys_UIS
	ui/HospitalizaciaEdit.ui
	ui/MainWindow.ui
	ui/NemocnicaVyber.ui
	ui/PacientEdit.ui
)

set(nemsys_QRC
	ui/data.qrc
)

qt4_wrap_cpp(nemsys_MOC_SRCS ${nemsys_MOC_HDRS})
qt4_wrap_ui(nemsys_UIS_SRCS ${nemsys_UIS})
qt4_add_resources(nemsys_QRC_SRCS ${nemsys_QRC})
#qt4_add_translation(lrelease_outputs ${nemsys_TRANS})

add_executable(nemsys
	${nemsys_SRCS}
	${nemsys_HDRS}
	${nemsys_UIS_SRCS}
	${nemsys_MOC_SRCS}
	${nemsys_QRC_SRCS}
)

target_link_libraries(nemsys ${Boost_LIBRARIES} ${QT_LIBRARIES})

# podpora PCH
# https://svn.kvirc.de/kvirc/browser/trunk/kvirc/cmake/modules/FindPCHSupport.cmake?rev=1454
option(WANT_PCH "Whether to use pre-compiled headers" OFF)
set(USE_PCH FALSE)
if (WANT_PCH)
	find_package(PCHSupport)
	if (PCHSupport_FOUND)
		add_definitions(-DUSE_PCH)
		set(USE_PCH TRUE)
		option(WANT_PCH "Whether to use pre-compiled headers""")
		message(STATUS "Enabling precompiled headers for GCC ${gcc_compiler_version}")
	endif (PCHSupport_FOUND)
endif (WANT_PCH)

if(USE_PCH)
	add_precompiled_header(nemsys src/pch.h)
endif(USE_PCH)

