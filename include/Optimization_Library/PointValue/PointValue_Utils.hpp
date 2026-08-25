#pragma once

#include <ostream>
#include <cmath>

#include "PointValue_Base.hpp"

namespace Optimization_Library {
    template<std::floating_point T, size_t dim, typename Stream>
	auto& operator << (Stream& os, const PointValue<T, dim>& point_value) {
		os << '{' << point_value.point << ", " << point_value.value << '}';
		return os;
	};

    template<std::floating_point T, size_t dim>
    constexpr bool operator < (const PointValue<T, dim>& lhs, const PointValue<T, dim>& rhs) noexcept { return lhs.value < rhs.value; }

	template<std::floating_point T, size_t dim>
    constexpr bool operator > (const PointValue<T, dim>& lhs, const PointValue<T, dim>& rhs) noexcept { return lhs.value > rhs.value; }

    template<std::floating_point T, size_t dim>
    constexpr bool is_approx (const PointValue<T, dim>& lhs, const PointValue<T, dim>& rhs, T eps = static_cast<T>(1e-9)) noexcept {
        return (std::abs(lhs.value - rhs.value) <= eps && is_approx(lhs.point, rhs.point, eps));
    }
} // namespace Optimization_Library