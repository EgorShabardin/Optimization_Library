#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <iostream>
#include <utility>

import Point;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEMPLATE_TEST_CASE("Point_Operators - Functions sqrt and abs", "[point][operators][sqrt_abs]", double, float, long double) {
    SECTION("Function sqrt") {
        const Point<TestType, 3> point(4.0, 9.0, 1.0);
        const Point<TestType, 3> sqrt_point = sqrt(point);

        REQUIRE_THAT(sqrt_point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(sqrt_point[1], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(sqrt_point[2], WithinAbs(1.0, 1e-6));
        REQUIRE(sqrt_point.dimensions == 3);
    }

    SECTION("Function abs") {
        const Point<TestType, 5> point(1.4, -2.3, 1.5, -4.4, -1.2);
        const Point<TestType, 5> abs_point = abs(point);
        
        REQUIRE_THAT(abs_point[0], WithinAbs(1.4, 1e-6));
        REQUIRE_THAT(abs_point[1], WithinAbs(2.3, 1e-6));
        REQUIRE_THAT(abs_point[2], WithinAbs(1.5, 1e-6));
        REQUIRE_THAT(abs_point[3], WithinAbs(4.4, 1e-6));
        REQUIRE_THAT(abs_point[4], WithinAbs(1.2, 1e-6));
        REQUIRE(abs_point.dimensions == 5);
    }
}

TEMPLATE_TEST_CASE("Point_Utils - Output operator to the stream", "[point][utils][stream]", double, float, long double) {
    SECTION("Outputting a point with a dimension greater than 1 to the stream") {
        const Point<TestType, 4> point(3.3, 2.1, 5.5, 1.2);
        std::ostringstream stream;
        stream << point;

        REQUIRE(stream.str() == "(3.3, 2.1, 5.5, 1.2)");
        REQUIRE(&(stream << point) == &stream);
        REQUIRE_FALSE(stream.str().empty());
    }

    SECTION("Output to the stream of a point with a dimension equal to 1") {
        const Point<TestType, 1> point(3.3);
        std::ostringstream stream;
        stream << point;

        REQUIRE(stream.str() == "(3.3)");
        REQUIRE(&(stream << point) == &stream);
        REQUIRE_FALSE(stream.str().empty());
    }
}

TEMPLATE_TEST_CASE("Point_Utils - Calculation of norms", "[point][utils][norms]", double, float, long double) {
    const Point<TestType, 4> point(0.0, -3.0, 4.0, 0.0);

    SECTION("Calculation of the L1 norm") {
        const TestType norm = norm_l1(point);
        REQUIRE_THAT(norm, WithinAbs(7.0, 1e-6));
    }

    SECTION("Calculation of the L2 norm") {
        const TestType norm = norm_l2(point);
        REQUIRE_THAT(norm, WithinAbs(5.0, 1e-6));
    }

    SECTION("Calculation of the Linf norm") {
        const TestType norm = norm_linf(point);
        REQUIRE_THAT(norm, WithinAbs(4.0, 1e-6));
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Utils - Calculation of the dot product", "[point][utils][dot]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    SECTION("The dot product of arbitrary vectors") {
        const Point<TestType1, 6> first_point(3.5, -2.2, 5.5, 1.2, 9.4, 5.1);
        const Point<TestType2, 6> second_point(1.2, 1.3, -5.5, 10.2, -3.3, -2.0);

        const auto dot_product = dot(first_point, second_point);
        REQUIRE_THAT(dot_product, WithinAbs(-57.89, 1e-5));
    }

    SECTION("The dot product of orthogonal vectors") {
        const Point<TestType1, 3> first_point(1.0, 1.0, 3.0);
        const Point<TestType2, 3> second_point(2.0, 1.0, -1.0);

        const auto dot_product = dot(first_point, second_point);
        REQUIRE_THAT(dot_product, WithinAbs(0.0, 1e-6));
    }

    SECTION("Comparison of the dot product and the L2 norm") {
        const Point<TestType1, 2> point(3.0, 4.0);

        const auto norm = norm_l2(point);
        const auto dot_product = dot(point, point);
        REQUIRE_THAT(dot_product, WithinAbs(norm * norm, 1e-6));
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Utils - Calculating the distance between points", "[point][utils][dist]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    const Point<TestType1, 3> first_point(1.0, 2.0, 3.0);
    const Point<TestType2, 3> second_point(4.0, 6.0, 3.0);

    SECTION("The distance between arbitrary points") {
        const auto distance = dist(first_point, second_point);
        REQUIRE_THAT(distance, WithinAbs(5.0, 1e-6));
    }

    SECTION("The distance between the same point") {
        const auto distance = dist(first_point, first_point);
        REQUIRE_THAT(distance, WithinAbs(0.0, 1e-6));
    }

    SECTION("The symmetry of the distance between points") {
        const auto first_distance = dist(first_point, second_point);
        const auto second_distance = dist(second_point, first_point);
        REQUIRE_THAT(first_distance, WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(second_distance, WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(second_distance, WithinAbs(first_distance, 1e-6));
    }
}

TEMPLATE_TEST_CASE("Point_Utils - Vector normalization", "[point][utils][normalize]", double, float, long double) {
    SECTION("Normalization of an arbitrary point") {
        const Point<TestType, 3> point(0.0, 3.0, 4.0);
        const Point<TestType, 3> normalize_point = normalize(point);

        REQUIRE_THAT(normalize_point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(normalize_point[1], WithinAbs(0.6, 1e-6));
        REQUIRE_THAT(normalize_point[2], WithinAbs(0.8, 1e-6));
        REQUIRE_THAT(norm_l2(normalize_point), WithinAbs(1.0, 1e-6));
        
        const Point<TestType, 3> other_point = normalize_point * norm_l2(point);
        REQUIRE_THAT(other_point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(other_point[1], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(other_point[2], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(norm_l2(other_point), WithinAbs(5.0, 1e-6));
    }

    SECTION("Zero point normalization") {
        const Point<TestType, 5> point = Point<TestType, 5>::zeros();
        const Point<TestType, 5> normalize_point = normalize(point);

        REQUIRE_THAT(normalize_point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(normalize_point[1], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(normalize_point[2], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(normalize_point[3], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(normalize_point[4], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(norm_l2(normalize_point), WithinAbs(0.0, 1e-6));
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Utils - Approximate equality", "[point][utils][approx]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    SECTION("Comparison of identical points") {
        const Point<TestType1, 3> first_point(1.0, 2.0, 3.0);
        const Point<TestType2, 3> second_point(1.0, 2.0, 3.0);
        REQUIRE(is_approx(first_point, second_point));
    }

    SECTION("Comparison of points that differ by less than epsilon") {
        const Point<TestType1, 3> first_point(1.0, 2.0, 3.0);
        const Point<TestType2, 3> second_point(1.001, 2.001, 3.001);
        REQUIRE(is_approx(first_point, second_point, static_cast<std::common_type_t<TestType1, TestType2>>(1e-2)));
    }

    SECTION("Comparison of points that differ by more than epsilon") {
        const Point<TestType1, 3> first_point(1.0, 2.0, 3.0);
        const Point<TestType2, 3> second_point(1.0001, 2.0001, 3.000000001);
        REQUIRE_FALSE(is_approx(first_point, second_point, static_cast<std::common_type_t<TestType1, TestType2>>(1e-6)));
    }
}