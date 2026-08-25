#pragma once

#include <concepts>
#include <utility>

#include "../Point.hpp"

namespace Optimization_Library {
	template<std::floating_point T = double, size_t dim = 1>
	struct PointValue {
		Point<T, dim> point;
		T value;

		constexpr PointValue() noexcept = default;
		constexpr PointValue(const PointValue&) noexcept = default;
		constexpr PointValue(PointValue&&) noexcept = default;
		constexpr PointValue& operator = (const PointValue&) noexcept = default;
		constexpr PointValue& operator = (PointValue&&) noexcept = default;

		constexpr PointValue(const RawPoint<T, dim>& point, T value) noexcept : point{point}, value{value} {}
		constexpr PointValue(RawPoint<T, dim>&& point, T value) noexcept : point{std::move(point)}, value{value} {}

		constexpr PointValue(const Point<T, dim>& point, T value) noexcept : point{point}, value{value} {}
		constexpr PointValue(Point<T, dim>&& point, T value) noexcept : point{std::move(point)}, value{value} {}

		template<typename Function>
		static constexpr PointValue<T, dim> Compute_Value(const Point<T, dim>& point, Function&& function) {
			return PointValue {point, std::forward<Function>(function)(point)};
		}

		template<typename Function>
		static constexpr PointValue<T, dim> Compute_Value(const RawPoint<T, dim>& point, Function&& function) {
			return PointValue {Point<T, dim>(point), std::forward<Function>(function)(point)};
		}

		template<typename Function>
		constexpr void update(Function&& func) { value = std::forward<Function>(func)(point); }

		static constexpr PointValue<T, dim> Zeros () noexcept { return PointValue {Point<T, dim>::Zeros(), T(0)}; }

		constexpr T operator [] (size_t i) const noexcept { return this->point[i]; }
		constexpr T& operator [] (size_t i) noexcept { return this->point[i]; }
	}; // struct PointValue
} // namespace Optimization_Library