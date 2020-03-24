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
    std::function< void()> initialise;
  } in;

  struct
  {
    std::function< void()> detected;
  } out;

  dzn::port::meta meta;
  inline ISensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");

    if (! out.detected) throw dzn::binding_error(meta, "out.detected");

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


//version: 2.9.1
