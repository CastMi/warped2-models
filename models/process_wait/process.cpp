/*
 * Copyright (C) 2015 Michele Castellana <michele.castellana@cern.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include <vector>
#include <utility>
#include <cassert>
#include <map>
#include <unordered_set>
#include "VHDLObj.hpp"
#include "process.hpp"
#include "events.hpp"

std::vector<std::shared_ptr<warped::Event> > Process::initializeLP() {
   std::cout << name_ << " initialization" << std::endl;
   std::vector<std::shared_ptr<warped::Event> > response_events;
   return response_events;
}


std::vector<std::shared_ptr<warped::Event> > Process::receiveEvent(const warped::Event& event) {
   const VHDLEvent my_event = static_cast<const VHDLEvent&>(event);
   std::cout << name_ << ": received a message from " << event.sender_name_ << " at time " << std::to_string(event.timestamp()) << ". " << std::endl;
   std::vector<std::shared_ptr<warped::Event> > events;
   switch(my_event.gettype())
   {
      case EVENT_WAIT:
         /* Resume */
         std::cout << name_ << ": it is a resume message. " << std::endl;
         events = executeVHDL( event );
         break;
      case EVENT_SIGNAL:
         /*
          * Signal changed.
          * TODO: Check my status
          */
         std::cout << name_ << ": a signal is changed. " << std::endl;
         events = executeVHDL(event);
         break;
      default:
         /* This should not happen */
         assert(false);
   }
   return events;
}

std::vector<std::shared_ptr<warped::Event> > Process::executeVHDL( const warped::Event& event ) {
   std::vector<std::shared_ptr<warped::Event> > events;
   switch(state_.waitLabel)
   {
      case 0: state_.waitLabel++;
              std::cout << name_ << ": executing 10 something wait. " << std::endl;
              events = executeWait( state_.waitLabel, event.timestamp() + 10 );
              break;
      case 1: state_.waitLabel++;
              std::cout << name_ << ": executing 20 something wait. " << std::endl;
              events = executeWait( state_.waitLabel, event.timestamp() + 20 );
              break;
      case 2: std::cout << name_ << ": finished computation. Resetting state. " << std::endl;
              state_.resetState();
              break;
      default: /* This should not happen */
              assert(false);
              break;
   }
   return events;
}

std::vector<std::shared_ptr<warped::Event> > Process::executeWait( unsigned int waitID, unsigned int howmuch ) {
   std::vector<std::shared_ptr<warped::Event> > events;
   std::cout << name_ << ": sending event to myself at time " << std::to_string(waitID) << " to resume! " << std::endl;
   events.emplace_back(new Wait { name_, howmuch, waitID });
   return events;
}
