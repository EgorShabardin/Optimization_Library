#pragma once

#include <type_traits>
#include <algorithm>
#include <concepts>

#include "Operators_Base.hpp"
#include "Point_Base.hpp"

namespace Optimization_Library {
	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator + (const Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), Point_Operators::Binary_Operators::plus<R>{});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator + (const Point<T, dim>& lhs, U rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::Unary_Operators::plus<R>{rhs});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator + (T lhs, const Point<U, dim>& rhs) noexcept { return rhs + lhs; }

	template <std::floating_point T = double, std::floating_point U = double, size_t dim>
	constexpr Point<T, dim>& operator += (Point<T, dim>& lhs, U rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), lhs.begin(), Point_Operators::Unary_Operators::plus<T>{rhs});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator += (Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), Point_Operators::Binary_Operators::plus<T>{});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator - (const Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), Point_Operators::Binary_Operators::minus<R>{});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator - (const Point<T, dim>& lhs, U rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::Unary_Operators::minus<R>{rhs});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator - (T lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(rhs.begin(), rhs.end(), result.begin(), [lhs](const U& val) { return static_cast<R>(lhs - val); });
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator -= (Point<T, dim>& lhs, U rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), lhs.begin(), Point_Operators::Unary_Operators::minus<T>{rhs});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator -= (Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), Point_Operators::Binary_Operators::minus<T>{});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator * (const Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), Point_Operators::Binary_Operators::multiplies<R>{});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator * (const Point<T, dim>& lhs, U rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::Unary_Operators::multiplies<R>{rhs});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator * (T lhs, const Point<U, dim>& rhs) noexcept { return rhs * lhs; }

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator *= (Point<T, dim>& lhs, U rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), lhs.begin(), Point_Operators::Unary_Operators::multiplies<T>{rhs});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator *= (Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), Point_Operators::Binary_Operators::multiplies<T>{});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator / (const Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), result.begin(), Point_Operators::Binary_Operators::divides<R>{});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator / (const Point<T, dim>& lhs, U rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::Unary_Operators::divides<R>{rhs});
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr auto operator / (T lhs, const Point<U, dim>& rhs) noexcept {
		using R = std::common_type_t<T, U>;
		Point<R, dim> result;
		std::transform(rhs.begin(), rhs.end(), result.begin(), [lhs](const U& val) { return static_cast<R>(lhs / val); });
		return result;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator /= (Point<T, dim>& lhs, U rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), lhs.begin(), Point_Operators::Unary_Operators::divides<T>{rhs});
		return lhs;
	}

	template <std::floating_point T, std::floating_point U, size_t dim>
	constexpr Point<T, dim>& operator /= (Point<T, dim>& lhs, const Point<U, dim>& rhs) noexcept {
		std::transform(lhs.begin(), lhs.end(), rhs.begin(), lhs.begin(), Point_Operators::Binary_Operators::divides<T>{});
		return lhs;
	}

	template <std::floating_point T, size_t dim>
	constexpr Point<T, dim> abs(const Point<T, dim>& lhs) noexcept {
		Point<T, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::abs<T>{});
		return result;
	}

	template <std::floating_point T, size_t dim>
	constexpr Point<T, dim> sqrt(const Point<T, dim>& lhs) {
		Point<T, dim> result;
		std::transform(lhs.begin(), lhs.end(), result.begin(), Point_Operators::sqrt<T>{});
		return result;
	}
} // namespace Optimization_Library