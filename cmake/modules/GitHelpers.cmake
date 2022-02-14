include_guard(GLOBAL)

find_package(Git)

macro(directory_git_hash)
    set(_GIT_HEAD_HASH GIT_NOTFOUND)
    if(Git_FOUND)
        execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --verify HEAD
            WORKING_DIRECTORY   "${CMAKE_CURRENT_LIST_DIR}"
            RESULT_VARIABLE     EXECUTE_PROCESS_RESULT
            OUTPUT_VARIABLE     _GIT_HEAD_HASH
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        if(NOT EXECUTE_PROCESS_RESULT EQUAL 0)
            message(WARNING "execute_process failed with: ${EXECUTE_PROCESS_RESULT}")
        endif()
    endif()
endmacro()

macro(directory_git_dirty)
    set(_GIT_DIRTY false)
    if(Git_FOUND)
        execute_process(COMMAND "${GIT_EXECUTABLE}" status --porcelain
            WORKING_DIRECTORY   "${CMAKE_CURRENT_LIST_DIR}"
            RESULT_VARIABLE     EXECUTE_PROCESS_RESULT
            OUTPUT_VARIABLE     _GIT_STATUS_OUTPUT
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        if(NOT EXECUTE_PROCESS_RESULT EQUAL 0)
            message(WARNING "execute_process failed with: ${EXECUTE_PROCESS_RESULT}")
        endif()
        if(NOT _GIT_STATUS_OUTPUT MATCHES "^$")
            set(_GIT_DIRTY true)
        endif()
    endif()
endmacro()