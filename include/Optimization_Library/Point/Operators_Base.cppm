module;

#include <functional>
#include <concepts>
#include <cmath>

export module Point:Operators_Base;

export namespace Optimization_Library {
	namespace Point_Operators {

		namespace Unary_Operators {
			template<std::floating_point T>
			struct plus {
				T value;
				constexpr plus (T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs + value; }
			};

			template<std::floating_point T>
			struct minus {
				T value;
				constexpr minus(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs - value; }
			};

			template<std::floating_point T>
			struct multiplies {
				T value;
				constexpr multiplies(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs * value; }
			};

			template<std::floating_point T>
			struct divides {
				T value;
				constexpr divides(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs / value; }
			};

			template<std::floating_point T>
            struct negative {
                constexpr T operator() (T lhs) const noexcept { return -lhs; }
            };

			template<std::floating_point T> plus(T) -> plus<T>;
			template<std::floating_point T> minus(T) -> minus<T>;
			template<std::floating_point T> multiplies(T) -> multiplies<T>;
			template<std::floating_point T> divides(T) -> divides<T>;
		} // namespace Unary_Operators

		namespace Binary_Operators {
			template<std::floating_point T>
			using plus = std::plus<T>;

			template<std::floating_point T>
			using minus = std::minus<T>;

			template<std::floating_point T>
			using multiplies = std::multiplies<T>;

			template<std::floating_point T>
			using divides = std::divides<T>;
		} // namespace Binary_Operators

		template<std::floating_point T>
		struct sqrt {
			constexpr T operator() (T lhs) const noexcept { return std::sqrt(lhs); }
		};

		template<std::floating_point T>
		struct abs {
			constexpr T operator() (T lhs) const noexcept { return std::abs(lhs); }
		};

	} // namespace Point_Operators
} // namespace Optimization_Library