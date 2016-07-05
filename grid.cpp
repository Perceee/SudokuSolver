#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "node.h"

//Standard 9x9 sudoku
const int NUMCOLS = 324;
const int NUMROWS = 729;
const int NUMBOXES = 81;

//Following the rows and columns layout in
//http://www.stolaf.edu/people/hansonr/sudoku/exactcovermatrix.htm
const int MULT_R_ROW = 81;
const int MULT_R_COL = 9;
//COND0: only one of value in each of 81 cells
//COND1: only one of 1-9 in each of 9 rows
//COND2: only one of 1-9 in each of 9 columns
//COND3: only one of 1-9 in each of 9 blocks
const int MULT_C = 9;
const int COND0 = 0; //the starting column for each condition
const int COND1 = 80;
const int COND2 = 161;
const int COND3 = 242;
const int NUM_CONDS = 4;
/*_______ sudoku block layout
 *|1|2|3|
 *|-----|
 *|4|5|6|
 *|-----|
 *|7|8|9|
 *|-----|
 */


Matrix_ExactCover *m_create_header(const std::vector<int>& input) {

	Node_Constraint *curr, *prev;
	Matrix_ExactCover *m = new Matrix_ExactCover();

	//First contraint node
	m->head = new Node_Constraint();
	prev = m->head;
	prev->colVal = 0;
	prev->size = 0;

	//All other contraint nodes in doubly LL
	for (int i = 1; i < NUMCOLS; ++i) {
		curr = new Node_Constraint();
		curr->colVal = i;
		curr->size = 0;
		curr->left = prev;
		prev->right = curr;
		prev = curr;
	}
	//Circular LL
	curr->right = m->head;
	m->head->left = curr;

	return m;
}

Matrix_ExactCover *m_create_cells(Matrix_ExactCover *m, const std::vector<int>& input) {
	assert (input.size() == NUMBOXES);
	int val, s_row, s_col, ec_row, s_block;
	int ec_cond[NUM_CONDS];
	Node *cell, *prev;
	auto it = input.begin();	
	s_row = 0;
	s_col = 0;
	s_block = 0;
	//Construct the matrix
	for (int i = 0; i < NUMCOLS; ++i) {

		if ((val = *it)) { //only non-zero values
			ec_row = val + s_row*MULT_R_ROW + s_col*MULT_R_COL;
			ec_cond[0] = it - input.begin(); //position in sudoku
			ec_cond[1] = COND1 + s_row*MULT_C + val;
			ec_cond[2] = COND2 + s_col*MULT_C + val;
			ec_cond[3] = COND3 + s_block*MULT_C + val;
			

			for (int j = 0; j < NUM_CONDS; ++j){
				cell = new Node();
				cell->colVal = ec_cond[j];
				cell->rowVal = ec_row;
				//put constraint header into vector for O(1) access?
				//append this node to the column's LL
				//join the entire row doubly horizontally

			}


		}
		s_col = (s_col+1)%9; //update sudoku position
		s_row += !s_col;
		s_block = 1 + 3*(s_row/3)+(s_col/3);
		++it;
	}
}