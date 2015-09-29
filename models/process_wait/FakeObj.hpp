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

#ifndef FAKEOBJ_HPP_DEFINED
#define FAKEOBJ_HPP_DEFINED

#include "VHDLObj.hpp"
#include "warped.hpp"
#include <string>
#include <memory>
#include <vector>
#include <utility>

/*
 * This is a fake object that should simulate
 * an architecture that sends a message to all the processes
 */
class FakeObj : public VHDLObj {
   public:
      FakeObj (const std::string& name)
              : VHDLObj(name)
      {}
      
      virtual std::vector<std::shared_ptr<warped::Event> > initializeLP() override;
      virtual std::vector<std::shared_ptr<warped::Event> > receiveEvent(const warped::Event&) override;
      void addObj( std::string name ) { objects_.emplace_back(name); }
      
   protected:
      virtual std::vector<std::shared_ptr<warped::Event> > assignSignal( const std::string,
                                                                         const int,
                                                                         const unsigned int,
                                                                         const unsigned int ) override;

      std::vector<std::string> objects_;
};

#endif
