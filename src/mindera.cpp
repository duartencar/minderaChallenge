#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "GroupFinder.h"
#include "StreamSolver.h"

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

void printUsage() {
	std::cout << "Usage:\n\t./minderaChallenge.out [fileName]\n\n\tfileName must be in ../resources/" << std::endl;
}

void memoryMode(std::string path) {

	clock_t t = clock();

	std::vector<std::string> grid = readFile(path);

	if(grid.size() == 0) {
		std::cout << "File is empty or corrupt!\n";
		return;
	}

	t = clock() - t;

	std::cout << path << " read in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	t = clock();

	GroupFinder *g = new GroupFinder(grid.size(), grid.at(0).size());

	insertIntoGroupFinder(g, grid);

	t = clock() - t;

	std::cout << path << " processed in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

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

	return;
}

std::string getCleanLine(std::string dirtyLine) {

	std::string toReturn;

	for(char c : dirtyLine) {
		if(c == '1' || c == '0') {
			toReturn.push_back(c);
		}
	}

	return toReturn;
}

std::vector<int> getIndexesFromLine(std::string line) {
	std::vector<int> indexHolder = std::vector<int>();

	for(int x = 0; x < (int)line.length(); x++) {
		if(line.at(x) == '1') {
			indexHolder.push_back(x);
		}
	}

	return indexHolder;
}

void streamMode(std::string path) {

	std::ifstream gridFile(path);

	if(!gridFile) {
		std::cout << "Cannot open input file.\n";
		return;
	}

	std::string gridLine;
	std::string previousLine;
	std::string currentLine;
	std::vector<int> previousLineIndexes;
	std::vector<int> currentLineIndexes;

	std::getline(gridFile, gridLine); //first line invalid
	std::getline(gridFile, gridLine);

	previousLine = getCleanLine(gridLine);

	previousLineIndexes = getIndexesFromLine(previousLine);

	StreamSolver *s = new StreamSolver(previousLineIndexes);

	int y = 1;

	clock_t t = clock();

	while(std::getline(gridFile, gridLine)) {
		if(gridLine.length() <= 2) {
			continue;
		}
		else {
			s->processLine(getIndexesFromLine(getCleanLine(gridLine)), y);

			gridLine.clear();

			y++;
		}
	}

	t = clock() - t;

	std::cout << path << " read, processed and groups calculated in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	std::cout << "Want to print groups?";

	if(readConfirmation()) {
		s->printGroups();
	}
}

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printUsage();
		return 0;
	}

	std::string resourceDir = std::string("../resources/");

	std::cout << "Want to use stream mode?";

	if(readConfirmation()) {
		streamMode(resourceDir.append(argv[1]));
	}
	else {
		memoryMode(resourceDir.append(argv[1]));
	}

	return 0;
}
