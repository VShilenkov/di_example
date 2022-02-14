include_guard(GLOBAL)

include(FeatureSummary)

macro(project_options suffix)

    # Option declaration guard
    get_property(_project_options_options_created_${suffix}_var 
        GLOBAL 
        PROPERTY _project_options_options_created_${suffix}
    )

    if(NOT _project_options_options_created_${suffix}_var)
        set_property(GLOBAL 
            PROPERTY
                _project_options_options_created_${suffix} True
        )

        option(WITH_DOCUMENTING_${suffix} "Generate documentation for ${suffix}" OFF)
        add_feature_info([${suffix}].Documenting WITH_DOCUMENTING_${suffix}
            "Generate documentation for ${suffix}"
        )

        option(WITH_UNIT_TEST_${suffix} "Build unit tests for ${suffix}" OFF)
        add_feature_info([${suffix}].Unit-tests WITH_UNIT_TEST_${suffix}
            "Build unit tests for ${suffix}"
        )

        option(WITH_COMPONENT_TEST_${suffix} "Build component tests for ${suffix}" OFF)
        add_feature_info([${suffix}].Component-tests WITH_COMPONENT_TEST_${suffix}
            "Build component tests for ${suffix}"
        )

        option(WITH_SW_ELEMENT_TEST_${suffix} "Build sofware element tests for ${suffix}" OFF)
        add_feature_info([${suffix}].Software-Element-tests WITH_SW_ELEMENT_TEST_${suffix}
            "Build sofware element tests for ${suffix}"
        )

        option(WITH_COVERAGE_${suffix} "Generate code coverage counters for ${suffix}" OFF)
        add_feature_info([${suffix}].Coverage WITH_COVERAGE_${suffix}
            "Generate code coverage counters for ${suffix}"
        )

        option(WITH_EXAMPLE_${suffix} "Build examples for ${suffix}" OFF)
        add_feature_info([${suffix}].Example WITH_EXAMPLE_${suffix}
            "Build examples for ${suffix}"
        )

        option(ENGINEERING_BUILD_${suffix} "Build ${suffix} as engeneering variant" OFF)
        add_feature_info([${suffix}].Engineering-build ENGINEERING_BUILD_${suffix}
            "Build ${suffix} as engeneering variant"
        )
    endif()
endmacro()