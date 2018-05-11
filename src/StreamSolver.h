#ifndef STREAMSOLVER_H_
#define STREAMSOLVER_H_

#include "LineGroup.h"
#include <string>
#include <vector>

class StreamSolver {
private:
	std::vector<std::vector<LineGroup *>> groups;
	std::vector<std::vector<LineGroup *>> previousLineGroups;

	bool checkIfGroupBelongsToOtherGroup(std::vector<int *> alreadyExisting, std::vector<int *> newGroup);
	std::vector<std::vector<int *>> getNeighboorsInLine(std::vector<int> indexs, int y);
	bool neighboorCoords(int * a, int * b);
	std::vector<LineGroup *> concatenateGroups(std::vector<LineGroup *> toConcatenate, std::vector<LineGroup *> concatenated);
	void printGroup(std::vector<int *> g);
public:
	StreamSolver(std::vector<LineGroup *> firstLineGroups);
	virtual ~StreamSolver();
	void processLine(std::vector<LineGroup *> lineGroups);
	void printCoord(int * coord);
	void printGroups();
	void finalize();
	unsigned numberOfGroups();
};

#endif /* STREAMSOLVER_H_ */
