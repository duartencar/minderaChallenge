#ifndef GROUPFINDER_H_
#define GROUPFINDER_H_

#include <vector>
#include <iostream>

class GroupFinder {

private:
	unsigned length;
	unsigned width;
	bool **visited;
	char **grid;
	std::vector<int*> exploredCells;
	std::vector<std::vector<int*>> groups;
	void initializeGrids();
	void explore(int y, int x);
public:
	GroupFinder(unsigned length, unsigned width);
	virtual ~GroupFinder();
	void setGridCell(unsigned x, unsigned y, char value);
	unsigned getLength();
	unsigned getWidth();
	void findGroups();
	void printGroups();
	void freeMemory();
};

#endif /* GROUPFINDER_H_ */
