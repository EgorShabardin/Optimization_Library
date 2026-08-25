#pragma once

#include <concepts>

/*
   * Optimization_Library - PointValue Module
   *
   * A collective header file for working with N-dimensional Point with its objective function value.
   * It includes the basic structure and essential utilities.
*/

#include "PointValue/PointValue_Base.hpp"       // Core structure
#include "PointValue/PointValue_Utils.hpp"      // Basic utilities

namespace Optimization_Library {
    template<std::floating_point T = double>
    using PointValue1D = PointValue<T, 1>;
    using PointValue1D_d = PointValue1D<double>;

    template<std::floating_point T = double>
    using PointValue2D = PointValue<T, 2>;
    using PointValue2D_d = PointValue2D<double>;

    template<std::floating_point T = double>
    using PointValue3D = PointValue<T, 3>;
    using PointValue3D_d = PointValue3D<double>;
} // namespace Optimization_Library