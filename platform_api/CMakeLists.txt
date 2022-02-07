# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.12...3.18)

# Target Declaration -----------------------------------------------------------
## header-only library for platform interfaces
add_library(platform_api INTERFACE)
add_library(platform::api ALIAS platform_api)


# Target Definition ------------------------------------------------------------
target_include_directories(platform_api
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
)

set(platform_api_PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/IStorageService.hpp)

set_target_properties(platform_api
    PROPERTIES
        PUBLIC_HEADER "${platform_api_PUBLIC_HEADER}"
)


# Target Installation ---------------------------------------------------------
install(TARGETS platform_api
    PUBLIC_HEADER   DESTINATION ${PACKAGE_INSTALL_INCLUDE_DIR}
    COMPONENT       library/api
)
