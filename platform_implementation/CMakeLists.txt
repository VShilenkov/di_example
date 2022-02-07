# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# Project Declaration ---------------------------------------------------------
project(platform-implementation
    VERSION         0.0.1
    DESCRIPTION    "platform-implementation"
    HOMEPAGE_URL   ""
    LANGUAGES       CXX
)

# Target Declaration -----------------------------------------------------------
add_library(${PROJECT_NAME} STATIC)
add_library(platform::implementation ALIAS ${PROJECT_NAME})

# Target Definition ------------------------------------------------------------
target_sources(${PROJECT_NAME} PRIVATE CPlatformStorageService.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
)




