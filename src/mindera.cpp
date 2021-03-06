#include <iostream>
#include <vector>
#include <string>
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

		line.clear();
	}

	gridFile.close();

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

	for(std::string x : elements) {
		x.clear();
		x.shrink_to_fit();
	}
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

void printUsage() {
	std::cout << "Usage:\n\t./minderaChallenge.out [fileName]\n\n\tfileName must be in ../resources/" << std::endl;
}

void findGroups(std::string path) {

	std::cout << "Want to print groups at end? (uses more memory, but faster)";

	bool print = readConfirmation();

	clock_t t = clock();

	std::vector<std::string> grid = readFile(path);

	if(grid.size() == 0) {
		std::cout << "File is empty or corrupt!\n";
		return;
	}

	GroupFinder *g = new GroupFinder(grid.size(), grid.at(0).size(), print);

	insertIntoGroupFinder(g, grid);

	freeMemory(grid);

	g->findGroups();

	t = clock() - t;

	std::cout << g->numberOfGroups() << " groups found in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	if(!g->alreadyPrinted()) {
		std::cout << "Want to print groups?";

		if(readConfirmation()) {
			g->printGroups();
		}
	}

	std::cout << "\nCleaning memory!\n";

	g->freeMemory();

	std::free(g);

	return;
}

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printUsage();
		return 0;
	}

	std::string resourceDir = std::string("../resources/");

	findGroups(resourceDir.append(argv[1]));

	return 0;
}
