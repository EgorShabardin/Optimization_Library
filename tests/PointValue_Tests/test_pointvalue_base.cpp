#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <iostream>
#include <utility>

import Point;
import PointValue;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEMPLATE_TEST_CASE("PointValue_Base - Pointvalue creation constructors", "[pointvalue][constructors]", double, float, long double) {
      SECTION("Default empty constructor") {
        const PointValue<TestType, 2> pointvalue;
        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(0.0, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("Constructor using an lvalue reference to Point and value") {
        const Point<TestType, 2> point(1.5, -2.5);
        const PointValue<TestType, 2> pointvalue{point, 42.0};
        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(42.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(1.5, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(-2.5, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("Constructor using rvalue references to Point and value") {
        Point<TestType, 3> point{3.0, 4.0, 5.1};
        const PointValue<TestType, 3> pointvalue{std::move(point), 10.0};
        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(pointvalue[2], WithinAbs(5.1, 1e-6));
        REQUIRE(pointvalue.dimensions == 3);
    }

    SECTION("Using factory methods FromFunction with an lvalue reference to Point") {
        const Point<TestType, 5> point{2.0, 3.0, 4.1, 5.5, 1.2};
        auto lambda = [](const Point<TestType, 5>& point) { return point[1] + point[3]; };
        const PointValue<TestType, 5> pointvalue = PointValue<TestType, 5>::FromFunction(point, lambda);

        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(8.5, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(pointvalue[2], WithinAbs(4.1, 1e-6));
        REQUIRE_THAT(pointvalue[3], WithinAbs(5.5, 1e-6));
        REQUIRE_THAT(pointvalue[4], WithinAbs(1.2, 1e-6));
        REQUIRE(pointvalue.dimensions == 5);
        
        REQUIRE_THAT(point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(4.1, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(5.5, 1e-6));
        REQUIRE_THAT(point[4], WithinAbs(1.2, 1e-6));
        REQUIRE(point.dimensions == 5);
    }

    SECTION("Using factory methods FromFunction with an rvalue reference to Point") {
        const PointValue<TestType, 2> pointvalue = PointValue<TestType, 2>::FromFunction(Point<TestType, 2>{3.0, 4.0}, 
            [](const Point<TestType, 2>& point) { return point[0] * point[1]; }
        );

        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(12.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(4.0, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);
    }
}

TEMPLATE_TEST_CASE("PointValue_Base - Access to elements and updating it", "[pointvalue][access]", double, float, long double) {
    SECTION("The get_point() method for accessing a point") {
        const Point<TestType, 3> point(1.2, -1.5, 6.5);
        const PointValue<TestType, 3> pointvalue{point, 2.4};

        const Point<TestType, 3> other_point = pointvalue.get_point();
        REQUIRE_THAT(pointvalue[0], WithinAbs(other_point[0], 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(other_point[1], 1e-6));
        REQUIRE_THAT(pointvalue[2], WithinAbs(other_point[2], 1e-6));
    }

    SECTION("The update() method for updating the value") {
        const Point<TestType, 2> point{2.0, 5.0};
        PointValue<TestType, 2> pointvalue{point, 0.0};
        pointvalue.update([](const Point<TestType, 2>& point) { return point[0] * point[1]; });

        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(5.0, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("The update() method for updating the lvalue point and value") {
        const Point<TestType, 2> point{2.0, 5.0};
        PointValue<TestType, 2> pointvalue{Point<TestType, 2>(1.5, 4.4), 4.3};
        pointvalue.update(point, [](const Point<TestType, 2>& point) { return point[0] * point[1]; });

        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(5.0, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);

        REQUIRE_THAT(point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(5.0, 1e-6));
        REQUIRE(point.dimensions == 2);
    }

    SECTION("The update() method for updating the rvalue point and value") {
        PointValue<TestType, 2> pointvalue{Point<TestType, 2>(1.5, 4.4), 4.3};
        pointvalue.update(Point<TestType, 2>(2.0, 5.0), [](const Point<TestType, 2>& point) { return point[0] * point[1]; });

        REQUIRE_THAT(pointvalue.get_value(), WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(pointvalue[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(pointvalue[1], WithinAbs(5.0, 1e-6));
        REQUIRE(pointvalue.dimensions == 2);
    }

}

TEMPLATE_TEST_CASE("PointValues_Base - Aliases for pointvalue", "[pointvalue][aliases]", double, float, long double) {
    SECTION("Aliase PointValue1D") {
        PointValue1D<TestType> pointvalue(Point1D<TestType>(4.4), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, TestType>);
        REQUIRE(pointvalue.dimensions == 1);
    }

    SECTION("Aliase PointValue1D_d") {
        PointValue1D_d pointvalue(Point1D_d(4.4), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, double>);
        REQUIRE(pointvalue.dimensions == 1);
    }

    SECTION("Aliase PointValue1D_f") {
        PointValue1D_f pointvalue(Point1D_f(4.4f), 3.2f);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, float>);
        REQUIRE(pointvalue.dimensions == 1);
    }

    SECTION("Aliase PointValue2D") {
        PointValue2D<TestType> pointvalue(Point2D<TestType>(4.4, 5.5), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, TestType>);
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("Aliase PointValue2D_d") {
        PointValue2D_d pointvalue(Point2D_d(4.4, 5.5), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, double>);
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("Aliase PointValue2D_d") {
        PointValue2D_f pointvalue(Point2D_f(4.4f, 5.5f), 3.2f);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, float>);
        REQUIRE(pointvalue.dimensions == 2);
    }

    SECTION("Aliase PointValue3D") {
        PointValue3D<TestType> pointvalue(Point3D<TestType>(4.4, 5.5, 6.7), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, TestType>);
        REQUIRE(pointvalue.dimensions == 3);
    }

    SECTION("Aliase PointValue3D_d") {
        PointValue3D_d pointvalue(Point3D_d(4.4, 5.5, 6.7), 3.2);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, double>);
        REQUIRE(pointvalue.dimensions == 3);
    }

    SECTION("Aliase PointValue3D_d") {
        PointValue3D_f pointvalue(Point3D_f(4.4f, 5.5f, 6.7f), 3.2f);
        static_assert(std::is_same_v<typename decltype(pointvalue)::value_type, float>);
        REQUIRE(pointvalue.dimensions == 3);
    }
}