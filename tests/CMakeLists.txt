cmake_minimum_required(VERSION 3.12)
project(tdd-session)


include(UseGTest)
enable_testing()


add_executable(platform-consumer-test)
target_sources(platform-consumer-test 
    PRIVATE 
        CPlatformConsumerTest.cpp
)

target_include_directories(platform-consumer-test 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(platform-consumer-test
    PRIVATE
        platform::consumer          # this is the target where our class-under-test defined
        test::gmock::main           # this is to have main(), gmock functionality and gtest
)

add_test(
    NAME platform-consumer-test
    COMMAND $<TARGET_FILE:platform-consumer-test>
)

