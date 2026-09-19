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

TEMPLATE_TEST_CASE("PointValue_Utils - Output operator to the stream", "[pointvalue][utils][stream]", double, float, long double) {
    SECTION("Outputting a pointvalue with a dimension greater than 1 to the stream") {
        const PointValue<TestType, 5> pointvalue(Point<TestType, 5>(1.2, 3.3, 1.5, 6.3, -5.3), -3.1);
        std::ostringstream stream;
        stream << pointvalue;

        REQUIRE(stream.str() == "{(1.2, 3.3, 1.5, 6.3, -5.3), -3.1}");
        REQUIRE(&(stream << pointvalue) == &stream);
        REQUIRE_FALSE(stream.str().empty());
    }

    SECTION("Output to the stream of a pointvalue with a dimension equal to 1") {
        const PointValue<TestType, 1> pointvalue(Point<TestType, 1>(1.2), -3.1);
        std::ostringstream stream;
        stream << pointvalue;

        REQUIRE(stream.str() == "{(1.2), -3.1}");
        REQUIRE(&(stream << pointvalue) == &stream);
        REQUIRE_FALSE(stream.str().empty());
    }
}

TEMPLATE_PRODUCT_TEST_CASE("PointValue_Utils - Comparison operators", "[pointvalue][utils][comparisons]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    SECTION("The < and <= operators, comparison to the lesser") {
        const PointValue<TestType1, 2> pointvalue_small{Point<TestType1, 2>{1.0, 2.0}, 10.0};
        const PointValue<TestType2, 2> pointvalue_large{Point<TestType2, 2>{0.0, 0.0}, 25.0};

        REQUIRE(pointvalue_small < pointvalue_large);
        REQUIRE(pointvalue_small <= pointvalue_large);
        REQUIRE_FALSE(pointvalue_large < pointvalue_small);
        REQUIRE_FALSE(pointvalue_large <= pointvalue_small);
    }

    SECTION("The > and >= operators, comparison for more") {
        const PointValue<TestType1, 2> pointvalue_small{Point<TestType1, 2>{1.0, 2.0}, 10.0};
        const PointValue<TestType2, 2> pointvalue_large{Point<TestType2, 2>{0.0, 0.0}, 25.0};

        REQUIRE(pointvalue_large > pointvalue_small);
        REQUIRE(pointvalue_large >= pointvalue_small);
        REQUIRE_FALSE(pointvalue_small > pointvalue_large);
        REQUIRE_FALSE(pointvalue_small >= pointvalue_large);
    }

    SECTION("The < and <= operators, comparison for equality") {
        const PointValue<TestType1, 2> first_pointvalue{Point<TestType1, 2>{1.0, 2.0}, 10.0};
        const PointValue<TestType2, 2> second_pointvalue{Point<TestType2, 2>{0.0, 0.0}, 10.0};

        REQUIRE(first_pointvalue >= second_pointvalue);
        REQUIRE(first_pointvalue <= second_pointvalue);
        REQUIRE(second_pointvalue >= first_pointvalue);
        REQUIRE(second_pointvalue <= first_pointvalue);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("PointValue_Utils - Approximate equality", "[pointvalue][utils][approx]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    SECTION("Comparison of identical pointvalue") {
        const PointValue<TestType1, 3> first_pointvalue(Point<TestType1, 3>(1.0, 2.0, 3.0), 1.2);
        const PointValue<TestType1, 3> second_pointvalue(Point<TestType1, 3>(1.0, 2.0, 3.0), 1.2);
        REQUIRE(is_approx(first_pointvalue, second_pointvalue));
    }

    SECTION("Comparison of identical points with different values") {
        const PointValue<TestType1, 3> first_pointvalue(Point<TestType1, 3>(1.0, 2.0, 3.0), 5.4);
        const PointValue<TestType1, 3> second_pointvalue(Point<TestType1, 3>(1.0, 2.0, 3.0), 1.2);
        REQUIRE_FALSE(is_approx(first_pointvalue, second_pointvalue));
    }

    SECTION("Comparison of different points with the same values") {
        const PointValue<TestType1, 3> first_pointvalue(Point<TestType1, 3>(1.5, 2.2, 4.7), 5.4);
        const PointValue<TestType1, 3> second_pointvalue(Point<TestType1, 3>(3.0, 5.0, 8.9), 5.4);
        REQUIRE_FALSE(is_approx(first_pointvalue, second_pointvalue));
    }
}