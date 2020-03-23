// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>


/********************************** COMPONENT *********************************/
#ifndef GRABBER_HH
#define GRABBER_HH

#include "ISensor.hh"
#include "IMotor.hh"
#include "IGrabber.hh"



struct Grabber
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_Grabber_State
#define ENUM_Grabber_State 1


  struct State
  {
    enum type
    {
      initial,grabbing,resetting
    };
  };


#endif // ENUM_Grabber_State

  ::Grabber::State::type state;


  std::function<void ()> out_grabber;

  ::IGrabber grabber;

  ::ISensor presence;
  ::IMotor motor;


  Grabber(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Grabber& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void grabber_grabDisk();
  void presence_detected();
  void motor_finished();
  void motor_error();

};

#endif // GRABBER_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
