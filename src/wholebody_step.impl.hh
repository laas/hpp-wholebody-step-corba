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

#ifndef HPP_WHOLEBODY_STEP_CORBA_WHOLEBODY_STEP_HH
# define HPP_WHOLEBODY_STEP_CORBA_WHOLEBODY_STEP_HH

# include <omniORB4/CORBA.h>
# include <hpp/wholebody-step-planner/fwd.hh>

# include "wholebody_step.hh"

namespace hpp {
  namespace wholeBodyStepPlanner {
    namespace impl {
      class WholeBodyStep : public virtual POA_hpp::WholeBodyStep
      {
      public:
	WholeBodyStep ();
	void setPlanner (Planner* planner);
	virtual CORBA::Short
	generateGoalConfig (CORBA::Double x, CORBA::Double y, CORBA::Double z,
			    CORBA::UShort nbConfig);
      private:
	Planner* planner_;
      }; // class WholeBodyStep
    } // namespace impl
  } // namespace wholeBodyStepPlanner
} // namespace hpp

#endif //HPP_WHOLEBODY_STEP_CORBA_WHOLEBODY_STEP_HH
