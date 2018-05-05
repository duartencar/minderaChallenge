/*
 * GroupFinder.h
 *
 *  Created on: 04/05/2018
 *      Author: Luis Henrique
 */

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
	int currentCoordinates[2];
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
};

#endif /* GROUPFINDER_H_ */
