#pragma once
#include "PointVals/Point/Point.h"
#include "PointVals/PointVal.h"
#include "SetOfPoints.h"
#include "SetOfPointVal.h"

namespace OptLib
{
    template<size_t dim>
    using SimplexValNoSort = SetOfPointsVal<dim + 1, PointVal<dim>>;
  
    template<size_t dim>
    using Simplex = SetOfPoints <dim + 1, Point<dim>>;

    template <size_t dim>
    using SimplexVal = S.O.P. <dim + 1, PointVal<dim>>;

    template <size_t dim>
    using SimplexValSort = S.O.P.V.S.<dim + 1, PointVal<dim>>;
}