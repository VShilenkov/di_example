# Requirements to the cmake ---------------------------------------------------
cmake_minimum_required(VERSION 3.16)

# Project Declaration ---------------------------------------------------------
project(di-example
    VERSION         0.0.1
    DESCRIPTION    "di-example"
    HOMEPAGE_URL   ""
    LANGUAGES       CXX
)

# Global settings -------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Target Declaration ----------------------------------------------------------
add_executable(${PROJECT_NAME})

# Includes --------------------------------------------------------------------
add_subdirectory(cmake) # support local includes

include(ProjectOptions)

# Options ---------------------------------------------------------------------
project_options(${PROJECT_NAME})

# Dependency Resolution -------------------------------------------------------
# in normal case it should be find_package(platform_implementation REQUIRED)
# because this is some outer component which we consumes
# but for our example it will be built here and we include this directly

add_subdirectory(platform_implementation)

# Subdirectories --------------------------------------------------------------
add_subdirectory(platform_api)
add_subdirectory(platform_abstraction)
add_subdirectory(platform_consumer)


# Target Definition ------------------------------------------------------------
target_sources(${PROJECT_NAME} PRIVATE main.cpp)

## Dependency on a platform abstraction only in main
## consumer has dependency only on interface
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        platform::abstraction
        platform::consumer
)

if(WITH_UNIT_TEST_${PROJECT_NAME})
    # we decide to do some tests
    include(CTest)
    add_subdirectory(tests)
endif()

if(WITH_DOCUMENTING_${suffix})
    # here I could add docs subdirectory to be able to generate documentation if any
endif()

# Feature summary --------------------------------------------------------------
feature_summary(WHAT ALL
    DESCRIPTION "-- [${PROJECT_NAME} summary] ---------------------------------"
)