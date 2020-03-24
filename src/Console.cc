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
#include "Console.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



StateReporter::StateReporter(const dzn::locator& dzn_locator)
: dzn_meta{"","StateReporter",0,0,{& iLedW.meta,& iLedR.meta,& iLedD.meta},{},{[this]{iStateReport.check_bindings();},[this]{iLedW.check_bindings();},[this]{iLedR.check_bindings();},[this]{iLedD.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::StateReporter::State::Off)

, iStateReport({{"iStateReport",this,&dzn_meta},{"",0,0}})

, iLedW({{"",0,0},{"iLedW",this,&dzn_meta}})
, iLedR({{"",0,0},{"iLedR",this,&dzn_meta}})
, iLedD({{"",0,0},{"iLedD",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  iStateReport.in.report = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_report();}, this->iStateReport.meta, "report");};
  iStateReport.in.turnOff = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_turnOff();}, this->iStateReport.meta, "turnOff");};
  iStateReport.in.setWaiting = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_setWaiting();}, this->iStateReport.meta, "setWaiting");};
  iStateReport.in.setReceived = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_setReceived();}, this->iStateReport.meta, "setReceived");};
  iStateReport.in.setDispensing = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_setDispensing();}, this->iStateReport.meta, "setDispensing");};





}

void StateReporter::iStateReport_report()
{
  if (state == ::StateReporter::State::Off) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOff();
  }
  else if (state == ::StateReporter::State::Waiting) 
  {
    this->iLedW.in.turnOn();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOff();
  }
  else if (state == ::StateReporter::State::Received) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOn();
    this->iLedD.in.turnOff();
  }
  else if (state == ::StateReporter::State::Dispensing) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOn();
  }
  else if ((!(state == ::StateReporter::State::Dispensing) && (!(state == ::StateReporter::State::Received) && (!(state == ::StateReporter::State::Waiting) && !(state == ::StateReporter::State::Off))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void StateReporter::iStateReport_turnOff()
{

  {
    state = ::StateReporter::State::Off;
  }

  return;

}
void StateReporter::iStateReport_setWaiting()
{

  {
    state = ::StateReporter::State::Waiting;
  }

  return;

}
void StateReporter::iStateReport_setReceived()
{

  {
    state = ::StateReporter::State::Waiting;
  }

  return;

}
void StateReporter::iStateReport_setDispensing()
{

  {
    state = ::StateReporter::State::Waiting;
  }

  return;

}


void StateReporter::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void StateReporter::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

Reporter::Reporter(const dzn::locator& dzn_locator)
: dzn_meta{"","Reporter",0,0,{},{& r.dzn_meta,& led1.dzn_meta,& led2.dzn_meta,& led3.dzn_meta},{[this]{iStateReport.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, r(dzn_locator)
, led1(dzn_locator)
, led2(dzn_locator)
, led3(dzn_locator)

, iStateReport(r.iStateReport)

{


  r.dzn_meta.parent = &dzn_meta;
  r.dzn_meta.name = "r";
  led1.dzn_meta.parent = &dzn_meta;
  led1.dzn_meta.name = "led1";
  led2.dzn_meta.parent = &dzn_meta;
  led2.dzn_meta.name = "led2";
  led3.dzn_meta.parent = &dzn_meta;
  led3.dzn_meta.name = "led3";


  connect(led1.iLed, r.iLedW);
  connect(led2.iLed, r.iLedR);
  connect(led3.iLed, r.iLedD);

  dzn::rank(iStateReport.meta.provides.meta, 0);

}

void Reporter::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Reporter::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.9.1