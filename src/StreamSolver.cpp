#include "StreamSolver.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "LineGroup.h"


StreamSolver::StreamSolver(std::vector<LineGroup *> firstLineGroups) {

	std::vector<LineGroup *> startingGroups;

	for(LineGroup * g : firstLineGroups) {
		startingGroups = std::vector<LineGroup *>();
		startingGroups.push_back(g);
		previousLineGroups.push_back(startingGroups);
	}
}

StreamSolver::~StreamSolver() {

}

bool StreamSolver::neighboorCoords(int * a, int * b) {

	return false;
}

bool StreamSolver::checkIfGroupBelongsToOtherGroup(std::vector<int *> alreadyExisting, std::vector<int *> newGroup) {

	return false;
}

std::vector<LineGroup *> StreamSolver::concatenateGroups(std::vector<LineGroup *> toConcatenate, std::vector<LineGroup *> concatenated) {

	std::vector<LineGroup *> unification;

	unification.reserve(toConcatenate.size() + concatenated.size());

	unification.insert(unification.end(), toConcatenate.begin(), toConcatenate.end());

	unification.insert(unification.end(), concatenated.begin(), concatenated.end());

	return unification;
}

void StreamSolver::printCoord(int * coord) {
	std::cout << "[" << coord[0] << "," << coord[1] << "]";
}

void StreamSolver::printGroup(std::vector<int *> g) {

	std::cout << "[ ";

	for(unsigned i = 0; i < g.size(); i++) {
		printCoord(g[i]);

		if(i != g.size() - 1) {
			std::cout << ", ";
		}
	}

	std::cout << " ] \n";
}

void StreamSolver::processLine(std::vector<LineGroup *> lineGroups) {

	std::vector<std::vector<LineGroup *>> toConcatenate;

	for(LineGroup * group : lineGroups) {

		int k = 0;
		for(std::vector<LineGroup *> previousGroups : previousLineGroups) {
			if(group->getLineNumber() - previousGroups[previousGroups.size()- 1]->getLineNumber() == 2) {
				groups.push_back(previousGroups);
				std::cout << "apaga k= "<< k << std::endl;
				//previousLineGroups.erase(previousLineGroups.begin() + k);
				std::cout << "apaga size= " << previousLineGroups.size() << std::endl;
				k--;
			}
			else {
				for(int i = previousGroups.size() - 1; i > -1; i--) {
					if(previousGroups[i]->nextTo(group)) {
						toConcatenate.push_back(previousGroups);
					}
				}
			}

			std::cout << "Incrementa \n";
			k++;
		}

		if(toConcatenate.size() > 0) {
			std::vector<LineGroup *> newGroup = std::vector<LineGroup *>();

			while(!toConcatenate.empty()) {
				std::cout << "toConcatenate size     = " << toConcatenate.size() << std::endl;
				std::cout << "previousLineGroups size= " << previousLineGroups.size() << std::endl;
				newGroup = concatenateGroups(newGroup, toConcatenate[0]);
				toConcatenate.erase(toConcatenate.begin());
				previousLineGroups.erase(find(previousLineGroups.begin(), previousLineGroups.end(), toConcatenate[0]));
			}

			newGroup.push_back(group);

			previousLineGroups.push_back(newGroup);
		}
		else {
			std::vector<LineGroup *> newGroup = std::vector<LineGroup *>();
			newGroup.push_back(group);
			previousLineGroups.push_back(newGroup);
		}

	}
}

void StreamSolver::finalize() {

	while(!previousLineGroups.empty()) {
		if(previousLineGroups[0].size() != 1 || !previousLineGroups[0][0]->isSingle()) {
			groups.push_back(previousLineGroups[0]);
		}

		previousLineGroups.erase(previousLineGroups.begin());
	}

}

void StreamSolver::printGroups() {

	for(std::vector<LineGroup *> previousGroups : previousLineGroups) {

	}
}

unsigned StreamSolver::numberOfGroups() {
	return groups.size();
}
