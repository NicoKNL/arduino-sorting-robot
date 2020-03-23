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
/********************************** INTERFACE *********************************/
#ifndef ISENSOR_HH
#define ISENSOR_HH



struct iSensor
{
#ifndef ENUM_iSensor_State
#define ENUM_iSensor_State 1


  struct State
  {
    enum type
    {
      Unknown,Low,High
    };
  };


#endif // ENUM_iSensor_State

  struct
  {
    std::function< void()> initialise;
  } in;

  struct
  {
    std::function< void()> detected;
  } out;

  dzn::port::meta meta;
  inline iSensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");

    if (! out.detected) throw dzn::binding_error(meta, "out.detected");

  }
};

inline void connect (iSensor& provided, iSensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iSensor_State
#define ENUM_TO_STRING_iSensor_State 1
inline std::string to_string(::iSensor::State::type v)
{
  switch(v)
  {
    case ::iSensor::State::Unknown: return "State_Unknown";
    case ::iSensor::State::Low: return "State_Low";
    case ::iSensor::State::High: return "State_High";

  }
  return "";
}
#endif // ENUM_TO_STRING_iSensor_State

#ifndef STRING_TO_ENUM_iSensor_State
#define STRING_TO_ENUM_iSensor_State 1
inline ::iSensor::State::type to_iSensor_State(std::string s)
{
  static std::map<std::string, ::iSensor::State::type> m = {
    {"State_Unknown", ::iSensor::State::Unknown},
    {"State_Low", ::iSensor::State::Low},
    {"State_High", ::iSensor::State::High},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iSensor_State


#endif // ISENSOR_HH

/********************************** INTERFACE *********************************/
/********************************** INTERFACE *********************************/
#ifndef IMOTORCONTROL_HH
#define IMOTORCONTROL_HH



struct iMotorControl
{
#ifndef ENUM_iMotorControl_State
#define ENUM_iMotorControl_State 1


  struct State
  {
    enum type
    {
      NotReady,Ready
    };
  };


#endif // ENUM_iMotorControl_State
#ifndef ENUM_iMotorControl_Direction
#define ENUM_iMotorControl_Direction 1


  struct Direction
  {
    enum type
    {
      Forwards,Backwards,Neutral
    };
  };


#endif // ENUM_iMotorControl_Direction

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
  inline iMotorControl(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");
    if (! in.goForward) throw dzn::binding_error(meta, "in.goForward");
    if (! in.goBackward) throw dzn::binding_error(meta, "in.goBackward");
    if (! in.stop) throw dzn::binding_error(meta, "in.stop");


  }
};

inline void connect (iMotorControl& provided, iMotorControl& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_iMotorControl_State
#define ENUM_TO_STRING_iMotorControl_State 1
inline std::string to_string(::iMotorControl::State::type v)
{
  switch(v)
  {
    case ::iMotorControl::State::NotReady: return "State_NotReady";
    case ::iMotorControl::State::Ready: return "State_Ready";

  }
  return "";
}
#endif // ENUM_TO_STRING_iMotorControl_State
#ifndef ENUM_TO_STRING_iMotorControl_Direction
#define ENUM_TO_STRING_iMotorControl_Direction 1
inline std::string to_string(::iMotorControl::Direction::type v)
{
  switch(v)
  {
    case ::iMotorControl::Direction::Forwards: return "Direction_Forwards";
    case ::iMotorControl::Direction::Backwards: return "Direction_Backwards";
    case ::iMotorControl::Direction::Neutral: return "Direction_Neutral";

  }
  return "";
}
#endif // ENUM_TO_STRING_iMotorControl_Direction

#ifndef STRING_TO_ENUM_iMotorControl_State
#define STRING_TO_ENUM_iMotorControl_State 1
inline ::iMotorControl::State::type to_iMotorControl_State(std::string s)
{
  static std::map<std::string, ::iMotorControl::State::type> m = {
    {"State_NotReady", ::iMotorControl::State::NotReady},
    {"State_Ready", ::iMotorControl::State::Ready},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iMotorControl_State
#ifndef STRING_TO_ENUM_iMotorControl_Direction
#define STRING_TO_ENUM_iMotorControl_Direction 1
inline ::iMotorControl::Direction::type to_iMotorControl_Direction(std::string s)
{
  static std::map<std::string, ::iMotorControl::Direction::type> m = {
    {"Direction_Forwards", ::iMotorControl::Direction::Forwards},
    {"Direction_Backwards", ::iMotorControl::Direction::Backwards},
    {"Direction_Neutral", ::iMotorControl::Direction::Neutral},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_iMotorControl_Direction


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
    ::iMotorControl motorControl;


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
    ::iSensor sensorBlack;


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
    ::iSensor sensorWhite;


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
#ifndef SKEL_SENSOREND_HH
#define SKEL_SENSOREND_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct SensorEnd
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::iSensor sensorEnd;


    SensorEnd(const dzn::locator& dzn_locator)
    : dzn_meta{"","SensorEnd",0,0,{},{},{[this]{sensorEnd.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , sensorEnd({{"sensorEnd",this,&dzn_meta},{"",0,0}})


    {
      sensorEnd.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensorEnd) = false; return sensorEnd_initialise();}, this->sensorEnd.meta, "initialise");};


    }
    virtual ~ SensorEnd() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const SensorEnd& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void sensorEnd_initialise () = 0;

  };
}

#endif // SENSOREND_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef INTERNALBELTCONTROL_HH
#define INTERNALBELTCONTROL_HH




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

  ::iMotorControl motorControl;
  ::iSensor presSensorBlackStack;
  ::iSensor presSensorWhiteStack;
  ::iSensor sensorEnd;


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
  void sensorEnd_detected();

};

#endif // INTERNALBELTCONTROL_HH

/********************************** COMPONENT *********************************/


//version: 2.9.1
