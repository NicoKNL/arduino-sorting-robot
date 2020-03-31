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
      On,Off
    };
  };


#endif // ENUM_IMotor_State

  struct
  {
    std::function< void(int)> initialise;
    std::function< void()> turnOn;
    std::function< void()> turnOff;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IMotor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");
    if (! in.turnOn) throw dzn::binding_error(meta, "in.turnOn");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");


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
    case ::IMotor::State::On: return "State_On";
    case ::IMotor::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMotor_State

#ifndef STRING_TO_ENUM_IMotor_State
#define STRING_TO_ENUM_IMotor_State 1
inline ::IMotor::State::type to_IMotor_State(std::string s)
{
  static std::map<std::string, ::IMotor::State::type> m = {
    {"State_On", ::IMotor::State::On},
    {"State_Off", ::IMotor::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMotor_State


#endif // IMOTOR_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_MOTOR_HH
#define SKEL_MOTOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct Motor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IMotor motor;


    Motor(const dzn::locator& dzn_locator)
    : dzn_meta{"","Motor",0,0,{},{},{[this]{motor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , motor({{"motor",this,&dzn_meta},{"",0,0}})


    {
      motor.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_initialise(pin);}, this->motor.meta, "initialise");};
      motor.in.turnOn = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_turnOn();}, this->motor.meta, "turnOn");};
      motor.in.turnOff = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_turnOff();}, this->motor.meta, "turnOff");};


    }
    virtual ~ Motor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Motor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void motor_initialise (int pin) = 0;
    virtual void motor_turnOn () = 0;
    virtual void motor_turnOff () = 0;

  };
}

#endif // MOTOR_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
