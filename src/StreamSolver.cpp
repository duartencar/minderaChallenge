#include "StreamSolver.h"
#include <string>
#include <vector>
#include <iostream>

StreamSolver::StreamSolver(std::vector<int> firstLineIndexs) {

	previousLineIndexs = firstLineIndexs;

	previousLineGroups = getNeighboorsInLine(firstLineIndexs, 0);
}

StreamSolver::~StreamSolver() {

}

bool StreamSolver::neighboorCoords(int * a, int * b) {

	if(a[1] == b[1] && (a[0] - b[0] == 1 || a[0] - b[0] == -1)) { //same X value
		return true;
	}
	else if(a[0] == b[0] && (a[1] - b[1] == 1 || a[1] - b[1] == -1)) {
		return true;
	}
	else {
		return false;
	}
}

bool StreamSolver::checkIfGroupBelongsToOtherGroup(std::vector<int *> alreadyExisting, std::vector<int *> newGroup) {

	for(int * group : alreadyExisting) {
		for(int * oneOfnew : newGroup) {
			if(neighboorCoords(group, oneOfnew)) {
				return true;
			}
		}
	}

	return false;
}

std::vector<int *> StreamSolver::concatenateGroups(std::vector<int *> toConcatenate, std::vector<int *> concatenated) {

	std::vector<int *> unification;

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

void StreamSolver::processLine(std::vector<int> indexs, int y) {

	std::vector<std::vector<int *>> lineGroups = getNeighboorsInLine(indexs, y);

	for(unsigned i = 0; i < lineGroups.size(); i++) {
		for(int j = previousLineGroups.size() - 1; j > -1 ; j--) { //newest groups are in the back

			if(checkIfGroupBelongsToOtherGroup(previousLineGroups[j], lineGroups[i])) {

				lineGroups[i] = concatenateGroups(previousLineGroups[j], lineGroups[i]);

				previousLineGroups.erase(previousLineGroups.begin() + j);

				j--;
			}
		}
	}

	for(std::vector<int *> g : previousLineGroups) {
		if(g.size() >= 2) {
			groups.push_back(g);
		}
	}

	previousLineGroups.clear();

	for(std::vector<int *> g : lineGroups) {
		previousLineGroups.push_back(g);
	}
}

std::vector<std::vector<int *>> StreamSolver::getNeighboorsInLine(std::vector<int> indexs, int y) {
	std::vector<std::vector<int *>> groups = std::vector<std::vector<int *>>();
	std::vector<int *> miniGroup = std::vector<int *>();

	unsigned i = 0;

	int * coord = new int[2];
	coord[0] = y;
	coord[1] = indexs.at(0);

	miniGroup.push_back(coord);

	while(i != indexs.size() - 1) {
		coord = new int[2];
		coord[0] = y;
		coord[1] = indexs[i+1];

		if(indexs[i+1] - indexs[i] == 1) {
			miniGroup.push_back(coord);
		}
		else {
			groups.push_back(miniGroup);
			miniGroup.clear();
			miniGroup.push_back(coord);
		}

		i++;
	}

	if(!miniGroup.empty()) {
		groups.push_back(miniGroup);
	}

	return groups;
}

void StreamSolver::printGroups() {

	for(std::vector<int *> g : previousLineGroups) {
		if(g.size() >= 2) {
			groups.push_back(g);
		}
	}

	for(std::vector<int *> g : groups) {
		printGroup(g);
	}
}
