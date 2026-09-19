#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include <type_traits>
#include <utility>

import Point;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Addition operators with two points", "[point][operators][points][addition]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 3> first_point(1.0, 2.0, 3.0);
    Point<TestType2, 3> second_point(4.0, 5.0, 6.0);

    SECTION("Addition assignment operation") {
        first_point += second_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(7.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(9.0, 1e-6));
        REQUIRE(first_point.dimensions == 3);
        REQUIRE(&(first_point += second_point) == &first_point);
    }

    SECTION("The addition operation with assignment to itself") {
        first_point += first_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(6.0, 1e-6));
        REQUIRE(first_point.dimensions == 3);
        REQUIRE(&(first_point += first_point) == &first_point);
    }

    SECTION("Binary addition operation") {
        const auto result = first_point + second_point;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(7.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(9.0, 1e-6));
        REQUIRE(result.dimensions == 3);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Addition operators with a point and a scalar", "[point][operators][scalar][addition]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;
    
    Point<TestType1, 3> point(1.0, 2.0, 3.0);
    const TestType2 scalar = 2.5;

    SECTION("Addition assignment operation") {
        point += scalar;
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType1>);

        REQUIRE_THAT(point[0], WithinAbs(3.5, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(4.5, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(5.5, 1e-6));
        REQUIRE(point.dimensions == 3);
        REQUIRE(&(point += scalar) == &point);
    }

    SECTION("Binary addition operation") {
        const auto first_result = point + scalar;
        static_assert(std::is_same_v<typename decltype(first_result)::value_type, std::common_type_t<TestType1, TestType2>>);
        
        REQUIRE_THAT(first_result[0], WithinAbs(3.5, 1e-6));
        REQUIRE_THAT(first_result[1], WithinAbs(4.5, 1e-6));
        REQUIRE_THAT(first_result[2], WithinAbs(5.5, 1e-6));
        REQUIRE(first_result.dimensions == 3);

        const auto second_result = scalar + point;
        static_assert(std::is_same_v<typename decltype(second_result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(second_result[0], WithinAbs(3.5, 1e-6));
        REQUIRE_THAT(second_result[1], WithinAbs(4.5, 1e-6));
        REQUIRE_THAT(second_result[2], WithinAbs(5.5, 1e-6));
        REQUIRE(second_result.dimensions == 3);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Subtraction operators with two points", "[point][operators][points][subtraction]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 5> first_point(1.0, 2.0, 3.0, 4.3, 1.2);
    Point<TestType2, 5> second_point(4.0, 5.0, 6.0, 5.5, 7.8);

    SECTION("Subtraction assignment operation") {
        first_point -= second_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(first_point[3], WithinAbs(-1.2, 1e-6));
        REQUIRE_THAT(first_point[4], WithinAbs(-6.6, 1e-6));
        REQUIRE(first_point.dimensions == 5);
        REQUIRE(&(first_point -= second_point) == &first_point);
    }

    SECTION("The subtraction operation with assignment to itself") {
        first_point -= first_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(first_point[3], WithinAbs(0.0, 1e-6));
        REQUIRE_THAT(first_point[4], WithinAbs(0.0, 1e-6));
        REQUIRE(first_point.dimensions == 5);
        REQUIRE(&(first_point -= first_point) == &first_point);
    }

    SECTION("Binary subtraction operation") {
        const auto result = first_point - second_point;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(-3.0, 1e-6));
        REQUIRE_THAT(result[3], WithinAbs(-1.2, 1e-6));
        REQUIRE_THAT(result[4], WithinAbs(-6.6, 1e-6));
        REQUIRE(result.dimensions == 5);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Subtraction operators with a point and a scalar", "[point][operators][scalar][subtraction]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 5> point(1.0, 2.0, 3.0, 4.3, 1.2);
    const TestType2 scalar = 2.5;

    SECTION("Subtraction assignment operation") {
        point -= scalar;
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType1>);

        REQUIRE_THAT(point[0], WithinAbs(-1.5, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(-0.5, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(0.5, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(1.8, 1e-6));
        REQUIRE_THAT(point[4], WithinAbs(-1.3, 1e-6));
        REQUIRE(point.dimensions == 5);
        REQUIRE(&(point -= scalar) == &point);
    }

    SECTION("Binary subtraction operation") {
        const auto result = point - scalar;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(-1.5, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(-0.5, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(0.5, 1e-6));
        REQUIRE_THAT(result[3], WithinAbs(1.8, 1e-6));
        REQUIRE_THAT(result[4], WithinAbs(-1.3, 1e-6));
        REQUIRE(result.dimensions == 5);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Multiplication operators with two points", "[point][operators][points][multiplication]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 2> first_point(1.0, 2.0);
    Point<TestType2, 2> second_point(4.0, 5.0);

    SECTION("Multiplication assignment operation") {
        first_point *= second_point;   
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(10.0, 1e-6));
        REQUIRE(first_point.dimensions == 2);
        REQUIRE(&(first_point *= second_point) == &first_point);
    }

    SECTION("The multiplication operation with assignment to itself") {
        first_point *= first_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(4.0, 1e-6));
        REQUIRE(first_point.dimensions == 2);
        REQUIRE(&(first_point *= first_point) == &first_point);
    }

    SECTION("Binary multiplication operation") {
        const auto result = first_point * second_point;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(10.0, 1e-6));
        REQUIRE(result.dimensions == 2);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Multiplication operators with a point and a scalar", "[point][operators][scalar][multiplication]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 2> point(1.0, 2.0);
    const TestType2 scalar = 2.5;

    SECTION("Multiplication assignment operation") {
        point *= scalar;
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType1>);

        REQUIRE_THAT(point[0], WithinAbs(2.5, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(5.0, 1e-6));
        REQUIRE(point.dimensions == 2);
        REQUIRE(&(point *= scalar) == &point);
    }

    SECTION("Binary multiplication operation") {
        const auto first_result = point * scalar;
        static_assert(std::is_same_v<typename decltype(first_result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(first_result[0], WithinAbs(2.5, 1e-6));
        REQUIRE_THAT(first_result[1], WithinAbs(5.0, 1e-6));
        REQUIRE(first_result.dimensions == 2);

        const auto second_result = scalar * point;
        static_assert(std::is_same_v<typename decltype(second_result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(second_result[0], WithinAbs(2.5, 1e-6));
        REQUIRE_THAT(second_result[1], WithinAbs(5.0, 1e-6));
        REQUIRE(second_result.dimensions == 2);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Division operators with two points", "[point][operators][points][division]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {

    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 4> first_point(4.0, 10.0, 18.0, 16.8);
    Point<TestType2, 4> second_point(2.0, 2.0, 3.0, 4.0);

    SECTION("Division assignment operation") {
        first_point /= second_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(6.0, 1e-6));
        REQUIRE_THAT(first_point[3], WithinAbs(4.2, 1e-6));
        REQUIRE(first_point.dimensions == 4);
        REQUIRE(&(first_point /= second_point) == &first_point);
    }

    SECTION("The division operation with assignment to itself") {
        first_point /= first_point;
        static_assert(std::is_same_v<typename decltype(first_point)::value_type, TestType1>);

        REQUIRE_THAT(first_point[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(first_point[1], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(first_point[2], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(first_point[3], WithinAbs(1.0, 1e-6));
        REQUIRE(first_point.dimensions == 4);
        REQUIRE(&(first_point /= first_point) == &first_point);
    }

    SECTION("Binary division operation") {
        const auto result = first_point / second_point;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(6.0, 1e-6));
        REQUIRE_THAT(result[3], WithinAbs(4.2, 1e-6));
        REQUIRE(result.dimensions == 4);
    }
}

TEMPLATE_PRODUCT_TEST_CASE("Point_Operators - Division operators with a point and a scalar", "[point][operators][scalar][division]",
    std::pair, ((float, float), (float, double), (float, long double), (double, float), (double, double), (double, long double),
    (long double, float), (long double, double), (long double, long double))) {
    
    using TestType1 = typename TestType::first_type;
    using TestType2 = typename TestType::second_type;

    Point<TestType1, 4> point(4.0, 10.0, 18.0, 16.8);
    const TestType2 scalar = 2.0;

    SECTION("Division assignment operation") {
        point /= scalar;
        static_assert(std::is_same_v<typename decltype(point)::value_type, TestType1>);

        REQUIRE_THAT(point[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(point[1], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(point[2], WithinAbs(9.0, 1e-6));
        REQUIRE_THAT(point[3], WithinAbs(8.4, 1e-6));
        REQUIRE(point.dimensions == 4);
        REQUIRE(&(point /= scalar) == &point);
    }

    SECTION("Binary division operation") {
        const auto result = point / scalar;
        static_assert(std::is_same_v<typename decltype(result)::value_type, std::common_type_t<TestType1, TestType2>>);

        REQUIRE_THAT(result[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(9.0, 1e-6));
        REQUIRE_THAT(result[3], WithinAbs(8.4, 1e-6));
        REQUIRE(result.dimensions == 4);
    }
}

TEMPLATE_TEST_CASE("Point_Operators - Unary operators", "[point][operators][unary]", float, double, long double) {
    const Point<TestType, 10> point(1.5, -2.0, 3.25, 5.4, -0.4, 3.1, -2.2, 5.2, -99.0, -1.0);

    SECTION("Unary minus operation") {
        const Point<TestType, 10> result = -point;
        REQUIRE_THAT(result[0], WithinAbs(-1.5, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(-3.25, 1e-6));
        REQUIRE_THAT(result[3], WithinAbs(-5.4, 1e-6));
        REQUIRE_THAT(result[4], WithinAbs(0.4, 1e-6));
        REQUIRE_THAT(result[5], WithinAbs(-3.1, 1e-6));
        REQUIRE_THAT(result[6], WithinAbs(2.2, 1e-6));
        REQUIRE_THAT(result[7], WithinAbs(-5.2, 1e-6));
        REQUIRE_THAT(result[8], WithinAbs(99.0, 1e-6));
        REQUIRE_THAT(result[9], WithinAbs(1.0, 1e-6));
        REQUIRE(result.dimensions == 10);
    }
}

TEMPLATE_TEST_CASE("Point_Operators - Complex expressions and chained operations", "[point][operators][expressions]", float, double, long double) {
    SECTION("Multi-term linear combination") {
        const Point<TestType, 3> first_point(1.0, 2.0, 3.0);
        const Point<TestType, 3> second_point(4.0, -2.0, 0.5);
        const Point<TestType, 3> third_point(2.0, 8.0, 4.0);
        const TestType scalar = 2.0;

        const Point<TestType, 3> result = (first_point * scalar + second_point) - (-third_point / scalar);
        REQUIRE_THAT(result[0], WithinAbs(7.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(6.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(8.5, 1e-6));
        REQUIRE(result.dimensions == 3);
    }

    SECTION("Quadratic polynomial evaluation") {
        const Point<TestType, 3> point(2.0, -3.0, 0.5);
        const TestType first_scalar = 1.0;
        const TestType second_scalar = 2.0;
        const TestType third_scalar = 3.0;

        const Point<TestType, 3> result = second_scalar * (point * point) - third_scalar * point + first_scalar;
        REQUIRE_THAT(result[0], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(28.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(0.0, 1e-6));
        REQUIRE(result.dimensions == 3);
    }
}