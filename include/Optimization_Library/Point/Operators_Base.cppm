module;

#include <functional>
#include <concepts>
#include <cmath>

module Point:Operators_Base;

namespace Optimization_Library {
	namespace Point_Operators {

		namespace Unary_Operators {
			template<std::floating_point T>
			struct plus {
				T value;
				explicit constexpr plus (T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs + value; }
			};

			template<std::floating_point T>
			struct minus {
				T value;
				explicit constexpr minus(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs - value; }
			};

			template<std::floating_point T>
			struct multiplies {
				T value;
				explicit constexpr multiplies(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs * value; }
			};

			template<std::floating_point T>
			struct divides {
				T value;
				explicit constexpr divides(T value) noexcept : value{value} {}
				constexpr T operator() (T lhs) const noexcept { return lhs / value; }
			};

			template<std::floating_point T>
			struct negative {
				constexpr T operator() (T lhs) const noexcept { return -lhs; }
			};
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
			T operator() (T lhs) const noexcept { return std::sqrt(lhs); }
		};

		template<std::floating_point T>
		struct abs {
			T operator() (T lhs) const noexcept { return std::abs(lhs); }
		};

	} // namespace Point_Operators
} // namespace Optimization_Library