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
#ifndef ISENSOR_HH
#define ISENSOR_HH



struct ISensor
{
#ifndef ENUM_ISensor_State
#define ENUM_ISensor_State 1


  struct State
  {
    enum type
    {
      Unknown,Low,High
    };
  };


#endif // ENUM_ISensor_State

  struct
  {
    std::function< void()> initialise;
  } in;

  struct
  {
    std::function< void()> detected;
  } out;

  dzn::port::meta meta;
  inline ISensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");

    if (! out.detected) throw dzn::binding_error(meta, "out.detected");

  }
};

inline void connect (ISensor& provided, ISensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_ISensor_State
#define ENUM_TO_STRING_ISensor_State 1
inline std::string to_string(::ISensor::State::type v)
{
  switch(v)
  {
    case ::ISensor::State::Unknown: return "State_Unknown";
    case ::ISensor::State::Low: return "State_Low";
    case ::ISensor::State::High: return "State_High";

  }
  return "";
}
#endif // ENUM_TO_STRING_ISensor_State

#ifndef STRING_TO_ENUM_ISensor_State
#define STRING_TO_ENUM_ISensor_State 1
inline ::ISensor::State::type to_ISensor_State(std::string s)
{
  static std::map<std::string, ::ISensor::State::type> m = {
    {"State_Unknown", ::ISensor::State::Unknown},
    {"State_Low", ::ISensor::State::Low},
    {"State_High", ::ISensor::State::High},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_ISensor_State


#endif // ISENSOR_HH

/********************************** INTERFACE *********************************/


//version: 2.9.1
