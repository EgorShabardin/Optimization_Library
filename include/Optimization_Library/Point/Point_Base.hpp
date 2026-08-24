#pragma once

#include <initializer_list>
#include <type_traits>
#include <algorithm>
#include <concepts>
#include <utility>
#include <array>

namespace Optimization_Library {
	template<std::floating_point T = double, size_t dim = 1>
	using RawPoint = std::array<T, dim>;

	template<std::floating_point T = double, size_t dim = 1>
	struct Point : private RawPoint<T, dim> {
	public:
		using RawPoint<T, dim>::RawPoint;
		using RawPoint<T, dim>::operator[];
		using RawPoint<T, dim>::at;
		using RawPoint<T, dim>::data;
		using RawPoint<T, dim>::size;
		using RawPoint<T, dim>::begin;
		using RawPoint<T, dim>::end;
		using RawPoint<T, dim>::cbegin;
		using RawPoint<T, dim>::cend;

		using typename RawPoint<T, dim>::iterator;
		using typename RawPoint<T, dim>::const_iterator;
		using typename RawPoint<T, dim>::value_type;

		constexpr const RawPoint<T, dim>& as_array() const noexcept { return *this; }
        constexpr RawPoint<T, dim>& as_array() noexcept { return *this; }

		constexpr Point() noexcept = default;
		constexpr Point(const Point&) noexcept = default;
		constexpr Point(Point&&) noexcept = default;
		constexpr Point& operator = (const Point&) noexcept = default;
		constexpr Point& operator = (Point&&) noexcept = default;

		constexpr Point(const RawPoint<T, dim>& other) noexcept : RawPoint<T, dim>(other) {}
        constexpr Point(RawPoint<T, dim>&& other) noexcept : RawPoint<T, dim>(std::move(other)) {}

		template<typename... Args>
        requires (sizeof...(Args) == dim) && (std::convertible_to<Args, T> && ...)
        constexpr Point(Args... args) noexcept : RawPoint<T, dim>{static_cast<T>(args)...} {}

		constexpr Point (std::initializer_list<T> values_list) noexcept {
			std::copy_n(values_list.begin(), std::min(values_list.size(), dim), this->begin());
		}

		constexpr explicit Point (T value) noexcept { this->fill(value); }
		static constexpr Point<T, dim> Zeros () noexcept { return Point(T(0)); }
		static constexpr Point<T, dim> Ones () noexcept { return Point(T(1)); }
	}; // struct Point
} // namespace Optimization_Library