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

#include "filters/libav/VideoWriterFilter.h"

FilterRegister<VideoWriterFilter> VideoWriterFilter::reg("video_writer");

VideoWriterFilter::VideoWriterFilter(string name) :
Filter(name) {
  
  inputPortRawFrame = createInputPort<RawFrame>("RawFrame input");
  
  videoWriter = new VideoWriter();
  
}

void VideoWriterFilter::init() {
  
  Attribute * attr;
  
  int width, height;
  
  string output_video = getProp("output_video");
  
  inputPortRawFrame->lockAttr();
  attr = inputPortRawFrame->getAttr();
  width = stoi(attr->getProp("width"));
  height = stoi(attr->getProp("height"));
  inputPortRawFrame->unlockAttr();
  
  videoWriter->init(output_video, width, height);
}
void VideoWriterFilter::run() {
  
  inputPortRawFrame->lock();
  
  if (inputPortRawFrame->getStatus() == SampleStatus::EOS) {
    status = FilterStatus::EOS; 
    inputPortRawFrame->unlock();
    return;
  }
  
  RawFrame * inFrame = inputPortRawFrame->get();
  
  videoWriter->write(inFrame);
  
  inputPortRawFrame->unlock();
  
}

VideoWriterFilter::~VideoWriterFilter() {
  delete videoWriter;
  destroyPort(inputPortRawFrame);
}

