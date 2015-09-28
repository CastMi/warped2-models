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

#ifndef PROCESS_HPP_DEFINED
#define PROCESS_HPP_DEFINED

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_set>
#include <VHDLObj.hpp>

#include "warped.hpp"

/* TODO: manage procedure call */
class Process : public VHDLObj {
   public:
      Process (const std::string& name)
         :   VHDLObj(name)
      {}
      
      virtual std::vector<std::shared_ptr<warped::Event> > initializeLP() override;
      virtual std::vector<std::shared_ptr<warped::Event> > receiveEvent(const warped::Event&);

   protected:

   private:
      std::vector<std::shared_ptr<warped::Event> > executeVHDL( const warped::Event& event );
      std::vector<std::shared_ptr<warped::Event> > executeWait( unsigned int waitID, unsigned int howmuch );
};

#endif
