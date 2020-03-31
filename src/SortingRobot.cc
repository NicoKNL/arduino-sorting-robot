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
: dzn_meta{"","Master",0,0,{& ingest.meta,& factoryFloorSensor.meta,& sortingSystem.meta},{},{[this]{master.check_bindings();},[this]{ingest.check_bindings();},[this]{factoryFloorSensor.check_bindings();},[this]{sortingSystem.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::Master::State::Off), waitNext(false)

, master({{"master",this,&dzn_meta},{"",0,0}})

, ingest({{"",0,0},{"ingest",this,&dzn_meta}})
, factoryFloorSensor({{"",0,0},{"factoryFloorSensor",this,&dzn_meta}})
, sortingSystem({{"",0,0},{"sortingSystem",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  master.in.start = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_start();}, this->master.meta, "start");};
  master.in.stop = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_stop();}, this->master.meta, "stop");};
  master.in.emergency = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_emergency();}, this->master.meta, "emergency");};
  master.in.forceWait = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_forceWait();}, this->master.meta, "forceWait");};
  master.in.cancelWait = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_cancelWait();}, this->master.meta, "cancelWait");};
  ingest.out.finished = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->ingest) = false; return ingest_finished();}, this->ingest.meta, "finished");};
  factoryFloorSensor.out.high = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->factoryFloorSensor) = false; return factoryFloorSensor_high();}, this->factoryFloorSensor.meta, "high");};
  sortingSystem.out.finished = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sortingSystem) = false; return sortingSystem_finished();}, this->sortingSystem.meta, "finished");};


  master.in.getState = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->master) = false; return master_getState();}, this->master.meta, "getState");};



}

void Master::master_start()
{
  if (state == ::Master::State::Off) 
  {
    state = ::Master::State::Idle;
  }
  else if (!(state == ::Master::State::Off)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_stop()
{
  if (state == ::Master::State::Idle) 
  {
    state = ::Master::State::Off;
  }
  else if (state == ::Master::State::Waiting) 
  {
    state = ::Master::State::Off;
  }
  else if (state == ::Master::State::Error) 
  {
    state = ::Master::State::Off;
  }
  else if ((!(state == ::Master::State::Error) && (!(state == ::Master::State::Waiting) && !(state == ::Master::State::Idle)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_emergency()
{
  if (state == ::Master::State::Idle) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::Waiting) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::Error) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::IngestingDisk) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::Sorting) 
  {
    state = ::Master::State::Error;
  }
  else if ((!(state == ::Master::State::Sorting) && (!(state == ::Master::State::IngestingDisk) && (!(state == ::Master::State::Error) && (!(state == ::Master::State::Waiting) && !(state == ::Master::State::Idle)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_forceWait()
{
  if (state == ::Master::State::Idle) 
  {
    state = ::Master::State::Waiting;
  }
  else if (state == ::Master::State::Waiting) 
  {
    state = ::Master::State::Waiting;
  }
  else if (state == ::Master::State::Error) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::IngestingDisk) 
  {
    waitNext = true;
  }
  else if (state == ::Master::State::Sorting) 
  {
    waitNext = true;
  }
  else if ((!(state == ::Master::State::Sorting) && (!(state == ::Master::State::IngestingDisk) && (!(state == ::Master::State::Error) && (!(state == ::Master::State::Waiting) && !(state == ::Master::State::Idle)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::master_cancelWait()
{
  if (state == ::Master::State::Waiting) 
  {
    state = ::Master::State::Idle;
  }
  else if (state == ::Master::State::Error) 
  {
    state = ::Master::State::Error;
  }
  else if (state == ::Master::State::IngestingDisk) 
  {
    waitNext = false;
  }
  else if (state == ::Master::State::Sorting) 
  {
    waitNext = false;
  }
  else if ((!(state == ::Master::State::Sorting) && (!(state == ::Master::State::IngestingDisk) && (!(state == ::Master::State::Error) && !(state == ::Master::State::Waiting))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
::IMaster::State::type Master::master_getState()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  return this->reply_IMaster_State;
}
void Master::ingest_finished()
{
  if (state == ::Master::State::IngestingDisk) 
  {
    state = ::Master::State::Sorting;
    this->sortingSystem.in.startSorting();
  }
  else if (!(state == ::Master::State::IngestingDisk)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Master::factoryFloorSensor_high()
{

  {
    ;
  }
  if (state == ::Master::State::Idle) 
  {
    state = ::Master::State::IngestingDisk;
    this->ingest.in.startIngest();
  }
  else 
  return;

}
void Master::sortingSystem_finished()
{
  if (state == ::Master::State::Sorting) 
  {
    {
      if (waitNext) 
      {
        waitNext = false;
        state = ::Master::State::Waiting;
      }
      else 
      {
        state = ::Master::State::Idle;
      }
    }
  }
  else if (!(state == ::Master::State::Sorting)) dzn_locator.get<dzn::illegal_handler>().illegal();
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
: dzn_meta{"","SortingRobotSystem",0,0,{},{& m.dzn_meta,& factorFloorSensor.dzn_meta,& i.dzn_meta,& wheelMotor.dzn_meta,& wheelStopSensor.dzn_meta,& ingestTimer.dzn_meta,& beltSensorWhite.dzn_meta,& beltSensorBlack.dzn_meta,& sortingSystem.dzn_meta,& cs.dzn_meta,& whiteActuator.dzn_meta,& blackActuator.dzn_meta,& beltMotor.dzn_meta,& sortingTimer.dzn_meta},{[this]{master.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, m(dzn_locator)
, factorFloorSensor(dzn_locator)
, i(dzn_locator)
, wheelMotor(dzn_locator)
, wheelStopSensor(dzn_locator)
, ingestTimer(dzn_locator)
, beltSensorWhite(dzn_locator)
, beltSensorBlack(dzn_locator)
, sortingSystem(dzn_locator)
, cs(dzn_locator)
, whiteActuator(dzn_locator)
, blackActuator(dzn_locator)
, beltMotor(dzn_locator)
, sortingTimer(dzn_locator)

, master(m.master)

{


  m.dzn_meta.parent = &dzn_meta;
  m.dzn_meta.name = "m";
  factorFloorSensor.dzn_meta.parent = &dzn_meta;
  factorFloorSensor.dzn_meta.name = "factorFloorSensor";
  i.dzn_meta.parent = &dzn_meta;
  i.dzn_meta.name = "i";
  wheelMotor.dzn_meta.parent = &dzn_meta;
  wheelMotor.dzn_meta.name = "wheelMotor";
  wheelStopSensor.dzn_meta.parent = &dzn_meta;
  wheelStopSensor.dzn_meta.name = "wheelStopSensor";
  ingestTimer.dzn_meta.parent = &dzn_meta;
  ingestTimer.dzn_meta.name = "ingestTimer";
  beltSensorWhite.dzn_meta.parent = &dzn_meta;
  beltSensorWhite.dzn_meta.name = "beltSensorWhite";
  beltSensorBlack.dzn_meta.parent = &dzn_meta;
  beltSensorBlack.dzn_meta.name = "beltSensorBlack";
  sortingSystem.dzn_meta.parent = &dzn_meta;
  sortingSystem.dzn_meta.name = "sortingSystem";
  cs.dzn_meta.parent = &dzn_meta;
  cs.dzn_meta.name = "cs";
  whiteActuator.dzn_meta.parent = &dzn_meta;
  whiteActuator.dzn_meta.name = "whiteActuator";
  blackActuator.dzn_meta.parent = &dzn_meta;
  blackActuator.dzn_meta.name = "blackActuator";
  beltMotor.dzn_meta.parent = &dzn_meta;
  beltMotor.dzn_meta.name = "beltMotor";
  sortingTimer.dzn_meta.parent = &dzn_meta;
  sortingTimer.dzn_meta.name = "sortingTimer";


  connect(factorFloorSensor.sensor, m.factoryFloorSensor);
  connect(i.ingest, m.ingest);
  connect(wheelMotor.motor, i.wheelMotor);
  connect(wheelStopSensor.sensor, i.wheelStopSensor);
  connect(ingestTimer.timer, i.timer);
  connect(sortingSystem.sortingSystem, m.sortingSystem);
  connect(cs.colourSensor, sortingSystem.colourSensor);
  connect(beltSensorWhite.sensor, sortingSystem.beltSensorWhite);
  connect(beltSensorBlack.sensor, sortingSystem.beltSensorBlack);
  connect(whiteActuator.actuator, sortingSystem.whiteActuator);
  connect(blackActuator.actuator, sortingSystem.blackActuator);
  connect(beltMotor.motor, sortingSystem.beltMotor);
  connect(sortingTimer.timer, sortingSystem.timer);

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