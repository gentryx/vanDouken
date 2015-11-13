//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2015 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef VANDOUKEN_SIMULATOR_HPP
#define VANDOUKEN_SIMULATOR_HPP

#include "config.hpp"
#include "cell.hpp"

#include <libgeodecomp/parallelization/hpxsimulator.h>
#include <libgeodecomp/geometry/partitions/recursivebisectionpartition.h>

namespace vandouken {
    typedef
        LibGeoDecomp::HpxSimulator::HpxSimulator<
            Cell,
            LibGeoDecomp::RecursiveBisectionPartition<2>
        >
        Simulator;
}

#endif
