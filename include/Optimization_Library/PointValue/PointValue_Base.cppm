module;

#include <type_traits>
#include <functional>
#include <concepts>
#include <utility>
#include <cstddef>

export module PointValue:PointValue_Base;

export import Point;

export namespace Optimization_Library {

	template<typename Function, typename PointType, typename ReturnType>
	concept ObjectiveFunction =
    	std::invocable<Function, const PointType&> &&
    	std::convertible_to<std::invoke_result_t<Function, const PointType&>, ReturnType>;

	template<std::floating_point T = double, std::size_t dim = 1> requires (dim > 0)
	struct PointValue {
		private:
		Point<T, dim> point{};
		T value{0};

		public:
		[[nodiscard]] constexpr T operator [] (std::size_t i) const noexcept { return this->point[i]; }
		[[nodiscard]] constexpr T get_value() const noexcept { return this->value; }
		[[nodiscard]] constexpr const Point<T, dim>& get_point() const noexcept { return this->point; }
		static constexpr std::size_t dimensions = dim;
		using value_type = T;

		constexpr PointValue() noexcept = default;
		explicit constexpr PointValue(const Point<T, dim>& point, T value) noexcept : point{point}, value{value} {}
		explicit constexpr PointValue(Point<T, dim>&& point, T value) noexcept : point{std::move(point)}, value{value} {}

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
		constexpr void update(const Point<T, dim>& point, Function&& func) {
			this->value = std::invoke(std::forward<Function>(func), point);
			this->point = point;
		}

		template<ObjectiveFunction<Point<T, dim>, T> Function>
		constexpr void update(Point<T, dim>&& point, Function&& func) {
			this->value = std::invoke(std::forward<Function>(func), point);
			this->point = std::move(point);
		}

		template<ObjectiveFunction<Point<T, dim>, T> Function>
		constexpr void update(Function&& func) { this->value = std::invoke(std::forward<Function>(func), point); }
	}; // struct PointValue

} // namespace Optimization_Library