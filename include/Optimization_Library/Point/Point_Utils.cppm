module;

#include <type_traits>
#include <functional>
#include <algorithm>
#include <concepts>
#include <numeric>
#include <cstddef>
#include <limits>
#include <cmath>

export module Point:Point_Utils;

import :Point_Operators;
import :Point_Base;

export namespace Optimization_Library {

	template<std::floating_point T, std::size_t dim, typename Stream>
	requires requires(Stream& os, T val) { os << val; }
	Stream& operator << (Stream& os, const Point<T, dim>& point) {
		os << '(' << point[0];
		for (std::size_t i = 1; i != dim; ++i) { os << ", " << point[i]; }
		os << ')';

		return os;
	}

	template <std::floating_point T, std::floating_point U, std::size_t dim>
	[[nodiscard]] constexpr auto dot(const Point<T, dim>& first_point, const Point<U, dim>& second_point) noexcept {
		using R = std::common_type_t<T, U>;
		return std::transform_reduce(first_point.begin(), first_point.end(), second_point.begin(), static_cast<R>(0));
	}

	template<std::floating_point T, std::size_t dim>
	[[nodiscard]] T norm_l1(const Point<T, dim>& point) noexcept {
		return std::transform_reduce(point.begin(), point.end(), static_cast<T>(0), std::plus<T>{}, [](const T val) { return std::abs(val); });
	}

	template<std::floating_point T, std::size_t dim>
	[[nodiscard]] T norm_l2(const Point<T, dim>& point) noexcept { return std::sqrt(dot(point, point)); }

	template<std::floating_point T, std::size_t dim>
	[[nodiscard]] T norm_linf(const Point<T, dim>& point) noexcept {
		return std::transform_reduce(point.begin(), point.end(), static_cast<T>(0), [](T a, T b) { return std::max(a, b); }, [](const T val) { return std::abs(val); });
	}

	template <std::floating_point T, std::floating_point U, std::size_t dim>
	[[nodiscard]] auto dist(const Point<T, dim>& first_point, const Point<U, dim>& second_point) noexcept {
		return norm_l2(first_point - second_point);
	}

	template<std::floating_point T, std::size_t dim>
	[[nodiscard]] Point<T, dim> normalize (const Point<T, dim>& point) noexcept {
		const T point_norm = norm_l2(point);
		if (point_norm > std::numeric_limits<T>::epsilon() * 1e3) { return point / point_norm; }
		return point;
	}

	template <std::floating_point T, std::floating_point U, std::size_t dim>
	[[nodiscard]] constexpr bool is_approx (const Point<T, dim>& lhs, const Point<U, dim>& rhs,
		std::common_type_t<T, U> eps = std::numeric_limits<std::common_type_t<T, U>>::epsilon() * 1e3) noexcept {

		using R = std::common_type_t<T, U>;
		const Point<R, dim> diff = lhs - rhs;
		return dot(diff, diff) <= (eps * eps);
	}

} // namespace Optimization_Library