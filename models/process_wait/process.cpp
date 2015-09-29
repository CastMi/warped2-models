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


std::vector<std::shared_ptr<warped::Event> > Process::receiveEvent( const warped::Event& event ) {
   const VHDLEvent my_event = static_cast<const VHDLEvent&>(event);
   std::cout << name_ << ": received a message from " << event.sender_name_ <<
   " at time " << std::to_string(event.timestamp()) << ". " << std::endl;
   std::vector<std::shared_ptr<warped::Event> > events;
   switch(my_event.gettype())
   {
      case EVENT_WAIT:
         /* Resume */
         std::cout << name_ << ": it is a resume message. " << std::endl;
         events = executeVHDL( event );
         break;
      case EVENT_SIGNAL:
         {
            std::cout << name_ << ": it is a signal changed message. " << std::endl;
            const SigEvent sign_event = static_cast<const SigEvent&>(event);
            // Is the signal in my sensitivity list?
            if(sens_list_.find(sign_event.SignalName()) != sens_list_.end())
            {
               std::cout << name_ << ": the signal " << sign_event.SignalName() <<
               " has new the new value of " << std::to_string(sign_event.Value()) <<
               ". " << std::endl;
               events = executeVHDL( event );
            } else {
               std::cout << name_ << ": the signal " << sign_event.SignalName() <<
               " is not in my sensitivity list. " << std::endl;
               assignSignal( sign_event.SignalName(), sign_event.Value(), 0, sign_event.timestamp() );
            }
            break;
         }
      default:
         /* This should not happen */
         assert(false);
   }
   return events;
}

std::vector<std::shared_ptr<warped::Event> > Process::executeVHDL( const warped::Event& event ) {
   std::vector<std::shared_ptr<warped::Event> > events;
   std::vector<std::shared_ptr<warped::Event> > temp;
   switch(state_.waitLabel)
   {
      case 0: state_.waitLabel++;
              std::cout << name_ << ": executing 10 something wait. " << std::endl;
              // try to assign a signal immediately.
              temp = assignSignal("signame", 1, 0, event.timestamp());
              events.insert(events.end(), temp.begin(), temp.end());
              // go to sleep
              temp = executeWait( state_.waitLabel, event.timestamp() + 10 );
              events.insert(events.end(), temp.begin(), temp.end());
              break;
      case 1: state_.waitLabel++;
              // try to assign a signal with a delay of 5.
              temp = assignSignal("signame", 1, 5, event.timestamp());
              events.insert(events.end(), temp.begin(), temp.end());
              // go to sleep
              std::cout << name_ << ": executing 20 something wait. " << std::endl;
              temp = executeWait( state_.waitLabel, event.timestamp() + 20 );
              events.insert(events.end(), temp.begin(), temp.end());
              break;
      case 2: std::cout << name_ << ": finished computation of the process. Resetting state. "
      << std::endl;
              state_.resetState();
              break;
      default: /* This should not happen */
              assert(false);
              break;
   }
   return events;
}

std::vector<std::shared_ptr<warped::Event> > Process::assignSignal( const std::string name,
                                                                    const int value,
                                                                    const unsigned int delay,
                                                                    const unsigned int timestamp ) {
   std::vector<std::shared_ptr<warped::Event> > events;
   if (delay == 0) {
      std::cout << name_ << ": assigning the signal without sending a message. " << std::endl;
   } else {
      std::cout << name_ << ": sending a message to assign a signal with a delay of " << std::to_string(delay) << ". " << std::endl;
      events.emplace_back(new SigEvent { name_, value, name, timestamp + delay });
   }
   return events;
}

std::vector<std::shared_ptr<warped::Event> > Process::executeWait( unsigned int waitID, unsigned int howmuch ) {
   std::vector<std::shared_ptr<warped::Event> > events;
   std::cout << name_ << ": sending event to myself at time " << std::to_string(howmuch) << " to resume! " << std::endl;
   events.emplace_back(new Wait { name_, howmuch, waitID });
   return events;
}
