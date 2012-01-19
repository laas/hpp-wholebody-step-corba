# Copyright (c) 2011 CNRS
# Author: Florent Lamiraux
#
# This file is part of hpp-wholebody-step-corba.
# hpp-wholebody-step-corba is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# hpp-wholebody-step-corba is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# hpp-wholebody-step-corba.  If not, see
# <http://www.gnu.org/licenses/>.

from omniORB import CORBA
import CosNaming

from hpp import WholeBodyStep

class CorbaError(Exception):
    """
    Raised when a CORBA error occurs.
    """
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class Client:
  """
  Connect and create clients for hpp-wholebody-step-planner library.
  """
  def __init__(self):
    """
    Initialize CORBA and create default clients.
    """
    import sys
    self.orb = CORBA.ORB_init (sys.argv, CORBA.ORB_ID)
    obj = self.orb.resolve_initial_references("NameService")
    self.rootContext = obj._narrow(CosNaming.NamingContext)
    if self.rootContext is None:
        raise CorbaError ('failed to narrow the root context')

    name = [CosNaming.NameComponent ("hpp", "plannerContext"),
            CosNaming.NameComponent ("hpp", "wholeBodyStep")]
    
    try:
        obj = self.rootContext.resolve (name)
    except CosNaming.NamingContext.NotFound, ex:
        raise CorbaError ('failed to find wholeBodyStep service.')
    try:
        client = obj._narrow (WholeBodyStep)
    except KeyError:
        raise CorbaError ('invalid service name wholebodyStep')

    if client is None:
      # This happens when stubs from client and server are not synchronized.
        raise CorbaError (
            'failed to narrow client for service wholebodyStep')
    self.problem = client
