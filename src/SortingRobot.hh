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
      On,Off
    };
  };


#endif // ENUM_IMaster_State

  struct
  {
    std::function< void()> start;
    std::function< void()> stop;
    std::function< void()> emergency;
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
    case ::IMaster::State::On: return "State_On";
    case ::IMaster::State::Off: return "State_Off";

  }
  return "";
}
#endif // ENUM_TO_STRING_IMaster_State

#ifndef STRING_TO_ENUM_IMaster_State
#define STRING_TO_ENUM_IMaster_State 1
inline ::IMaster::State::type to_IMaster_State(std::string s)
{
  static std::map<std::string, ::IMaster::State::type> m = {
    {"State_On", ::IMaster::State::On},
    {"State_Off", ::IMaster::State::Off},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IMaster_State


#endif // IMASTER_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_LED_HH
#define SKEL_LED_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "ILed.hh"



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
#ifndef MASTER_HH
#define MASTER_HH

#include "ISensor.hh"
#include "ILed.hh"



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
      On,Off
    };
  };


#endif // ENUM_Master_State

  ::Master::State::type state;


  std::function<void ()> out_master;

  ::IMaster master;

  ::ISensor sensor;
  ::ILed led;


  Master(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Master& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void master_start();
  void master_stop();
  void master_emergency();
  void sensor_high();
  void sensor_low();

};

#endif // MASTER_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef SORTINGROBOTSYSTEM_HH
#define SORTINGROBOTSYSTEM_HH


#include <dzn/locator.hh>

#include "Led.hh"
#include "Sensor.hh"



struct SortingRobotSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::Master m;
  ::Led led;
  ::Sensor sensor;

  ::IMaster& master;


  SortingRobotSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // SORTINGROBOTSYSTEM_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.9.1
