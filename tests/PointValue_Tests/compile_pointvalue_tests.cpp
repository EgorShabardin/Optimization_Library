#include <concepts>
#include <compare>

import PointValue;
import Point;

using namespace Optimization_Library;

namespace PointValue_Base {
    constexpr PointValue<double, 3> pointvalue;
    static_assert(pointvalue[0] == 0.0 && pointvalue[1] == 0.0 && pointvalue[2] == 0.0 && pointvalue.get_value() == 0.0);
    static_assert(pointvalue.dimensions == 3);

    constexpr Point<float, 2> point(2.3f, 4.4f);
    constexpr PointValue<float, 2> pointvalue_lvalue(point, 4.2f);
    static_assert(pointvalue_lvalue[0] == 2.3f && pointvalue_lvalue[1] == 4.4f && pointvalue_lvalue.get_value() == 4.2f);
    static_assert(pointvalue_lvalue.dimensions == 2);

    constexpr PointValue<long double, 2> pointvalue_rvalue(Point<long double, 2>(3.3l, 2.1l), 4.2l);
    static_assert(pointvalue_rvalue[0] == 3.3l && pointvalue_rvalue[1] == 2.1l && pointvalue_rvalue.get_value() == 4.2l);
    static_assert(pointvalue_rvalue.dimensions == 2);

    constexpr Point<float, 2> other_point = pointvalue_lvalue.get_point();
    static_assert(other_point[0] == 2.3f && other_point[1] == 4.4f);
    static_assert(other_point.dimensions == 2);

    auto square_sum = [](const auto& p) constexpr -> double { return p[0] * p[0] + 3.0; };
    constexpr Point<double, 1> point_fromfun(2.0);
    constexpr PointValue<double, 1> first_pointvalue_fromfun = PointValue<double, 1>::FromFunction(point_fromfun, square_sum);
    static_assert(first_pointvalue_fromfun[0] == 2.0 && first_pointvalue_fromfun.get_value() == 7.0);
    static_assert(first_pointvalue_fromfun.dimensions == 1);

    constexpr PointValue<double, 1> second_pointvalue_fromfun = PointValue<double, 1>::FromFunction(Point<double, 1>(3.0), square_sum);
    static_assert(second_pointvalue_fromfun[0] == 3.0 && second_pointvalue_fromfun.get_value() == 12.0);
    static_assert(second_pointvalue_fromfun.dimensions == 1);

    constexpr bool test_update_methods() {
        PointValue<double, 1> pointvalue(Point<double, 1>(1.0), 0.0);
        pointvalue.update(square_sum);
        if (pointvalue[0] != 1.0 || pointvalue.get_value() != 4.0) return false;

        constexpr Point<double, 1> new_point(4.0);
        pointvalue.update(new_point, square_sum);
        if (pointvalue[0] != 4.0 || pointvalue.get_value() != 19.0) return false;

        pointvalue.update(Point<double, 1>(5.0), square_sum);
        if (pointvalue[0] != 5.0 || pointvalue.get_value() != 28.0) return false;

        return true;
    }
    static_assert(test_update_methods(), "PointValue update methods test failed!");
}

namespace PointValue_Utils {
    constexpr PointValue<double, 2> first_pointvalue(Point<double, 2>(1.0, 2.0), 5.0);
    constexpr PointValue<double, 2> second_pointvalue(Point<double, 2>(1.0, 2.0), 10.0);
    constexpr PointValue<double, 2> third_pointvalue(Point<double, 2>(1.0, 2.0), 5.0);
    constexpr PointValue<float, 2>  float_pointvalue(Point<float, 2>(1.0f, 2.0001f), 5.0001f);

    static_assert((first_pointvalue <=> second_pointvalue) == std::partial_ordering::less);
    static_assert((second_pointvalue <=> first_pointvalue) == std::partial_ordering::greater);
    static_assert((first_pointvalue <=> third_pointvalue) == std::partial_ordering::equivalent);
    static_assert((first_pointvalue <=> float_pointvalue) == std::partial_ordering::less);

    static_assert(first_pointvalue < second_pointvalue);
    static_assert(second_pointvalue > first_pointvalue);
    static_assert(first_pointvalue <= third_pointvalue);
    static_assert(first_pointvalue >= third_pointvalue);
    static_assert(first_pointvalue <= float_pointvalue);
    static_assert(!std::equality_comparable_with<PointValue<double,2>, PointValue<double,2>>);

    static_assert(is_approx(first_pointvalue, third_pointvalue));
    static_assert(is_approx(first_pointvalue, float_pointvalue, 1e-3, 1e-3));
    static_assert(!is_approx(first_pointvalue, float_pointvalue, 1e-6, 1e-6));
}

namespace ObjectiveFunction_Concept {
    constexpr auto valid_objective = [](const Point<double, 2>& p) -> double { return p[0] + p[1]; };
    static_assert(ObjectiveFunction<decltype(valid_objective), Point<double, 2>, double>);

    constexpr auto wrong_param = [](int x) -> double { return x; };
    static_assert(!ObjectiveFunction<decltype(wrong_param), Point<double, 2>, double>);

    struct NotConvertible {};
    constexpr auto wrong_return = [](const Point<double, 2>&) -> NotConvertible { return {}; };
    static_assert(!ObjectiveFunction<decltype(wrong_return), Point<double, 2>, double>);

}