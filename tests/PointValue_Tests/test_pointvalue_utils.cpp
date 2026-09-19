#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

#include <utility>

import PointValue;
import Point;

using namespace Optimization_Library;

TEST_CASE("PointValue_Utils - Testing comparison operators", "[pointvalue][utils][comparisons]") {
    SECTION("Comparison operators (<, <=, >, >=, ==, !=) based on value for double") {
        PointValue<double, 2> pointvalue_small{Point<double, 2>{1.0, 2.0}, 10.0};
        PointValue<double, 2> pointvalue_equal{Point<double, 2>{5.0, 6.0}, 10.0};
        PointValue<double, 2> pointvalue_large{Point<double, 2>{0.0, 0.0}, 25.0};

        REQUIRE(pointvalue_small < pointvalue_large);
        REQUIRE(pointvalue_large > pointvalue_small);
        REQUIRE_FALSE(pointvalue_large < pointvalue_small);
        REQUIRE_FALSE(pointvalue_small > pointvalue_large);

        REQUIRE(pointvalue_small <= pointvalue_large);
        REQUIRE(pointvalue_small <= pointvalue_equal);
        REQUIRE(pointvalue_large >= pointvalue_small);
        REQUIRE(pointvalue_equal >= pointvalue_small);

        REQUIRE(pointvalue_small == pointvalue_equal);
        REQUIRE(pointvalue_small != pointvalue_large);
        REQUIRE_FALSE(pointvalue_small == pointvalue_large);
        REQUIRE_FALSE(pointvalue_small != pointvalue_equal);
    }

    SECTION("Comparison operators for float types") {
        PointValue<float, 1> first_pointvalue{Point<float, 1>{1.0f}, -5.2f};
        PointValue<float, 1> second_pointvalue{Point<float, 1>{2.0f}, 3.1f};

        REQUIRE(first_pointvalue < second_pointvalue);
        REQUIRE(second_pointvalue > first_pointvalue);
        REQUIRE(first_pointvalue <= second_pointvalue);
        REQUIRE(second_pointvalue >= first_pointvalue);
        REQUIRE(first_pointvalue != second_pointvalue);
    }
}

TEST_CASE("PointValue_Utils - Testing approximate equality", "[pointvalue][utils][is_approx]") {
    SECTION("Checking approximate equality within default and custom epsilon") {
        PointValue<double, 2> pointvalue_base{Point<double, 2>{1.0, 2.0}, 10.0};
        
        PointValue<double, 2> pointvalue_identical{Point<double, 2>{1.0, 2.0}, 10.0};
        REQUIRE(is_approx(pointvalue_base, pointvalue_identical));

        PointValue<double, 2> pointvalue_close{Point<double, 2>{1.0 + 1e-8, 2.0 - 1e-8}, 10.0 + 1e-8};
        REQUIRE(is_approx(pointvalue_base, pointvalue_close, 1e-6));

        PointValue<double, 2> pointvalue_diffvalue{Point<double, 2>{1.0, 2.0}, 10.1};
        REQUIRE_FALSE(is_approx(pointvalue_base, pointvalue_diffvalue, 1e-3));

        PointValue<double, 2> pointvalue_diffpoint{Point<double, 2>{1.5, 2.0}, 10.0};
        REQUIRE_FALSE(is_approx(pointvalue_base, pointvalue_diffpoint, 1e-3));
    }

    SECTION("Checking is_approx for float types") {
        PointValue<float, 3> pointvalue_float_base{Point<float, 3>{1.0f, 2.0f, 3.0f}, 5.0f};
        PointValue<float, 3> pointvalue_float_close{Point<float, 3>{1.00001f, 2.0f, 2.99999f}, 5.00001f};

        REQUIRE(is_approx(pointvalue_float_base, pointvalue_float_close, 1e-4f));
    }
}