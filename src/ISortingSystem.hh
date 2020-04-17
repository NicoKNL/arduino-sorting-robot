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
#ifndef ISORTINGSYSTEM_HH
#define ISORTINGSYSTEM_HH



struct ISortingSystem
{
#ifndef ENUM_ISortingSystem_State
#define ENUM_ISortingSystem_State 1


  struct State
  {
    enum type
    {
      Idle,AwaitColourScan,SortWhite,SortBlack,SortOther
    };
  };


#endif // ENUM_ISortingSystem_State

  struct
  {
    std::function< void()> reset;
    std::function< void()> startSorting;
    std::function< void()> emergency;
  } in;

  struct
  {
    std::function< void()> finished;
  } out;

  dzn::port::meta meta;
  inline ISortingSystem(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.reset) throw dzn::binding_error(meta, "in.reset");
    if (! in.startSorting) throw dzn::binding_error(meta, "in.startSorting");
    if (! in.emergency) throw dzn::binding_error(meta, "in.emergency");

    if (! out.finished) throw dzn::binding_error(meta, "out.finished");

  }
};

inline void connect (ISortingSystem& provided, ISortingSystem& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_ISortingSystem_State
#define ENUM_TO_STRING_ISortingSystem_State 1
inline std::string to_string(::ISortingSystem::State::type v)
{
  switch(v)
  {
    case ::ISortingSystem::State::Idle: return "State_Idle";
    case ::ISortingSystem::State::AwaitColourScan: return "State_AwaitColourScan";
    case ::ISortingSystem::State::SortWhite: return "State_SortWhite";
    case ::ISortingSystem::State::SortBlack: return "State_SortBlack";
    case ::ISortingSystem::State::SortOther: return "State_SortOther";

  }
  return "";
}
#endif // ENUM_TO_STRING_ISortingSystem_State

#ifndef STRING_TO_ENUM_ISortingSystem_State
#define STRING_TO_ENUM_ISortingSystem_State 1
inline ::ISortingSystem::State::type to_ISortingSystem_State(std::string s)
{
  static std::map<std::string, ::ISortingSystem::State::type> m = {
    {"State_Idle", ::ISortingSystem::State::Idle},
    {"State_AwaitColourScan", ::ISortingSystem::State::AwaitColourScan},
    {"State_SortWhite", ::ISortingSystem::State::SortWhite},
    {"State_SortBlack", ::ISortingSystem::State::SortBlack},
    {"State_SortOther", ::ISortingSystem::State::SortOther},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_ISortingSystem_State


#endif // ISORTINGSYSTEM_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_TIMER_HH
#define SKEL_TIMER_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ITimer.hh"



namespace skel {
  struct Timer
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ITimer timer;


    Timer(const dzn::locator& dzn_locator)
    : dzn_meta{"","Timer",0,0,{},{},{[this]{timer.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , timer({{"timer",this,&dzn_meta},{"",0,0}})


    {
      timer.in.start = [&](long milliseconds){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->timer) = false; return timer_start(milliseconds);}, this->timer.meta, "start");};
      timer.in.cancel = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->timer) = false; return timer_cancel();}, this->timer.meta, "cancel");};


    }
    virtual ~ Timer() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Timer& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void timer_start (long milliseconds) = 0;
    virtual void timer_cancel () = 0;

  };
}

#endif // TIMER_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_COLOURSENSOR_HH
#define SKEL_COLOURSENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IColourSensor.hh"



namespace skel {
  struct ColourSensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IColourSensor colourSensor;


    ColourSensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","ColourSensor",0,0,{},{},{[this]{colourSensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , colourSensor({{"colourSensor",this,&dzn_meta},{"",0,0}})


    {
      colourSensor.in.initialise = [&](int pinA,int pinB){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->colourSensor) = false; return colourSensor_initialise(pinA,pinB);}, this->colourSensor.meta, "initialise");};


    }
    virtual ~ ColourSensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const ColourSensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void colourSensor_initialise (int pinA,int pinB) = 0;

  };
}

#endif // COLOURSENSOR_HH

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
      sensor.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensor) = false; return sensor_initialise(pin);}, this->sensor.meta, "initialise");};


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
    virtual void sensor_initialise (int pin) = 0;

  };
}

#endif // SENSOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_ACTUATOR_HH
#define SKEL_ACTUATOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IActuator.hh"



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
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_MOTOR_HH
#define SKEL_MOTOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IMotor.hh"



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
/********************************** COMPONENT *********************************/
#ifndef SORTINGSYSTEM_HH
#define SORTINGSYSTEM_HH

#include "IColourSensor.hh"
#include "ISensor.hh"
#include "ISensor.hh"
#include "IActuator.hh"
#include "IActuator.hh"
#include "IMotor.hh"
#include "ITimer.hh"



struct SortingSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;

  ::ISortingSystem::State::type state;
  long delay;


  std::function<void ()> out_sortingSystem;

  ::ISortingSystem sortingSystem;

  ::IColourSensor colourSensor;
  ::ISensor beltSensorWhite;
  ::ISensor beltSensorBlack;
  ::IActuator whiteActuator;
  ::IActuator blackActuator;
  ::IMotor beltMotor;
  ::ITimer timer;


  SortingSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const SortingSystem& m)  {
    (void)m;
    return os << "[" << m.state <<", " << m.delay <<"]" ;
  }
  private:
  void sortingSystem_reset();
  void sortingSystem_startSorting();
  void sortingSystem_emergency();
  void colourSensor_detectedWhite();
  void colourSensor_detectedBlack();
  void colourSensor_detectedUnknown();
  void beltSensorWhite_high();
  void beltSensorBlack_high();
  void timer_timeout();

};

#endif // SORTINGSYSTEM_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
