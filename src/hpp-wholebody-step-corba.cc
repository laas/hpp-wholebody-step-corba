// Copyright (C) 2013 CNRS-LAAS
// Author: Florent Lamiraux
//
// This file is part of the hpp-wholebody-step-corba.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#include <iostream>
#include <KineoModel/kppLicense.h>

#include <hpp/util/debug.hh>

#include <hpp/wholebody-step-planner/planner.hh>
#include <hpp/corbaserver/wholebody-step/server.hh>
#include <hpp/corbaserver/server.hh>

using hpp::wholeBodyStepPlanner::Planner;
typedef hpp::wholeBodyStepPlanner::Server WholeBodyServer;
typedef hpp::corbaServer::Server CorbaServer;

int
main (int argc, char* argv[])
{
  if (!CkppLicense::initialize ())
    hppDoutFatal (error, "failed to get a Kineo license");

  double samplingPeriod = 0.05;
  Planner* wbsPlanner = new Planner (samplingPeriod);
  wbsPlanner->setFootPrintLimits(-0.2,0.2,-0.25,-0.13,-M_PI /4,0.1);

  CorbaServer corbaServer (wbsPlanner, argc, (const char**) argv, true);
  WholeBodyServer wbsServer (argc, argv, true);
  wbsServer.setPlanner (wbsPlanner);

  try {
    corbaServer.startCorbaServer ();
    hppDout (info, "successfully start hpp-corbaserver");
  } catch (const std::exception& exc) {
    hppDout (error, "Faile to start hpp-corbaserver");
  }
  try {
    wbsServer.startCorbaServer ("hpp", "plannerContext",
				"hpp", "wholeBodyStep");

    hppDout (info, "Successfully started corba server for whole body planner");
  } catch (const std::exception& exc) {
    hppDout (error, "failed to start corba server for whole body planner");
  }
  corbaServer.processRequest(true);
}
