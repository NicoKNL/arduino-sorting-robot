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
#ifndef IMASTER_HH
#define IMASTER_HH



struct IMaster
{
#ifndef ENUM_IMaster_State
#define ENUM_IMaster_State 1


  struct State
  {
    enum type
    {
      Off,Idle,Waiting,Error,IngestingDisk,Sorting
    };
  };


#endif // ENUM_IMaster_State

  struct
  {
    std::function< void()> start;
    std::function< void()> stop;
    std::function< void()> emergency;
    std::function< void()> forceWait;
    std::function< void()> cancelWait;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IMaster(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.start) throw dzn::binding_error(meta, "in.start");
    if (! in.stop) throw dzn::binding_error(meta, "in.stop");
    if (! in.emergency) throw dzn::binding_error(meta, "in.emergency");
    if (! in.forceWait) throw dzn::binding_error(meta, "in.forceWait");
    if (! in.cancelWait) throw dzn::binding_error(meta, "in.cancelWait");


  }
};

inline void connect (IMaster& provided, IMaster& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IMaster_State
#define ENUM_TO_STRING_IMaster_State 1
inline std::string to_string(::IMaster::State::type v)
{
  switch(v)
  {
    case ::IMaster::State::Off: return "State_Off";
    case ::IMaster::State::Idle: return "State_Idle";
    case ::IMaster::State::Waiting: return "State_Waiting";
    case ::IMaster::State::Error: return "State_Error";
    case ::IMaster::State::IngestingDisk: return "State_IngestingDisk";
    case ::IMaster::State::Sorting: return "State_Sorting";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMaster_State

#ifndef STRING_TO_ENUM_IMaster_State
#define STRING_TO_ENUM_IMaster_State 1
inline ::IMaster::State::type to_IMaster_State(std::string s)
{
  static std::map<std::string, ::IMaster::State::type> m = {
    {"State_Off", ::IMaster::State::Off},
    {"State_Idle", ::IMaster::State::Idle},
    {"State_Waiting", ::IMaster::State::Waiting},
    {"State_Error", ::IMaster::State::Error},
    {"State_IngestingDisk", ::IMaster::State::IngestingDisk},
    {"State_Sorting", ::IMaster::State::Sorting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMaster_State


#endif // IMASTER_HH

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
/********************************** COMPONENT *********************************/
#ifndef MASTER_HH
#define MASTER_HH

#include "IIngest.hh"
#include "ISensor.hh"
#include "ISortingSystem.hh"



struct Master
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_Master_State
#define ENUM_Master_State 1


  struct State
  {
    enum type
    {
      Off,Idle,Waiting,Error,IngestingDisk,Sorting
    };
  };


#endif // ENUM_Master_State

  ::Master::State::type state;
  bool waitNext;


  std::function<void ()> out_master;

  ::IMaster master;

  ::IIngest ingest;
  ::ISensor factoryFloorSensor;
  ::ISortingSystem sortingSystem;


  Master(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Master& m)  {
    (void)m;
    return os << "[" << m.state <<", " << m.waitNext <<"]" ;
  }
  private:
  void master_start();
  void master_stop();
  void master_emergency();
  void master_forceWait();
  void master_cancelWait();
  void ingest_finished();
  void factoryFloorSensor_high();
  void sortingSystem_finished();

};

#endif // MASTER_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef SORTINGROBOTSYSTEM_HH
#define SORTINGROBOTSYSTEM_HH


#include <dzn/locator.hh>

#include "Sensor.hh"
#include "IIngest.hh"
#include "Motor.hh"
#include "Sensor.hh"
#include "Timer.hh"
#include "Sensor.hh"
#include "Sensor.hh"
#include "ISortingSystem.hh"
#include "ColourSensor.hh"
#include "Actuator.hh"
#include "Actuator.hh"
#include "Motor.hh"
#include "Timer.hh"



struct SortingRobotSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::Master m;
  ::Sensor factorFloorSensor;
  ::Ingester i;
  ::Motor wheelMotor;
  ::Sensor wheelStopSensor;
  ::Timer ingestTimer;
  ::Sensor beltSensorWhite;
  ::Sensor beltSensorBlack;
  ::SortingSystem sortingSystem;
  ::ColourSensor cs;
  ::Actuator whiteActuator;
  ::Actuator blackActuator;
  ::Motor beltMotor;
  ::Timer sortingTimer;

  ::IMaster& master;


  SortingRobotSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // SORTINGROBOTSYSTEM_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.9.1
