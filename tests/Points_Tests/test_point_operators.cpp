#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

import Point;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEST_CASE("Point_Operators - Testing addition operators", "[point][operators][addition]") {
    Point3D_d first_point(1.0, 2.0, 3.0);
    Point3D_d second_point(4.0, 5.0, 6.0);
    const double scalar = 2.5;

    SECTION("Addition assignment operation") {
        first_point += second_point;
        REQUIRE_THAT(first_point[0], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(first_point[1], WithinAbs(7.0, 1e-9));
        REQUIRE_THAT(first_point[2], WithinAbs(9.0, 1e-9));

        second_point += scalar;
        REQUIRE_THAT(second_point[0], WithinAbs(6.5, 1e-9));
        REQUIRE_THAT(second_point[1], WithinAbs(7.5, 1e-9));
        REQUIRE_THAT(second_point[2], WithinAbs(8.5, 1e-9));
    }

    SECTION("Binary addition operation") {
        const Point3D_d first_result = first_point + second_point;
        REQUIRE_THAT(first_result[0], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(first_result[1], WithinAbs(7.0, 1e-9));
        REQUIRE_THAT(first_result[2], WithinAbs(9.0, 1e-9));

        const Point3D_d second_result = first_point + scalar;
        REQUIRE_THAT(second_result[0], WithinAbs(3.5, 1e-9));
        REQUIRE_THAT(second_result[1], WithinAbs(4.5, 1e-9));
        REQUIRE_THAT(second_result[2], WithinAbs(5.5, 1e-9));

        const Point3D_d third_result = scalar + first_point;
        REQUIRE_THAT(third_result[0], WithinAbs(3.5, 1e-9));
        REQUIRE_THAT(third_result[1], WithinAbs(4.5, 1e-9));
        REQUIRE_THAT(third_result[2], WithinAbs(5.5, 1e-9));
    }
}

TEST_CASE("Point_Operators - Testing subtraction operators", "[point][operators][subtraction]") {
    Point3D_d first_point(1.0, 2.0, 3.0);
    Point3D_d second_point(4.0, 5.0, 6.0);
    const double scalar = 2.5;

    SECTION("Subtraction assignment operation") {
        first_point -= second_point;
        REQUIRE_THAT(first_point[0], WithinAbs(-3.0, 1e-9));
        REQUIRE_THAT(first_point[1], WithinAbs(-3.0, 1e-9));
        REQUIRE_THAT(first_point[2], WithinAbs(-3.0, 1e-9));

        second_point -= scalar;
        REQUIRE_THAT(second_point[0], WithinAbs(1.5, 1e-9));
        REQUIRE_THAT(second_point[1], WithinAbs(2.5, 1e-9));
        REQUIRE_THAT(second_point[2], WithinAbs(3.5, 1e-9));
    }

    SECTION("Binary subtraction operation") {
        const Point3D_d first_result = first_point - second_point;
        REQUIRE_THAT(first_result[0], WithinAbs(-3.0, 1e-9));
        REQUIRE_THAT(first_result[1], WithinAbs(-3.0, 1e-9));
        REQUIRE_THAT(first_result[2], WithinAbs(-3.0, 1e-9));

        const Point3D_d second_result = first_point - scalar;
        REQUIRE_THAT(second_result[0], WithinAbs(-1.5, 1e-9));
        REQUIRE_THAT(second_result[1], WithinAbs(-0.5, 1e-9));
        REQUIRE_THAT(second_result[2], WithinAbs(0.5, 1e-9));
    }
}

TEST_CASE("Point_Operators - Testing multiplication operators", "[point][operators][multiplication]") {
    Point3D_d first_point(1.0, 2.0, 3.0);
    Point3D_d second_point(4.0, 5.0, 6.0);
    const double scalar = 2.5;

    SECTION("Multiplication assignment operation") {
        first_point *= second_point;
        REQUIRE_THAT(first_point[0], WithinAbs(4.0, 1e-9));
        REQUIRE_THAT(first_point[1], WithinAbs(10.0, 1e-9));
        REQUIRE_THAT(first_point[2], WithinAbs(18.0, 1e-9));

        second_point *= scalar;
        REQUIRE_THAT(second_point[0], WithinAbs(10.0, 1e-9));
        REQUIRE_THAT(second_point[1], WithinAbs(12.5, 1e-9));
        REQUIRE_THAT(second_point[2], WithinAbs(15.0, 1e-9));
    }

    SECTION("Binary multiplication operation") {
        const Point3D_d first_result = first_point * second_point;
        REQUIRE_THAT(first_result[0], WithinAbs(4.0, 1e-9));
        REQUIRE_THAT(first_result[1], WithinAbs(10.0, 1e-9));
        REQUIRE_THAT(first_result[2], WithinAbs(18.0, 1e-9));

        const Point3D_d second_result = first_point * scalar;
        REQUIRE_THAT(second_result[0], WithinAbs(2.5, 1e-9));
        REQUIRE_THAT(second_result[1], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(second_result[2], WithinAbs(7.5, 1e-9));

        const Point3D_d third_result = scalar * first_point;
        REQUIRE_THAT(third_result[0], WithinAbs(2.5, 1e-9));
        REQUIRE_THAT(third_result[1], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(third_result[2], WithinAbs(7.5, 1e-9));
    }
}

TEST_CASE("Point_Operators - Testing division operators", "[point][operators][division]") {
    Point3D_d first_point(4.0, 10.0, 18.0);
    Point3D_d second_point(2.0, 2.0, 3.0);
    const double scalar = 2.0;

    SECTION("Division assignment operation") {
        first_point /= second_point;
        REQUIRE_THAT(first_point[0], WithinAbs(2.0, 1e-9));
        REQUIRE_THAT(first_point[1], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(first_point[2], WithinAbs(6.0, 1e-9));

        first_point /= scalar;
        REQUIRE_THAT(first_point[0], WithinAbs(1.0, 1e-9));
        REQUIRE_THAT(first_point[1], WithinAbs(2.5, 1e-9));
        REQUIRE_THAT(first_point[2], WithinAbs(3.0, 1e-9));
    }

    SECTION("Binary division operation") {
        const Point3D_d first_result = first_point / second_point;
        REQUIRE_THAT(first_result[0], WithinAbs(2.0, 1e-9));
        REQUIRE_THAT(first_result[1], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(first_result[2], WithinAbs(6.0, 1e-9));

        const Point3D_d second_result = first_point / scalar;
        REQUIRE_THAT(second_result[0], WithinAbs(2.0, 1e-9));
        REQUIRE_THAT(second_result[1], WithinAbs(5.0, 1e-9));
        REQUIRE_THAT(second_result[2], WithinAbs(9.0, 1e-9));
    }
}

TEST_CASE("Point_Operators - Testing unary operators", "[point][operators][unary]") {
    const Point3D_d point(1.5, -2.0, 3.25);

    SECTION("Unary minus operation") {
        const Point3D_d result = -point;
        REQUIRE_THAT(result[0], WithinAbs(-1.5, 1e-9));
        REQUIRE_THAT(result[1], WithinAbs(2.0, 1e-9));
        REQUIRE_THAT(result[2], WithinAbs(-3.25, 1e-9));
    }
}

TEST_CASE("Point_Operators - Testing complex expressions and chained operations", "[point][operators][complex]") {
    SECTION("Multi-term linear combination with unary operators") {
        const Point3D_d first_point(1.0, 2.0, 3.0);
        const Point3D_d second_point(4.0, -2.0, 0.5);
        const Point3D_d third_point(2.0, 8.0, 4.0);

        const Point3D_d result = (first_point * 2.0 + second_point) - (-third_point / 2.0);
        REQUIRE_THAT(result[0], WithinAbs(7.0, 1e-9));
        REQUIRE_THAT(result[1], WithinAbs(6.0, 1e-9));
        REQUIRE_THAT(result[2], WithinAbs(8.5, 1e-9));
    }

    SECTION("Element-wise quadratic polynomial evaluation") {
        const Point3D_d point(2.0, -3.0, 0.5);

        const Point3D_d result = 2.0 * (point * point) - 3.0 * point + 1.0;
        REQUIRE_THAT(result[0], WithinAbs(3.0, 1e-9));
        REQUIRE_THAT(result[1], WithinAbs(28.0, 1e-9));
        REQUIRE_THAT(result[2], WithinAbs(0.0, 1e-9));
    }
}

TEST_CASE("Point_Operators - Mixed-type addition", "[point][operators][mixed][addition]") {
    const Point<float, 3> point_float(1.0f, 2.0f, 3.0f);
    const Point<double, 3> point_double(4.0, 5.0, 6.0);
    const double scalar_double = 2.5;

    SECTION("Point<float> + Point<double> -> Point<double>") {
        const auto result = point_float + point_double;
        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(7.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(9.0, 1e-6));
    }

    SECTION("Point<float> + double and double + Point<float> -> Point<double>") {
        const auto first_result = point_float + scalar_double;
        const auto second_result = scalar_double + point_float;

        static_assert(std::is_same_v<typename decltype(first_result)::value_type, double>);
        REQUIRE_THAT(first_result[0], WithinAbs(3.5, 1e-6));
        REQUIRE_THAT(first_result[1], WithinAbs(4.5, 1e-6));
        REQUIRE_THAT(first_result[2], WithinAbs(5.5, 1e-6));

        static_assert(std::is_same_v<typename decltype(second_result)::value_type, double>);
        REQUIRE_THAT(second_result[0], WithinAbs(3.5, 1e-6));
        REQUIRE_THAT(second_result[1], WithinAbs(4.5, 1e-6));
        REQUIRE_THAT(second_result[2], WithinAbs(5.5, 1e-6));
    }

    SECTION("Point<float> += double (in-place modification)") {
        Point<float, 3> point_float(1.0f, 2.0f, 3.0f);
        point_float += scalar_double;

        static_assert(std::is_same_v<typename decltype(point_float)::value_type, float>);
        REQUIRE_THAT(point_float[0], WithinAbs(3.5f, 1e-6));
        REQUIRE_THAT(point_float[1], WithinAbs(4.5f, 1e-6));
        REQUIRE_THAT(point_float[2], WithinAbs(5.5f, 1e-6));
    }
}

TEST_CASE("Point_Operators - Mixed-type subtraction", "[point][operators][mixed][subtraction]") {
    const Point<float, 3> point_float(1.0f, 2.0f, 3.0f);
    const Point<double, 3> point_double(4.0, 5.0, 6.0);
    const double scalar_double = 2.5;

    SECTION("Point<double> - Point<float> -> Point<double>") {
        const auto result = point_double - point_float;
        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(3.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(3.0, 1e-6));
    }

    SECTION("Point<float> - double -> Point<double>") {
        const auto result = point_float - scalar_double;
        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(-1.5, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(-0.5, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(0.5, 1e-6));
    }

    SECTION("Point<float> -= double (in-place modification)") {
        Point<float, 3> point_float(4.0f, 5.0f, 6.0f);
        point_float -= scalar_double;

        static_assert(std::is_same_v<typename decltype(point_float)::value_type, float>);
        REQUIRE_THAT(point_float[0], WithinAbs(1.5f, 1e-6));
        REQUIRE_THAT(point_float[1], WithinAbs(2.5f, 1e-6));
        REQUIRE_THAT(point_float[2], WithinAbs(3.5f, 1e-6));
    }
}

TEST_CASE("Point_Operators - Mixed-type multiplication", "[point][operators][mixed][multiplication]") {
    const Point<float, 3> point_float(2.0f, 4.0f, 6.0f);
    const Point<double, 3> point_double(0.5, 1.5, 2.5);
    const double scalar_double = 2.5;

    SECTION("Point<float> * Point<double> -> Point<double>") {
        const auto result = point_float * point_double;
        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(1.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(6.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(15.0, 1e-6));
    }

    SECTION("Point<float> * double and double * Point<float> -> Point<double>") {
        const auto first_result = point_float * scalar_double;
        const auto second_result = scalar_double * point_float;

        static_assert(std::is_same_v<typename decltype(first_result)::value_type, double>);
        REQUIRE_THAT(first_result[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(first_result[1], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(first_result[2], WithinAbs(15.0, 1e-6));


        static_assert(std::is_same_v<typename decltype(second_result)::value_type, double>);
        REQUIRE_THAT(second_result[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(second_result[1], WithinAbs(10.0, 1e-6));
        REQUIRE_THAT(second_result[2], WithinAbs(15.0, 1e-6));
    }

    SECTION("Point<float> *= double (in-place modification)") {
        Point<float, 3> point_float(2.0f, 4.0f, 6.0f);
        point_float *= scalar_double;

        static_assert(std::is_same_v<typename decltype(point_float)::value_type, float>);
        REQUIRE_THAT(point_float[0], WithinAbs(5.0f, 1e-6));
        REQUIRE_THAT(point_float[1], WithinAbs(10.0f, 1e-6));
        REQUIRE_THAT(point_float[2], WithinAbs(15.0f, 1e-6));
    }
}

TEST_CASE("Point_Operators - Mixed-type division", "[point][operators][mixed][division]") {
    const Point<double, 3> point_double(10.0, 15.0, 20.0);
    const Point<float, 3> point_float(2.0f, 3.0f, 4.0f);
    const double scalar_double = 2.5;

    SECTION("Point<double> / Point<float> -> Point<double>") {
        const auto result = point_double / point_float;
        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(5.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(5.0, 1e-6));
    }

    SECTION("Point<float> / double -> Point<double>") {
        const Point<float, 3> point_float(5.0f, 10.0f, 15.0f);
        const auto result = point_float / scalar_double;

        static_assert(std::is_same_v<typename decltype(result)::value_type, double>);
        REQUIRE_THAT(result[0], WithinAbs(2.0, 1e-6));
        REQUIRE_THAT(result[1], WithinAbs(4.0, 1e-6));
        REQUIRE_THAT(result[2], WithinAbs(6.0, 1e-6));
    }

    SECTION("Point<float> /= double (in-place modification)") {
        Point<float, 3> point_float(5.0f, 10.0f, 15.0f);
        point_float /= scalar_double;

        static_assert(std::is_same_v<typename decltype(point_float)::value_type, float>);
        REQUIRE_THAT(point_float[0], WithinAbs(2.0f, 1e-6));
        REQUIRE_THAT(point_float[1], WithinAbs(4.0f, 1e-6));
        REQUIRE_THAT(point_float[2], WithinAbs(6.0f, 1e-6));
    }
}