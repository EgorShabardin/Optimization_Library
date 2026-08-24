#pragma once

#include <functional>
#include <concepts>
#include <cmath>

namespace Optimization_Library {
	namespace Point_Operators {
		namespace Unary_Operators {
			template<std::floating_point T>
			struct plus {
				T value;

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr plus (U value) noexcept : value{static_cast<T>(value)} {}

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr T operator() (U lhs) const noexcept { return static_cast<T>(lhs) + value; }
			};

			template<std::floating_point T>
			struct minus {
				T value;

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr minus(U value) noexcept : value{static_cast<T>(value)} {}

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr T operator() (U lhs) const noexcept { return static_cast<T>(lhs) - value; }
			};

			template<std::floating_point T>
			struct multiplies {
				T value;

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr multiplies(U value) noexcept : value{static_cast<T>(value)} {}

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr T operator() (U lhs) const noexcept { return static_cast<T>(lhs) * value; }
			};

			template<std::floating_point T>
			struct divides {
				T value;

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr divides(U value) noexcept : value{static_cast<T>(value)} {}

				template<std::floating_point U> requires std::convertible_to<U, T>
				constexpr T operator() (U lhs) const { return static_cast<T>(lhs) / value; }
			};
		} // namespace Unary_Operators

		namespace Binary_Operators {
			template<std::floating_point T = void>
			using plus = std::plus<T>;

			template<std::floating_point T = void>
			using minus = std::minus<T>;

			template<std::floating_point T = void>
			using multiplies = std::multiplies<T>;

			template<std::floating_point T = void>
			using divides = std::divides<T>;
		} // namespace Binary_Operators

		template<std::floating_point T>
		struct sqrt {
			constexpr T operator() (T lhs) const { return std::sqrt(lhs); }
		};

		template<std::floating_point T>
		struct abs {
			constexpr T operator() (T lhs) const noexcept { return std::abs(lhs); }
		};
	} // namespace Point_Operators
} // namespace Optimization_Library