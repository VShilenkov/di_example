# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# Target Declaration -----------------------------------------------------------
add_library(platform_consumer STATIC)
add_library(platform::consumer ALIAS platform_consumer)

# Target Definition ------------------------------------------------------------
target_sources(platform_consumer PRIVATE CPlatformConsumer.cpp)

target_include_directories(platform_consumer
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${PACKAGE_INSTALL_INCLUDE_DIR}>
)

target_link_libraries(platform_consumer
    PUBLIC
        platform::api
    PRIVATE
        platform::abstraction
)