module;

#include <concepts>

export module Point;

/*
   * Optimization_Library - Point Module
   *
   * A collective header file for working with N-dimensional points.
   * It includes the basic structure, mathematical operations, and essential utilities.
*/


export import :Point_Base;           // Core structure
import :Operators_Base;              // Internal functors
export import :Point_Operators;      // Mathematical operators
export import :Point_Utils;          // Basic utilities

export namespace Optimization_Library {

    template<std::floating_point T = double>
    using Point1D = Point<T, 1>;
    using Point1D_d = Point1D<double>;
    using Point1D_f = Point1D<float>;

    template<std::floating_point T = double>
    using Point2D = Point<T, 2>;
    using Point2D_d = Point2D<double>;
    using Point2D_f = Point2D<float>;

    template<std::floating_point T = double>
    using Point3D = Point<T, 3>;
    using Point3D_d = Point3D<double>;
    using Point3D_f = Point3D<float>;

} // namespace Optimization_Library