add_executable(unit_tests
    test_point_base.cpp
    test_point_operators.cpp
    test_point_utils.cpp
)

target_link_libraries(unit_tests
    PRIVATE
        Optimization_Library::Optimization_Library
        Catch2::Catch2WithMain
)

catch_discover_tests(unit_tests)