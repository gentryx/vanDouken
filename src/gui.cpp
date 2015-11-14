//  Copyright (c) 2012-2013 Thomas Heller
//  Copyright (c) 2012-2015 Andreas Schaefer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <libgeodecomp/parallelization/hpxsimulator.h>
#include <libgeodecomp/geometry/partitions/recursivebisectionpartition.h>
#include "gridprovider.hpp"
#include "steeringprovider.hpp"
#include "initializer.hpp"
// #include "startgui.hpp"
// #include "simulator.hpp"
// #include "simulation.hpp"
// #include "simulationcontroller.hpp"

// #include "parameters.hpp"
// #include "cell.hpp"

#include <hpx/hpx_fwd.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>

#include <boost/assign.hpp>

#if !defined(__MIC)
#include <QApplication>
#include <QDialog>
#include "ui_startdialog.h"
#endif

bool standalone = false;

namespace vandouken {
    typedef
        LibGeoDecomp::HpxSimulator::HpxSimulator<
            Cell,
            LibGeoDecomp::RecursiveBisectionPartition<2>
        >
        Simulator;
}

int hpx_main(int argc, char **argv)
{
    std::cout << "ping5\n";
    if(standalone) {
        // vandouken::SimulationController simulation = vandouken::runSimulation();
        // hpx::lcos::future<void> runFuture = simulation.run();
        // simulation.run();

        std::cout << "creating simulation\n";
        LibGeoDecomp::Coord<2> simulationDim(100, 50);
        auto *init = vandouken::createInitializer(simulationDim);

        // vandouken::Simulator simulator(
        //     vandouken::createInitializer(simulationDim),
        //     std::vector<double>(1, 1),
        //     0, // Balancer
        //     1, // Balancing Period
        //     1  //ghostzoneWidth
        //                                );
        std::cout << "simulation created\n";
        // simulator.run();

        std::cout << "simulation started\n";
//         vandouken::GridProvider gridProvider(simulation.numUpdateGroups(), simulation.getInitializer()->gridBox());
//         vandouken::SteeringProvider steererProvider(simulation.numUpdateGroups(), simulation.getInitializer()->gridDimensions());
// #if !defined(__MIC)
//         vandouken::startGUI(boost::program_options::variables_map(), simulation, &gridProvider, &steererProvider, vandouken::MainWindow::control);
// #endif
//         simulation.stop();
//         runFuture.wait();
        return hpx::finalize();
    }
    else {
//         vandouken::SimulationController simulation;
//         vandouken::GridProvider gridProvider(simulation.numUpdateGroups(), simulation.getInitializer()->gridBox());
//         vandouken::SteeringProvider steererProvider(simulation.numUpdateGroups(), simulation.getInitializer()->gridDimensions());
// #if !defined(__MIC)
//         vandouken::startGUI(boost::program_options::variables_map(), simulation, &gridProvider, &steererProvider, vandouken::MainWindow::control);
// #endif
        return hpx::disconnect();
    }
}

int main(int argc, char **argv)
{
    std::cout << "ping1\n";
#if !defined(__MIC)
    QApplication app(argc, argv);
    app.setOverrideCursor(QCursor(Qt::BlankCursor));
#endif
    /*
    QDialog qDialog;
    Ui_Dialog dialog;
    dialog.setupUi(&qDialog);
    dialog.numThreads->setMaximum(hpx::threads::hardware_concurrency());
    if(qDialog.exec() == QDialog::Rejected)
        return -1;

    standalone = dialog.runLocalCheck->isChecked();

    std::string agasHost = dialog.host->displayText().toStdString();
    std::string agasPort = dialog.port->displayText().toStdString();
    std::string numThreads = boost::lexical_cast<std::string>(dialog.numThreads->value());
    std::string overcommitFactor = boost::lexical_cast<std::string>(dialog.overcommitFactor->value());
    */

    std::cout << "ping2\n";
    // boost::program_options::options_description
    //     commandLineParameters("Usage: " HPX_APPLICATION_STRING " [options]");

    /*
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "vandouken.overcommitfactor!=" + overcommitFactor;
    cfg += "hpx.os_threads=" + numThreads;
    */
    standalone = true;
    //if(standalone) 
    {
        std::cout << "ping3\n";
        // vandouken::setupParameters(commandLineParameters, "standalone");
        /*
        cfg += "hpx.agas.port=" + agasPort;
        return hpx::init(commandLineParameters, argc, argv, cfg);
        */

        // We want HPX to run hpx_main() on all localities to avoid the
        // initial overhead caused by broadcasting the work from one to
        // all other localities:
        std::vector<std::string> config(1, "hpx.run_hpx_main!=1");

        std::cout << "ping4\n";
        return hpx::init(argc, argv, config);
    }
    /*
    else {
        vandouken::setupParameters(commandLineParameters, "gui");
        cfg += "hpx.runtime_mode=connect";
        cfg += "hpx.agas.address=" + agasHost;
        return hpx::init(
            commandLineParameters,
            argc,
            argv,
            cfg,
            HPX_STD_FUNCTION<void()>(),
            HPX_STD_FUNCTION<void()>(),
            hpx::runtime_mode_connect);
    }
    */
}
