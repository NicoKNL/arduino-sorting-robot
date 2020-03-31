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
#ifndef IINGEST_HH
#define IINGEST_HH



struct IIngest
{
#ifndef ENUM_IIngest_State
#define ENUM_IIngest_State 1


  struct State
  {
    enum type
    {
      Idle,Monitoring,Ingesting
    };
  };


#endif // ENUM_IIngest_State

  struct
  {
    std::function< void()> startIngest;
  } in;

  struct
  {
    std::function< void()> finished;
  } out;

  dzn::port::meta meta;
  inline IIngest(const dzn::port::meta& m) : meta(m) {}

  void check_bindings() const
  {
    if (! in.startIngest) throw dzn::binding_error(meta, "in.startIngest");

    if (! out.finished) throw dzn::binding_error(meta, "out.finished");

  }
};

inline void connect (IIngest& provided, IIngest& required)
{
  provided.out = required.out;
  required.in = provided.in;
  provided.meta.requires = required.meta.requires;
  required.meta.provides = provided.meta.provides;
}


#ifndef ENUM_TO_STRING_IIngest_State
#define ENUM_TO_STRING_IIngest_State 1
inline std::string to_string(::IIngest::State::type v)
{
  switch(v)
  {
    case ::IIngest::State::Idle: return "State_Idle";
    case ::IIngest::State::Monitoring: return "State_Monitoring";
    case ::IIngest::State::Ingesting: return "State_Ingesting";

  }
  return "";
}
#endif // ENUM_TO_STRING_IIngest_State

#ifndef STRING_TO_ENUM_IIngest_State
#define STRING_TO_ENUM_IIngest_State 1
inline ::IIngest::State::type to_IIngest_State(std::string s)
{
  static std::map<std::string, ::IIngest::State::type> m = {
    {"State_Idle", ::IIngest::State::Idle},
    {"State_Monitoring", ::IIngest::State::Monitoring},
    {"State_Ingesting", ::IIngest::State::Ingesting},
  };
  return m.at(s);
}
#endif // STRING_TO_ENUM_IIngest_State


#endif // IINGEST_HH

/********************************** INTERFACE *********************************/
/***********************************  FOREIGN  **********************************/
#ifndef SKEL_INGESTER_HH
#define SKEL_INGESTER_HH

#include <dzn/locator.hh>
#include <dzn/runtime.hh>




namespace skel {
  struct Ingester
  {
    dzn::meta dzn_meta;
    dzn::runtime& dzn_rt;
    dzn::locator const& dzn_locator;
    ::IIngest ingest;


    Ingester(const dzn::locator& dzn_locator)
    : dzn_meta{"","Ingester",0,0,{},{},{[this]{ingest.check_bindings();}}}
    , dzn_rt(dzn_locator.get<dzn::runtime>())
    , dzn_locator(dzn_locator)

    , ingest({{"ingest",this,&dzn_meta},{"",0,0}})


    {
      ingest.in.startIngest = [&](){return dzn::call_in(this,[=]{ dzn_locator.get<dzn::runtime>().skip_block(&this->ingest) = false; return ingest_startIngest();}, this->ingest.meta, "startIngest");};


    }
    virtual ~ Ingester() {}
    virtual std::ostream& stream_members(std::ostream& os) const { return os; }
    void check_bindings() const;
    void dump_tree(std::ostream& os) const;
    void set_state(std::map<std::string,std::map<std::string,std::string> >){}
    void set_state(std::map<std::string,std::string>_alist){}
    friend std::ostream& operator << (std::ostream& os, const Ingester& m)  {
      return m.stream_members(os);
    }
    private:
    virtual void ingest_startIngest () = 0;

  };
}

#endif // INGESTER_HH

/***********************************  FOREIGN  **********************************/


//version: 2.9.1
