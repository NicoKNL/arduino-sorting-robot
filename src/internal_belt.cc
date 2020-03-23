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
#include "internal_belt.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



InternalBeltControl::InternalBeltControl(const dzn::locator& dzn_locator)
: dzn_meta{"","InternalBeltControl",0,0,{& motorControl.meta,& presSensorBlackStack.meta,& presSensorWhiteStack.meta,& sensorEnd.meta},{},{[this]{beltControl.check_bindings();},[this]{motorControl.check_bindings();},[this]{presSensorBlackStack.check_bindings();},[this]{presSensorWhiteStack.check_bindings();},[this]{sensorEnd.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, goal(::InternalBeltControl::Goal::None), state(::InternalBeltControl::State::NotReady)

, beltControl({{"beltControl",this,&dzn_meta},{"",0,0}})

, motorControl({{"",0,0},{"motorControl",this,&dzn_meta}})
, presSensorBlackStack({{"",0,0},{"presSensorBlackStack",this,&dzn_meta}})
, presSensorWhiteStack({{"",0,0},{"presSensorWhiteStack",this,&dzn_meta}})
, sensorEnd({{"",0,0},{"sensorEnd",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  beltControl.in.initialise = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltControl) = false; return beltControl_initialise();}, this->beltControl.meta, "initialise");};
  beltControl.in.toStackBlack = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltControl) = false; return beltControl_toStackBlack();}, this->beltControl.meta, "toStackBlack");};
  beltControl.in.toStackWhite = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltControl) = false; return beltControl_toStackWhite();}, this->beltControl.meta, "toStackWhite");};
  beltControl.in.toEnd = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->beltControl) = false; return beltControl_toEnd();}, this->beltControl.meta, "toEnd");};
  presSensorBlackStack.out.detected = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->presSensorBlackStack) = false; return presSensorBlackStack_detected();}, this->presSensorBlackStack.meta, "detected");};
  presSensorWhiteStack.out.detected = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->presSensorWhiteStack) = false; return presSensorWhiteStack_detected();}, this->presSensorWhiteStack.meta, "detected");};
  sensorEnd.out.detected = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->sensorEnd) = false; return sensorEnd_detected();}, this->sensorEnd.meta, "detected");};





}

void InternalBeltControl::beltControl_initialise()
{
  if (state == ::InternalBeltControl::State::NotReady) 
  {
    this->motorControl.in.initialise();
    state = ::InternalBeltControl::State::Ready;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) ;
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::beltControl_toStackBlack()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::Black;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) 
  {
    this->motorControl.in.goBackward();
    goal = ::InternalBeltControl::Goal::Black;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) 
  {
    this->motorControl.in.goBackward();
    goal = ::InternalBeltControl::Goal::Black;
  }
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::beltControl_toStackWhite()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::White;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::White;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) 
  {
    this->motorControl.in.goBackward();
    goal = ::InternalBeltControl::Goal::White;
  }
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::beltControl_toEnd()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::End;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::End;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) 
  {
    this->motorControl.in.goForward();
    goal = ::InternalBeltControl::Goal::End;
  }
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) ;
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::presSensorBlackStack_detected()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) 
  {
    this->motorControl.in.stop();
    this->beltControl.out.atBlack();
    goal = ::InternalBeltControl::Goal::None;
  }
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::Black)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::presSensorWhiteStack_detected()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) 
  {
    this->motorControl.in.stop();
    this->beltControl.out.atWhite();
    goal = ::InternalBeltControl::Goal::None;
  }
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::White)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void InternalBeltControl::sensorEnd_detected()
{
  if (state == ::InternalBeltControl::State::NotReady) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) ;
  else if ((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) 
  {
    this->motorControl.in.stop();
    this->beltControl.out.atEnd();
    goal = ::InternalBeltControl::Goal::None;
  }
  else if ((!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::End)) && (!((state == ::InternalBeltControl::State::Ready && goal == ::InternalBeltControl::Goal::None)) && !(state == ::InternalBeltControl::State::NotReady)))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void InternalBeltControl::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void InternalBeltControl::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}




//version: 2.9.1