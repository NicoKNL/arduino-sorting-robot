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
#include "IIngest.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



Ingester::Ingester(const dzn::locator& dzn_locator)
: dzn_meta{"","Ingester",0,0,{& wheelMotor.meta,& wheelStopSensor.meta,& timer.meta},{},{[this]{ingest.check_bindings();},[this]{wheelMotor.check_bindings();},[this]{wheelStopSensor.check_bindings();},[this]{timer.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::Ingester::State::Idle), delay(5000)

, ingest({{"ingest",this,&dzn_meta},{"",0,0}})

, wheelMotor({{"",0,0},{"wheelMotor",this,&dzn_meta}})
, wheelStopSensor({{"",0,0},{"wheelStopSensor",this,&dzn_meta}})
, timer({{"",0,0},{"timer",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  ingest.in.startIngest = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->ingest) = false; return ingest_startIngest();}, this->ingest.meta, "startIngest");};
  wheelStopSensor.out.high = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->wheelStopSensor) = false; return wheelStopSensor_high();}, this->wheelStopSensor.meta, "high");};
  timer.out.timeout = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->timer) = false; return timer_timeout();}, this->timer.meta, "timeout");};





}

void Ingester::ingest_startIngest()
{
  if (state == ::Ingester::State::Idle) 
  {
    state = ::Ingester::State::Monitoring;
    this->timer.in.start(delay);
  }
  else if (!(state == ::Ingester::State::Idle)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Ingester::wheelStopSensor_high()
{

  {
    ;
  }
  if (state == ::Ingester::State::Ingesting) 
  {
    state = ::Ingester::State::Idle;
    this->wheelMotor.in.turnOff();
    this->ingest.out.finished();
  }
  else 
  return;

}
void Ingester::timer_timeout()
{
  if (state == ::Ingester::State::Monitoring) 
  {
    state = ::Ingester::State::Ingesting;
    this->wheelMotor.in.turnOn();
  }
  else if (!(state == ::Ingester::State::Monitoring)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Ingester::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Ingester::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}




//version: 2.9.1