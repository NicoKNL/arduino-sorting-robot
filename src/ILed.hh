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
#ifndef ILED_HH
#define ILED_HH



struct ILed
{
#ifndef ENUM_ILed_State
#define ENUM_ILed_State 1


  struct State
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_ILed_State

  struct
  {
    std::function< void()> turnOn;
    std::function< void()> turnOff;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline ILed(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");


  }
};

inline void connect (ILed& provided, ILed& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_ILed_State
#define ENUM_TO_STRING_ILed_State 1
inline std::string to_string(::ILed::State::type v)
{
  switch(v)
  {
    case ::ILed::State::On: return "State_On";
    case ::ILed::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_ILed_State

#ifndef STRING_TO_ENUM_ILed_State
#define STRING_TO_ENUM_ILed_State 1
inline ::ILed::State::type to_ILed_State(std::string s)
{
  static std::map<std::string, ::ILed::State::type> m = {
    {"State_On", ::ILed::State::On},
    {"State_Off", ::ILed::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_ILed_State


#endif // ILED_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LED_HH
#define SKEL_LED_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct Led
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ILed led;


    Led(const dzn::locator& dzn_locator)
    : dzn_meta{"","Led",0,0,{},{},{[this]{led.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , led({{"led",this,&dzn_meta},{"",0,0}})


    {
      led.in.turnOn = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->led) = false; return led_turnOn();}, this->led.meta, "turnOn");};
      led.in.turnOff = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->led) = false; return led_turnOff();}, this->led.meta, "turnOff");};


    }
    virtual ~ Led() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Led& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void led_turnOn () = 0;
    virtual void led_turnOff () = 0;

  };
}

#endif // LED_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
