project(birl)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
set(TARNAME birl)


# program name, version etc

set(PACKAGE_VERSION "1.6.2")
set(PACKAGE_NAME "Birl")
set(PACKAGE_TARNAME "${TARNAME}")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/JessonChan/birl")

find_package(PkgConfig REQUIRED)

##########################################################################
if(NOT DEFINED BIN_INSTALL_DIR)
    set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
endif(NOT DEFINED BIN_INSTALL_DIR)
if(NOT DEFINED DATA_INSTALL_DIR)
    set(DATA_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/share")
endif(NOT DEFINED DATA_INSTALL_DIR)
if(NOT DEFINED MAN_INSTALL_DIR)
    set(MAN_INSTALL_DIR "${DATA_INSTALL_DIR}/man")
endif(NOT DEFINED MAN_INSTALL_DIR)
if(NOT DEFINED DESKTOP_INSTALL_DIR)
    set(DESKTOP_INSTALL_DIR "${DATA_INSTALL_DIR}/applications/")
endif(NOT DEFINED DESKTOP_INSTALL_DIR)
if(NOT DEFINED LOCALE_INSTALL_DIR)
    set(LOCALE_INSTALL_DIR "${DATA_INSTALL_DIR}/locale/")
endif(NOT DEFINED LOCALE_INSTALL_DIR)

add_definitions(-DDATA_INSTALL_DIR="${DATA_INSTALL_DIR}")

file(GLOB birl_DATAFILE "birl/*")
install(FILES ${birl_DATAFILE} DESTINATION ${DATA_INSTALL_DIR}/birl/)


configure_file(./birl.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/birl.desktop)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/birl.desktop DESTINATION ${DESKTOP_INSTALL_DIR})


# compile option switch
option(NLS "Native language support" ON)

# build requirements
find_package(PkgConfig REQUIRED)
if(NLS)
	find_package(Gettext)
endif(NLS)

# build requirements
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(GDKPIXBUF REQUIRED gdk-pixbuf-2.0)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)


##########################################################################
add_definitions(-g -Wall -Wextra)
if(NLS AND GETTEXT_FOUND)
	add_definitions(-DGETTEXT_PACKAGE="${PACKAGE_TARNAME}")
	add_definitions(-DENABLE_NLS="1")
	message(STATUS "Native language support:  YES" )
else(NLS AND GETTEXT_FOUND)
	message(STATUS "Native language support:  NO" )
endif(NLS AND GETTEXT_FOUND)
add_definitions(-DLOCALE_DIR="${LOCALE_INSTALL_DIR}")

##########################################################################

include_directories(
    ${GTK2_INCLUDE_DIRS}
    ${GDKPIXBUF_INCLUDE_DIRS}
    ${GLIB2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(birl_SRC
    about.c
    common.c  
    config.c  
    dlfunc.c  
    main.c  
    md5.c  
    mentohust.c  
    mycheck.c  
    myconfig.c  
    myfunc.c  
    myini.c  
    mystate.c  
    trayicon.c
)

add_executable(birl ${birl_SRC})
target_link_libraries(birl ${GTK2_LIBRARIES} ${GDKPIXBUF_LIBRARIES} ${GTHREAD2_LIBRARIES})

install(TARGETS birl RUNTIME DESTINATION ${BIN_INSTALL_DIR})
