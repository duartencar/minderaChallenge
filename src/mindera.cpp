#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "GroupFinder.h"

std::vector<std::string> readFile(const std::string fileName) {

	std::vector<std::string> grid;

	std::string line;

	std::string gridLine;

	std::ifstream gridFile(fileName);

	if(!gridFile) {
	    std::cout << "Cannot open input file.\n";
	    return grid;
	  }

	while(std::getline(gridFile, line)) {

		if(line.length() <= 2) {
			continue;
		}
		else {
			for(char c : line) {

				if(c == '1' || c == '0') {
					gridLine.push_back(c);
				}
			}

			grid.push_back(gridLine);
		}

		gridLine.clear();
	}

	return grid;
}

void insertIntoGroupFinder(GroupFinder *g, std::vector<std::string> cells) {

	for(unsigned y = 0; y < g->getLength(); y++) {

		for(unsigned x = 0; x < g->getWidth(); x++) {
			g->setGridCell(x, y, cells.at(y).at(x));
		}
	}
}

void freeMemory(std::vector<std::string> elements) {

	elements.clear();
	elements.shrink_to_fit();
}

bool readConfirmation() {
    std::string temp;
    do{
        std::cout << "[Y/n]: ";
        getline(std::cin, temp);
    }while(temp != "Y" &&
           temp !="y" &&
           temp != "N" &&
           temp != "n");

    return temp == "Y" || temp == "y";
}

int main(int argc, char* argv[]) {

	if(argc != 2) {
		std::cout << "Insert file name in parameters!" << std::endl;
		return 0;
	}

	std::string resourceDir = std::string("../resources/");

	clock_t t = clock();

	std::vector<std::string> grid = readFile(resourceDir.append(argv[1]));

	if(grid.size() == 0) {
		return 0;
	}

	t = clock() - t;

	std::cout << resourceDir << " read in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	t = clock();

	GroupFinder *g = new GroupFinder(grid.size(), grid.at(0).size());

	insertIntoGroupFinder(g, grid);

	t = clock() - t;

	std::cout << resourceDir << " processed in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	t = clock();

	g->findGroups();

	t = clock() - t;

	std::cout << "Groups found in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	std::cout << "Want to print groups?";

	if(readConfirmation()) {
		g->printGroups();
	}

	g->freeMemory();

	std::free(g);

	return 0;
}
