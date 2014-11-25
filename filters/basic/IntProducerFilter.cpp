/*
 * 
 *  Tiny Multimedia Framework
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "filters/basic/IntProducerFilter.h"

FilterRegister<IntProducerFilter> IntProducerFilter::reg("int_producer");

IntProducerFilter::IntProducerFilter(const string& name) : Filter(name), number(0) {
  outputInt = createOutputPort<int>("string output");
}

void IntProducerFilter::init() {
  
  limit = stoi(getProp("limit"));
  
}

void IntProducerFilter::run() {
  
  outputInt->lock();
  
  int * out = outputInt->get(); 
  *out = number;
  
  log("producing "+to_string(number));
  sleep(500);
  
  if(number == limit) {
    outputInt->setStatus(SampleStatus::EOS);
    status = FilterStatus::EOS;
  }
  
  outputInt->unlock();
  
  number++;
}

void IntProducerFilter::runRT() {
  
  string data = to_string(number);
  
  bool canlock = outputInt->lockRT();
  
  if (!canlock) {
    log("droping "+data);
    sleep(500);
    number++;
    return;
  }
  
  int * out = outputInt->get(); 
  *out = number;
  
  log("producing "+to_string(number));
  sleep(500);
  
  if(number == limit) {
    outputInt->setStatus(SampleStatus::EOS);
    status = FilterStatus::EOS;
  }
  
  outputInt->unlock();
  
  number++;
}

IntProducerFilter::~IntProducerFilter() {
  destroyPort(outputInt);
}
