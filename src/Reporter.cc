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
#include "Reporter.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



SateReporter::SateReporter(const dzn::locator& dzn_locator)
: dzn_meta{"","SateReporter",0,0,{& iLedW.meta,& iLedR.meta,& iLedD.meta},{},{[this]{iStateReport.check_bindings();},[this]{iLedW.check_bindings();},[this]{iLedR.check_bindings();},[this]{iLedD.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::SateReporter::State::Off)

, iStateReport({{"iStateReport",this,&dzn_meta},{"",0,0}})

, iLedW({{"",0,0},{"iLedW",this,&dzn_meta}})
, iLedR({{"",0,0},{"iLedR",this,&dzn_meta}})
, iLedD({{"",0,0},{"iLedD",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  iStateReport.in.report = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_report();}, this->iStateReport.meta, "report");};
  iStateReport.in.setState = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->iStateReport) = false; return iStateReport_setState();}, this->iStateReport.meta, "setState");};





}

void SateReporter::iStateReport_report()
{
  if (state == ::SateReporter::State::Off) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOff();
  }
  else if (state == ::SateReporter::State::Waiting) 
  {
    this->iLedW.in.turnOn();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOff();
  }
  else if (state == ::SateReporter::State::Received) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOn();
    this->iLedD.in.turnOff();
  }
  else if (state == ::SateReporter::State::Dispensing) 
  {
    this->iLedW.in.turnOff();
    this->iLedR.in.turnOff();
    this->iLedD.in.turnOn();
  }
  else if ((!(state == ::SateReporter::State::Dispensing) && (!(state == ::SateReporter::State::Received) && (!(state == ::SateReporter::State::Waiting) && !(state == ::SateReporter::State::Off))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SateReporter::iStateReport_setState()
{

  {
    ;
  }

  return;

}


void SateReporter::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SateReporter::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

Reporter::Reporter(const dzn::locator& dzn_locator)
: dzn_meta{"","Reporter",0,0,{},{& r.dzn_meta,& led1.dzn_meta,& led2.dzn_meta,& led3.dzn_meta},{[this]{iSateReport.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, r(dzn_locator)
, led1(dzn_locator)
, led2(dzn_locator)
, led3(dzn_locator)

, iSateReport(r.iStateReport)

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

  dzn::rank(iSateReport.meta.provides.meta, 0);

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