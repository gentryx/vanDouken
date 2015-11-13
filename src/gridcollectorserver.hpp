//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2015 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef VANDOUKEN_GRIDCOLLECTORSERVER_HPP
#define VANDOUKEN_GRIDCOLLECTORSERVER_HPP

#include "config.hpp"
#include "particle.hpp"
#include "regionbuffer.hpp"

#include <libgeodecomp/storage/grid.h>
#include <libgeodecomp/geometry/region.h>

#include <hpx/include/components.hpp>

namespace vandouken
{
    class GridCollector;

    class GridCollectorServer :
        public hpx::components::managed_component_base<GridCollectorServer>
    {
    public:
        GridCollectorServer()
        {
            BOOST_ASSERT(false);
        }

        typedef
            hpx::components::server::create_component_action<
                vandouken::GridCollectorServer
            , std::ptrdiff_t
            >
            CreateAction;

        typedef
            hpx::components::server::create_component_action<
                vandouken::GridCollectorServer
              , std::ptrdiff_t const
            >
            ConstCreateAction;

        GridCollectorServer(std::ptrdiff_t collector) :
            collector(reinterpret_cast<GridCollector*>(collector))
        {}

        std::size_t addGridConsumer();
        HPX_DEFINE_COMPONENT_ACTION(GridCollectorServer, addGridConsumer, AddGridConsumerAction);
        void removeGridConsumer(std::size_t);
        HPX_DEFINE_COMPONENT_ACTION(GridCollectorServer, removeGridConsumer, RemoveGridConsumerAction);

        typedef std::pair<unsigned, RegionBuffer> PairType;

        PairType
        getNextBuffer(std::size_t id);
        HPX_DEFINE_COMPONENT_ACTION(GridCollectorServer, getNextBuffer, GetNextBufferAction);

    private:
        GridCollector *collector;
    };
}

HPX_REGISTER_BASE_LCO_WITH_VALUE_DECLARATION(
    vandouken::GridCollectorServer::PairType
  , GridCollectorServerPairType
)

HPX_REGISTER_ACTION_DECLARATION(
    vandouken::GridCollectorServer::CreateAction
  , vandoukenGridCollectorServerCreateAction)

HPX_REGISTER_ACTION_DECLARATION(
    vandouken::GridCollectorServer::ConstCreateAction
  , vandoukenGridCollectorServerConstCreateAction)

HPX_REGISTER_ACTION_DECLARATION(
    vandouken::GridCollectorServer::AddGridConsumerAction,
    vandoukenGridCollectorServerAddGridConsumerAction)

HPX_REGISTER_ACTION_DECLARATION(
    vandouken::GridCollectorServer::RemoveGridConsumerAction,
    vandoukenGridCollectorServerRemoveGridConsumerAction)

HPX_REGISTER_ACTION_DECLARATION(
    vandouken::GridCollectorServer::GetNextBufferAction,
    vandoukenGridCollectorServerGetNextBufferAction)

#endif
