#include "GroupFinder.h"

GroupFinder::GroupFinder(unsigned length, unsigned width, bool printAtEnd) {

	this->length = length;

	this->width = width;

	this->printAtEnd = printAtEnd;

	initializeGrids();

	this->stringLength = getCoordinatesMaxLength();

	exploredCells = std::vector<int*>();

	groups = std::vector<std::vector<int*>>();
}

GroupFinder::~GroupFinder() {
}

bool GroupFinder::alreadyPrinted() {
	return !printAtEnd;
}

int GroupFinder::getCoordinatesMaxLength() {

	char temporary[100];

	int lengthNChars = sprintf(temporary, "%d", length);

	int widthNChars = sprintf(temporary, "%d", width);

	return 5 + lengthNChars + widthNChars;
}

void GroupFinder::initializeGrids() {

	visited = new bool*[length];

	grid = new char*[length];

	for(unsigned y = 0; y < length; y++) {

		grid[y] = new char[width];

		visited[y] = new bool[width];

		for(unsigned x = 0; x < width; x++) {
			visited[y][x] = false;
		}
	}
}

void GroupFinder::setGridCell(unsigned x, unsigned y, char value) {
	grid[y][x] = value;
}

unsigned GroupFinder::getLength() {
	return this->length;
}

unsigned GroupFinder::getWidth() {
	return this->width;
}

void GroupFinder::explore(int y, int x) {

	visited[y][x] = true;

	bool hasNeighboor = false;

	if(y+1 < (int)length && grid[y+1][x] == '1') {
		if(!visited[y+1][x]) {
			explore(y+1, x);
		}

		hasNeighboor = true;
	}
	if(y-1 >= 0 && grid[y-1][x] == '1') {
		if(!visited[y-1][x]) {
			explore(y-1, x);
		}

		hasNeighboor = true;
	}
	if(x-1 >= 0 && grid[y][x-1] == '1') {
		if(!visited[y][x-1]) {
			explore(y, x-1);
		}

		hasNeighboor = true;
	}
	if(x+1 < (int)width && grid[y][x+1] == '1') {
		if(!visited[y][x+1]) {
			explore(y, x+1);
		}

		hasNeighboor = true;
	}

	if(hasNeighboor) {
		int * coord = new int[2];
		coord[0] = y;
		coord[1] = x;
		exploredCells.push_back(coord);
	}
}

void GroupFinder::findGroups() {

	for(unsigned y = 0; y < length; y++) {
		for(unsigned x = 0; x < width; x++) {

			if(!visited[y][x] && grid[y][x] == '1') {

				explore(y, x);

				if(exploredCells.size() >= 2) {
					if(printAtEnd) {
						groups.push_back(exploredCells);
					}
					else {
						printGroup(exploredCells);
						freeGroup(exploredCells);
					}

					nGroups++;
				}

				exploredCells.clear();
			}
		}
	}
}

void GroupFinder::printGroup(std::vector<int *> v) {
	std::string toPrint = "[ ";

	char temporary[this->stringLength];

	for(unsigned j = 0; j < v.size() - 1; j++) {
		sprintf(temporary, "[%d,%d], ",v[j][1], v[j][0]);

		toPrint.append(temporary);
	}

	std::cout << toPrint << "[" << v[v.size()-1][1] << "," << v[v.size()-1][0] << "] ]\n";
}

void GroupFinder::printGroups() {

	for(unsigned i = 0; i < groups.size(); i++) {
		printGroup(groups.at(i));
	}
}

void GroupFinder::freeGroup(std::vector<int *> trash) {

	for(unsigned i = 0; i < trash.size(); i++) {
		std::free(trash[i]);
	}
}

void GroupFinder::freeMemory() {

	for(unsigned i = 0; i < length; i++) {
		std::free(grid[i]);

		std::free(visited[i]);
	}

	std::free(grid);

	std::free(visited);


	freeGroup(exploredCells);
	exploredCells.clear();
	exploredCells.shrink_to_fit();

	for(unsigned i = 0; i < groups.size(); i++) {
		freeGroup(groups[i]);
	}
	groups.clear();
	groups.shrink_to_fit();
}

unsigned GroupFinder::numberOfGroups() {
	return this->nGroups;
}
