add_executable(point_tests
    test_point_base.cpp
    test_point_operators.cpp
    test_point_utils.cpp
    compile_point_tests.cpp
)

target_link_libraries(point_tests
    PRIVATE
        Optimization_Library::Optimization_Library
        Catch2::Catch2WithMain
)

catch_discover_tests(point_tests)