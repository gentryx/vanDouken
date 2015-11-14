//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2013 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "simulationcontroller.hpp"
#include "simulationcontrollerserver.hpp"

#include <hpx/runtime/components/new.hpp>

#include "log.hpp"

namespace vandouken {
    SimulationController::SimulationController()
    {
        // while(thisId == hpx::naming::invalid_id)
        // {
        //     hpx::naming::id_type id;
        //     hpx::agas::resolve_name_sync(VANDOUKEN_SIMULATION_CONTROLLER_NAME, id);
        //     if(!id)
        //     {
        //         hpx::this_thread::suspend(boost::posix_time::seconds(1));
        //         continue;
        //     }
        //     hpx::naming::gid_type gid = id.get_gid();
        //     hpx::naming::detail::strip_credits_from_gid(gid);
        //     thisId = hpx::id_type(gid, hpx::id_type::unmanaged);
        // }
        // MSG("resolved " << VANDOUKEN_SIMULATION_CONTROLLER_NAME << "\n");
    }

    SimulationController::SimulationController(const LibGeoDecomp::Coord<2>& simulationDim)
    {
        // thisId = hpx::components::new_<ComponentType>(hpx::find_here(), simulationDim).get();
        // hpx::agas::register_name_sync(VANDOUKEN_SIMULATION_CONTROLLER_NAME, thisId);
    }

    SimulationController::~SimulationController()
    {
        // thisId = hpx::naming::invalid_id;
    }

    boost::shared_ptr<LibGeoDecomp::Initializer<Cell> > SimulationController::getInitializer() const
    {
        // return ComponentType::GetInitializerAction()(thisId);
    }

// hpx::lcos::future<void>
void
SimulationController::run() const
    {
        // return hpx::async<ComponentType::RunAction>(thisId);
    }

    void SimulationController::stop() const
    {
        // ComponentType::StopAction()(thisId);
    }

    std::size_t SimulationController::numUpdateGroups() const
    {
        return 0;
        // return ComponentType::NumUpdateGroupsAction()(thisId);
    }
}
