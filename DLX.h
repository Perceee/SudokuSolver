#ifndef DLX_H
#define DLX_H

#include <stack>

#include "grid.h"

const int MAXSIZE = 9;

struct SolutionSet {
	std::stack<Node *> solRows;
	Matrix_ExactCover *m;
	bool solved;
	int solutionNum;

	//Operations

	void insertNewRow(Node *n);
	Node *restorePrevRow();
	void solve();
	bool m_cover_inputs(const std::vector<int>& input);
	void m_restore_inputs();
	void printSolution();
};


#endif