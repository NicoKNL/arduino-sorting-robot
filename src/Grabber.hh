#include <dzn/meta.hh>

namespace dzn {
  struct locator;
  struct runtime;
}



#include <iostream>
#include <map>


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
      motor.in.next = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_next();}, this->motor.meta, "next");};
      motor.in.reset = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_reset();}, this->motor.meta, "reset");};


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
    virtual void motor_next () = 0;
    virtual void motor_reset () = 0;

  };
}

#endif // MOTOR_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef GRABBER_HH
#define GRABBER_HH

#include "ISensor.hh"
#include "IMotor.hh"
#include "IGrabber.hh"



struct Grabber
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_Grabber_State
#define ENUM_Grabber_State 1


  struct State
  {
    enum type
    {
      initial,grabbing,resetting
    };
  };


#endif // ENUM_Grabber_State

  ::Grabber::State::type state;


  std::function<void ()> out_grabber;

  ::IGrabber grabber;

  ::ISensor presence;
  ::IMotor motor;


  Grabber(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Grabber& m)  {
    (void)m;
    return os << "[" << m.state <<"]" ;
  }
  private:
  void grabber_grabDisk();
  void presence_detected();
  void motor_finished();
  void motor_error();

};

#endif // GRABBER_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
