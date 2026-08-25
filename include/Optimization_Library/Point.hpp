#pragma once

#include <concepts>

/*
   * Optimization_Library - Point Module
   *
   * A collective header file for working with N-dimensional points.
   * It includes the basic structure, mathematical operations, and essential utilities.
*/


#include "Point/Point_Base.hpp"           // Core structure
#include "Point/Operators_Base.hpp"       // Internal functors
#include "Point/Point_Operators.hpp"      // Mathematical operators
#include "Point/Point_Utils.hpp"          // Basic utilities

namespace Optimization_Library {
    template<std::floating_point T = double>
    using Point1D = Point<T, 1>;
    using Point1D_d = Point1D<double>;

    template<std::floating_point T = double>
    using Point2D = Point<T, 2>;
    using Point2D_d = Point2D<double>;

    template<std::floating_point T = double>
    using Point3D = Point<T, 3>;
    using Point3D_d = Point3D<double>;
} // namespace Optimization_Library