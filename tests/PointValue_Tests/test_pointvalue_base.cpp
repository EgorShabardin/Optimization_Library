#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

#include <functional>
#include <utility>

import Point;
import PointValue;

using namespace Optimization_Library;

TEST_CASE("PointValue_Base - Testing pointvalue creation constructors", "[pointvalue][constructors]") {
      SECTION("Default constructor of zero elements") {
        PointValue<double, 2> pointvalue_double;
        REQUIRE(pointvalue_double.value == 0.0);
        REQUIRE(pointvalue_double.point[0] == 0.0);
        REQUIRE(pointvalue_double.point[1] == 0.0);
        REQUIRE(pointvalue_double.point.dimensions == 2);

        PointValue<float, 1> pointvalue_float;
        REQUIRE(pointvalue_float.value == 0.0);
        REQUIRE(pointvalue_float.point[0] == 0.0);
        REQUIRE(pointvalue_float.point.dimensions == 1);
    }

    SECTION("Constructor using an lvalue reference to Point and value") {
        Point<double, 2> point_double{1.5, -2.5};
        PointValue<double, 2> pointvalue_double{point_double, 42.0};

        REQUIRE(pointvalue_double.value == 42.0);
        REQUIRE(pointvalue_double.point[0] == 1.5);
        REQUIRE(pointvalue_double.point[1] == -2.5);
        REQUIRE(pointvalue_double.point.dimensions == 2);

        REQUIRE(point_double[0] == 1.5);
        REQUIRE(point_double[1] == -2.5);
        REQUIRE(point_double.dimensions == 2);

        Point<float, 4> point_float{1.2f, 1.5f, 5.5f, 2.1f};
        PointValue<float, 4> pointvalue_float{point_float, 1.0f};

        REQUIRE(pointvalue_float.value == 1.0f);
        REQUIRE(pointvalue_float.point[0] == 1.2f);
        REQUIRE(pointvalue_float.point[1] == 1.5f);
        REQUIRE(pointvalue_float.point[2] == 5.5f);
        REQUIRE(pointvalue_float.point[3] == 2.1f);
        REQUIRE(pointvalue_float.point.dimensions == 4);

        REQUIRE(point_float[0] == 1.2f);
        REQUIRE(point_float[1] == 1.5f);
        REQUIRE(point_float[2] == 5.5f);
        REQUIRE(point_float[3] == 2.1f);
        REQUIRE(point_float.dimensions == 4);
    }

    SECTION("Constructor using rvalue references to Point and value") {
        Point<double, 3> point_double{3.0, 4.0, 5.1};
        PointValue<double, 3> pointvalue_double{std::move(point_double), 10.0};

        REQUIRE(pointvalue_double.value == 10.0);
        REQUIRE(pointvalue_double.point[0] == 3.0);
        REQUIRE(pointvalue_double.point[1] == 4.0);
        REQUIRE(pointvalue_double.point[2] == 5.1);
        REQUIRE(pointvalue_double.point.size() == 3);

        Point<float, 1> point_float{11.2f};
        PointValue<float, 1> pointvalue_float{std::move(point_float), 12.6f};

        REQUIRE(pointvalue_float.value == 12.6f);
        REQUIRE(pointvalue_float.point[0] == 11.2f);
        REQUIRE(pointvalue_float.point.size() == 1);
    }

    SECTION("Using factory methods FromFunction with an lvalue reference to Point") {
        Point<double, 5> point_double{2.0, 3.0, 4.1, 5.5, 1.2};
        auto lambda_double = [](const Point<double, 5>& point) { return point[1] + point[3]; };
        PointValue<double, 5> pointvalue_double = PointValue<double, 5>::FromFunction(point_double, lambda_double);

        REQUIRE(pointvalue_double.value == 8.5);
        REQUIRE(pointvalue_double.point[0] == 2.0);
        REQUIRE(pointvalue_double.point[1] == 3.0);
        REQUIRE(pointvalue_double.point[2] == 4.1);
        REQUIRE(pointvalue_double.point[3] == 5.5);
        REQUIRE(pointvalue_double.point[4] == 1.2);
        REQUIRE(pointvalue_double.point.dimensions == 5);
        
        REQUIRE(point_double[0] == 2.0);
        REQUIRE(point_double[1] == 3.0);
        REQUIRE(point_double[2] == 4.1);
        REQUIRE(point_double[3] == 5.5);
        REQUIRE(point_double[4] == 1.2);
        REQUIRE(point_double.dimensions == 5);
    }

    SECTION("Using factory methods FromFunction with an rvalue reference to Point") {
        PointValue<float, 2> pointvalue_float = PointValue<float, 2>::FromFunction(Point<float, 2>{3.0f, 4.0f}, 
            [](const Point<float, 2>& point) { return point[0] * point[1]; }
        );

        REQUIRE(pointvalue_float.value == 12.0f);
        REQUIRE(pointvalue_float.point[0] == 3.0f);
        REQUIRE(pointvalue_float.point[1] == 4.0f);
        REQUIRE(pointvalue_float.point.dimensions == 2);
    }
}

TEST_CASE("PointValue_Base - Testing access to elements and updating it", "[pointvalue][access]") {
    SECTION("The update method for updating the value") {
        Point<double, 2> point_double{2.0, 5.0};
        PointValue<double, 2> pointvalue_double{point_double, 0.0};

        pointvalue_double.update([](const Point<double, 2>& point) { return point[0] * point[1]; });
        REQUIRE(pointvalue_double.value == 10.0);
        REQUIRE(pointvalue_double.point[0] == 2.0);
        REQUIRE(pointvalue_double.point[1] == 5.0);
        REQUIRE(pointvalue_double.point.dimensions == 2);

        Point<float, 3> point_float{2.2f, 3.3f, 4.4f};
        PointValue<float, 3> pointvalue_float{point_float, 0.0};

        pointvalue_float.update([](const Point<float, 3>& point) { return point[2] + point[1] * point[0]; });
        REQUIRE(pointvalue_float.value == 11.66f);
        REQUIRE(pointvalue_float.point[0] == 2.2f);
        REQUIRE(pointvalue_float.point[1] == 3.3f);
        REQUIRE(pointvalue_float.point[2] == 4.4f);
        REQUIRE(pointvalue_float.point.dimensions == 3);
    }

    SECTION("Access to the point coordinates via the [] operator") {
        const PointValue<double, 3> pointvalue_const{Point<double, 3>{1.0, 2.0, 3.0}, 99.0};
        REQUIRE(pointvalue_const.value == 99.0);
        REQUIRE(pointvalue_const[0] == 1.0);
        REQUIRE(pointvalue_const[1] == 2.0);
        REQUIRE(pointvalue_const[2] == 3.0);
        REQUIRE(pointvalue_const.point.dimensions == 3);

        PointValue<float, 3> pointvalue_nonconst{Point<float, 3>{1.0f, 2.0f, 3.0f}, 99.0};
        pointvalue_nonconst[0] = 10.0f;
        pointvalue_nonconst[1] = 20.0f;
        pointvalue_nonconst[2] = 30.0f;

        REQUIRE(pointvalue_nonconst.value == 99.0);
        REQUIRE(pointvalue_nonconst[0] == 10.0f);
        REQUIRE(pointvalue_nonconst[1] == 20.0f);
        REQUIRE(pointvalue_nonconst[2] == 30.0f);
        REQUIRE(pointvalue_nonconst.point.dimensions == 3);
    }
}