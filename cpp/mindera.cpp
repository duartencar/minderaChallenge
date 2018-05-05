#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "GroupFinder.h"

std::vector<std::string> readFile(const std::string fileName) {

	std::vector<std::string> fileLines;

	std::string line;

	std::ifstream gridFile(fileName);

	if(!gridFile) {
	    std::cout << "Cannot open input file.\n";
	    return fileLines;
	  }

	while(std::getline(gridFile, line)) {
		fileLines.push_back(line);
	}

	fileLines.erase(fileLines.begin());

	fileLines.erase(fileLines.end());

	return fileLines;
}

std::vector<std::string> processFileLines(std::vector<std::string> fileLines) {

	std::vector<std::string> cells;

	std::string lineCells;

	for(unsigned y = 0; y < fileLines.size(); y++) {

		lineCells.clear();

		for(char c : fileLines.at(y)) {

			if(c == '1' || c == '0') {
				lineCells.push_back(c);
			}
		}

		cells.push_back(lineCells);
	}

	return cells;
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
	elements.clear();
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
		std::cout << "Insert fileName in parameters!" << std::endl;
	}

	std::string resourceDir = std::string("./resources/");

	clock_t t = clock();

	std::vector<std::string> lines = readFile(resourceDir.append(argv[1]));

	if(lines.size() == 0) {
		return 0;
	}

	std::cout << "File read!\n";

	std::vector<std::string> processedLines = processFileLines(lines);

	freeMemory(lines);

	std::cout << "Lines processed and thrown away!\n";

	GroupFinder *g = new GroupFinder(processedLines.size(), processedLines.at(0).size());

	insertIntoGroupFinder(g, processedLines);

	t = clock() - t;

	std::cout << "File read and processed in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	freeMemory(processedLines);

	std::cout << "Cells inserted and thrown away!\n";

	t = clock();

	std::cout << "Grid " << g->getLength() << " by " << g->getWidth() << std::endl;

	g->findGroups();

	std::cout << "Done!\n";

	t = clock() - t;

	std::cout << "Groups found in " << ((float)t)/CLOCKS_PER_SEC << " seconds.\n";

	std::cout << "Want to print groups?";

	if(readConfirmation()) {
		g->printGroups();
	}

	return 0;
}


