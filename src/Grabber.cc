#include "Grabber.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>



Grabber::Grabber(const dzn::locator& dzn_locator)
: dzn_meta{"","Grabber",0,0,{& presence.meta,& motor.meta},{},{[this]{presence.check_bindings();},[this]{motor.check_bindings();},[this]{grabber.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)
, state(::Grabber::State::initial)

, grabber({{"grabber",this,&dzn_meta},{"",0,0}})

, presence({{"",0,0},{"presence",this,&dzn_meta}})
, motor({{"",0,0},{"motor",this,&dzn_meta}})


{
  dzn_rt.performs_flush(this) = true;

  grabber.in.grabDisk = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->grabber) = false; return grabber_grabDisk();}, this->grabber.meta, "grabDisk");};
  presence.out.detected = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->presence) = false; return presence_detected();}, this->presence.meta, "detected");};
  motor.out.finished = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_finished();}, this->motor.meta, "finished");};
  motor.out.error = [&](){return dzn::call_out(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->motor) = false; return motor_error();}, this->motor.meta, "error");};





}

void Grabber::grabber_grabDisk()
{
  if (state == ::Grabber::State::initial) state = ::Grabber::State::grabbing;
  else if (state == ::Grabber::State::grabbing) ;
  else if ((!(state == ::Grabber::State::grabbing) && !(state == ::Grabber::State::initial))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Grabber::presence_detected()
{
  if (state == ::Grabber::State::grabbing) this->motor.in.next();
  else if (!(state == ::Grabber::State::grabbing)) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Grabber::motor_finished()
{
  if (state == ::Grabber::State::grabbing) 
  {
    this->grabber.out.finished();
    state = ::Grabber::State::initial;
  }
  else if (state == ::Grabber::State::resetting) state = ::Grabber::State::initial;
  else if ((!(state == ::Grabber::State::resetting) && !(state == ::Grabber::State::grabbing))) dzn_locator.get<dzn::illegal_handler>().illegal();
  else dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}
void Grabber::motor_error()
{
  dzn_locator.get<dzn::illegal_handler>().illegal();

  return;

}


void Grabber::check_bindings() const
{
  dzn::check_bindings(&dzn_meta);
}
void Grabber::dump_tree(std::ostream& os) const
{
  dzn::dump_tree(os, &dzn_meta);
}




//version: 2.9.1