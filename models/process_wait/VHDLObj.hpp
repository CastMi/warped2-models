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

#ifndef VHDLOBJ_HPP_DEFINED
#define VHDLOBJ_HPP_DEFINED

#include <memory>
#include <string>
#include <iostream>
#include "warped.hpp"
#include <vector>

enum WaitState {
/* Wait for wakeup event */
WAIT,
/* Go on, no problem here */
OK
};

WARPED_DEFINE_LP_STATE_STRUCT(VHDLState) {
   void resetState() { waitLabel = 0;
   					state_ = OK; }
   WaitState getcurState() const { return state_; }
   					
   unsigned int waitLabel;
   WaitState state_;
};

class VHDLObj : public warped::LogicalProcess {
   public:
      VHDLObj (const std::string& name)
         :   LogicalProcess(name),
         state_()
      {}
      virtual ~VHDLObj() {};

      virtual std::vector<std::shared_ptr<warped::Event> > receiveEvent(const warped::Event&) = 0;
      warped::LPState& getState() override { return this->state_; }
      
   protected:
      VHDLState state_;
};

#endif
