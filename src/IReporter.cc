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
#include "IReporter.hh"

#include <dzn/locator.hh>
#include <dzn/runtime.hh>


//SYSTEM

Reporter::Reporter(const dzn::locator& dzn_locator)
: dzn_meta{"","Reporter",0,0,{},{& r.dzn_meta,& led1.dzn_meta,& led2.dzn_meta,& led3.dzn_meta},{[this]{iStateReport.check_bindings();}}}
, dzn_rt(dzn_locator.get<dzn::runtime>())
, dzn_locator(dzn_locator)


, r(dzn_locator)
, led1(dzn_locator)
, led2(dzn_locator)
, led3(dzn_locator)

, iStateReport(r.iStateReport)

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

  dzn::rank(iStateReport.meta.provides.meta, 0);

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