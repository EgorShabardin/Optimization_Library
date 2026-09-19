module;

#include <functional>
#include <concepts>
#include <utility>
#include <cstddef>

export module PointValue:PointValue_Base;

import Point;

export namespace Optimization_Library {

	template<typename Function, typename PointType, typename ReturnType>
	concept ObjectiveFunction =
    	std::invocable<Function, const PointType&> &&
    	std::convertible_to<std::invoke_result_t<Function, const PointType&>, ReturnType>;

	template<std::floating_point T = double, size_t dim = 1> requires (dim > 0)
	struct PointValue {
		Point<T, dim> point {};
		T value {0};

		constexpr PointValue() noexcept = default;
		[[nodiscard]] constexpr PointValue(const Point<T, dim>& point, T value) noexcept : point{point}, value{value} {}
		[[nodiscard]] constexpr PointValue(Point<T, dim>&& point, T value) noexcept : point{std::move(point)}, value{value} {}

		template<ObjectiveFunction<Point<T, dim>, T> Function>
		[[nodiscard]] static constexpr PointValue<T, dim> FromFunction(const Point<T, dim>& point, Function&& function) {
			return PointValue {point, std::invoke(std::forward<Function>(function), point)};
		}

		template<ObjectiveFunction<Point<T, dim>, T> Function>
		[[nodiscard]] static constexpr PointValue<T, dim> FromFunction(Point<T, dim>&& point, Function&& function) {
			const T function_value = std::invoke(std::forward<Function>(function), point);
			return PointValue {std::move(point), function_value};
		}

		template<ObjectiveFunction<Point<T, dim>, T> Function>
		constexpr void update(Function&& func) { value = std::invoke(std::forward<Function>(func), point); }

		[[nodiscard]] constexpr T operator [] (size_t i) const noexcept { return this->point[i]; }
		[[nodiscard]] constexpr T& operator [] (size_t i) noexcept { return this->point[i]; }
	}; // struct PointValue

} // namespace Optimization_Library