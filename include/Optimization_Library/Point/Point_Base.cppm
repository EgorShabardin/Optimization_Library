module;

#include <type_traits>
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <array>

export module Point:Point_Base;

namespace Optimization_Library {

	template<std::floating_point T = double, std::size_t dim = 1> requires (dim > 0)
	using RawPoint = std::array<T, dim>;

	export template<std::floating_point T = double, std::size_t dim = 1> requires (dim > 0)
	struct Point : private RawPoint<T, dim> {
		using RawPoint<T, dim>::operator[];
		using RawPoint<T, dim>::at;
		using RawPoint<T, dim>::data;
		using RawPoint<T, dim>::size;
		using RawPoint<T, dim>::begin;
		using RawPoint<T, dim>::end;
		using RawPoint<T, dim>::cbegin;
		using RawPoint<T, dim>::cend;

		using iterator = typename RawPoint<T, dim>::iterator;
		using const_iterator = typename RawPoint<T, dim>::const_iterator;
		using value_type = typename RawPoint<T, dim>::value_type;

		static constexpr std::size_t dimensions = dim;
		[[nodiscard]] constexpr const RawPoint<T, dim>& as_array () const noexcept { return *this; }

		constexpr Point() noexcept : RawPoint<T, dim>{} {}
        explicit constexpr Point(const RawPoint<T, dim>& other) noexcept : RawPoint<T, dim>(other) {}

		template<typename... Args>
        requires (sizeof...(Args) == dim) && (std::convertible_to<Args, T> && ...)
        explicit constexpr Point(Args... args) noexcept : RawPoint<T, dim>{static_cast<T>(args)...} {}

		[[nodiscard]] static constexpr Point<T,dim> zeros() noexcept { return Point{}; }
		[[nodiscard]] static constexpr Point<T,dim> ones() noexcept {
			Point result;
			std::fill(result.begin(), result.end(), static_cast<T>(1));
			return result;
		}
	}; // struct Point

	export template<typename First, typename... Rest>
	requires (std::floating_point<First> && ... && std::floating_point<Rest>)
	Point(First, Rest...) -> Point<std::common_type_t<First, Rest...>, 1 + sizeof...(Rest)>;

} // namespace Optimization_Library