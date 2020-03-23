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


/********************************** INTERFACE *********************************/
#ifndef IMOTOR_HH
#define IMOTOR_HH



struct IMotor
{
#ifndef ENUM_IMotor_State
#define ENUM_IMotor_State 1


  struct State
  {
    enum type
    {
      initial,moving,resetting
    };
  };


#endif // ENUM_IMotor_State

  struct
  {
    std::function< void()> next;
    std::function< void()> reset;
  } in;

  struct
  {
    std::function< void()> finished;
    std::function< void()> error;
  } out;

  dzn::port::meta meta;
  inline IMotor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.next) throw dzn::binding_error(meta, "in.next");
    if (! in.reset) throw dzn::binding_error(meta, "in.reset");

    if (! out.finished) throw dzn::binding_error(meta, "out.finished");
    if (! out.error) throw dzn::binding_error(meta, "out.error");

  }
};

inline void connect (IMotor& provided, IMotor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IMotor_State
#define ENUM_TO_STRING_IMotor_State 1
inline std::string to_string(::IMotor::State::type v)
{
  switch(v)
  {
    case ::IMotor::State::initial: return "State_initial";
    case ::IMotor::State::moving: return "State_moving";
    case ::IMotor::State::resetting: return "State_resetting";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMotor_State

#ifndef STRING_TO_ENUM_IMotor_State
#define STRING_TO_ENUM_IMotor_State 1
inline ::IMotor::State::type to_IMotor_State(std::string s)
{
  static std::map<std::string, ::IMotor::State::type> m = {
    {"State_initial", ::IMotor::State::initial},
    {"State_moving", ::IMotor::State::moving},
    {"State_resetting", ::IMotor::State::resetting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMotor_State


#endif // IMOTOR_HH

/********************************** INTERFACE *********************************/


//version: 2.9.1
