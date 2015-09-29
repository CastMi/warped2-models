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

#include <vector>
#include <memory>

#include "warped.hpp"
#include "FakeObj.hpp"
#include "process.hpp"
#include "VHDLObj.hpp"
#include "events.hpp"
#include "tclap/ValueArg.h"

#define NUMPROC 4

int main(int argc, const char** argv) {
   std::vector<TCLAP::Arg*> args;
   warped::Simulation my_sim ("Process Simulation", argc, argv);

   std::vector<Process> processes;
   std::vector<FakeObj> fakeobjs;

   fakeobjs.emplace_back(std::string("FakeObj"));

   for (unsigned int i = 0; i < NUMPROC; i++) {
      processes.emplace_back(i);
   }

   std::vector<warped::LogicalProcess*> object_pointers;
   
   for (Process& o : processes) {
      fakeobjs.front().addObj(o.name_);
      object_pointers.push_back(&o);
   }
   for (FakeObj& o : fakeobjs) {
      object_pointers.push_back(&o);
   }
   my_sim.simulate(object_pointers);
   
   return 0;
}

