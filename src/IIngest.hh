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
#ifndef IINGEST_HH
#define IINGEST_HH



struct IIngest
{
#ifndef ENUM_IIngest_State
#define ENUM_IIngest_State 1


  struct State
  {
    enum type
    {
      Idle,Monitoring,Ingesting
    };
  };


#endif // ENUM_IIngest_State

  struct
  {
    std::function< void()> reset;
    std::function< void()> startIngest;
  } in;

  struct
  {
    std::function< void()> finished;
  } out;

  dzn::port::meta meta;
  inline IIngest(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.reset) throw dzn::binding_error(meta, "in.reset");
    if (! in.startIngest) throw dzn::binding_error(meta, "in.startIngest");

    if (! out.finished) throw dzn::binding_error(meta, "out.finished");

  }
};

inline void connect (IIngest& provided, IIngest& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IIngest_State
#define ENUM_TO_STRING_IIngest_State 1
inline std::string to_string(::IIngest::State::type v)
{
  switch(v)
  {
    case ::IIngest::State::Idle: return "State_Idle";
    case ::IIngest::State::Monitoring: return "State_Monitoring";
    case ::IIngest::State::Ingesting: return "State_Ingesting";

  }
  return "";
}
#endif // ENUM_TO_STRING_IIngest_State

#ifndef STRING_TO_ENUM_IIngest_State
#define STRING_TO_ENUM_IIngest_State 1
inline ::IIngest::State::type to_IIngest_State(std::string s)
{
  static std::map<std::string, ::IIngest::State::type> m = {
    {"State_Idle", ::IIngest::State::Idle},
    {"State_Monitoring", ::IIngest::State::Monitoring},
    {"State_Ingesting", ::IIngest::State::Ingesting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IIngest_State


#endif // IINGEST_HH

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
/********************************** COMPONENT *********************************/
#ifndef INGESTER_HH
#define INGESTER_HH

#include "IMotor.hh"
#include "ISensor.hh"
#include "ITimer.hh"



struct Ingester
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;

  ::IIngest::State::type state;
  long delay;


  std::function<void ()> out_ingest;

  ::IIngest ingest;

  ::IMotor wheelMotor;
  ::ISensor wheelStopSensor;
  ::ITimer timer;


  Ingester(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Ingester& m)  {
    (void)m;
    return os << "[" << m.state <<", " << m.delay <<"]" ;
  }
  private:
  void ingest_reset();
  void ingest_startIngest();
  void wheelStopSensor_high();
  void timer_timeout();

};

#endif // INGESTER_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
