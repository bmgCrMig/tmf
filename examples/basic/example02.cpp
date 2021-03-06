/*
 * 
 *  Tiny Multimedia Framework (tmf)
 *  Copyright (C) 2014 Arash Shafiei
 *
 *  This file is part of tmf.
 *
 *  tmf is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  tmf is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with tmf.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "core/tmf.h"

using namespace tmf;

int main(int argc, char** argv) {
  
  Pipeline* pipe = Factory::createPipeline("Real-Time Three onsumer/One producer");
  
  Filter* producer = Factory::createFilter("string_producer", "producer");
  
  Filter* consumer1 = Factory::createFilter("string_consumer", "consumer1");
  Filter* consumer2 = Factory::createFilter("string_consumer", "consumer2");
  Filter* consumer3 = Factory::createFilter("string_consumer", "consumer3");
  
  pipe->addFilters(producer, consumer1, consumer2, consumer3, nullptr);
  
  pipe->connectFilters(producer, consumer1);
  pipe->connectFilters(producer, consumer2);
  pipe->connectFilters(producer, consumer3);
  
  producer->setProp("limit", 10);
  pipe->setRealTime(true);
  
  pipe->init();
  
  pipe->run();
  
  Factory::destroyPipeline(pipe);
  
  return 0;
}
