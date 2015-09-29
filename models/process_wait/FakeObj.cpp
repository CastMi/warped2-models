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

#include "FakeObj.hpp"
#include <boost/foreach.hpp>
#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include "events.hpp"

std::vector<std::shared_ptr<warped::Event> > FakeObj::initializeLP() {
   std::cout << name_ << " initialization" << std::endl;
   std::vector<std::shared_ptr<warped::Event> > response_events;
   unsigned int i = 0;
   
   BOOST_FOREACH( std::string elem, objects_ ) {
         std::cout << name_ << " sends a message to " << elem << ". It should receive it at time " << std::to_string(i) << ". " << std::endl;
         response_events.emplace_back(new SigEvent { elem, 1, "clk", i++ });
   }
   return response_events;
}

std::vector<std::shared_ptr<warped::Event> > FakeObj::assignSignal( const std::string,
                                                                    const int,
                                                                    const unsigned int,
                                                                    const unsigned int ) {
   std::vector<std::shared_ptr<warped::Event> > response_events;
   return response_events;
}

std::vector<std::shared_ptr<warped::Event> > FakeObj::receiveEvent( const warped::Event& ) {
   /* This object should not receive events*/
   assert(false);
   std::vector<std::shared_ptr<warped::Event> > response_events;
   return response_events;
}
