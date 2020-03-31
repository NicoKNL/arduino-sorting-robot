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

  struct
  {
    std::function< void()> start;
    std::function< void()> stop;
    std::function< void()> emergency;
    std::function< void()> forceWait;
    std::function< void()> continue;
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
    if (! in.continue) throw dzn::binding_error(meta, "in.continue");


  }
};

inline void connect (IMaster& provided, IMaster& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // IMASTER_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_INGESTER_HH
#define SKEL_INGESTER_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IIngest.hh"



namespace skel {
  struct Ingester
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IIngest ingest;


    Ingester(const dzn::locator& dzn_locator)
    : dzn_meta{"","Ingester",0,0,{},{},{[this]{ingest.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , ingest({{"ingest",this,&dzn_meta},{"",0,0}})


    {
      ingest.in.startIngest = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->ingest) = false; return ingest_startIngest();}, this->ingest.meta, "startIngest");};


    }
    virtual ~ Ingester() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Ingester& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void ingest_startIngest () = 0;

  };
}

#endif // INGESTER_HH

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

#include "ISensor.hh"



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

#include "ISensor.hh"



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
#ifndef SKEL_WHITEACTUATOR_HH
#define SKEL_WHITEACTUATOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IActuator.hh"



namespace skel {
  struct WhiteActuator
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IActuator whiteActuator;


    WhiteActuator(const dzn::locator& dzn_locator)
    : dzn_meta{"","WhiteActuator",0,0,{},{},{[this]{whiteActuator.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , whiteActuator({{"whiteActuator",this,&dzn_meta},{"",0,0}})


    {
      whiteActuator.in.extend = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->whiteActuator) = false; return whiteActuator_extend();}, this->whiteActuator.meta, "extend");};
      whiteActuator.in.withdraw = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->whiteActuator) = false; return whiteActuator_withdraw();}, this->whiteActuator.meta, "withdraw");};


    }
    virtual ~ WhiteActuator() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const WhiteActuator& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void whiteActuator_extend () = 0;
    virtual void whiteActuator_withdraw () = 0;

  };
}

#endif // WHITEACTUATOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_BLACKACTUATOR_HH
#define SKEL_BLACKACTUATOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "IActuator.hh"



namespace skel {
  struct BlackActuator
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IActuator blackActuator;


    BlackActuator(const dzn::locator& dzn_locator)
    : dzn_meta{"","BlackActuator",0,0,{},{},{[this]{blackActuator.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , blackActuator({{"blackActuator",this,&dzn_meta},{"",0,0}})


    {
      blackActuator.in.extend = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->blackActuator) = false; return blackActuator_extend();}, this->blackActuator.meta, "extend");};
      blackActuator.in.withdraw = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->blackActuator) = false; return blackActuator_withdraw();}, this->blackActuator.meta, "withdraw");};


    }
    virtual ~ BlackActuator() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const BlackActuator& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void blackActuator_extend () = 0;
    virtual void blackActuator_withdraw () = 0;

  };
}

#endif // BLACKACTUATOR_HH

/***********************************  FOREIGN  **********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_SORTINGSYSTEM_HH
#define SKEL_SORTINGSYSTEM_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>

#include "SortingSystem.hh"



namespace skel {
  struct SortingSystem
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::ISortingController controller;


    SortingSystem(const dzn::locator& dzn_locator)
    : dzn_meta{"","SortingSystem",0,0,{},{},{[this]{controller.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , controller({{"controller",this,&dzn_meta},{"",0,0}})


    {
      controller.in.startSorting = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->controller) = false; return controller_startSorting();}, this->controller.meta, "startSorting");};


    }
    virtual ~ SortingSystem() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const SortingSystem& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void controller_startSorting () = 0;

  };
}

#endif // SORTINGSYSTEM_HH

/***********************************  FOREIGN  **********************************/
/********************************** COMPONENT *********************************/
#ifndef MASTER_HH
#define MASTER_HH

#include "IIngest.hh"
#include "ISensor.hh"
#include "SortingSystem.hh"



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
  ::ISortingController sortingSystem;


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
  void master_continue();
  void ingest_finished();
  void factoryFloorSensor_high();
  void factoryFloorSensor_low();
  void sortingSystem_finished();

};

#endif // MASTER_HH

/********************************** COMPONENT *********************************/
/***********************************  SYSTEM  ***********************************/
#ifndef SORTINGROBOTSYSTEM_HH
#define SORTINGROBOTSYSTEM_HH


#include <dzn/locator.hh>

#include "Ingester.hh"
#include "Sensor.hh"
#include "SortingSystem.hh"



struct SortingRobotSystem
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::Master m;
  ::Ingester i;
  ::Sensor sensors;
  ::SortingSystem sortingSystem;

  ::IMaster& master;


  SortingRobotSystem(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // SORTINGROBOTSYSTEM_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.9.1
