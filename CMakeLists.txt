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
include(FeatureSummary)

# Options ---------------------------------------------------------------------
project_options(${PROJECT_NAME})

option(WITH_INCLUDE_WHAT_YOU_USE "Build with include-what-you-use globaly enabled" OFF)
add_feature_info([GLOBAL].include-what-you-use WITH_INCLUDE_WHAT_YOU_USE
    "Build with include-what-you-use globaly enabled"
)

option(WITH_CLANG_TIDY "Build with clang-tidy globaly enabled" OFF)
add_feature_info([GLOBAL].clang-tidy WITH_CLANG_TIDY
    "Build with clang-tidy globaly enabled"
)

option(WITH_LINK_WHAT_YOU_USE "Build with link-what-you-use globaly enabled" OFF)
add_feature_info([GLOBAL].link-what-you-use WITH_LINK_WHAT_YOU_USE
    "Build with link-what-you-use globaly enabled"
)

if(WITH_INCLUDE_WHAT_YOU_USE)
    find_program(iwyu_executable include-what-you-use REQUIRED)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "${iwyu_executable}")
endif()

if(WITH_CLANG_TIDY)
    find_program(CLANG_TIDY_EXECUTABLE 
        NAMES
            clang-tidy
            clang-tidy-15
            clang-tidy-14
            clang-tidy-13
            clang-tidy-12
            clang-tidy-11
        REQUIRED
    )
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE}" -p "${CMAKE_BINARY_DIR}")
endif() 

if(WITH_LINK_WHAT_YOU_USE)
    set(CMAKE_LINK_WHAT_YOU_USE True)
endif()

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