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
#include "SortingRobot.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



Master::Master(const dzn::locator& dzn_locator)
: dzn_meta{"","Master",0,0,{& sensor.meta,& led.meta},{},{[this]{master.check_bindings();},[this]{sensor.check_bindings();},[this]{led.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::Master::State::Off)

, master({{"master",this,&dzn_meta},{"",0,0}})

, sensor({{"",0,0},{"sensor",this,&dzn_meta}})
, led({{"",0,0},{"led",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  master.in.start = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_start();}, this->master.meta, "start");};
  master.in.stop = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_stop();}, this->master.meta, "stop");};
  master.in.emergency = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_emergency();}, this->master.meta, "emergency");};
  sensor.out.high = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensor) = false; return sensor_high();}, this->sensor.meta, "high");};
  sensor.out.low = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensor) = false; return sensor_low();}, this->sensor.meta, "low");};





}

void Master::master_start()
{
  if (state == ::Master::State::Off) 
  {
    state = ::Master::State::On;
    this->led.in.turnOff();
  }
  else if (state == ::Master::State::On) ;
  else if ((!(state == ::Master::State::On) && !(state == ::Master::State::Off))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_stop()
{
  if (state == ::Master::State::Off) ;
  else if (state == ::Master::State::On) 
  {
    this->led.in.turnOff();
    state = ::Master::State::Off;
  }
  else if ((!(state == ::Master::State::On) && !(state == ::Master::State::Off))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_emergency()
{
  if (state == ::Master::State::Off) ;
  else if (state == ::Master::State::On) 
  {
    this->led.in.turnOff();
    state = ::Master::State::Off;
  }
  else if ((!(state == ::Master::State::On) && !(state == ::Master::State::Off))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::sensor_high()
{
  if (state == ::Master::State::On) this->led.in.turnOn();
  else if (!(state == ::Master::State::On)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::sensor_low()
{
  if (state == ::Master::State::On) this->led.in.turnOff();
  else if (!(state == ::Master::State::On)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Master::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Master::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

SortingRobotSystem::SortingRobotSystem(const dzn::locator& dzn_locator)
: dzn_meta{"","SortingRobotSystem",0,0,{},{& m.dzn_meta,& led.dzn_meta,& sensor.dzn_meta},{[this]{master.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, m(dzn_locator)
, led(dzn_locator)
, sensor(dzn_locator)

, master(m.master)

{


  m.dzn_meta.parent = &dzn_meta;
  m.dzn_meta.name = "m";
  led.dzn_meta.parent = &dzn_meta;
  led.dzn_meta.name = "led";
  sensor.dzn_meta.parent = &dzn_meta;
  sensor.dzn_meta.name = "sensor";


  connect(led.led, m.led);
  connect(sensor.sensor, m.sensor);

  dzn::rank(master.meta.provides.meta, 0);

}

void SortingRobotSystem::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SortingRobotSystem::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.9.1