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

#include <Pipeline.h>

Pipeline::Pipeline(const string& name) {
	this->name = name;
	this->start = 0;
	this->status = PIPELINE_STOPPED;
}

Pipeline::~Pipeline() {

}

void Pipeline::connectFilters(Filter * inf, Filter * outf) {
	filters.insert(inf);
	filters.insert(outf);
	if (this->start == 0 && inf->inputPortNum() == 0)
		this->start = inf;

	if (this->start == 0 && outf->inputPortNum() == 0)
		this->start = outf;

	inf->connectFilter(outf);
}

//void Pipeline::setStarter(Filter *starter) {
//	this->start = starter;
//}

void Pipeline::setProp(const string & key, const string & val) {
	props.insert(std::make_pair(key, val));
}

string Pipeline::getProp(const string & key) {
	return props[key];
}

PipelineStatus Pipeline::init() {
	if (start == NULL) {
		cerr << "Pipeline does not have enough filters to run.\n";
		return PIPELINE_STOPPED;
	}

	for (set<Filter*>::iterator it = filters.begin(); it != filters.end(); ++it)
		(*it)->initializeFilter();
	return PIPELINE_RUNNING;

}

PipelineStatus Pipeline::run() {

	FilterStatus status = start->executeFilter();

	if (status == FILTER_FINISHED)
		return PIPELINE_FINISHED;
	if (status == FILTER_ERROR)
		return PIPELINE_STOPPED;

	return PIPELINE_RUNNING;
}
