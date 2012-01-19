// Copyright (C) 2011,2012 CNRS-LAAS
// Author: Sebastien Dalibard.
//
// This file is part of the hpp-wholebody-step-corba.
//
// hpp-wholebody-step-corba is free software: you can redistribute
// it and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// hpp-wholebody-step-corba is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with hpp-wholebody-step-corba.  If not, see
// <http://www.gnu.org/licenses/>.

#include <cassert>
#include <hpp/wholebody-step-planner/planner.hh>
#include "wholebody_step.impl.hh"

namespace hpp {
  namespace wholeBodyStepPlanner {
    namespace impl {
      WholeBodyStep::WholeBodyStep () : planner_ (0) {}
      void WholeBodyStep::setPlanner (Planner* planner)
      {
	planner_ = planner;
      }
      CORBA::Short WholeBodyStep::generateGoalConfig
      (CORBA::Double x, CORBA::Double y, CORBA::Double z)
      {
	assert (planner_);
	return planner_->generateGoalConfig (x, y, z);
      }
    } // namespace impl
  } // namespace wholeBodyStepPlanner
} // namespace hpp
