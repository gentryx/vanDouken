//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2015 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef VANDOUKEN_GRIDCOLLECTOR_HPP
#define VANDOUKEN_GRIDCOLLECTOR_HPP

#include "config.hpp"
#include "cell.hpp"
#include "particle.hpp"
#include "regionbuffer.hpp"

#include <hpx/runtime/naming/name.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#include <libgeodecomp/io/parallelwriter.h>
#include <libgeodecomp/communication/hpxserialization.h>

namespace vandouken {
    class GridCollector : public LibGeoDecomp::ParallelWriter<Cell>
    {
    public:
        typedef boost::shared_ptr<Particles> BufferType;

        static const int DIM = Topology::DIM;
        using LibGeoDecomp::ParallelWriter<Cell>::GridType;
        typedef LibGeoDecomp::Region<Topology::DIM> RegionType;
        typedef LibGeoDecomp::Coord<Topology::DIM> CoordType;

        typedef
            std::map<
                unsigned,
                RegionBuffer
            >
            BufferMap;

        typedef hpx::lcos::local::spinlock Mutex;
        GridCollector(unsigned period);

        LibGeoDecomp::ParallelWriter<Cell> *clone() const
        {
            return new GridCollector(LibGeoDecomp::ParallelWriter<Cell>::period);
        }

        void stepFinished(
            const GridType& grid,
            const RegionType& validRegion,
            const CoordType& globalDimensions,
            unsigned step,
            LibGeoDecomp::WriterEvent event,
            std::size_t rank,
            bool lastCall);

        std::size_t addGridConsumer();
        void removeGridConsumer(std::size_t);

        std::pair<unsigned, RegionBuffer>
        getNextBuffer(std::size_t id);
    private:
        GridCollector() : 
            LibGeoDecomp::ParallelWriter<Cell>("", 1),
            nextId(0)
        {}

        template<typename ARCHIVE>
        void serialize(ARCHIVE& ar, unsigned)
        {
            ar & hpx::serialization::base_object<LibGeoDecomp::ParallelWriter<Cell> >(*this);
        }

        std::size_t nextId;
        std::set<std::size_t> ids;
        BufferMap buffers;

        hpx::util::high_resolution_timer timer;

        hpx::naming::id_type collectorServerId;
        Mutex mutex;
        Mutex bufferMutex;
    };
}

#endif
