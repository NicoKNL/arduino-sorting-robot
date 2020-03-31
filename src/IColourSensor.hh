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
#ifndef ICOLOURSENSOR_HH
#define ICOLOURSENSOR_HH



struct IColourSensor
{

  struct
  {
    std::function< void(int,int)> initialise;
  } in;

  struct
  {
    std::function< void()> detectedWhite;
    std::function< void()> detectedBlack;
    std::function< void()> detectedUnknown;
  } out;

  dzn::port::meta meta;
  inline IColourSensor(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.initialise) throw dzn::binding_error(meta, "in.initialise");

    if (! out.detectedWhite) throw dzn::binding_error(meta, "out.detectedWhite");
    if (! out.detectedBlack) throw dzn::binding_error(meta, "out.detectedBlack");
    if (! out.detectedUnknown) throw dzn::binding_error(meta, "out.detectedUnknown");

  }
};

inline void connect (IColourSensor& provided, IColourSensor& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}





#endif // ICOLOURSENSOR_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_COLOURSENSOR_HH
#define SKEL_COLOURSENSOR_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct ColourSensor
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IColourSensor colourSensor;


    ColourSensor(const dzn::locator& dzn_locator)
    : dzn_meta{"","ColourSensor",0,0,{},{},{[this]{colourSensor.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , colourSensor({{"colourSensor",this,&dzn_meta},{"",0,0}})


    {
      colourSensor.in.initialise = [&](int pinA,int pinB){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->colourSensor) = false; return colourSensor_initialise(pinA,pinB);}, this->colourSensor.meta, "initialise");};


    }
    virtual ~ ColourSensor() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const ColourSensor& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void colourSensor_initialise (int pinA,int pinB) = 0;

  };
}

#endif // COLOURSENSOR_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
