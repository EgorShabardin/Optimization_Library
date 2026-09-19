module;

#include <concepts>

/*
   * Optimization_Library - PointValue Module
   *
   * A collective header file for working with N-dimensional Point with its objective function value.
   * It includes the basic structure and essential utilities.
*/

export module PointValue;

export import :PointValue_Base;      // Core structure
export import :PointValue_Utils;     // Basic utilities

export namespace Optimization_Library {

    template<std::floating_point T = double>
    using PointValue1D = PointValue<T, 1>;
    using PointValue1D_d = PointValue1D<double>;
    using PointValue1D_f = PointValue1D<float>;

    template<std::floating_point T = double>
    using PointValue2D = PointValue<T, 2>;
    using PointValue2D_d = PointValue2D<double>;
    using PointValue2D_f = PointValue2D<float>;

    template<std::floating_point T = double>
    using PointValue3D = PointValue<T, 3>;
    using PointValue3D_d = PointValue3D<double>;
    using PointValue3D_f = PointValue3D<float>;

} // namespace Optimization_Library