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
#ifndef IGRABBER_HH
#define IGRABBER_HH



struct IGrabber
{
#ifndef ENUM_IGrabber_State
#define ENUM_IGrabber_State 1


  struct State
  {
    enum type
    {
      initial,grabbing,resetting
    };
  };


#endif // ENUM_IGrabber_State

  struct
  {
    std::function< void()> grabDisk;
  } in;

  struct
  {
    std::function< void()> finished;
    std::function< void()> error;
  } out;

  dzn::port::meta meta;
  inline IGrabber(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.grabDisk) throw dzn::binding_error(meta, "in.grabDisk");

    if (! out.finished) throw dzn::binding_error(meta, "out.finished");
    if (! out.error) throw dzn::binding_error(meta, "out.error");

  }
};

inline void connect (IGrabber& provided, IGrabber& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IGrabber_State
#define ENUM_TO_STRING_IGrabber_State 1
inline std::string to_string(::IGrabber::State::type v)
{
  switch(v)
  {
    case ::IGrabber::State::initial: return "State_initial";
    case ::IGrabber::State::grabbing: return "State_grabbing";
    case ::IGrabber::State::resetting: return "State_resetting";

  }
  return "";
}
#endif // ENUM_TO_STRING_IGrabber_State

#ifndef STRING_TO_ENUM_IGrabber_State
#define STRING_TO_ENUM_IGrabber_State 1
inline ::IGrabber::State::type to_IGrabber_State(std::string s)
{
  static std::map<std::string, ::IGrabber::State::type> m = {
    {"State_initial", ::IGrabber::State::initial},
    {"State_grabbing", ::IGrabber::State::grabbing},
    {"State_resetting", ::IGrabber::State::resetting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IGrabber_State


#endif // IGRABBER_HH

/********************************** INTERFACE *********************************/


//version: 2.9.1
