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
#ifndef IACTUATOR_HH
#define IACTUATOR_HH



struct IActuator
{
#ifndef ENUM_IActuator_State
#define ENUM_IActuator_State 1


  struct State
  {
    enum type
    {
      Withdrawn,Extended
    };
  };


#endif // ENUM_IActuator_State

  struct
  {
    std::function< void(int)> initialise;
    std::function< void()> extend;
    std::function< void()> withdraw;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IActuator(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");
    if (! in.extend) throw dzn::binding_error(meta, "in.extend");
    if (! in.withdraw) throw dzn::binding_error(meta, "in.withdraw");


  }
};

inline void connect (IActuator& provided, IActuator& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IActuator_State
#define ENUM_TO_STRING_IActuator_State 1
inline std::string to_string(::IActuator::State::type v)
{
  switch(v)
  {
    case ::IActuator::State::Withdrawn: return "State_Withdrawn";
    case ::IActuator::State::Extended: return "State_Extended";

  }
  return "";
}
#endif // ENUM_TO_STRING_IActuator_State

#ifndef STRING_TO_ENUM_IActuator_State
#define STRING_TO_ENUM_IActuator_State 1
inline ::IActuator::State::type to_IActuator_State(std::string s)
{
  static std::map<std::string, ::IActuator::State::type> m = {
    {"State_Withdrawn", ::IActuator::State::Withdrawn},
    {"State_Extended", ::IActuator::State::Extended},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IActuator_State


#endif // IACTUATOR_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_ACTUATOR_HH
#define SKEL_ACTUATOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct Actuator
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IActuator actuator;


    Actuator(const dzn::locator& dzn_locator)
    : dzn_meta{"","Actuator",0,0,{},{},{[this]{actuator.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , actuator({{"actuator",this,&dzn_meta},{"",0,0}})


    {
      actuator.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->actuator) = false; return actuator_initialise(pin);}, this->actuator.meta, "initialise");};
      actuator.in.extend = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->actuator) = false; return actuator_extend();}, this->actuator.meta, "extend");};
      actuator.in.withdraw = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->actuator) = false; return actuator_withdraw();}, this->actuator.meta, "withdraw");};


    }
    virtual ~ Actuator() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Actuator& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void actuator_initialise (int pin) = 0;
    virtual void actuator_extend () = 0;
    virtual void actuator_withdraw () = 0;

  };
}

#endif // ACTUATOR_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
