#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_test_macros.hpp>

import Point;

using namespace Optimization_Library;
using Catch::Matchers::WithinAbs;

TEST_CASE("Point_Utils - Testing dot product and norms", "[point][utils][norm_dot]") {
    const Point3D_d first_point(1.0, 2.0, 3.0);
    const Point3D_d second_point(4.0, -5.0, 6.0);

    SECTION("Dot product operation") {
        const double result = dot(first_point, second_point);
        REQUIRE_THAT(result, WithinAbs(12.0, 1e-9));
    }

    SECTION("Dot product of orthogonal vectors") {
        const Point3D_d first_vector(1.0, 0.0, 0.0);
        const Point3D_d second_vector(0.0, 5.0, 0.0);

        const double result = dot(first_vector, second_vector);
        REQUIRE_THAT(result, WithinAbs(0.0, 1e-9));
    }

    SECTION("L1 norm calculation") {
        const Point3D_d point(3.0, 4.0, 0.0);
        const double l1_norm = norm_l1(point);
        REQUIRE_THAT(l1_norm, WithinAbs(7.0, 1e-9));
    }

    SECTION("L2 norm calculation") {
        const Point3D_d point(3.0, 4.0, 0.0);
        const double l2_norm = norm_l2(point);
        REQUIRE_THAT(l2_norm, WithinAbs(5.0, 1e-9));
    }

    SECTION("Inf norm calculation") {
        const Point3D_d point(3.0, 4.0, 0.0);
        const double inf_norm = norm_inf(point);
        REQUIRE_THAT(inf_norm, WithinAbs(4.0, 1e-9));
    }
}

TEST_CASE("Point_Utils - Testing distance and normalization", "[point][utils][dist_norm]") {
    const Point3D_d first_point(1.0, 2.0, 3.0);
    const Point3D_d second_point(4.0, 6.0, 3.0);

    SECTION("Distance calculation between two points") {
        const double distance_value = dist(first_point, second_point);
        REQUIRE_THAT(distance_value, WithinAbs(5.0, 1e-9));
    }

    SECTION("Normalization operation") {
        const Point3D_d point(0.0, 3.0, 4.0);
        const Point3D_d unit_vector = normalize(point);

        REQUIRE_THAT(unit_vector[0], WithinAbs(0.0, 1e-9));
        REQUIRE_THAT(unit_vector[1], WithinAbs(0.6, 1e-9));
        REQUIRE_THAT(unit_vector[2], WithinAbs(0.8, 1e-9));
        REQUIRE_THAT(norm_l2(unit_vector), WithinAbs(1.0, 1e-9));
    }
}

TEST_CASE("Point_Utils - Testing component-wise operations", "[point][utils][component]") {
    const Point3D_d point(1.4, -2.3, 1.5);

    SECTION("Sum of all components") {
        const double total_sum = sum(point);
        REQUIRE_THAT(total_sum, WithinAbs(0.6, 1e-9));
    }

    SECTION("Component-wise absolute values") {
        const Point3D_d abs_point = abs(point);
        REQUIRE_THAT(abs_point[0], WithinAbs(1.4, 1e-9));
        REQUIRE_THAT(abs_point[1], WithinAbs(2.3, 1e-9));
        REQUIRE_THAT(abs_point[2], WithinAbs(1.5, 1e-9));
    }

    SECTION("Component-wise sqrt values") {
        const Point3D_d point(4.0, 9.0, 1.0);
        const Point3D_d sqrt_point = sqrt(point);
        REQUIRE_THAT(sqrt_point[0], WithinAbs(2.0, 1e-9));
        REQUIRE_THAT(sqrt_point[1], WithinAbs(3.0, 1e-9));
        REQUIRE_THAT(sqrt_point[2], WithinAbs(1.0, 1e-9));
    }

    SECTION("Minimum element in point") {
        const double min_val = min(point);
        REQUIRE_THAT(min_val, WithinAbs(-2.3, 1e-9));
    }

    SECTION("Maximum element in point") {
        const double max_val = max(point);
        REQUIRE_THAT(max_val, WithinAbs(1.5, 1e-9));
    }
}

TEST_CASE("Point_Utils - Testing approximate equality", "[point][utils][approx]") {
    const Point3D_d base_point(1.0, 2.0, 3.0);
    const Point3D_d close_point(1.0000000001, 2.0000000001, 3.0000000001);
    const Point3D_d different_point(1.01, 2.0, 3.0);

    SECTION("Exact match and small numerical noise within tolerance") {
        REQUIRE(is_approx(base_point, base_point));
        REQUIRE(is_approx(base_point, close_point, 1e-8));
    }

    SECTION("Difference outside tolerance threshold") {
        REQUIRE_FALSE(is_approx(base_point, different_point, 1e-3));
    }
}