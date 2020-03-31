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
#ifndef ISENSOR_HH
#define ISENSOR_HH



struct ISensor
{
#ifndef ENUM_ISensor_State
#define ENUM_ISensor_State 1


  struct State
  {
    enum type
    {
      Unknown,Low,High
    };
  };


#endif // ENUM_ISensor_State

  struct
  {
    std::function< void(int)> initialise;
  } in;

  struct
  {
    std::function< void()> high;
    std::function< void()> low;
  } out;

  dzn::port::meta meta;
  inline ISensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");

    if (! out.high) throw dzn::binding_error(meta, "out.high");
    if (! out.low) throw dzn::binding_error(meta, "out.low");

  }
};

inline void connect (ISensor& provided, ISensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_ISensor_State
#define ENUM_TO_STRING_ISensor_State 1
inline std::string to_string(::ISensor::State::type v)
{
  switch(v)
  {
    case ::ISensor::State::Unknown: return "State_Unknown";
    case ::ISensor::State::Low: return "State_Low";
    case ::ISensor::State::High: return "State_High";

  }
  return "";
}
#endif // ENUM_TO_STRING_ISensor_State

#ifndef STRING_TO_ENUM_ISensor_State
#define STRING_TO_ENUM_ISensor_State 1
inline ::ISensor::State::type to_ISensor_State(std::string s)
{
  static std::map<std::string, ::ISensor::State::type> m = {
    {"State_Unknown", ::ISensor::State::Unknown},
    {"State_Low", ::ISensor::State::Low},
    {"State_High", ::ISensor::State::High},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_ISensor_State


#endif // ISENSOR_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_SENSOR_HH
#define SKEL_SENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct Sensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor factoryFloorSensor;


    Sensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","Sensor",0,0,{},{},{[this]{factoryFloorSensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , factoryFloorSensor({{"factoryFloorSensor",this,&dzn_meta},{"",0,0}})


    {
      factoryFloorSensor.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->factoryFloorSensor) = false; return factoryFloorSensor_initialise(pin);}, this->factoryFloorSensor.meta, "initialise");};


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
    virtual void factoryFloorSensor_initialise (int pin) = 0;

  };
}

#endif // SENSOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_WHITESENSOR_HH
#define SKEL_WHITESENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct whiteSensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor beltWhiteSensor;


    whiteSensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","whiteSensor",0,0,{},{},{[this]{beltWhiteSensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , beltWhiteSensor({{"beltWhiteSensor",this,&dzn_meta},{"",0,0}})


    {
      beltWhiteSensor.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltWhiteSensor) = false; return beltWhiteSensor_initialise(pin);}, this->beltWhiteSensor.meta, "initialise");};


    }
    virtual ~ whiteSensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const whiteSensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void beltWhiteSensor_initialise (int pin) = 0;

  };
}

#endif // WHITESENSOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_BLACKSENSOR_HH
#define SKEL_BLACKSENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct blackSensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISensor beltBlackSensor;


    blackSensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","blackSensor",0,0,{},{},{[this]{beltBlackSensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , beltBlackSensor({{"beltBlackSensor",this,&dzn_meta},{"",0,0}})


    {
      beltBlackSensor.in.initialise = [&](int pin){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltBlackSensor) = false; return beltBlackSensor_initialise(pin);}, this->beltBlackSensor.meta, "initialise");};


    }
    virtual ~ blackSensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const blackSensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void beltBlackSensor_initialise (int pin) = 0;

  };
}

#endif // BLACKSENSOR_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
