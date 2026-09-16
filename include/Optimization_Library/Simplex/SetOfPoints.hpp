#pragma once

#include <initializer_list>
#include <algorithm>
#include <concepts>
#include <utility>
#include <array>

#include "../Point.hpp"

namespace Optimization_Library {
	template<std::floating_point T = double, size_t dim = 1, size_t count = 1>
	using RawSetOfPoints = std::array<Point<T, dim>, count>;

	template<std::floating_point T = double, size_t dim = 1, size_t count = 1>
	struct SetOfPoints : private RawSetOfPoints<T, dim, count> {
		using RawSetOfPoints<T, dim, count>::RawSetOfPoints;
		using RawSetOfPoints<T, dim, count>::operator[];
		using RawSetOfPoints<T, dim, count>::at;
		using RawSetOfPoints<T, dim, count>::data;
		using RawSetOfPoints<T, dim, count>::size;
		using RawSetOfPoints<T, dim, count>::begin;
		using RawSetOfPoints<T, dim, count>::end;
		using RawSetOfPoints<T, dim, count>::cbegin;
		using RawSetOfPoints<T, dim, count>::cend;

		using typename RawSetOfPoints<T, dim, count>::iterator;
		using typename RawSetOfPoints<T, dim, count>::const_iterator;
		using typename RawSetOfPoints<T, dim, count>::reverse_iterator;
		using typename RawSetOfPoints<T, dim, count>::value_type;

		constexpr const RawSetOfPoints<T, dim, count>& as_array() const noexcept { return *this; }
        constexpr RawSetOfPoints<T, dim, count>& as_array() noexcept { return *this; }

		constexpr SetOfPoints() noexcept = default;
		constexpr SetOfPoints(const SetOfPoints&) noexcept = default;
		constexpr SetOfPoints(SetOfPoints&&) noexcept = default;
		constexpr SetOfPoints& operator = (const SetOfPoints&) noexcept = default;
		constexpr SetOfPoints& operator = (SetOfPoints&&) noexcept = default;

		constexpr SetOfPoints(const RawSetOfPoints<T, dim, count>& other) noexcept : RawSetOfPoints<T, dim, count>(other) {}
        constexpr SetOfPoints(RawSetOfPoints<T, dim, count>&& other) noexcept : RawSetOfPoints<T, dim, count>(std::move(other)) {}

		template<typename... Args>
        requires (sizeof...(Args) == count) && (std::same_as<Args, Point<T,dim>> && ...)
        constexpr SetOfPoints(Args... args) noexcept : RawSetOfPoints<T, dim, count>{args...} {}

		constexpr SetOfPoints(std::initializer_list<Point<T, dim>> values_list) noexcept {
			auto iter = std::copy_n(values_list.begin(), std::min(values_list.size(), count), this->begin());
			if (iter != this->end()) { std::fill(iter, this->end(), Point<T, dim>::Zeros()); }
		}

		constexpr explicit SetOfPoints (T value) noexcept { this->fill(Point<T, dim>(value)); }
		static constexpr SetOfPoints<T, dim, count> Zeros () noexcept { return SetOfPoints(T(0)); }
		static constexpr SetOfPoints<T, dim, count> Ones () noexcept { return SetOfPoints(T(1)); }
	}; // struct SetOfPoints
} // namespace Optimization_Library