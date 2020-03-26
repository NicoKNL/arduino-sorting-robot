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
#ifndef IINTERNALBELTCONTROL_HH
#define IINTERNALBELTCONTROL_HH



struct iInternalBeltControl
{
#ifndef ENUM_iInternalBeltControl_State
#define ENUM_iInternalBeltControl_State 1


  struct State
  {
    enum type
    {
      Black,White,End,Unknown
    };
  };


#endif // ENUM_iInternalBeltControl_State

  struct
  {
    std::function< void()> initialise;
    std::function< void()> toStackBlack;
    std::function< void()> toStackWhite;
    std::function< void()> toEnd;
  } in;

  struct
  {
    std::function< void()> atBlack;
    std::function< void()> atWhite;
    std::function< void()> atEnd;
  } out;

  dzn::port::meta meta;
  inline iInternalBeltControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");
    if (! in.toStackBlack) throw dzn::binding_error(meta, "in.toStackBlack");
    if (! in.toStackWhite) throw dzn::binding_error(meta, "in.toStackWhite");
    if (! in.toEnd) throw dzn::binding_error(meta, "in.toEnd");

    if (! out.atBlack) throw dzn::binding_error(meta, "out.atBlack");
    if (! out.atWhite) throw dzn::binding_error(meta, "out.atWhite");
    if (! out.atEnd) throw dzn::binding_error(meta, "out.atEnd");

  }
};

inline void connect (iInternalBeltControl& provided, iInternalBeltControl& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iInternalBeltControl_State
#define ENUM_TO_STRING_iInternalBeltControl_State 1
inline std::string to_string(::iInternalBeltControl::State::type v)
{
  switch(v)
  {
    case ::iInternalBeltControl::State::Black: return "State_Black";
    case ::iInternalBeltControl::State::White: return "State_White";
    case ::iInternalBeltControl::State::End: return "State_End";
    case ::iInternalBeltControl::State::Unknown: return "State_Unknown";

  }
  return "";
}
#endif // ENUM_TO_STRING_iInternalBeltControl_State

#ifndef STRING_TO_ENUM_iInternalBeltControl_State
#define STRING_TO_ENUM_iInternalBeltControl_State 1
inline ::iInternalBeltControl::State::type to_iInternalBeltControl_State(std::string s)
{
  static std::map<std::string, ::iInternalBeltControl::State::type> m = {
    {"State_Black", ::iInternalBeltControl::State::Black},
    {"State_White", ::iInternalBeltControl::State::White},
    {"State_End", ::iInternalBeltControl::State::End},
    {"State_Unknown", ::iInternalBeltControl::State::Unknown},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iInternalBeltControl_State


#endif // IINTERNALBELTCONTROL_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_MOTORCONTROL_HH
#define SKEL_MOTORCONTROL_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IMotorControl.hh"



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
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_SENSOR_HH
#define SKEL_SENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ISensor.hh"



namespace skel {
  struct Sensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor sensor;


    Sensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","Sensor",0,0,{},{},{[this]{sensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , sensor({{"sensor",this,&dzn_meta},{"",0,0}})


    {
      sensor.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensor) = false; return sensor_initialise();}, this->sensor.meta, "initialise");};


    }
    virtual ~ Sensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Sensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void sensor_initialise () = 0;

  };
}

#endif // SENSOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_PRESSENSORBLACKSTACK_HH
#define SKEL_PRESSENSORBLACKSTACK_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ISensor.hh"



namespace skel {
  struct PresSensorBlackStack
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor sensorBlack;


    PresSensorBlackStack(const dzn::locator& dzn_locator)
    : dzn_meta{"","PresSensorBlackStack",0,0,{},{},{[this]{sensorBlack.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , sensorBlack({{"sensorBlack",this,&dzn_meta},{"",0,0}})


    {
      sensorBlack.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensorBlack) = false; return sensorBlack_initialise();}, this->sensorBlack.meta, "initialise");};


    }
    virtual ~ PresSensorBlackStack() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const PresSensorBlackStack& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void sensorBlack_initialise () = 0;

  };
}

#endif // PRESSENSORBLACKSTACK_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_PRESSENSORWHITESTACK_HH
#define SKEL_PRESSENSORWHITESTACK_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ISensor.hh"



namespace skel {
  struct PresSensorWhiteStack
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor sensorWhite;


    PresSensorWhiteStack(const dzn::locator& dzn_locator)
    : dzn_meta{"","PresSensorWhiteStack",0,0,{},{},{[this]{sensorWhite.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , sensorWhite({{"sensorWhite",this,&dzn_meta},{"",0,0}})


    {
      sensorWhite.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensorWhite) = false; return sensorWhite_initialise();}, this->sensorWhite.meta, "initialise");};


    }
    virtual ~ PresSensorWhiteStack() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const PresSensorWhiteStack& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void sensorWhite_initialise () = 0;

  };
}

#endif // PRESSENSORWHITESTACK_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef INTERNALBELTCONTROL_HH
#define INTERNALBELTCONTROL_HH

#include "IMotorControl.hh"
#include "ISensor.hh"
#include "ISensor.hh"



struct InternalBeltControl
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_InternalBeltControl_Goal
#define ENUM_InternalBeltControl_Goal 1


  struct Goal
  {
    enum type
    {
      Black,White,End,None
    };
  };


#endif // ENUM_InternalBeltControl_Goal
#ifndef ENUM_InternalBeltControl_State
#define ENUM_InternalBeltControl_State 1


  struct State
  {
    enum type
    {
      NotReady,Ready
    };
  };


#endif // ENUM_InternalBeltControl_State

  ::InternalBeltControl::Goal::type goal;
  ::InternalBeltControl::State::type state;


  std::function<void ()> out_beltControl;

  ::iInternalBeltControl beltControl;

  ::IMotorControl motorControl;
  ::ISensor presSensorBlackStack;
  ::ISensor presSensorWhiteStack;


  InternalBeltControl(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const InternalBeltControl& m)  {
    (void)m;
    return os << "[" << m.goal <<", " << m.state <<"]" ;
  }
  private:
  void beltControl_initialise();
  void beltControl_toStackBlack();
  void beltControl_toStackWhite();
  void beltControl_toEnd();
  void presSensorBlackStack_detected();
  void presSensorWhiteStack_detected();

};

#endif // INTERNALBELTCONTROL_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
