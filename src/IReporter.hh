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
#ifndef IREPORTER_HH
#define IREPORTER_HH



struct IReporter
{

  struct
  {
    std::function< void()> report;
    std::function< void()> turnOff;
    std::function< void()> setWaiting;
    std::function< void()> setReceived;
    std::function< void()> setDispensing;
  } in;

  struct
  {
  } out;

  dzn::port::meta meta;
  inline IReporter(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.report) throw dzn::binding_error(meta, "in.report");
    if (! in.turnOff) throw dzn::binding_error(meta, "in.turnOff");
    if (! in.setWaiting) throw dzn::binding_error(meta, "in.setWaiting");
    if (! in.setReceived) throw dzn::binding_error(meta, "in.setReceived");
    if (! in.setDispensing) throw dzn::binding_error(meta, "in.setDispensing");


  }
};

inline void connect (IReporter& provided, IReporter& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // IREPORTER_HH

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
/***********************************  SYSTEM  ***********************************/
#ifndef REPORTER_HH
#define REPORTER_HH


#include <dzn/locator.hh>

#include "Console.hh"
#include "Led.hh"
#include "Led.hh"
#include "Led.hh"



struct Reporter
{
  dzn::meta dzn_meta;
  dzn::runtime& dzn_rt;
  dzn::locator const& dzn_locator;


  ::StateReporter r;
  ::Led led1;
  ::Led led2;
  ::Led led3;

  ::IReporter& iStateReport;


  Reporter(const dzn::locator&);
  void check_bindings() const;
  void dump_tree(std::ostream& os=std::clog) const;
};

#endif // REPORTER_HH

/***********************************  SYSTEM  ***********************************/


//version: 2.9.1
