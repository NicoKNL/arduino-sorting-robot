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
#ifndef ICOM_HH
#define ICOM_HH



struct ICom
{

  struct
  {
    std::function< void()> grab;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline ICom(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.grab) throw dzn::binding_error(meta, "in.grab");


  }
};

inline void connect (ICom& provided, ICom& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ICOM_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef ICONTROLLER_HH
#define ICONTROLLER_HH



struct IController
{

  struct
  {
    std::function< void()> init;
    std::function< void()> shutDown;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IController(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.init) throw dzn::binding_error(meta, "in.init");
    if (! in.shutDown) throw dzn::binding_error(meta, "in.shutDown");


  }
};

inline void connect (IController& provided, IController& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ICONTROLLER_HH

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
    ::ILed iLed;


    Led(const dzn::locator& dzn_locator)
    : dzn_meta{"","Led",0,0,{},{},{[this]{iLed.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , iLed({{"iLed",this,&dzn_meta},{"",0,0}})


    {
      iLed.in.turnOn = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iLed) = false; return iLed_turnOn();}, this->iLed.meta, "turnOn");};
      iLed.in.turnOff = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iLed) = false; return iLed_turnOff();}, this->iLed.meta, "turnOff");};


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
    virtual void iLed_turnOn () = 0;
    virtual void iLed_turnOff () = 0;

  };
}

#endif // LED_HH

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
#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "Console.hh"
#include "IInternalBeltControl.hh"



struct Controller
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;
#ifndef ENUM_Controller_Power
#define ENUM_Controller_Power 1


  struct Power
  {
    enum type
    {
      On,Off
    };
  };


#endif // ENUM_Controller_Power
#ifndef ENUM_Controller_Intake
#define ENUM_Controller_Intake 1


  struct Intake
  {
    enum type
    {
      Yes,No
    };
  };


#endif // ENUM_Controller_Intake

  ::Controller::Power::type power;
  ::Controller::Intake::type state;


  std::function<void ()> out_com;
  std::function<void ()> out_i;

  ::ICom com;
  ::IController i;

  ::IReporter reporter;
  ::iInternalBeltControl belt;


  Controller(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os) const;
  friend std::ostream& operator << (std::ostream& os, const Controller& m)  {
    (void)m;
    return os << "[" << m.power <<", " << m.state <<"]" ;
  }
  private:
  void com_grab();
  void i_init();
  void i_shutDown();
  void belt_atBlack();
  void belt_atWhite();
  void belt_atEnd();

};

#endif // CONTROLLER_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef INTERNALBELT_HH
#define INTERNALBELT_HH


#include <dzn/locator.hh>

#include "IInternalBeltControl.hh"
#include "MotorControl.hh"
#include "PresSensorWhiteStack.hh"
#include "PresSensorBlackStack.hh"



struct InternalBelt
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::InternalBeltControl beltControl;
  ::MotorControl m;
  ::PresSensorWhiteStack sW;
  ::PresSensorBlackStack sB;

  ::iInternalBeltControl& iBeltControl;


  InternalBelt(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // INTERNALBELT_HH

/***********************************  SYSTEM  ***********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef SORTINGROBOT_HH
#define SORTINGROBOT_HH


#include <dzn/locator.hh>

#include "Console.hh"



struct SortingRobot
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::InternalBelt belt;
  ::Reporter reporter;
  ::Controller controller;

  ::IController& i;
  ::ICom& com;


  SortingRobot(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // SORTINGROBOT_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.9.1
