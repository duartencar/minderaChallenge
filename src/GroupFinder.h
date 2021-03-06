#ifndef GROUPFINDER_H_
#define GROUPFINDER_H_

#include <vector>
#include <iostream>

class GroupFinder {

private:
	unsigned length;
	unsigned width;
	int stringLength;
	int nGroups = 0;
	bool printAtEnd;
	bool **visited;
	char **grid;
	std::vector<int*> exploredCells;
	std::vector<std::vector<int*>> groups;
	void initializeGrids();
	void explore(int y, int x);
	void printGroup(std::vector<int *> v);
	void freeGroup(std::vector<int *> trash);
	int getCoordinatesMaxLength();
public:
	GroupFinder(unsigned length, unsigned width, bool printAtEnd);
	virtual ~GroupFinder();
	void setGridCell(unsigned x, unsigned y, char value);
	bool alreadyPrinted();
	unsigned getLength();
	unsigned getWidth();
	void findGroups();
	void printGroups();
	void freeMemory();
	unsigned numberOfGroups();
};

#endif /* GROUPFINDER_H_ */
