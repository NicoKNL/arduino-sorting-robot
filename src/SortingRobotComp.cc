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
#include "SortingRobotComp.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



Controller::Controller(const dzn::locator& dzn_locator)
: dzn_meta{"","Controller",0,0,{& grabber.meta,& reporter.meta,& belt.meta},{},{[this]{grabber.check_bindings();},[this]{reporter.check_bindings();},[this]{belt.check_bindings();},[this]{com.check_bindings();},[this]{i.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, power(::Controller::Power::Off), state(::Controller::Intake::No)

, com({{"com",this,&dzn_meta},{"",0,0}})
, i({{"i",this,&dzn_meta},{"",0,0}})

, grabber({{"",0,0},{"grabber",this,&dzn_meta}})
, reporter({{"",0,0},{"reporter",this,&dzn_meta}})
, belt({{"",0,0},{"belt",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  com.in.grab = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->com) = false; return com_grab();}, this->com.meta, "grab");};
  i.in.init = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->i) = false; return i_init();}, this->i.meta, "init");};
  i.in.shutDown = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->i) = false; return i_shutDown();}, this->i.meta, "shutDown");};
  grabber.out.finished = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->grabber) = false; return grabber_finished();}, this->grabber.meta, "finished");};
  grabber.out.error = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->grabber) = false; return grabber_error();}, this->grabber.meta, "error");};
  belt.out.atBlack = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->belt) = false; return belt_atBlack();}, this->belt.meta, "atBlack");};
  belt.out.atWhite = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->belt) = false; return belt_atWhite();}, this->belt.meta, "atWhite");};
  belt.out.atEnd = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->belt) = false; return belt_atEnd();}, this->belt.meta, "atEnd");};





}

void Controller::com_grab()
{

  {
    state = ::Controller::Intake::Yes;
    this->grabber.in.grabDisk();
  }

  {
    state = ::Controller::Intake::No;
  }

  return;

}
void Controller::i_init()
{
  if (power == ::Controller::Power::Off) 
  {
    this->belt.in.initialise();
    power = ::Controller::Power::On;
    state = ::Controller::Intake::No;
  }
  else if (power == ::Controller::Power::On) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if ((!(power == ::Controller::Power::On) && !(power == ::Controller::Power::Off))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::i_shutDown()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  {
    ;
  }

  return;

}
void Controller::grabber_finished()
{
  if (state == ::Controller::Intake::No) dzn_locator.get<dzn::illegal_handler>().illegal();
  else if (state == ::Controller::Intake::Yes) 
  {
    state = ::Controller::Intake::No;
  }
  else if ((!(state == ::Controller::Intake::Yes) && !(state == ::Controller::Intake::No))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::grabber_error()
{

  {
    power = ::Controller::Power::Off;
  }

  {
    state = ::Controller::Intake::No;
    power = ::Controller::Power::Off;
  }

  return;

}
void Controller::belt_atBlack()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::belt_atWhite()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Controller::belt_atEnd()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Controller::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Controller::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

//SYSTEM

InternalBelt::InternalBelt(const dzn::locator& dzn_locator)
: dzn_meta{"","InternalBelt",0,0,{},{& beltControl.dzn_meta,& m.dzn_meta,& sW.dzn_meta,& sB.dzn_meta},{[this]{iBeltControl.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, beltControl(dzn_locator)
, m(dzn_locator)
, sW(dzn_locator)
, sB(dzn_locator)

, iBeltControl(beltControl.beltControl)

{


  beltControl.dzn_meta.parent = &dzn_meta;
  beltControl.dzn_meta.name = "beltControl";
  m.dzn_meta.parent = &dzn_meta;
  m.dzn_meta.name = "m";
  sW.dzn_meta.parent = &dzn_meta;
  sW.dzn_meta.name = "sW";
  sB.dzn_meta.parent = &dzn_meta;
  sB.dzn_meta.name = "sB";


  connect(m.motorControl, beltControl.motorControl);
  connect(sB.sensorBlack, beltControl.presSensorBlackStack);
  connect(sW.sensorWhite, beltControl.presSensorWhiteStack);

  dzn::rank(iBeltControl.meta.provides.meta, 0);

}

void InternalBelt::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void InternalBelt::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////
//SYSTEM

GrabberSystem::GrabberSystem(const dzn::locator& dzn_locator)
: dzn_meta{"","GrabberSystem",0,0,{},{& grabber.dzn_meta,& gsensor.dzn_meta,& gmotor.dzn_meta},{[this]{iGrabber.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, grabber(dzn_locator)
, gsensor(dzn_locator)
, gmotor(dzn_locator)

, iGrabber(grabber.grabber)

{


  grabber.dzn_meta.parent = &dzn_meta;
  grabber.dzn_meta.name = "grabber";
  gsensor.dzn_meta.parent = &dzn_meta;
  gsensor.dzn_meta.name = "gsensor";
  gmotor.dzn_meta.parent = &dzn_meta;
  gmotor.dzn_meta.name = "gmotor";


  connect(gsensor.sensor, grabber.presence);
  connect(gmotor.motor, grabber.motor);

  dzn::rank(iGrabber.meta.provides.meta, 0);

}

void GrabberSystem::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void GrabberSystem::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////
//SYSTEM

SortingRobot::SortingRobot(const dzn::locator& dzn_locator)
: dzn_meta{"","SortingRobot",0,0,{},{& belt.dzn_meta,& reporter.dzn_meta,& controller.dzn_meta,& grabber.dzn_meta},{[this]{i.check_bindings();},[this]{com.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, belt(dzn_locator)
, reporter(dzn_locator)
, controller(dzn_locator)
, grabber(dzn_locator)

, i(controller.i), com(controller.com)

{


  belt.dzn_meta.parent = &dzn_meta;
  belt.dzn_meta.name = "belt";
  reporter.dzn_meta.parent = &dzn_meta;
  reporter.dzn_meta.name = "reporter";
  controller.dzn_meta.parent = &dzn_meta;
  controller.dzn_meta.name = "controller";
  grabber.dzn_meta.parent = &dzn_meta;
  grabber.dzn_meta.name = "grabber";


  connect(grabber.iGrabber, controller.grabber);
  connect(belt.iBeltControl, controller.belt);
  connect(reporter.iStateReport, controller.reporter);

  dzn::rank(i.meta.provides.meta, 0);
  dzn::rank(com.meta.provides.meta, 0);

}

void SortingRobot::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void SortingRobot::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}

////////////////////////////////////////////////////////////////////////////////



//version: 2.9.1