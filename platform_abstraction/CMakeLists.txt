# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# Target Declaration -----------------------------------------------------------
add_library(platform_abstraction STATIC)
add_library(platform::abstraction ALIAS platform_abstraction)

# Target Definition ------------------------------------------------------------
target_sources(platform_abstraction PRIVATE CPlatformStorageDelegate.cpp)

target_include_directories(platform_abstraction
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
)

target_link_libraries(platform_abstraction
    PUBLIC
        platform::api
    PRIVATE
        platform::implementation
)