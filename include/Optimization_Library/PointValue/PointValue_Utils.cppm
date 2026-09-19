module;

#include <type_traits>
#include <concepts>
#include <compare>
#include <cstddef>
#include <limits>

export module PointValue:PointValue_Utils;

import :PointValue_Base;
import Point;

export namespace Optimization_Library {

    template<std::floating_point T, std::size_t dim, typename Stream>
    requires requires(Stream& os, T val) { os << val; }
	Stream& operator << (Stream& os, const PointValue<T, dim>& point_value) {
		os << '{' << point_value.get_point() << ", " << point_value.get_value() << '}';
		return os;
	}

    template<std::floating_point T, std::floating_point U, std::size_t dim>
    [[nodiscard]] constexpr std::partial_ordering operator <=> (const PointValue<T, dim>& lhs, const PointValue<U, dim>& rhs) noexcept {
        using R = std::common_type_t<T, U>;
        return static_cast<R>(lhs.get_value()) <=> static_cast<R>(rhs.get_value());
    }

    template<std::floating_point T, std::floating_point U, std::size_t dim>
    constexpr bool operator == (const PointValue<T, dim>& lhs, const PointValue<U, dim>& rhs) noexcept = delete;

    template<std::floating_point T, std::floating_point U, std::size_t dim>
    constexpr bool operator != (const PointValue<T, dim>& lhs, const PointValue<U, dim>& rhs) noexcept = delete;

    template<std::floating_point T, std::floating_point U, std::size_t dim>
    [[nodiscard]] constexpr bool is_approx (const PointValue<T, dim>& lhs, const PointValue<U, dim>& rhs,
        std::common_type_t<T, U> value_eps = std::numeric_limits<std::common_type_t<T, U>>::epsilon() * 1e3,
        std::common_type_t<T, U> point_eps = std::numeric_limits<std::common_type_t<T, U>>::epsilon() * 1e3) noexcept {

        using R = std::common_type_t<T, U>;
        const R diff = static_cast<R>(lhs.get_value()) - static_cast<R>(rhs.get_value());
        return (diff * diff <= value_eps * value_eps && is_approx(lhs.get_point(), rhs.get_point(), point_eps));
    }

} // namespace Optimization_Library