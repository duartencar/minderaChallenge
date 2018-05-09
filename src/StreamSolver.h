#ifndef STREAMSOLVER_H_
#define STREAMSOLVER_H_

#include <string>
#include <vector>

class StreamSolver {
private:
	std::vector<int> previousLineIndexs;
	std::vector<std::vector<int *>> groups;
	std::vector<std::vector<int *>> previousLineGroups;

	bool checkIfGroupBelongsToOtherGroup(std::vector<int *> alreadyExisting, std::vector<int *> newGroup);
	std::vector<std::vector<int *>> getNeighboorsInLine(std::vector<int> indexs, int y);
	bool neighboorCoords(int * a, int * b);
	std::vector<int *> concatenateGroups(std::vector<int *> toConcatenate, std::vector<int *> concatenated);
	void printGroup(std::vector<int *> g);
public:
	StreamSolver(std::vector<int> firstLineIndexs);
	virtual ~StreamSolver();
	void processLine(std::vector<int> indexs, int y);
	void printCoord(int * coord);
	void printGroups();
};

#endif /* STREAMSOLVER_H_ */
