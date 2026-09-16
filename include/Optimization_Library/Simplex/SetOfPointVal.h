#pragma once

#include <concepts>
#include <array>

#include "../PointValue.hpp"

namespace Optimization_Library {
    template<std::floating_point T = double, size_t dim = 1, size_t count = 1>
	using RawSetOfPointsValues = std::array<PointValue<T, dim>, count>;

    template<std::floating_point T = double, size_t dim = 1, size_t count = 1>
    struct SetOfPointsValues : private RawSetOfPointsValues<T, dim, count> {
        using RawSetOfPointsValues<T, dim, count>::RawSetOfPointsValues;
		using RawSetOfPointsValues<T, dim, count>::operator[];
		using RawSetOfPointsValues<T, dim, count>::at;
		using RawSetOfPointsValues<T, dim, count>::data;
		using RawSetOfPointsValues<T, dim, count>::size;
		using RawSetOfPointsValues<T, dim, count>::begin;
		using RawSetOfPointsValues<T, dim, count>::end;
		using RawSetOfPointsValues<T, dim, count>::cbegin;
		using RawSetOfPointsValues<T, dim, count>::cend;

		using typename RawSetOfPointsValues<T, dim, count>::iterator;
		using typename RawSetOfPointsValues<T, dim, count>::const_iterator;
		using typename RawSetOfPointsValues<T, dim, count>::reverse_iterator;
		using typename RawSetOfPointsValues<T, dim, count>::value_type;

        constexpr const RawSetOfPointsValues<T, dim, count>& as_array() const noexcept { return *this; }
        constexpr RawSetOfPointsValues<T, dim, count>& as_array() noexcept { return *this; }

        constexpr SetOfPointsValues() noexcept = default;
		constexpr SetOfPointsValues(const SetOfPointsValues&) noexcept = default;
		constexpr SetOfPointsValues(SetOfPointsValues&&) noexcept = default;
		constexpr SetOfPointsValues& operator = (const SetOfPointsValues&) noexcept = default;
		constexpr SetOfPointsValues& operator = (SetOfPointsValues&&) noexcept = default;

        constexpr SetOfPointsValues(const RawSetOfPointsValues<T, dim, count>& other) noexcept : RawSetOfPointsValues<T, dim, count>(other) {}
        constexpr SetOfPointsValues(RawSetOfPointsValues<T, dim, count>&& other) noexcept : RawSetOfPointsValues<T, dim, count>(std::move(other)) {}

		template<typename... Args>
        requires (sizeof...(Args) == count) && (std::same_as<Args, PointValue<T,dim>> && ...)
        constexpr SetOfPointsValues(Args... args) noexcept : RawSetOfPointsValues<T, dim, count>{args...} {}

		constexpr SetOfPoints(std::initializer_list<Point<T, dim>> values_list) noexcept {
			auto iter = std::copy_n(values_list.begin(), std::min(values_list.size(), count), this->begin());
			if (iter != this->end()) { std::fill(iter, this->end(), Point<T, dim>::Zeros()); }
		}

		constexpr explicit SetOfPoints (T value) noexcept { this->fill(Point<T, dim>(value)); }
		static constexpr SetOfPoints<T, dim, count> Zeros () noexcept { return SetOfPoints(T(0)); }
		static constexpr SetOfPoints<T, dim, count> Ones () noexcept { return SetOfPoints(T(1)); }





   
        SetOfPointVals() = delete;

        template<typename T>
        constexpr SetOfPointsVals (T&& coords, const std::array<double, count>& funcVals) :
            SetOfPoints<PointValT, count> (assign_values<PointValT, count>(std::forward<T>(coords), funcVals)) {}

        template<typename PointT>
        constexpr auto extract_points () const noexcept {
            SetOfPoints<PointT, count> result;

            for(size_t i = 0; i != count; ++i) { result[i] = (*this)[i].point; }
            return result;
        }
    };



    template<std::floating_point T = double, size_t dim = 1, size_t count = 1>
    constexpr SetOfPoints<T, dim, count> assign_values (T&& coords, const std::array<R, count>& FuncVals) noexcept {
        SetOfPoints<PointValT, count> result;

        for(size_t i = 0; i != count; ++i) {
            result[i] = PointValT{std::forward<decltype(coords[0])>(coords[i]), FuncVals[i]};
        }

        return result;
    }

    

    template <typename PointValT, size_t count>     
    class SetOfPointsValsSort : public SetOfPointsVals<PointValT, count> {
    public:
    };
} // namespace Optimization_Library