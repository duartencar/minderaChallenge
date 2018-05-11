#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "GroupFinder.h"
#include "StreamSolver.h"
#include "LineGroup.h"

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

	GroupFinder *g = new GroupFinder(grid.size(), grid.at(0).size());

	insertIntoGroupFinder(g, grid);

	g->findGroups();

	t = clock() - t;

	std::cout << g->numberOfGroups() << " groups found in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	std::cout << "Want to print groups?";

	if(readConfirmation()) {
		g->printGroups();
	}

	g->freeMemory();

	std::free(g);

	return;
}

std::vector<LineGroup *> getLineGroups(std::string dirtyLine, int y) {

	std::vector<LineGroup *> lineGroups;

	int x = 0;

	LineGroup *g = NULL;

	for(char c : dirtyLine) {
		if(c == '1') {
			if(g == NULL) {
				g = new LineGroup(x, y);
			}

			x++;
		}
		if(c == '0') {
			if(g != NULL) {
				g->setWidth(x);

				lineGroups.push_back(g);

				g = NULL;
			}

			x++;
		}
	}

	if(g != NULL) {
		g->setWidth(x);

		lineGroups.push_back(g);
	}

	return lineGroups;
}

std::vector<int> getIndexesFromLine(std::string line) {

	std::string processed;
	std::vector<int> indexHolder;

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
	std::vector<LineGroup *> firstLineGroups;

	std::getline(gridFile, gridLine); //first line invalid
	std::getline(gridFile, gridLine);

	firstLineGroups = getLineGroups(gridLine, 0);

	StreamSolver *s = new StreamSolver(firstLineGroups);

	int y = 1;

	clock_t t = clock();

	while(std::getline(gridFile, gridLine)) {

			s->processLine(getLineGroups(gridLine, y));

			gridLine.clear();

			y++;
	}

	s->finalize();

	t = clock() - t;

	std::cout << s->numberOfGroups() << " groups found in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

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
