#pragma once

#include <concepts>

/*
   * Optimization_Library - Point Module
   *
   * A collective header file for working with N-dimensional points.
   * It includes the basic structure, mathematical operations, and essential utilities.
*/


#include "Point/Point_Base.hpp"           // The main Point Structure
#include "Point/Operators_Base.hpp"       // The functors
#include "Point/Point_Operators.hpp"      // Mathematical operators
#include "Point/Point_Utils.hpp"          // Basic utilities

namespace Optimization_Library {
    template<std::floating_point T = double>
    using Point2D = Point<T, 2>;

    template<std::floating_point T = double>
    using Point3D = Point<T, 3>;
}