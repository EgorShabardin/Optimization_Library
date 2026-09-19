#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <iostream>
#include <cstddef>

import Point;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEMPLATE_TEST_CASE("Point_Base - Point creation constructors", "[point][constructors]", double, float, long double) {
    SECTION("Default empty constructor") {
        const Point<TestType, 2> point;
        REQUIRE_THAT(point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(0.0, 1e-6));
        REQUIRE(point.dimensions == 2);
    }

    SECTION("Factory method zeros") {
        const Point<TestType, 3> point = Point<TestType, 3>::zeros();
        REQUIRE_THAT(point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(0.0, 1e-6));
        REQUIRE(point.size() == 3);
    }

    SECTION("Factory method ones") {
        const Point<TestType, 5> point = Point<TestType, 5>::ones();
        REQUIRE_THAT(point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[4], WithinAbs(1.0, 1e-6));
        REQUIRE(point.size() == 5);
    }

    SECTION("Variadic constructor") {
        const Point<TestType, 6> point(1.0, 2.5, 3.0, -3.4, 0.5, 8.9);   
        REQUIRE_THAT(point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(2.5, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(-3.4, 1e-6));
        REQUIRE_THAT(point[4], WithinAbs(0.5, 1e-6));
        REQUIRE_THAT(point[5], WithinAbs(8.9, 1e-6));
        REQUIRE(point.dimensions == 6);
    }

    SECTION("Constructor from raw array") {
        const std::array<TestType, 3> arr{1.0, 2.0, 3.0};
        const Point<TestType, 3> point(arr);
        REQUIRE_THAT(point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(3.0, 1e-6));
        REQUIRE(point.dimensions == 3);
    }

    SECTION("CTAD constructor") {
        Point first_point(std::array<TestType, 3>{1.3, 3.3, 5.1});
        static_assert(std::is_same_v<decltype(first_point), Point<TestType, 3>>);

        REQUIRE_THAT(first_point[0], WithinAbs(1.3, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(3.3, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(5.1, 1e-6));
        REQUIRE(first_point.dimensions == 3);

        Point second_point(3.1f, 5.5, 1.2f, 9.0);
        static_assert(std::is_same_v<decltype(second_point), Point<double, 4>>);

        REQUIRE_THAT(second_point[0], WithinAbs(3.1, 1e-6));
        REQUIRE_THAT(second_point[1], WithinAbs(5.5, 1e-6));
        REQUIRE_THAT(second_point[2], WithinAbs(1.2, 1e-6));
        REQUIRE_THAT(second_point[3], WithinAbs(9.0, 1e-6));
        REQUIRE(second_point.dimensions == 4);
    }
}

TEMPLATE_TEST_CASE("Point_Base - Copy and Move semantics", "[point][copy_move]", double, float, long double) {
    Point<TestType, 3> original_point(1.0, 2.0, 3.0);

    SECTION("Copy constructor") {
        const Point<TestType, 3> copy_constructed(original_point);
        REQUIRE_THAT(copy_constructed[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(copy_constructed[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(copy_constructed[2], WithinAbs(3.0, 1e-6));
        REQUIRE(copy_constructed.dimensions == 3);
    }

    SECTION("Copy by assignment") {
        const Point<TestType, 3> copy_assigned = original_point;
        REQUIRE_THAT(copy_assigned[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(copy_assigned[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(copy_assigned[2], WithinAbs(3.0, 1e-6));
        REQUIRE(copy_assigned.dimensions == 3);
    }

    SECTION("Movement constructor") {
        const Point<TestType, 3> move_constructed(std::move(original_point));
        REQUIRE_THAT(move_constructed[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(move_constructed[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(move_constructed[2], WithinAbs(3.0, 1e-6));
        REQUIRE(move_constructed.dimensions == 3);
    }

    SECTION("Move by assignment") {
        const Point<TestType, 3> move_assigned = std::move(original_point);
        REQUIRE_THAT(move_assigned[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(move_assigned[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(move_assigned[2], WithinAbs(3.0, 1e-6));
        REQUIRE(move_assigned.dimensions == 3);
    }
}

TEMPLATE_TEST_CASE("Point_Base - Access to stored data", "[point][access]", double, float, long double) {
    Point<TestType, 4> point(10.0, 20.0, 30.0, 0.0);

    SECTION("Operator []") {
        REQUIRE_THAT(point[0], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(30.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(0.0, 1e-6));

        point[0] = 1.0;
        point[1] = 2.0;
        point[2] = 3.0;
        point[3] = 4.0;
        REQUIRE_THAT(point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(4.0, 1e-6));
    }

    SECTION("Method at()") {
        REQUIRE_THAT(point.at(0), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(point.at(1), WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(point.at(2), WithinAbs(30.0, 1e-6));
        REQUIRE_THAT(point.at(3), WithinAbs(0.0, 1e-6));

        REQUIRE_THROWS_AS(point.at(10), std::out_of_range);
        REQUIRE_THROWS_AS(point.at(-1), std::out_of_range);
    }

    SECTION("Method as_array()") {
        const std::array<TestType, 4>& const_array = point.as_array();
        REQUIRE_THAT(const_array[0], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(const_array[1], WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(const_array[2], WithinAbs(30.0, 1e-6));
        REQUIRE_THAT(const_array[3], WithinAbs(0.0, 1e-6));
        REQUIRE(const_array.size() == 4);
    }

    SECTION("Non-constant Method data()") {
        TestType* raw_data = point.data();
        REQUIRE_THAT(raw_data[0], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(raw_data[1], WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(raw_data[2], WithinAbs(30.0, 1e-6));
        REQUIRE_THAT(raw_data[3], WithinAbs(0.0, 1e-6));

        raw_data[0] = 1.0;
        raw_data[1] = 2.0;
        raw_data[2] = 3.0;
        raw_data[3] = 4.0;
        REQUIRE_THAT(raw_data[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(raw_data[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(raw_data[2], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(raw_data[3], WithinAbs(4.0, 1e-6));
    }

    SECTION("Constant Method data()") {
        const TestType* raw_data = point.data();
        REQUIRE_THAT(raw_data[0], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(raw_data[1], WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(raw_data[2], WithinAbs(30.0, 1e-6));
        REQUIRE_THAT(raw_data[3], WithinAbs(0.0, 1e-6));
    }

    SECTION("The dimensions field and the size() method") {
        const std::size_t dim = 4;
        const Point<TestType, dim> point(3.4, 5.5, 1.0, 4.2);

        REQUIRE(point.size() == 4);
        REQUIRE(point.dimensions == 4);
        REQUIRE(point.size() == point.dimensions);
    }

    SECTION("Exposed type aliases") {
        static_assert(std::is_same_v<typename Point<TestType, 4>::value_type, TestType>);
        static_assert(std::is_same_v<typename Point<TestType, 4>::iterator, typename std::array<TestType, 4>::iterator>);
        static_assert(std::is_same_v<typename Point<TestType, 4>::const_iterator, typename std::array<TestType, 4>::const_iterator>);
    }
}

TEMPLATE_TEST_CASE("Point_Base - Constant and non-constant iterators", "[point][iterators]", double, float, long double) {
    SECTION("Non-constant iterators") {
        const std::size_t dim = 5;
        Point<TestType, dim> point(10.0, 20.0, 30.0, 0.0, 5.3);

        REQUIRE_THAT(*point.begin(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(*(point.end() - 1), WithinAbs(5.3, 1e-6));
        REQUIRE(point.end() - point.begin() == dim);

        for (TestType& val : point) { val *= 2.0; }
        REQUIRE_THAT(point[0], WithinAbs(20.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(40.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(60.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(point[4], WithinAbs(10.6, 1e-6));
    }

    SECTION("Constant iterators") {
        const std::size_t dim = 5;
        const Point<TestType, dim> point(10.0, 20.0, 30.0, 0.0, 5.3);

        REQUIRE_THAT(*point.cbegin(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(*(point.cend() - 1), WithinAbs(5.3, 1e-6));
        REQUIRE(point.cend() - point.cbegin() == dim);

        TestType sum = 0.0;
        for (const TestType& val : point) { sum += val; }
        REQUIRE_THAT(sum, WithinAbs(65.3, 1e-5));
    }
}

TEMPLATE_TEST_CASE("Point_Base - Aliases for points", "[point][aliases]", double, float, long double) {
    SECTION("Aliase Point1D") {
        Point1D<TestType> point(4.4);
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType>);
        REQUIRE(point.dimensions == 1);
    }

    SECTION("Aliase Point1D_d") {
        Point1D_d point(4.4);
        static_assert(std::is_same_v<typename decltype(point)::value_type, double>);
        REQUIRE(point.dimensions == 1);
    }

    SECTION("Aliase Point1D_f") {
        Point1D_f point(4.4f);
        static_assert(std::is_same_v<typename decltype(point)::value_type, float>);
        REQUIRE(point.dimensions == 1);
    }

    SECTION("Aliase Point2D") {
        Point2D<TestType> point(4.4, 5.3);
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType>);
        REQUIRE(point.dimensions == 2);
    }

    SECTION("Aliase Point2D_d") {
        Point2D_d point(4.4, 5.3);
        static_assert(std::is_same_v<typename decltype(point)::value_type, double>);
        REQUIRE(point.dimensions == 2);
    }

    SECTION("Aliase Point2D_f") {
        Point2D_f point(4.4f, 5.3f);
        static_assert(std::is_same_v<typename decltype(point)::value_type, float>);
        REQUIRE(point.dimensions == 2);
    }

    SECTION("Aliase Point3D") {
        Point3D<TestType> point(4.4, 5.3, 1.2);
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType>);
        REQUIRE(point.dimensions == 3);
    }

    SECTION("Aliase Point3D_d") {
        Point3D_d point(4.4, 5.3, 1.2);
        static_assert(std::is_same_v<typename decltype(point)::value_type, double>);
        REQUIRE(point.dimensions == 3);
    }

    SECTION("Aliase Point3D_f") {
        Point3D_f point(4.4f, 5.3f, 1.2f);
        static_assert(std::is_same_v<typename decltype(point)::value_type, float>);
        REQUIRE(point.dimensions == 3);
    }
}