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
#ifndef IMOTORCONTROL_HH
#define IMOTORCONTROL_HH



struct IMotorControl
{
#ifndef ENUM_IMotorControl_State
#define ENUM_IMotorControl_State 1


  struct State
  {
    enum type
    {
      NotReady,Ready
    };
  };


#endif // ENUM_IMotorControl_State
#ifndef ENUM_IMotorControl_Direction
#define ENUM_IMotorControl_Direction 1


  struct Direction
  {
    enum type
    {
      Forwards,Backwards,Neutral
    };
  };


#endif // ENUM_IMotorControl_Direction

  struct
  {
    std::function< void()> initialise;
    std::function< void()> goForward;
    std::function< void()> goBackward;
    std::function< void()> stop;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IMotorControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");
    if (! in.goForward) throw dzn::binding_error(meta, "in.goForward");
    if (! in.goBackward) throw dzn::binding_error(meta, "in.goBackward");
    if (! in.stop) throw dzn::binding_error(meta, "in.stop");


  }
};

inline void connect (IMotorControl& provided, IMotorControl& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IMotorControl_State
#define ENUM_TO_STRING_IMotorControl_State 1
inline std::string to_string(::IMotorControl::State::type v)
{
  switch(v)
  {
    case ::IMotorControl::State::NotReady: return "State_NotReady";
    case ::IMotorControl::State::Ready: return "State_Ready";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMotorControl_State
#ifndef ENUM_TO_STRING_IMotorControl_Direction
#define ENUM_TO_STRING_IMotorControl_Direction 1
inline std::string to_string(::IMotorControl::Direction::type v)
{
  switch(v)
  {
    case ::IMotorControl::Direction::Forwards: return "Direction_Forwards";
    case ::IMotorControl::Direction::Backwards: return "Direction_Backwards";
    case ::IMotorControl::Direction::Neutral: return "Direction_Neutral";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMotorControl_Direction

#ifndef STRING_TO_ENUM_IMotorControl_State
#define STRING_TO_ENUM_IMotorControl_State 1
inline ::IMotorControl::State::type to_IMotorControl_State(std::string s)
{
  static std::map<std::string, ::IMotorControl::State::type> m = {
    {"State_NotReady", ::IMotorControl::State::NotReady},
    {"State_Ready", ::IMotorControl::State::Ready},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMotorControl_State
#ifndef STRING_TO_ENUM_IMotorControl_Direction
#define STRING_TO_ENUM_IMotorControl_Direction 1
inline ::IMotorControl::Direction::type to_IMotorControl_Direction(std::string s)
{
  static std::map<std::string, ::IMotorControl::Direction::type> m = {
    {"Direction_Forwards", ::IMotorControl::Direction::Forwards},
    {"Direction_Backwards", ::IMotorControl::Direction::Backwards},
    {"Direction_Neutral", ::IMotorControl::Direction::Neutral},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMotorControl_Direction


#endif // IMOTORCONTROL_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_MOTORCONTROL_HH
#define SKEL_MOTORCONTROL_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct MotorControl
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IMotorControl motorControl;


    MotorControl(const dzn::locator& dzn_locator)
    : dzn_meta{"","MotorControl",0,0,{},{},{[this]{motorControl.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , motorControl({{"motorControl",this,&dzn_meta},{"",0,0}})


    {
      motorControl.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motorControl) = false; return motorControl_initialise();}, this->motorControl.meta, "initialise");};
      motorControl.in.goForward = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motorControl) = false; return motorControl_goForward();}, this->motorControl.meta, "goForward");};
      motorControl.in.goBackward = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motorControl) = false; return motorControl_goBackward();}, this->motorControl.meta, "goBackward");};
      motorControl.in.stop = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motorControl) = false; return motorControl_stop();}, this->motorControl.meta, "stop");};


    }
    virtual ~ MotorControl() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const MotorControl& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void motorControl_initialise () = 0;
    virtual void motorControl_goForward () = 0;
    virtual void motorControl_goBackward () = 0;
    virtual void motorControl_stop () = 0;

  };
}

#endif // MOTORCONTROL_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
