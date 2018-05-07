#include "GroupFinder.h"

GroupFinder::GroupFinder(unsigned length, unsigned width) {

	this->length = length;

	this->width = width;

	initializeGrids();

	exploredCells =  std::vector<int*>();

	groups =  std::vector<std::vector<int*>>();
}

GroupFinder::~GroupFinder() {
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
	if(y-1 > 0 && grid[y-1][x] == '1') {
		if(!visited[y-1][x]) {
			explore(y-1, x);
		}

		hasNeighboor = true;
	}
	if(x-1 > 0 && grid[y][x-1] == '1') {
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

				if(exploredCells.size() > 1) {
					groups.push_back(exploredCells);
				}

				exploredCells.clear();
			}
		}
	}
}

void GroupFinder::printGroups() {

	for(unsigned i = 0; i < groups.size(); i++) {

		std::cout << "[ ";

		unsigned numberOfGroups = groups.at(i).size();

		for(unsigned j = 0; j < numberOfGroups - 1; j++) {

			std::cout << "[" << groups.at(i).at(j)[0] << "," << groups.at(i).at(j)[1] << "], ";
		}

		std::cout << "[" << groups.at(i).at(numberOfGroups-1)[0] << "," << groups.at(i).at(numberOfGroups-1)[1] << "] ]\n";
	}
}

void GroupFinder::freeMemory() {

	for(unsigned i = 0; i < length; i++) {
		std::free(grid[i]);

		std::free(visited[i]);
	}

	std::free(grid);

	std::free(visited);

	exploredCells.clear();

	groups.clear();
}

