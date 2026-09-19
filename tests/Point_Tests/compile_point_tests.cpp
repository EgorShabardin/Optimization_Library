#include <array>

import Point;

using namespace Optimization_Library;

namespace Point_Base {
    constexpr Point<double, 3> point_double;
    static_assert(point_double[0] == 0.0 && point_double[1] == 0.0 && point_double[2] == 0.0);
    static_assert(point_double.dimensions == 3);

    constexpr Point<float, 2> point_zeros = Point<float, 2>::zeros();
    static_assert(point_zeros[0] == 0.0f && point_zeros[1] == 0.0f);
    static_assert(point_zeros.dimensions == 2);

    constexpr Point<float, 1> point_ones = Point<float, 1>::ones();
    static_assert(point_ones[0] == 1.0f);
    static_assert(point_ones.dimensions == 1);

    constexpr Point<long double, 4> point_ldouble(3.4l, 5.4l, 2.1l, 0.5l);
    static_assert(point_ldouble[0] == 3.4l && point_ldouble[1] == 5.4l && point_ldouble[2] == 2.1l && point_ldouble[3] == 0.5l);
    static_assert(point_ldouble.dimensions == 4);

    constexpr const std::array<double, 3> arr{1.2, 3.3, 4.5};
    constexpr Point<double, 3> array_point(arr);
    static_assert(array_point[0] == 1.2 && array_point[1] == 3.3 && array_point[2] == 4.5);
    static_assert(array_point.dimensions == 3);

    constexpr const std::array<double, 3> other_arr = array_point.as_array();
    static_assert(other_arr[0] == 1.2 && other_arr[1] == 3.3 && other_arr[2] == 4.5);
    static_assert(other_arr.size() == 3);

    static_assert(!std::is_convertible_v<std::array<double,3>, Point<double,3>>);
}

namespace Point_Operators {
    constexpr Point<double, 3> first_point(1.0, 4.0, 5.0);
    constexpr Point<double, 3> second_point(3.0, 1.0, 3.0);
    constexpr double scalar = 2.0;

    constexpr auto sum = first_point + second_point;
    static_assert(sum[0] == 4.0 && sum[1] == 5.0 && sum[2] == 8.0);

    constexpr auto difference = first_point - second_point;
    static_assert(difference[0] == -2.0 && difference[1] == 3.0 && difference[2] == 2.0);

    constexpr auto product = first_point * second_point;
    static_assert(product[0] == 3.0 && product[1] == 4.0 && product[2] == 15.0);

    constexpr auto quotient = first_point / second_point;
    static_assert(quotient[0] == 1.0 / 3.0 && quotient[1] == 4.0 && quotient[2] == 5.0 / 3.0);

    constexpr auto point_scalar_sum = first_point + scalar;
    static_assert(point_scalar_sum[0] == 3.0 && point_scalar_sum[1] == 6.0 && point_scalar_sum[2] == 7.0);

    constexpr auto scalar_point_sum = scalar + first_point;
    static_assert(scalar_point_sum[0] == 3.0 && scalar_point_sum[1] == 6.0 && scalar_point_sum[2] == 7.0);

    constexpr auto point_scalar_product = first_point * scalar;
    static_assert(point_scalar_product[0] == 2.0 && point_scalar_product[1] == 8.0 && point_scalar_product[2] == 10.0);

    constexpr auto scalar_point_product = scalar * first_point;
    static_assert(scalar_point_product[0] == 2.0 && scalar_point_product[1] == 8.0 && scalar_point_product[2] == 10.0);

    constexpr auto point_scalar_difference = first_point - scalar;
    static_assert(point_scalar_difference[0] == -1.0 && point_scalar_difference[1] == 2.0 && point_scalar_difference[2] == 3.0);

    constexpr auto point_scalar_quotient = first_point / scalar;
    static_assert(point_scalar_quotient[0] == 0.5 && point_scalar_quotient[1] == 2.0 && point_scalar_quotient[2] == 2.5);

    constexpr bool test_add_assign_point() {
        Point<double, 3> fist_point(1.0, 4.0, 5.0);
        Point<double, 3> second_point(3.0, 1.0, 3.0);
        fist_point += second_point;

        return fist_point[0] == 4.0 && fist_point[1] == 5.0 && fist_point[2] == 8.0;
    }

    static_assert(test_add_assign_point());

    constexpr bool test_add_assign_scalar() {
        Point<double, 3> point(1.0, 4.0, 5.0);
        point += 2.0;

        return point[0] == 3.0 && point[1] == 6.0 && point[2] == 7.0;
    }

    static_assert(test_add_assign_scalar());

    constexpr bool test_sub_assign_point() {
        Point<double, 3> fist_point(1.0, 4.0, 5.0);
        Point<double, 3> second_point(3.0, 1.0, 3.0);
        fist_point -= second_point;

        return fist_point[0] == -2.0 && fist_point[1] == 3.0 && fist_point[2] == 2.0;
    }

    static_assert(test_sub_assign_point());

    constexpr bool test_sub_assign_scalar() {
        Point<double, 3> point(1.0, 4.0, 5.0);
        point -= 2.0;

        return point[0] == -1.0 && point[1] == 2.0 && point[2] == 3.0;
    }

    static_assert(test_sub_assign_scalar());

    constexpr bool test_mul_assign_point() {
        Point<double, 3> first_point(1.0, 4.0, 5.0);
        Point<double, 3> second_point(3.0, 1.0, 3.0);
        first_point *= second_point;

        return first_point[0] == 3.0 && first_point[1] == 4.0 && first_point[2] == 15.0;
    }

    static_assert(test_mul_assign_point());

    constexpr bool test_mul_assign_scalar() {
        Point<double, 3> point(1.0, 4.0, 5.0);
        point *= 2.0;

        return point[0] == 2.0 && point[1] == 8.0 && point[2] == 10.0;
    }

    static_assert(test_mul_assign_scalar());

    constexpr bool test_div_assign_point() {
        Point<double, 3> first_point(1.0, 4.0, 5.0);
        Point<double, 3> second_point(3.0, 1.0, 3.0);
        first_point /= second_point;

        return first_point[0] == 1.0 / 3.0 && first_point[1] == 4.0 && first_point[2] == 5.0 / 3.0;
    }

    static_assert(test_div_assign_point());

    constexpr bool test_div_assign_scalar() {
        Point<double, 3> point(1.0, 4.0, 5.0);
        point /= 2.0;

        return point[0] == 0.5 && point[1] == 2.0 && point[2] == 2.5;
    }

    static_assert(test_div_assign_scalar());
}

namespace Point_Utils {
    constexpr Point<double, 3> first_point(1.0, 4.0, 5.0);
    constexpr Point<double, 3> second_point(3.0, 1.0, 3.0);

    constexpr auto scalar_product = dot(first_point, second_point);
    static_assert(scalar_product == 22.0);

    constexpr Point<double, 3> close_point(1.0 + 1e-14, 4.0 - 1e-14, 5.0 + 1e-14);
    constexpr Point<double, 3> different_point(1.0, 4.0, 5.1);

    static_assert(is_approx(first_point, close_point));
    static_assert(!is_approx(first_point, different_point));
}