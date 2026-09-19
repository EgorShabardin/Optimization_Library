add_executable(pointvalue_tests
    test_pointvalue_base.cpp
    test_pointvalue_utils.cpp
)

target_link_libraries(pointvalue_tests
    PRIVATE
        Optimization_Library::Optimization_Library
        Catch2::Catch2WithMain
)

catch_discover_tests(pointvalue_tests)