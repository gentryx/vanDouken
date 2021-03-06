//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2013 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef VANDOUKEN_PARTICLESTEERER_HPP
#define VANDOUKEN_PARTICLESTEERER_HPP

#include "cell.hpp"

#include <hpx/runtime/naming/name.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#include <libgeodecomp/io/steerer.h>

#include <boost/serialization/list.hpp>

namespace vandouken {
    struct ParticleSteerer
        : LibGeoDecomp::Steerer<Cell>
    {
        typedef
            hpx::util::function<void(
                GridType *,
                const LibGeoDecomp::Region<2>&,
                const CoordType&,
                unsigned step)
            >
            SteererFunctor;

        ParticleSteerer()
          : LibGeoDecomp::Steerer<Cell>(1)
        {}

        LibGeoDecomp::Steerer<Cell> *clone()
        {
            return new ParticleSteerer();
        }

        void nextStep(
            GridType *grid,
            const LibGeoDecomp::Region<2>& validRegion,
            const CoordType& globalDimensions,
            unsigned step,
            LibGeoDecomp::SteererEvent,
            std::size_t rank,
            bool lastCall,
            SteererFeedback *feedback);

        void steer(const SteererFunctor& f);

        template <typename ARCHIVE>
        void serialize(ARCHIVE& ar, unsigned)
        {
            ar & boost::serialization::base_object<LibGeoDecomp::Steerer<Cell> >(*this);
            ar & steererServerId;
            ar & steererFunctors;
            ar & updatedRegion;
        }

        hpx::naming::id_type steererServerId;
        typedef hpx::lcos::local::spinlock Mutex;

        Mutex mutex;
        typedef std::list<std::pair<bool, SteererFunctor> > SteererFunctors;
        SteererFunctors steererFunctors;

        LibGeoDecomp::Region<2> updatedRegion;
    };
}

#endif
