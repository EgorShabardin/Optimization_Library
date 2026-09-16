#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <stdexcept>
#include <array>

import Point;

using namespace Optimization_Library;

TEST_CASE("Point_Base - Testing point creation constructors", "[point][constructors]") {
    SECTION("Default constructor of zero elements") {
        Point2D<double> point_double;
        REQUIRE(point_double[0] == 0.0);
        REQUIRE(point_double[1] == 0.0);
        REQUIRE(point_double.size() == 2);

        Point3D<float> point_float;
        REQUIRE(point_float[0] == 0.0);
        REQUIRE(point_float[1] == 0.0);
        REQUIRE(point_float[2] == 0.0);
        REQUIRE(point_float.size() == 3);
    }

    SECTION("Constructor from raw array") {
        std::array<double, 3> array_double{1.0, 2.0, 3.0};
        Point<double, 3> point_double(array_double);
        REQUIRE(point_double[0] == 1.0);
        REQUIRE(point_double[1] == 2.0);
        REQUIRE(point_double[2] == 3.0);
        REQUIRE(point_double.size() == 3);

        std::array<float, 2> array_float{1.0f, 2.0f};
        Point<float, 2> point_float(array_float);
        REQUIRE(point_float[0] == 1.0);
        REQUIRE(point_float[1] == 2.0);
        REQUIRE(point_float.size() == 2);
    }

    SECTION("Variadic constructor") {
        Point<double, 3> point_double(1.0, 2.5, 3.0);   
        REQUIRE(point_double[0] == 1.0);
        REQUIRE(point_double[1] == 2.5);
        REQUIRE(point_double[2] == 3.0);
        REQUIRE(point_double.size() == 3);

        Point<float, 1> point_float(1.0f);
        REQUIRE(point_float[0] == 1.0f);
        REQUIRE(point_float.size() == 1);
    }

    SECTION("Using CTAD to create a point") {
        Point point_double(std::array<double, 3>{1.3, 3.3, 5.1});
        static_assert(std::is_same_v<decltype(point_double), Point<double, 3>>);
        REQUIRE(point_double[0] == 1.3);
        REQUIRE(point_double[1] == 3.3);
        REQUIRE(point_double[2] == 5.1);
        REQUIRE(point_double.size() == 3);

        Point point_float(3.1f, 5.5f, 1.2f, 9.0f);
        static_assert(std::is_same_v<decltype(point_float), Point<float, 4>>);
        REQUIRE(point_float[0] == 3.1f);
        REQUIRE(point_float[1] == 5.5f);
        REQUIRE(point_float[2] == 1.2f);
        REQUIRE(point_float[3] == 9.0f);
        REQUIRE(point_float.size() == 4);
    }

    SECTION("Copy and Move semantics") {
        Point3D_d original_point(1.0, 2.0, 3.0);
        
        Point3D_d copy_constructed(original_point);
        REQUIRE(copy_constructed[0] == 1.0);
        REQUIRE(copy_constructed[1] == 2.0);
        REQUIRE(copy_constructed[2] == 3.0);
        REQUIRE(copy_constructed.size() == 3);

        Point3D_d copy_assigned;
        copy_assigned = original_point;
        REQUIRE(copy_assigned[0] == 1.0);
        REQUIRE(copy_assigned[1] == 2.0);
        REQUIRE(copy_assigned[2] == 3.0);
        REQUIRE(copy_assigned.size() == 3);

        Point3D_d move_constructed(std::move(original_point));
        REQUIRE(move_constructed[0] == 1.0);
        REQUIRE(move_constructed[1] == 2.0);
        REQUIRE(move_constructed[2] == 3.0);
        REQUIRE(move_constructed.size() == 3);

        Point3D_d move_assigned;
        move_assigned = std::move(copy_constructed);
        REQUIRE(move_assigned[0] == 1.0);
        REQUIRE(move_assigned[1] == 2.0);
        REQUIRE(move_assigned[2] == 3.0);
    }

    SECTION("Using aliases for double and float") {
        Point2D_f point_float(1.0f, 2.0f);
        static_assert(std::is_same_v<decltype(point_float), Point<float, 2>>);
        REQUIRE(point_float[0] == 1.0f);
        REQUIRE(point_float[1] == 2.0f);
        REQUIRE(point_float.size() == 2);

        Point3D_d point_double(1.0, 2.0, 3.0);
        static_assert(std::is_same_v<decltype(point_double), Point<double, 3>>);
        REQUIRE(point_double[0] == 1.0);
        REQUIRE(point_double[1] == 2.0);
        REQUIRE(point_double[2] == 3.0);
        REQUIRE(point_double.size() == 3);
    }

    SECTION("The use of factory methods") {
        Point3D_d point_zeros = Point3D_d::zeros();
        REQUIRE(point_zeros[0] == 0.0);
        REQUIRE(point_zeros[1] == 0.0);
        REQUIRE(point_zeros[2] == 0.0);
        REQUIRE(point_zeros.size() == 3);

        Point<float, 5> point_ones = Point<float, 5>::ones();
        REQUIRE(point_ones[0] == 1.0f);
        REQUIRE(point_ones[1] == 1.0f);
        REQUIRE(point_ones[2] == 1.0f);
        REQUIRE(point_ones[3] == 1.0f);
        REQUIRE(point_ones[4] == 1.0f);
        REQUIRE(point_ones.size() == 5);
    }
}

TEST_CASE("Point_Base - Testing access to elements and their storage", "[point][access_storage]") {
    Point3D_d point(10.0, 20.0, 30.0);

    SECTION("Operator [] and method at()") {
        REQUIRE(point[0] == 10.0);
        REQUIRE(point.at(0) == 10.0);
        REQUIRE(point[1] == 20.0);
        REQUIRE(point.at(1) == 20.0);
        REQUIRE(point[2] == 30.0);
        REQUIRE(point.at(2) == 30.0);
        
        point[0] = 15.0;
        REQUIRE(point[0] == 15.0);
        point[1] = 25.0;
        REQUIRE(point[1] == 25.0);
        point[2] = 35.0;
        REQUIRE(point[2] == 35.0);

        REQUIRE_THROWS_AS(point.at(3), std::out_of_range);
    }

    SECTION("Const and non-const method as_array()") {
        const Point3D_d& const_point = point;
        const std::array<double, 3>& const_array = const_point.as_array();
        REQUIRE(const_array[0] == 10.0);
        REQUIRE(const_array[1] == 20.0);
        REQUIRE(const_array[2] == 30.0);

        std::array<double, 3>& mutable_array = point.as_array();
        REQUIRE(mutable_array[0] == 10.0);
        REQUIRE(mutable_array[1] == 20.0);
        REQUIRE(mutable_array[2] == 30.0);

        mutable_array[0] = 99.0;
        REQUIRE(point[0] == 99.0);
        mutable_array[1] = 10.0;
        REQUIRE(point[1] == 10.0);
        mutable_array[2] = 33.5;
        REQUIRE(point[2] == 33.5);
    }

    SECTION("Access to the data pointer using the data() method.") {
        double* raw_data = point.data();
        REQUIRE(raw_data[0] == 10.0);
        REQUIRE(raw_data[1] == 20.0);
        REQUIRE(raw_data[2] == 30.0);

        raw_data[0] = 99.0;
        REQUIRE(point[0] == 99.0);
        raw_data[1] = 19.3;
        REQUIRE(point[1] == 19.3);
        raw_data[2] = 19.6;
        REQUIRE(point[2] == 19.6);
    }

    SECTION("Exposed type aliases") {
        static_assert(std::is_same_v<Point3D_d::value_type, double>);
        static_assert(std::is_same_v<Point3D_d::iterator, std::array<double, 3>::iterator>);
        static_assert(std::is_same_v<Point3D_d::const_iterator, std::array<double, 3>::const_iterator>);
    }
}

TEST_CASE("Point_Base - Testing iterators", "[point][iterators]") {
    Point3D_d point(1.0, 2.0, 3.0);

    SECTION("Mutable iterators") {
        for (auto& val : point) { val *= 2.0; }
        REQUIRE(point[0] == 2.0);
        REQUIRE(point[1] == 4.0);
        REQUIRE(point[2] == 6.0);
    }

    SECTION("Const iterators") {
        REQUIRE(*point.cbegin() == 1.0);
        REQUIRE(*(point.cend() - 1) == 3.0);
        REQUIRE(point.cend() - point.cbegin() == 3);
    }
}