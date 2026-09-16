module;

#include <algorithm>
#include <concepts>
#include <numeric>
#include <ostream>
#include <limits>
#include <cmath>

export module Point:Point_Utils;

import :Point_Operators;
import :Point_Base;

export namespace Optimization_Library {

	template<std::floating_point T, size_t dim, typename Stream>
	auto& operator << (Stream& os, const Point<T, dim>& point) {
		os << '(' << point[0];
		for (size_t i = 1; i != dim; ++i) { os << ", " << point[i]; }
		os << ')';

		return os;
	}

	template<std::floating_point T, size_t dim>
	[[nodiscard]] constexpr T dot(const Point<T, dim>& x, const Point<T, dim>& y) noexcept {
		return std::transform_reduce(x.begin(), x.end(), y.begin(), T(0));
	}

	template<std::floating_point T, size_t dim>
	[[nodiscard]] constexpr T sum(const Point<T, dim>& point) noexcept { return std::accumulate(point.begin(), point.end(), T(0)); }

	template<std::floating_point T, size_t dim>
	[[nodiscard]] constexpr T max(const Point<T, dim>& point) noexcept { return *std::max_element(point.begin(), point.end()); }

	template<std::floating_point T, size_t dim>
	[[nodiscard]] constexpr T min(const Point<T, dim>& point) noexcept { return *std::min_element(point.begin(), point.end()); }

	template<std::floating_point T, size_t dim>
	[[nodiscard]] T norm_l1(const Point<T, dim>& point) noexcept {
		T result = 0;
		for (const T& number : point) { result += std::abs(number); }
		return result;
	}

	template<std::floating_point T, size_t dim>
	[[nodiscard]] T norm_l2(const Point<T, dim>& point) noexcept { return std::sqrt(dot(point, point)); }

	template<std::floating_point T, size_t dim>
	[[nodiscard]] T norm_inf(const Point<T, dim>& point) noexcept {
		T result = 0;
		for (const T& number : point) { result = std::max(std::abs(number), result); }
		return result;
	}

	template<std::floating_point T, size_t dim>
	[[nodiscard]] T dist(const Point<T, dim>& x, const Point<T, dim>& y) noexcept { return norm_l2(x - y); }

	template<std::floating_point T, size_t dim>
	[[nodiscard]] Point<T, dim> normalize (const Point<T, dim>& point) noexcept {
		const T n = norm_l2(point);
		if (n > std::numeric_limits<T>::epsilon()) { return point / n; }
		return point;
	}

	template<std::floating_point T, size_t dim>
	[[nodiscard]] constexpr bool is_approx (const Point<T, dim>& lhs, const Point<T, dim>& rhs, T eps = static_cast<T>(1e-9)) noexcept {
		const Point<T, dim> diff = lhs - rhs;
		return dot(diff, diff) <= (eps * eps);
	}

} // namespace Optimization_Library