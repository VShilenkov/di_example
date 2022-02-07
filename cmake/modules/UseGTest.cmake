include_guard(GLOBAL)

if (TARGET test_gtest)  # make more strict include guard
    return()
endif()

find_package(GTest CONFIG)

add_library(test_gtest      INTERFACE IMPORTED GLOBAL)
add_library(test_gmock      INTERFACE IMPORTED GLOBAL)
add_library(test_gtest_main INTERFACE IMPORTED GLOBAL)
add_library(test_gmock_main INTERFACE IMPORTED GLOBAL)

add_library(test::gtest       ALIAS test_gtest)
add_library(test::gmock       ALIAS test_gmock)
add_library(test::gtest::main ALIAS test_gtest_main)
add_library(test::gmock::main ALIAS test_gmock_main)

if(GTest_FOUND)
    if(TARGET GTest::gtest_main)        # since cmake 3.20
        target_link_libraries(test_gtest      INTERFACE GTest::gtest)
        target_link_libraries(test_gmock      INTERFACE GTest::gmock)
        target_link_libraries(test_gtest_main INTERFACE GTest::gtest_main)
        target_link_libraries(test_gmock_main INTERFACE GTest::gmock_main)
    elseif(TARGET GTest::Main)          # since cmake 3.5
        target_link_libraries(test_gtest      INTERFACE GTest::GTest)
        target_link_libraries(test_gmock      INTERFACE GMock::GMock)
        target_link_libraries(test_gtest_main INTERFACE GTest::Main)
        target_link_libraries(test_gmock_main INTERFACE GMock::Main)
    else()                              # found but no targets - prior to cmake 3.5
        find_package(Threads REQUIRED) # mandatory

        if(Threads_FOUND)
            target_link_libraries(test_gtest      INTERFACE ${GTEST_LIBRARIES}      Threads::Threads)
            target_link_libraries(test_gmock      INTERFACE ${GMOCK_LIBRARY}        Threads::Threads)
            target_link_libraries(test_gtest_main INTERFACE ${GTEST_MAIN_LIBRARIES} Threads::Threads)
            target_link_libraries(test_gmock_main INTERFACE ${GMOCK_MAIN_LIBRARY}   Threads::Threads)
            
            foreach(_target gtest gmock)
                target_include_directories(test_${_target}      INTERFACE ${GTEST_INCLUDE_DIRS})
                target_include_directories(test_${_target}_main INTERFACE ${GTEST_INCLUDE_DIRS})
            endforeach()
        endif()
    endif()
else()                              # will fetch it
    include(FetchContent)

    FetchContent_Declare(googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG         release-1.11.0
    )

    FetchContent_GetProperties(googletest)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()

    target_link_libraries(test_gtest INTERFACE gtest)
    target_link_libraries(test_gmock INTERFACE gmock)

    target_link_libraries(test_gtest_main INTERFACE gtest_main)
    target_link_libraries(test_gmock_main INTERFACE gmock_main)
endif()

