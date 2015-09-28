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

#ifndef EVENTS_HPP_DEFINED
#define EVENTS_HPP_DEFINED

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <unordered_set>

#include "warped.hpp"

enum EventType {
/* Wakeup */
EVENT_WAIT,
/* Signal changed */
EVENT_SIGNAL
};

class VHDLEvent : public warped::Event {
   public:
      VHDLEvent() = default;
      VHDLEvent(const std::string& receiver_name,
                const unsigned int timestamp,
                EventType type)
             : receiver_name_(receiver_name),
               ts_(timestamp),
               type_(type)
      {}

      const std::string& receiverName() const { return receiver_name_; }
      unsigned int timestamp() const { return ts_; }
      EventType gettype() const { return type_; }
      
   private:
      std::string receiver_name_;
      unsigned int ts_;
      EventType type_;
};

/* Wakeup event */
class Wait : public VHDLEvent {
   public:
      Wait() = default;
      Wait(const std::string& receiver_name,
           const unsigned int timestamp,
           unsigned int wait)
        : VHDLEvent(receiver_name, timestamp, EVENT_WAIT),
           waitID_(wait)
      {}

      unsigned int waitid() const { return waitID_; }
      
      unsigned int waitID_;
};

class SigEvent : public VHDLEvent {
   public:
      SigEvent() = default;
      SigEvent(const std::string& receiver_name, int signal,
               const unsigned int timestamp)
            : VHDLEvent(receiver_name, timestamp, EVENT_SIGNAL),
              value_(signal)
      {}
   
private:
      int value_;
};

#endif
