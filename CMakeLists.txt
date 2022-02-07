# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# Project Declaration ---------------------------------------------------------
project(di-example
    VERSION         0.0.1
    DESCRIPTION    "di-example"
    HOMEPAGE_URL   ""
    LANGUAGES       CXX
)

# Dependency Resolution -------------------------------------------------------
# in normal case it should be find_package(platform_implementation REQUIRED)
# because this is some outer component which we consumes
# but for our example it will be built here and we include this directly

add_subdirectory(platform_implementation)

# Subdirectories --------------------------------------------------------------
add_subdirectory(cmake)
add_subdirectory(platform_api)
add_subdirectory(platform_abstraction)
add_subdirectory(platform_consumer)

# Target Declaration -----------------------------------------------------------
add_executable(${PROJECT_NAME})

# Target Definition ------------------------------------------------------------
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

## Dependency on a platform abstraction only in main
## consumer has dependency only on interface
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        platform::abstraction
        platform::consumer
)


# we decide to do some tests
include(CTest)
add_subdirectory(tests)