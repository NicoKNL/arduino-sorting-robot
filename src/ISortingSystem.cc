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
#include "ISortingSystem.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



SortingSystem::SortingSystem(const dzn::locator& dzn_locator)
: dzn_meta{"","SortingSystem",0,0,{& colourSensor.meta,& beltSensorWhite.meta,& beltSensorBlack.meta,& whiteActuator.meta,& blackActuator.meta,& beltMotor.meta,& timer.meta},{},{[this]{sortingSystem.check_bindings();},[this]{colourSensor.check_bindings();},[this]{beltSensorWhite.check_bindings();},[this]{beltSensorBlack.check_bindings();},[this]{whiteActuator.check_bindings();},[this]{blackActuator.check_bindings();},[this]{beltMotor.check_bindings();},[this]{timer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::ISortingSystem::State::Idle), delay(5000)

, sortingSystem({{"sortingSystem",this,&dzn_meta},{"",0,0}})

, colourSensor({{"",0,0},{"colourSensor",this,&dzn_meta}})
, beltSensorWhite({{"",0,0},{"beltSensorWhite",this,&dzn_meta}})
, beltSensorBlack({{"",0,0},{"beltSensorBlack",this,&dzn_meta}})
, whiteActuator({{"",0,0},{"whiteActuator",this,&dzn_meta}})
, blackActuator({{"",0,0},{"blackActuator",this,&dzn_meta}})
, beltMotor({{"",0,0},{"beltMotor",this,&dzn_meta}})
, timer({{"",0,0},{"timer",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  sortingSystem.in.reset = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sortingSystem) = false; return sortingSystem_reset();}, this->sortingSystem.meta, "reset");};
  sortingSystem.in.startSorting = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sortingSystem) = false; return sortingSystem_startSorting();}, this->sortingSystem.meta, "startSorting");};
  sortingSystem.in.emergency = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sortingSystem) = false; return sortingSystem_emergency();}, this->sortingSystem.meta, "emergency");};
  colourSensor.out.detectedWhite = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->colourSensor) = false; return colourSensor_detectedWhite();}, this->colourSensor.meta, "detectedWhite");};
  colourSensor.out.detectedBlack = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->colourSensor) = false; return colourSensor_detectedBlack();}, this->colourSensor.meta, "detectedBlack");};
  colourSensor.out.detectedUnknown = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->colourSensor) = false; return colourSensor_detectedUnknown();}, this->colourSensor.meta, "detectedUnknown");};
  beltSensorWhite.out.high = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltSensorWhite) = false; return beltSensorWhite_high();}, this->beltSensorWhite.meta, "high");};
  beltSensorBlack.out.high = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltSensorBlack) = false; return beltSensorBlack_high();}, this->beltSensorBlack.meta, "high");};
  timer.out.timeout = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->timer) = false; return timer_timeout();}, this->timer.meta, "timeout");};





}

void SortingSystem::sortingSystem_reset()
{

  {
    state = ::ISortingSystem::State::Idle;
    this->beltMotor.in.turnOff();
    this->whiteActuator.in.withdraw();
    this->blackActuator.in.withdraw();
  }

  return;

}
void SortingSystem::sortingSystem_startSorting()
{
  if (state == ::ISortingSystem::State::Idle) 
  {
    state = ::ISortingSystem::State::AwaitColourScan;
    this->beltMotor.in.turnOn();
  }
  else if (!(state == ::ISortingSystem::State::Idle)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void SortingSystem::sortingSystem_emergency()
{

  {
    state = ::ISortingSystem::State::Idle;
    this->beltMotor.in.turnOff();
  }

  return;

}
void SortingSystem::colourSensor_detectedWhite()
{

  {
    ;
  }
  if (state == ::ISortingSystem::State::AwaitColourScan) 
  {
    this->whiteActuator.in.extend();
    state = ::ISortingSystem::State::SortWhite;
  }
  else 
  return;

}
void SortingSystem::colourSensor_detectedBlack()
{

  {
    ;
  }
  if (state == ::ISortingSystem::State::AwaitColourScan) 
  {
    this->blackActuator.in.extend();
    state = ::ISortingSystem::State::SortBlack;
  }
  else 
  return;

}
void SortingSystem::colourSensor_detectedUnknown()
{

  {
    ;
  }
  if (state == ::ISortingSystem::State::AwaitColourScan) 
  {
    state = ::ISortingSystem::State::SortOther;
  }
  else 
  return;

}
void SortingSystem::beltSensorWhite_high()
{

  {
    ;
  }
  if (state == ::ISortingSystem::State::SortWhite) 
  {
    this->timer.in.start(delay);
  }
  else 
  return;

}
void SortingSystem::beltSensorBlack_high()
{

  {
    ;
  }
  if (state == ::ISortingSystem::State::SortBlack) 
  {
    this->timer.in.start(delay);
  }
  else if (state == ::ISortingSystem::State::SortOther) 
  {
    this->timer.in.start(delay);
  }
  else 
  return;

}
void SortingSystem::timer_timeout()
{
  if (state == ::ISortingSystem::State::SortWhite) 
  {
    state = ::ISortingSystem::State::Idle;
    this->whiteActuator.in.withdraw();
    this->beltMotor.in.turnOff();
    this->sortingSystem.out.finished();
  }
  else if (state == ::ISortingSystem::State::SortBlack) 
  {
    state = ::ISortingSystem::State::Idle;
    this->blackActuator.in.withdraw();
    this->beltMotor.in.turnOff();
    this->sortingSystem.out.finished();
  }
  else if (state == ::ISortingSystem::State::SortOther) 
  {
    state = ::ISortingSystem::State::Idle;
    this->beltMotor.in.turnOff();
    this->sortingSystem.out.finished();
  }
  else if ((!(state == ::ISortingSystem::State::SortOther) && (!(state == ::ISortingSystem::State::SortBlack) && !(state == ::ISortingSystem::State::SortWhite)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void SortingSystem::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SortingSystem::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}




//version: 2.9.1