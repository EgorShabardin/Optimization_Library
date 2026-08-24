#pragma once

#include <algorithm>
#include <concepts>
#include <numeric>
#include <ostream>
#include <cmath>

#include "Point_Operators.hpp"
#include "Point_Base.hpp"

namespace Optimization_Library {
	template<std::floating_point T, size_t dim, typename Stream>
	auto& operator << (Stream& os, const Point<T, dim>& point) {
		os << '(';
		for (size_t i = 0; i != dim; ++i) { os << point[i] << (i + 1 != dim ? ", " : ""); }
		os << ')';

		return os;
	}

	template<std::floating_point T, size_t dim>
	constexpr T dot (const Point<T, dim>& x, const Point<T, dim>& y) noexcept {
		return std::transform_reduce(x.begin(), x.end(), y.begin(), T(0));
	}

	template<std::floating_point T, size_t dim>
	constexpr T sum (const Point<T, dim>& point) noexcept { return std::accumulate(point.begin(), point.end(), T(0)); }

	template<std::floating_point T, size_t dim>
	constexpr T max (const Point<T, dim>& point) noexcept { return *std::max_element(point.begin(), point.end()); }

	template<std::floating_point T, size_t dim>
	constexpr T min (const Point<T, dim>& point) noexcept { return *std::min_element(point.begin(), point.end()); }

	template<std::floating_point T = double, size_t dim>
	constexpr T norm(const Point<T, dim>& point) noexcept { return std::sqrt(dot(point, point)); }

	template<std::floating_point T = double, size_t dim>
	constexpr T l1_norm(const Point<T, dim>& point) noexcept {
		T result = 0;
		for (const T& number : point) { result += std::abs(number); }
		return result;
	}

	template<std::floating_point T = double, size_t dim>
	constexpr T linf_norm(const Point<T, dim>& point) noexcept {
		T result = 0;
		for (const T& number : point) { result = std::max(std::abs(number), result); }
		return result;
	}

	template<std::floating_point T, size_t dim>
	constexpr T dist(const Point<T, dim>& x, const Point<T, dim>& y) noexcept { return norm(x - y); }

	template<std::floating_point T, size_t dim>
	constexpr Point<T, dim> normalize (const Point<T, dim>& point) noexcept {
		const T n = norm(point);
		if (n > 0) { return point / n; }
		return point;
	}
} // namespace Optimization_Library